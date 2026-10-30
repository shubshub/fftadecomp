/* Target bytes (184):
 * 70 b5 05 1c 09 06 0e 0e 12 04 14 14 9e f7 06 fa
 * 00 06 00 28 04 d0 00 2e 02 d1 25 48 60 43 04 12
 * 28 1c 9e f7 07 fa 00 06 00 28 04 d0 60 00 00 19
 * c0 00 00 19 04 12 28 1c 9e f7 44 fa 00 06 00 28
 * 05 d0 00 2e 03 d1 60 00 00 19 c0 01 04 12 28 1c
 * 9e f7 34 fb 00 06 00 28 04 d0 00 2e 02 d1 15 48
 * 60 43 04 12 28 1c 9e f7 35 fb 00 06 00 28 04 d0
 * 00 2e 02 d1 e6 20 60 43 04 12 28 1c 9e f7 36 fb
 * 00 06 00 28 04 d0 01 2e 02 d1 0a 48 60 43 04 12
 * 28 1c 9e f7 37 fb 00 06 00 28 04 d0 01 2e 02 d1
 * e6 20 60 43 04 12 20 1c 70 bc 02 bc 08 47 00 00
 * 33 01 00 00 19 01 00 00
 */
#include "ffta.h"

typedef struct Unit Unit;

extern u8 func_080CD944(Unit *unit);
extern u8 func_080CD95C(const Unit *unit);
extern u8 func_080CD9EC(const Unit *unit);
extern u8 func_080CDBE4(Unit *unit);
extern u8 func_080CDBFC(const void *object);
extern u8 func_080CDC14(const Unit *unit);
extern u8 func_080CDC2C(const Unit *unit);

s32 func_0812F528(Unit *unit, u8 mode, s16 input)
{
    s32 value = input;

    if (func_080CD944(unit) && mode == 0)
        value = (value * 307) >> 8;
    if (func_080CD95C(unit))
        value = (value * 25) >> 8;
    if (func_080CD9EC(unit) && mode == 0)
        value = (value * 384) >> 8;
    if (func_080CDBE4(unit) && mode == 0)
        value = (value * 281) >> 8;
    if (func_080CDBFC(unit) && mode == 0)
        value = (value * 230) >> 8;
    if (func_080CDC14(unit) && mode == 1)
        value = (value * 281) >> 8;
    if (func_080CDC2C(unit) && mode == 1)
        value = (value * 230) >> 8;

    return value;
}
