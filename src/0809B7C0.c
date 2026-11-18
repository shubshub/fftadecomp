#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
} MovingEntity;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Point0809B120;

typedef struct {
    MovingEntity *entity;
    Point0809B120 *points;
    u8 unknown_08[0x12];
    s16 index;
    u8 unknown_1C[0xC];
    u8 facing;
} Path0809B120;

typedef struct {
    u8 unknown_00[0x44];
    u32 value;
} ValueRecord;

extern u32 func_0809A53C(ValueRecord *record);
extern s32 func_0809B120(Path0809B120 *path);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_0809A530(void *object, u32 value);

void func_0809B7C0(Path0809B120 *path)
{
    path->facing = func_0809A53C((ValueRecord *)path->entity);
    if (path->facing)
        path->facing--;
    func_0809B120(path);
    func_0809A570(path->entity, 0, 0x100);
    switch (path->facing) {
    case 0:
    case 1:
        path->facing = 2;
        break;
    case 2:
    case 3:
        path->facing = 0;
        break;
    }
    func_0809A530(path->entity, path->facing);
}
