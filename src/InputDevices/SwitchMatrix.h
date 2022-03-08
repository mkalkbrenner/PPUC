/*
  SwitchMatrix.h.
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

#ifndef SwitchMatrix_h
#define SwitchMatrix_h

#include <Arduino.h>

#include "Matrix.h"
#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

#define CS_ODD  3
#define CS_EVEN 2
#define CS_X    4

class SwitchMatrix : public Matrix {
public:
    SwitchMatrix(EventDispatcher* eD, byte pf) : Matrix(eD, pf) {
        switchMatrixInstance = this;

        eventSource = EVENT_SOURCE_SWITCH;

        if (platform == PLATFORM_WPC) {
            // Read rows some micro seconds after column strobe signal.
            rowReadDelay = 4;

            // On WPC the switches are read every 2ms. Ensure that we have a complete read before sending next events.
            updateDelay = 3;
        }
        else if (platform == PLATFORM_DATA_EAST) {
            // @todo
        }
        else if (platform == PLATFORM_SYS11) {
            // @todo
        }

        maxChangesPerRead = 3;

        pinMode(CS_ODD, INPUT);
        pinMode(CS_EVEN, INPUT);
        pinMode(CS_X, INPUT);

        pinMode(22, INPUT);
        pinMode(23, INPUT);
        pinMode(24, INPUT);
        pinMode(25, INPUT);
        pinMode(26, INPUT);
        pinMode(27, INPUT);
        pinMode(28, INPUT);
        pinMode(29, INPUT);
    }

    void start();

    void stop();

    void readRow(int pin);
    static void _readRowForOddColumn();
    static void _readRowForEvenColumn();

protected:
    byte columnCounter = 255;
    int rowReadDelay = 0;

private:
    static SwitchMatrix* switchMatrixInstance;
};

#endif
