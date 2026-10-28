#include "ffta.h"

/* Complete [0x08068848, 0x08068862): 26 bytes, 11 instructions. */
typedef struct {
    u8 unknown_00[0x10];
    void (*callback)(void);
} SelectionState;

extern void func_080682E4(SelectionState *);
extern void func_08066C28(SelectionState *);

void func_08068848(SelectionState *state)
{
    func_080682E4(state);
    if (state->callback)
        func_08066C28(state);
}
