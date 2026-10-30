/* Target bytes (28):
 * 00 b5 05 48 00 68 32 f7 2f f9 42 88 01 21 11 43
 * 41 80 01 bc 00 47 00 00 c0 59 01 02
 */
#include "ffta.h"

struct ObjectHalfwordAt02 {
    u16 unknown_00;
    u16 value_02;
};

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

void func_080D3994(void)
{
    struct ObjectHalfwordAt02 *object = func_08005BFC(data_020159C0);

    object->value_02 |= 1;
}
