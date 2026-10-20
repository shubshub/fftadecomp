#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDE];
} SceneRecord;

typedef struct {
    u32 unknown_00[2];
    s16 x;
    u16 unknown_0A;
    s16 y;
} SceneObject;

SceneRecord *func_08121CB4(u8 selector);
SceneRecord *func_080C83CC(u8 selector);
void *func_08096D7C(void);
SceneObject *func_08099560(void *context, SceneRecord *record);

void func_08124E74(u8 selector, s8 x, s8 y, s16 *out_x, s16 *out_y)
{
    SceneRecord *record;
    SceneObject *object;

    if (x < 0)
        *out_x = 0;
    if (y < 0)
        *out_y = 0;
    if (selector == 0xFF) {
        SceneRecord *candidate = (SceneRecord *)0x02000080;
        s32 index;

        for (index = 0; index < 24; index++, candidate++) {
            if (candidate->flags & 0x400) {
                record = candidate;
                goto record_selected;
            }
        }
        record = 0;
    } else if ((s8)selector < 0) {
        record = func_08121CB4(selector);
    } else {
        record = func_080C83CC(selector);
    }
record_selected:
    object = func_08099560(func_08096D7C(), record);
    if (x >= 0) {
        s32 position = x * 32 + 16;

        position -= object->x;
        *out_x = position;
    }
    if (y >= 0) {
        s32 position = y * 32 + 16;

        position -= object->y;
        *out_y = position;
    }
}
