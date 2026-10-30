#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F30];
    u16 field_1f30;
    u16 field_1f32;
    u16 field_1f34;
    u16 field_1f36;
    u16 field_1f38;
} State080CBC94;

extern u8 g_state_02000000[];

/* Complete [0x080CBC94, 0x080CBCE0): 76 bytes, 23 instructions.
 * Target SHA-256: 604d871bf2bc01feab25e7b04ee333aec7bed10dc0ccfe82bd2716c71977eedd
 */
void func_080CBC94(void)
{
    State080CBC94 *state = (State080CBC94 *)g_state_02000000;

    state->field_1f30 = 4;
    state->field_1f32 = 0x157;
    state->field_1f34 = 0x124;
    state->field_1f36 = 9;
    state->field_1f38 = 0x7D;
}
