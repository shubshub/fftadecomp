#include "ffta.h"

/* 0x080D4444..0x080D449A: 86 bytes. */
typedef struct {
    const u8 *data;
    u8 unknown_04[3];
    u8 flags;
    u16 unknown_08;
    u16 index;
    u16 value;
} CommandState;

extern void func_080D4038(CommandState *);

void func_080D4444(CommandState *state)
{
    const u8 *entry = state->data + (state->index * 6 + 6);

    if (entry[1] != 0) {
        func_080D4038(state);
    } else {
        u8 low;
        u8 high;

        if ((u8)(entry[0] - 10) <= 1) {
            func_080D4038(state);
            return;
        }
        low = entry[2];
        high = entry[3];
        state->value = (high << 8) | low;
        if (entry[0] == 12)
            return;
        if (entry[0] == 13)
            return;
    }
    state->flags &= 0xFD;
}
