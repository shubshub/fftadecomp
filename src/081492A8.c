#include "ffta.h"

typedef struct {
    u8 unknown_00[0x980];
    u8 category : 7;
    u8 active : 1;
    u8 unknown_981[3];
    u8 field_984;
    u8 field_985;
} CategoryState081492A8;

/* Complete [0x081492A8, 0x081492D0): 40 bytes, 16 instructions. */
void func_081492A8(CategoryState081492A8 *state)
{
    state->category = 0;
    state->field_984 = 0;
    state->field_985 = 0;
}
