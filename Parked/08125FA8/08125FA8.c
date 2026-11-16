#include "control_flags.h"

/* Complete target [0x08125FA8, 0x08126118): 368 bytes, 153 instructions.
 * The 0x50-byte snapshot at state+0x64 is a byte copy of the control block
 * at 0x03000940; only the two members restored from it are named. */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Owner08125FA8;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Owner08125FA8 *owner;
    u8 unknown_08[0xC];
    u16 kind;
    u16 variant;
} Request08125FA8;

typedef struct {
    u16 display;
    u8 unknown_02[0x48];
    u8 bldcnt_lo;
    u8 unknown_4B[5];
} SavedControl08125FA8;

typedef struct {
    Owner08125FA8 *owner;
    u8 unknown_04[4];
    void *window;
    u8 timer;
    u8 kind;
    u8 variant;
    u8 unknown_0F[0x55];
    SavedControl08125FA8 saved_control;
} State08125FA8;

extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void *func_08121B64(u32 size);
extern void func_08121B78(u8 *object);
extern void *func_081443FC(void *, const void *, u32);
extern void func_0801174C(void *, u32, u32, void *, void *, u32, u32,
                          u32, u32, u32);
extern void func_0801339C(u16);
extern u16 func_08011860(void);

u32 func_08125FA8(void *task, Request08125FA8 *request, State08125FA8 *state)
{
    switch (request->phase) {
    case 1:
        if (state->window) {
            func_08121B78(state->window);
            state->window = 0;
        }
        break;
    case 0: {
        const void *control;

        state->owner = request->owner;
        state->kind = request->kind;
        state->variant = request->variant;
        state->timer = 0;
        control = &g_control_flags_03000940;
        func_081443FC(&state->saved_control, control, 0x50);
        g_control_flags_03000940.display |= 0xC00;
        g_control_flags_03000940.bldcnt_lo &= ~0x1C;
        break;
    }
    case 0x100:
        state->window = func_08121B64(0xA04);
        switch (state->kind) {
        case 1:
            func_0801174C(state->window, 1, state->variant, data_030008B0,
                          data_03000990, 2, 2, 24, 4, 0x3A0);
            func_0801339C(2);
            break;
        case 2:
            func_0801174C(state->window, 2, state->variant, data_030008B0,
                          data_03000990, 2, 2, 24, 0, 0x3A0);
            func_0801339C(2);
            break;
        }
        request->phase = 0x101;
        break;
    case 0x101:
        if (func_08011860())
            request->phase = 0x102;
        break;
    case 0x102:
        if (state->timer && --state->timer)
            break;
        func_08121B78(state->window);
        state->window = 0;
        request->phase = 0x103;
        break;
    case 0x103:
        g_control_flags_03000940.display = state->saved_control.display;
        g_control_flags_03000940.bldcnt_lo = state->saved_control.bldcnt_lo;
        state->owner->complete = 1;
        request->phase = 3;
        break;
    }
    return 0;
}
