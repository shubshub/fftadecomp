#include "ffta.h"

/* 0x08058C48..0x08058D40: 248 bytes, 115 instructions. */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06[2];
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

typedef struct {
    u32 name;
    u8 active;
    u8 initial_level;
    u8 job;
    u8 level;
    u8 unknown_08;
    u8 appearance;
    u8 unknown_0A[14];
    u16 health;
    u16 maximum_health;
    u16 magic;
    u16 maximum_magic;
    u16 attack;
    u16 defense;
    u16 power;
    u16 resistance;
    u16 flags;
    u8 unknown_2A[168];
    u16 percentage;
    u8 unknown_D4[52];
} Unit;

typedef void (*BufferInitializer)(void *, u32);
extern BufferInitializer g_callbacks_0836D4B8[];
extern UnitTemplate data_02002E78[];
extern u8 func_080CCAD8(u8 index);
extern u8 func_080CCAE8(u8 index);

void func_08058C48(Unit *unit, u8 index)
{
    UnitTemplate *entry;

    g_callbacks_0836D4B8[0](unit, sizeof(*unit));
    entry = &data_02002E78[index];
    unit->flags = 0x8000;
    unit->name = entry->name;
    unit->appearance = entry->appearance;
    unit->percentage = 100;
    unit->active = 1;
    unit->initial_level = func_080CCAD8(index);
    unit->job = func_080CCAE8(index);
    unit->level = func_080CCAD8(index);
    unit->unknown_08 = 0;
    unit->health = entry->health;
    unit->maximum_health = entry->health;
    unit->magic = entry->magic;
    unit->maximum_magic = entry->magic;
    unit->attack = entry->attack;
    unit->defense = entry->defense;
    unit->power = entry->power;
    unit->resistance = entry->resistance;
}
