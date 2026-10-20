#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xCC];
    u8 x;
    u8 y;
    u8 facing;
    u8 previousX;
    u8 previousY;
    u8 unknown_FB[0xD];
} SceneRecord;

typedef struct {
    SceneRecord *record;
    u8 unknown_04[0x2C];
    u32 flags;
} SceneObject;

extern SceneRecord g_state_02000080[24];

SceneRecord *func_08121CB4(u8 selector);
SceneRecord *func_080C83CC(u8 selector);
void *func_08096D7C(void);
SceneObject *func_08099560(void *context, SceneRecord *record);
void func_08099E68(SceneObject *object, s8 x, s8 y);
void func_08124710(SceneObject *object, u8 update, u8 value);

void func_08124480(u8 selector, u8 x, u8 y, u8 facing, u8 enabled)
{
    SceneRecord *record;
    SceneObject *object;

    if (selector == 0xFF) {
        SceneRecord *candidate = g_state_02000080;
        s32 index;

        record = 0;
        for (index = 0; index < 24; index++, candidate++) {
            if (candidate->flags & 0x400) {
                record = candidate;
                break;
            }
        }
    } else if ((s8)selector < 0) {
        record = func_08121CB4(selector);
    } else {
        record = func_080C83CC(selector);
    }
    record->x = x;
    record->y = y;
    record->facing = facing;
    object = func_08099560(func_08096D7C(), record);
    func_08099E68(object, (s8)object->record->x, (s8)object->record->y);
    object->record->previousX = object->record->x;
    object->record->previousY = object->record->y;
    func_08124710(object, 1, facing);
    if (enabled)
        object->flags &= ~1;
    else
        object->flags |= 1;
}
