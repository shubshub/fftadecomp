#include "ffta.h"

// Complete 0x080A5A7C..0x080A5B98: 284 bytes, 113 instructions.

typedef struct {
    u8 unknown_00[0x08];
    s16 x;
    u16 height;
    s16 y;
    u8 unknown_0E[0x11];
    s8 facing;
    u8 unknown_20[0x10];
    u32 flags;
} PhaseObject;

typedef struct {
    PhaseObject *object;
    u16 flags;
    s16 mode;
    u8 unknown_08[5];
    u8 phase;
} PhaseEntry;

typedef struct {
    u8 unknown_0000[0x26C0];
    u16 flags;
    void *task;
} PhaseState;

extern void func_080A92E4(s32 mode, s32 x, s32 height, s32 y, s32 effect);
extern void func_0809836C(PhaseObject *object, u16 action, s8 value, u16 option);
extern u32 func_08099C64(const PhaseObject *object);
extern void func_080D376C(void);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern void *func_080D3508(u16 resource, u32 mode, void *context);
extern u8 func_080D3878(const void *task);
extern void func_080D3864(void *task);

u32 func_080A5A7C(PhaseState *state, PhaseEntry *entry)
{
    switch (entry->phase) {
    case 0:
        func_080A92E4(entry->mode, entry->object->x,
                      (s16)(entry->object->height + 0x30), entry->object->y, 0);
        if (entry->mode < 0) {
            entry->phase = 5;
            return 0;
        }
        func_0809836C(entry->object, 5, entry->object->facing, 0);
        entry->phase = 1;
        break;
    case 1:
        if (func_08099C64(entry->object) == 0)
            break;
        if (!(entry->flags & 0x1000)) {
            entry->phase = 5;
            return 0;
        }
        if (state->flags & 8) {
            entry->phase = 3;
        } else {
            func_080D376C();
            state->flags |= 8;
            entry->phase = 2;
        }
        break;
    case 2:
        if (func_080D37F8() && func_080D39B0())
            entry->phase = 3;
        break;
    case 3:
        state->task = func_080D3508(0x15C, 0, entry->object);
        entry->phase = 4;
        break;
    case 4:
        if (state->task != 0) {
            if (!func_080D3878(state->task))
                break;
            func_080D3864(state->task);
            state->task = 0;
        }
        entry->object->flags |= 0x10;
        entry->phase = 5;
        break;
    case 5:
        return 0;
    }
    return 1;
}
