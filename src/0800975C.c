/* 0x0800975C..0x0800977C: 32 target bytes, including two literal words. */
#include "ffta.h"

typedef struct {
    u16 flags;
    u16 selector;
    u8 unknown_04[0x14];
    u32 first;
    u32 second;
    u8 unknown_20[0x1BAC];
    u32 tail;
} State;

void func_08008818(State *state, u32 first, u32 second, u16 selector, u32 setting);

void func_0800975C(State *state)
{
    func_08008818(state, 0x030008b0, 0x03000990, 0xe0, 0);
}
