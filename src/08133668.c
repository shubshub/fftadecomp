#include "ffta.h"

/* 0x08133668..0x08133692: 42 bytes, 19 instructions. */
typedef struct {
    u8 unknown_00[8];
    void *object;
    u8 kind;
    u8 unknown_0D[0x19];
    u16 flags;
} State;

extern void func_080CDFC0(void *object, u8 enabled);
extern void func_080CE488(void *object, u8 value);

void func_08133668(State *state)
{
    if (!(state->flags & 0x10)) {
        func_080CDFC0(state->object, 1);
        func_080CE488(state->object, state->kind + 0x36);
    }
}
