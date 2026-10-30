#include "ffta.h"

/* Target: complete [0x080992E0, 0x080993F4), 276 bytes, 127 instructions. */
typedef struct {
    u8 active;
    u8 unknown_01[0x23];
    u16 flags;
    u8 unknown_26[0xce];
} UnitData;

typedef struct {
    u32 unknown_00;
    UnitData unit;
    u8 state;
    u8 unknown_f9[0x0f];
} SceneRecord;

typedef struct {
    u8 unknown_00[0x80];
    SceneRecord first[24];
    u8 unknown_1940[0x1684];
    SceneRecord second[12];
} SceneRecords;

extern u8 func_080C84C0(const void *record);
extern void *func_08092440(void *context, SceneRecord *record);

void func_080992E0(void *context, SceneRecords *scene)
{
    s32 i;

    for (i = 0; i < 24; i++) {
        SceneRecord *record = &scene->first[i];
        UnitData *unit = &record->unit;
        if (unit->active && (scene->first[i].unit.flags & 1) &&
            !(scene->first[i].unit.flags & 0x20) &&
            !(u16)(scene->first[i].unit.flags & 0x100)) {
            if (func_080C84C0(record) &&
                (u8)(scene->first[i].state - 1) <= 1)
                scene->first[i].state = 0;
            func_08092440(context, record);
        }
    }
    for (i = 0; i < 12; i++) {
        SceneRecord *record = &scene->second[i];
        UnitData *unit = &record->unit;
        if (unit->active && (scene->second[i].unit.flags & 1) &&
            !(scene->second[i].unit.flags & 0x20) &&
            !(u16)(scene->second[i].unit.flags & 0x100)) {
            if (func_080C84C0(record) &&
                (u8)(scene->second[i].state - 1) <= 1)
                scene->second[i].state = 0;
            func_08092440(context, record);
        }
    }
}
