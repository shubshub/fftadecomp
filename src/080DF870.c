#include "ffta.h"

/* 0x080DF870..0x080DF8AE: 62 bytes. */
typedef struct {
    u8 unknown_00[0x34];
    u16 value;
} ObjectState;

extern ObjectState *func_080DD350(int index);
extern void func_080DE33C(int index, s8 value, int enabled);
extern u8 func_080DD73C(int index);
extern void func_080DE278(int index, s8 value);

void func_080DF870(int index, u8 value)
{
    ObjectState *state = func_080DD350(index);

    func_080DE33C(index, (s8)value, 1);
    if (func_080DD73C(index))
        state->value = 0xE6;
    else
        state->value = 0x2A;
    func_080DE278(index, (s8)value);
}
