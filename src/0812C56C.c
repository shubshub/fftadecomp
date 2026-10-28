#include "ffta.h"

/* Target: complete [0x0812C56C, 0x0812C5CA), 94 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    u16 value;
} State0812C56C;

extern u8 func_080CD92C(State0812C56C *);
extern u8 func_080CDA04(State0812C56C *);
extern u8 func_080CDADC(State0812C56C *);
extern u8 func_080CDB24(State0812C56C *);
extern u8 func_080CDA4C(State0812C56C *);

u32 func_0812C56C(State0812C56C *state)
{
    if (state->value == 0)
        return 0;
    if (func_080CD92C(state))
        return 0;
    if (func_080CDA04(state))
        return 0;
    if (func_080CDA04(state))
        return 0;
    if (func_080CDADC(state))
        return 0;
    if (func_080CDB24(state))
        return 0;
    if (func_080CDA4C(state))
        return 0;
    return 1;
}
