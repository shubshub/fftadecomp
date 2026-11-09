#include "control_flags.h"

/* Target: complete [0x081269E4, 0x08126AA8), 196 bytes, 86 instructions.
 * Structures are local offset views with unknown complete object extents. */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Completion081269E4;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Completion081269E4 *completion;
    u8 unknown_08[12];
    u16 first_target;
    u16 second_target;
    u16 duration;
} Descriptor081269E4;

typedef struct {
    u16 current;
    u8 unknown_02[22];
} Interpolation081269E4;

typedef struct {
    Completion081269E4 *completion;
    Interpolation081269E4 first;
    Interpolation081269E4 second;
} Payload081269E4;

extern void func_08007620(Interpolation081269E4 *, s32, s32, s32, s32);
extern void func_080076F4(Interpolation081269E4 *);
extern u32 func_08007894(const void *);

u32 func_081269E4(void *task, Descriptor081269E4 *descriptor,
                  Payload081269E4 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 first, second, duration;

            payload->completion = descriptor->completion;
            first = descriptor->first_target;
            second = descriptor->second_target;
            duration = descriptor->duration;
            func_08007620(&payload->first, g_control_flags_03000940.bldalpha_lo,
                          0, first, duration);
            func_08007620(&payload->second, g_control_flags_03000940.bldalpha_hi,
                          0, second, duration);
        }
        break;
    case 1:
        break;
    case 0x100:
        {
            u32 first_done, second_done;

            func_080076F4(&payload->first);
            func_080076F4(&payload->second);
            g_control_flags_03000940.bldalpha_lo = payload->first.current;
            g_control_flags_03000940.bldalpha_hi = payload->second.current;
            first_done = func_08007894(&payload->first);
            second_done = func_08007894(&payload->second);
            if (first_done && second_done)
                descriptor->phase = 0x102;
        }
        break;
    case 0x102:
        payload->completion->complete = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
