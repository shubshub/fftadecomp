#ifndef HISTORY_UNIT_H
#define HISTORY_UNIT_H

#include "ffta.h"

typedef struct UnitRecord080C62CC {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0xF1];
    u8 x;
    u8 y;
    u8 facing;
    u8 unknown_F9[0x0F];
} HistoryUnit;

struct State080C62CC;

struct State080C62CC *func_080C6858(HistoryUnit *records, s32 count);

#endif
