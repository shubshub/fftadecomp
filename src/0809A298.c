#include "ffta.h"

typedef struct Object Object;

extern void func_080975DC(Object *object, u16 value, s8 adjustment, s32 mode);

/* 0x0809A298..0x0809A2AC: 20 bytes. */
void func_0809A298(Object *object, u16 value, s8 adjustment)
{
    func_080975DC(object, value, adjustment, 1);
}
