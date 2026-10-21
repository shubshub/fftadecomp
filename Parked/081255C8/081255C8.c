#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 unknown_28;
    u8 unknown_2A[0x108 - 0x2A];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

extern State g_state_02000080;

void *func_080C83CC(u8 category);
void *func_08121CB4(u8 index);
void *func_08096D7C(void);
void *func_08099560(void *object, void *record);

void *func_081255C8(u32 selector)
{
    SceneRecord *record;
    s32 index;

    if ((u8)selector == 0xFF) {
        record = 0;
        for (index = 0; index < 24; index++) {
            if (g_state_02000080.first[index].unknown_28 & 0x400) {
                record = &g_state_02000080.first[index];
                break;
            }
        }
    } else if ((s8)selector < 0) {
        record = func_08121CB4((u8)selector);
    } else {
        record = func_080C83CC((u8)selector);
    }
    return func_08099560(func_08096D7C(), record);
}
