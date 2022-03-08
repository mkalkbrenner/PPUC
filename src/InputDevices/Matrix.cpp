#include "Matrix.h"

Matrix::Matrix(EventDispatcher* eD, byte pf) {
    eventDispatcher = eD;
    platform = pf;

    setLastColToRead(8);

    for (int i = 0; i < lastColToRead; i++) {
        rows[i] = B00000000;
        previousRows[i] = B00000000;
    }
}

void Matrix::setLastColToRead(byte last) {
    lastColToRead = last;
}

void Matrix::registerFieldAsEvent(byte row, byte column, byte number) {
    if (registeredFieldsCounter < (MAX_FIELDS_REGISTERED - 1)) {
        registeredFieldRowCol[++registeredFieldsCounter] = word(row - 1, column - 1);
        registeredFieldNum[registeredFieldsCounter] = number;
    }
}

void Matrix::registerAllFieldsAsEvent() {
    registeredFieldsCounter = -1;

    if (platform == PLATFORM_WPC) {
        for (byte col = 1; col <= lastColToRead; col++) {
            for (byte row = 1; row <= 8; row++) {
                registerFieldAsEvent(row, col, col * 10 + row);
            }
        }
    }
    else if (platform == PLATFORM_DATA_EAST || platform == PLATFORM_SYS11) {
        byte number = 0;
        for (byte col = 1; col <= lastColToRead; col++) {
            for (byte row = 1; row <= 8; row++) {
                registerFieldAsEvent(row, col, ++number);
            }
        }
    }
}

void Matrix::update() {
    if (updateDelay > 0) {
        uint32_t ms = millis();

        if (nextUpdate > ms) {
            return;
        }

        nextUpdate = ms + updateDelay;
    }

    byte fieldNum[maxChangesPerRead] = {0};
    byte value[maxChangesPerRead] = {0};
    byte counter = 0;

    for (int col = 0; col < lastColToRead; col++) {
        for (int row = 0; row < 8; row++) {
            word row_col = word(row, col);
            for (byte i = 0; i <= registeredFieldsCounter; i++) {
                if (row_col == registeredFieldRowCol[i]) {
                    byte bit = 1 << row;
                    if ((rows[col] & bit) != (previousRows[col] & bit)) {
                        if (counter < maxChangesPerRead) {
                            fieldNum[counter] = registeredFieldNum[i];
                            value[counter++] = (rows[col] & bit) ? 1 : 0;
                        }
                        else {
                            // Too many changes, assume erroneous read.
                            return;
                        }
                    }
                }
            }
        }
        previousRows[col] = rows[col];
    }

    if (counter <= maxChangesPerRead) {
        for (int i = 0; i < counter; i++) {
            eventDispatcher->dispatch(
                new Event(eventSource, word(0, fieldNum[i]), value[i])
            );
        }
    }
}

void Matrix::print() {
    Serial.print("Matrix "); Serial.println(eventSource);
    Serial.println("  8 7 6 5 4 3 2 1");
    for (int i = 0; i < lastColToRead; i++) {
        Serial.print(i + 1);
        for (byte mask = 0x80; mask; mask >>= 1) {
            Serial.print(mask & rows[i] ? " *" : " -");
        }
        Serial.println();
    }
}
