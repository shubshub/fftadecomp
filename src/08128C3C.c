#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 hp;
    u16 max_hp;
    u16 mp;
    u16 max_mp;
    u16 stat_20;
    u16 stat_22;
    u16 stat_24;
    u16 stat_26;
    u8 unknown_28[0xD2 - 0x28];
    s16 stat_D2;
} Unit08128C3C;

typedef struct {
    u8 unknown_00[2];
    u8 index : 3;
    u8 unknown_02_3 : 5;
} __attribute__((packed)) Key08128C3C;

typedef struct {
    u8 unknown_00[8];
    Unit08128C3C *unit;
    Key08128C3C *key;
} State08128C3C;

extern const u8 data_083A8260[];
extern u32 func_080C92F0(void *unit, u32 selector);

u8 func_08128C3C(State08128C3C *state, u8 kind)
{
    Unit08128C3C *unit = state->unit;
    s16 amount = 0;
    u8 divisor = data_083A8260[state->key->index];

    switch (kind) {
    case 0:
        amount = func_080C92F0(unit, 0x17) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->max_hp <= amount)
            amount = unit->max_hp - 1;
        unit->max_hp -= amount;
        if (unit->hp > unit->max_hp)
            unit->hp = unit->max_hp;
        break;
    case 1:
        amount = func_080C92F0(unit, 0x18) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->max_mp <= amount)
            amount = unit->max_mp - 1;
        unit->max_mp -= amount;
        if (unit->mp > unit->max_mp)
            unit->mp = unit->max_mp;
        break;
    case 2:
        amount = func_080C92F0(unit, 0x1A) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->stat_20 <= amount)
            amount = unit->stat_20 - 1;
        unit->stat_20 -= amount;
        break;
    case 3:
        amount = func_080C92F0(unit, 0x1B) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->stat_22 <= amount)
            amount = unit->stat_22 - 1;
        unit->stat_22 -= amount;
        break;
    case 4:
        amount = func_080C92F0(unit, 0x1C) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->stat_24 <= amount)
            amount = unit->stat_24 - 1;
        unit->stat_24 -= amount;
        break;
    case 5:
        amount = func_080C92F0(unit, 0x1D) / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->stat_26 <= amount)
            amount = unit->stat_26 - 1;
        unit->stat_26 -= amount;
        break;
    case 6:
        amount = 10 / divisor;
        if (amount == 0)
            amount = 1;
        else if (amount > 10)
            amount = 10;
        if (unit->stat_D2 - amount <= 10)
            amount = unit->stat_D2 - 10;
        unit->stat_D2 -= amount;
        break;
    }
    return amount;
}
