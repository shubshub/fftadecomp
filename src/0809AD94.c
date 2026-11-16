#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[0x58];
    s16 counter;
} CounterObject;

extern u8 func_0812E4A8(const void *object);
extern u8 func_080CDB24(const void *object);
extern u8 func_080CDADC(const void *object);

/* Complete [0x0809AD94, 0x0809ADDC): 72 bytes, 29 instructions.
 * Target: 10b5041c206893f085fb000600280bd0206832f0bdfe0006002805d1206832f0
 * 93fe0006002805d0211c5c31004804e0ffff0000211c5c3102480880012010bc02bc
 * 0847feff0000
 * A list callback like func_0809AD6C: func_0809ABE8 (src/0809ABE8.c) calls it
 * with the closure argument in r1 (func_08099A70 stores it at 0x08099A82),
 * which this callback leaves unused.
 */
u32 func_0809AD94(CounterObject *object, const CounterObject *excluded)
{
    if (!func_0812E4A8(object->unit) || func_080CDB24(object->unit) ||
        func_080CDADC(object->unit))
        object->counter = -1;
    else
        object->counter = -2;
    return 1;
}
