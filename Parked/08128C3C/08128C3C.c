#include "ffta.h"

/* Complete [0x08128C3C, 0x08128E3E): 514 bytes, 226 instructions.
 * 30b509060a0e856800230749c06880784007400f40180478062a00d9ece090000249401800688746
 * 60823a086c8c1208888c1208ce8c1208148d12084c8d1208848d1208bc8d1208f48d1208281c1721
 * a0f730fb211c19f00dff0004030c0014002801d1012302e0632800dd6323698b18040014814202dc
 * 481e0004030cca1a6a83298b1004000c814200d8b4e02a83b2e0281c1821a0f70dfb211c19f0eafe
 * 0004030c0014002801d1012302e0632800dd6323e98b18040014814202dc481e0004030cca1aea83
 * a98b1004000c814200d891e0aa838fe0281c1a21a0f7eafa211c19f0c7fe0004030c0014002801d1
 * 012302e0632800dd6323298c18040014814202dc481e0004030cc81a288473e0281c1b21a0f7cefa
 * 211c19f0abfe0004030c0014002801d1012302e0632800dd6323698c18040014814202dc481e0004
 * 030cc81a688457e0281c1c21a0f7b2fa211c19f08ffe0004030c0014002801d1012302e0632800dd
 * 6323a98c18040014814202dc481e0004030cc81aa8843be0281c1d21a0f796fa211c19f073fe0004
 * 030c0014002801d1012302e0632800dd6323e98c18040014814202dc481e0004030cc81ae8841fe0
 * 0a20211c19f05efc0004030c0014002801d1012302e00a2800dd0a232a1cd2320020115e18040014
 * 091a0a2903dc10880a380004030c118818040014091a11801806000e30bc02bc0847
 */

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
