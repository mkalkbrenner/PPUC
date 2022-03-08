#include <TimerOne.h>

#include "LightMatrix.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
LightMatrix* LightMatrix::lightMatrixInstance = NULL;

void LightMatrix::start() {
    Timer1.attachInterrupt(LightMatrix::_readRow);
}

void LightMatrix::stop() {
    Timer1.detachInterrupt();
}

void LightMatrix::_readRow() {
    // 74HC165 16bit sampling
    uint16_t inData = lightMatrixInstance->sampleInput();
    byte inColMask = (inData >> 8); // LSB is col 0, MSB is col 7
    byte inRowMask = ~(byte)inData; // high means OFF, LSB is row 0, MSB is row 7

    // evaluate the column reading
    // only one bit should be set as only one column can be active at a time
    uint32_t inCol = NUM_COLS;
    switch (inColMask) {
        case 0x01: inCol = 0; break;
        case 0x02: inCol = 1; break;
        case 0x04: inCol = 2; break;
        case 0x08: inCol = 3; break;
        case 0x10: inCol = 4; break;
        case 0x20: inCol = 5; break;
        case 0x40: inCol = 6; break;
        case 0x80: inCol = 7; break;
        default:
            // This may happen if the sample is taken in between column transition.
            // Depending on the pinball ROM version the duration of this transition varies.
            // On a Whitewater with Home ROM LH6 (contains anti ghosting updates) this
            // gap was measured to be around 30us long.
            // Machines with anti-ghosting firmware will show a gap with no column enabled
            // for a while during the transition while older firmwares might have two
            // columns enabled at the same time due to slow transistor deactivation. Both
            // cases are caught here.
            // See also https://emmytech.com/arcade/led_ghost_busting/index.html for details.
            return;
    }

    // Update only with a valid input. If the input is invalid the current
    // matrix state is left unchanged.
    // The matrix is updated only once per original column cycle. The code
    // waits for a number of consecutive consistent information before updating the matrix.
    if (lightMatrixInstance->updateValid(inCol, inRowMask)) {
        //Serial.print(inCol + 1); Serial.print(": "); Serial.println(inRowMask, BIN);
        // update the current column
        lightMatrixInstance->rows[inCol] = inRowMask;
    }
}

uint16_t LightMatrix::sampleInput() {
    // drive CLK and LOAD low
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    // wait some time
    uint16_t data = 0;
    data += 17;
    data -= 3;

    // drive LOAD high to save pin states
    digitalWrite(7, HIGH);

    // clock in all data
    for (byte i = 0; i < 16; i++) {
        data <<= 1;                        // make way for the new bit
        digitalWrite(6, LOW);              // CLK low
        data |= digitalRead(5);            // read data bit
        digitalWrite(6, HIGH);             // CLK high
    }

    return data;
}

bool LightMatrix::updateValid(byte inCol, byte inRowMask) {
    // check if the current column has not been handled already
    if (inRowMask != lastRowMask[inCol]) {
        // reset the counter when the data changes
        consistentSamples[inCol] = 1;
        lastRowMask[inCol] = inRowMask;
    }
    // count number of consecutive samples with consistent data
    else if (consistentSamples[inCol] < 255) {
        consistentSamples[inCol]++;
    }

    if (consistentSamples[inCol] >= SINGLE_UPDATE_CONS) {
        return true;
    }

    return false;
}
