#include "ffta.h"

typedef struct Object Object;

extern void func_080975DC(Object *object, u16 value, s8 adjustment, s32 mode);
extern void func_08097704(Object *object, u16 value, s8 adjustment);

/* An inlined copy of func_0809A298 (src/0809A298.c). */
static inline void inlined_0809A298(Object *object, u16 value, s8 adjustment)
{
    func_080975DC(object, value, adjustment, 1);
}

/* 0x0809A2D8..0x0809A302: 42 bytes, 19 instructions.
 * Target: 70b5061c 0d1c141c 2d042d0c 24062416 291c221c 0123fdf7 75f9301c
 *         291c221c fdf704fa 70bc01bc 0047
 */
void func_0809A2D8(Object *object, u16 value, s8 adjustment)
{
    inlined_0809A298(object, value, adjustment);
    func_08097704(object, value, adjustment);
}
