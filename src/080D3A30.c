#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 value;
} State080D3A30;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* Target bytes [080D3A30, 080D3A50):
 * 00 B5 05 48 00 68 32 F7 E1 F8 42 88 03 49 11 40
 * 41 80 01 BC 00 47 00 00 C0 59 01 02 DF FF 00 00.
 */
void func_080D3A30(void)
{
    State080D3A30 *state = func_08005BFC(data_020159C0);

    state->value &= ~0x20;
}
