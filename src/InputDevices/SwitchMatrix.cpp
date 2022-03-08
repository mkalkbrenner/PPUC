#include "SwitchMatrix.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
SwitchMatrix* SwitchMatrix::switchMatrixInstance = NULL;

void SwitchMatrix::start() {
    attachInterrupt(digitalPinToInterrupt(CS_ODD), SwitchMatrix::_readRowForOddColumn, RISING);
}

void SwitchMatrix::stop() {
    detachInterrupt(digitalPinToInterrupt(CS_ODD));
    detachInterrupt(digitalPinToInterrupt(CS_EVEN));
}

void SwitchMatrix::_readRowForOddColumn() {
    //Serial.println("CS_ODD");
    switchMatrixInstance->readRow(CS_ODD);
}

void SwitchMatrix::_readRowForEvenColumn() {
    //Serial.println("CS_EVEN");
    switchMatrixInstance->readRow(CS_EVEN);
}

void SwitchMatrix::readRow(int pin) {
    // Immediately turn off further interrupts.
    detachInterrupt(digitalPinToInterrupt(pin));

    delayMicroseconds(rowReadDelay);

    if (pin == CS_ODD && digitalRead(CS_X) == LOW) {
        //Serial.println("CS_X");
        columnCounter = 0;
    }

    if (columnCounter >= 0 && columnCounter < lastColToRead) {
        //Serial.println(switchMatrixInstance->columnCounter, DEC);

#if defined (__AVR__) || (__avr__)
        // Read row return at PIN 22 - 29 three times and use the majority of bits.
        byte a = PINA;
        delayMicroseconds(4);
        byte b = PINA;
        delayMicroseconds(4);
        byte c = PINA;
#else
        // The Switch Matrix adapter currently requires an Arduino.
        byte a = 0;
        byte b = 0;
        byte c = 0;
#endif

        if (columnCounter > 0 ||
            // The first column is only valid, if CS_X is still LOW. Otherwise it's noise.
            (columnCounter == 0 && digitalRead(CS_X) == LOW)
        ) {
            //Serial.println("READ");
            rows[columnCounter++] |= ((a & b) | (b & c) | (c & a)) ^ B11111111;
        }
        else {
            columnCounter = 255;
        }
    }

    if (columnCounter >= lastColToRead) {
        columnCounter = 255;
    }

    if (pin == CS_ODD && columnCounter >= 0 && columnCounter < lastColToRead) {
        attachInterrupt(digitalPinToInterrupt(CS_EVEN), SwitchMatrix::_readRowForEvenColumn, RISING);
    }
    else {
        attachInterrupt(digitalPinToInterrupt(CS_ODD), SwitchMatrix::_readRowForOddColumn, RISING);
    }
}
