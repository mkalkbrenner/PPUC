/*
  Matrix.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

// WPC matrix numbering:
//
//    | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8
// ---+----+----+----+----+----+----+----+----
// R1 | 11 | 21 | 31 | 41 | 51 | 61 | 71 | 81
// ---+----+----+----+----+----+----+----+----
// R2 | 12 | 22 | 32 | 42 | 52 | 62 | 72 | 82
// ---+----+----+----+----+----+----+----+----
// R3 | 13 | 23 | 33 | 43 | 53 | 63 | 73 | 83
// ---+----+----+----+----+----+----+----+----
// R4 | 14 | 24 | 34 | 44 | 54 | 64 | 74 | 84
// ---+----+----+----+----+----+----+----+----
// R5 | 15 | 25 | 35 | 45 | 55 | 65 | 75 | 85
// ---+----+----+----+----+----+----+----+----
// R6 | 16 | 26 | 36 | 46 | 56 | 66 | 76 | 86
// ---+----+----+----+----+----+----+----+----
// R7 | 17 | 27 | 37 | 47 | 57 | 67 | 77 | 87
// ---+----+----+----+----+----+----+----+----
// R8 | 18 | 28 | 38 | 48 | 58 | 68 | 78 | 88

// WPC matrix numbering (IJ, STTNG, TZ):
//
//    | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8 | C9
// ---+----+----+----+----+----+----+----+----+----
// R1 | 11 | 21 | 31 | 41 | 51 | 61 | 71 | 81 | 91
// ---+----+----+----+----+----+----+----+----+----
// R2 | 12 | 22 | 32 | 42 | 52 | 62 | 72 | 82 | 92
// ---+----+----+----+----+----+----+----+----+----
// R3 | 13 | 23 | 33 | 43 | 53 | 63 | 73 | 83 | 93
// ---+----+----+----+----+----+----+----+----+----
// R4 | 14 | 24 | 34 | 44 | 54 | 64 | 74 | 84 | 94
// ---+----+----+----+----+----+----+----+----+----
// R5 | 15 | 25 | 35 | 45 | 55 | 65 | 75 | 85 | 95
// ---+----+----+----+----+----+----+----+----+----
// R6 | 16 | 26 | 36 | 46 | 56 | 66 | 76 | 86 | 96
// ---+----+----+----+----+----+----+----+----+----
// R7 | 17 | 27 | 37 | 47 | 57 | 67 | 77 | 87 | 97
// ---+----+----+----+----+----+----+----+----+----
// R8 | 18 | 28 | 38 | 48 | 58 | 68 | 78 | 88 | 98

// DE matrix numbering:
//
//    | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8
// ---+----+----+----+----+----+----+----+----
// R1 |  1 |  9 | 17 | 25 | 33 | 41 | 49 | 57
// ---+----+----+----+----+----+----+----+----
// R2 |  2 | 10 | 18 | 26 | 34 | 42 | 50 | 58
// ---+----+----+----+----+----+----+----+----
// R3 |  3 | 11 | 19 | 27 | 35 | 43 | 51 | 59
// ---+----+----+----+----+----+----+----+----
// R4 |  4 | 12 | 20 | 28 | 36 | 44 | 52 | 60
// ---+----+----+----+----+----+----+----+----
// R5 |  5 | 13 | 21 | 29 | 37 | 45 | 53 | 61
// ---+----+----+----+----+----+----+----+----
// R6 |  6 | 14 | 22 | 30 | 38 | 46 | 54 | 62
// ---+----+----+----+----+----+----+----+----
// R7 |  7 | 15 | 23 | 31 | 39 | 47 | 55 | 63
// ---+----+----+----+----+----+----+----+----
// R8 |  8 | 16 | 24 | 32 | 40 | 48 | 56 | 64

// In case of 9 Columns on WPC the 9th column is only read every second run.

#ifndef Matrix_h
#define Matrix_h

#include "../PPUC.h"

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

#ifndef NUM_COLS
#define NUM_COLS 9
#endif

#ifndef MAX_FIELDS_REGISTERED
#define MAX_FIELDS_REGISTERED (NUM_COLS * 8)
#endif

class Matrix {
public:
    Matrix(EventDispatcher* eD, byte pf);

    virtual void start() = 0;

    virtual void stop() = 0;

    void update();

    void print();

    void setLastColToRead(byte lastColToRead);

    void registerFieldAsEvent(byte row, byte column, byte number);

    void registerAllFieldsAsEvent();

    static void _readRow() {}

    volatile byte lastColToRead;
    volatile byte rows[NUM_COLS];

protected:
    EventDispatcher* eventDispatcher;

    char eventSource;
    byte maxChangesPerRead = 6;
    byte previousRows[NUM_COLS];

    int registeredFieldsCounter = -1;
    word registeredFieldRowCol[MAX_FIELDS_REGISTERED];
    byte registeredFieldNum[MAX_FIELDS_REGISTERED];

    byte platform;

    byte updateDelay = 0;
    uint32_t nextUpdate = 0;
};

#endif
