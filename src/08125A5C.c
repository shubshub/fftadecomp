#include "ffta.h"
#include "control_flags.h"

/* Complete [0x08125A5C, 0x08125DE8): 908 bytes, 454 instructions,
 * including the literal pools. */

typedef struct {
    u8 unknown_00[6];
    u8 done;
} Owner08125A5C;

typedef struct {
    u8 unknown_00;
    u8 selection;
    u8 selector;
    u8 offsets;
} Command08125A5C;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Owner08125A5C *owner;
    const Command08125A5C *command;
} Task08125A5C;

typedef struct {
    Owner08125A5C *owner;
    const Command08125A5C *command;
    void *window;
    u8 timer;
    u8 unknown_0D[2];
    u8 saved_2FC0;
    u8 unknown_10[0x54];
    __typeof__(g_control_flags_03000940) control;
} State08125A5C;

typedef struct {
    u8 unknown_00[0xF8];
    u8 facing;
} Object08125A5C;

typedef struct {
    u8 unknown_0000[0x2174];
    u16 unknown_2174;
    u8 unknown_2176[0x2FC0 - 0x2176];
    u16 unknown_2FC0_0 : 3;
    u16 unknown_2FC0_3 : 2;
} Global08125A5C;

extern Global08125A5C g_state_02000000;
extern const u8 g_table_085273D8[][14];
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern u8 data_06005000[];
extern u8 data_06005800[];
extern u8 data_06008000[];

extern void func_0801E458(u8, u8, u8, s16, s16, void *, void *);
extern u8 func_080C9540(u16 flag);
extern void func_080C9574(u16 flag, u16 enabled);
extern void *func_08121B64(u32 size);
extern void func_08121B78(void *object);
extern Object08125A5C *func_08125578(u8 selector);
extern u8 func_08125994(void *object);
extern void func_0801174C(void *window, u8 id, u8 selection, void *first,
                          void *second, s32 x, s32 y, u32 width, u32 height,
                          u32 tile);
extern void func_080132B8(void *object, u8 alternate);
extern void func_08013108(u8 first, u8 second, u8 enabled, u32 tile);
extern u16 func_08011860(void);
extern void func_08011C60(void);

/* With both offsets at -3 or beyond, the object's facing picks the corner
 * (the switch at 0x08125BCE-0x08125C16). */
static inline void face_offsets(Object08125A5C *object, s8 *x, s8 *y)
{
    if (*x <= -3 && *y <= -3) {
        switch (object->facing) {
        case 0:
            *x = -2;
            *y = 0;
            break;
        case 2:
            *x = 0;
            *y = -2;
            break;
        case 1:
            *x = -2;
            *y = -2;
            break;
        case 3:
            *x = 0;
            *y = 0;
            break;
        }
    }
}

s32 func_08125A5C(void *context, Task08125A5C *task, State08125A5C *state)
{
    switch (task->phase) {
    case 1:
        if (state->window) {
            func_08121B78(state->window);
            state->window = 0;
        }
        break;
    case 0:
        state->owner = task->owner;
        state->command = task->command;
        state->control = g_control_flags_03000940;
        g_control_flags_03000940.display |= 0xC00;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 0;
        func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06005800);
        func_0801E458(3, 0, 0, 0, 0, data_06008000, data_06005000);
        if (func_080C9540(0x252)) {
            state->saved_2FC0 = g_state_02000000.unknown_2FC0_3;
            g_state_02000000.unknown_2FC0_3 = 0;
        }
        break;
    case 0x100:
    {
        const Command08125A5C *command = state->command;
        u8 selection = command->selection;
        u8 selector = command->selector;
        u8 offsets = command->offsets;
        s8 x;
        s8 y;
        Object08125A5C *object;

        x = offsets & 7;
        y = (offsets >> 3) & 7;
        x = -x;
        y = -y;
        state->window = func_08121B64(0x794);
        object = func_08125578(selector);
        if (object) {
            selection += func_08125994(object);
            face_offsets(object, &x, &y);
            func_0801174C(state->window, 3, selection, data_030008B0,
                          data_03000990, x, y, 0, 6, 0x240);
            func_080132B8(object, x == -2);
        } else {
            func_0801174C(state->window, 3, selection, data_030008B0,
                          data_03000990, x, y, 0, 6, 0x240);
            if (selector < 2 || selector > 0x80) {
                func_080132B8(0, x == -2);
            } else {
                const u8 *entry = g_table_085273D8[selector];
                u8 second;
                u8 first;

                first = entry[0xB];
                second = entry[0xC];

                func_08013108(first, second, x == -2, 0x4800);
            }
        }
        task->phase = 0x101;
        break;
    }
    case 0x101:
        if (func_08011860()) {
            if (func_080C9540(0x252)) {
                g_state_02000000.unknown_2FC0_3 = state->saved_2FC0;
                func_080C9574(0x252, 0);
                g_state_02000000.unknown_2174 = 0;
            }
            state->timer = 30;
            task->phase = 0x102;
        }
        func_08011C60();
        break;
    case 0x102:
        if (state->timer) {
            if (--state->timer)
                break;
        }
        func_08121B78(state->window);
        state->window = 0;
        task->phase = 0x103;
        break;
    case 0x103:
        g_control_flags_03000940.display = state->control.display;
        g_control_flags_03000940.bldcnt_lo = state->control.bldcnt_lo;
        g_control_flags_03000940.bldcnt_hi = state->control.bldcnt_hi;
        g_control_flags_03000940.bldalpha_lo = state->control.bldalpha_lo;
        g_control_flags_03000940.bldalpha_hi = state->control.bldalpha_hi;
        state->owner->done = 1;
        task->phase = 3;
        break;
    }
    return 0;
}
