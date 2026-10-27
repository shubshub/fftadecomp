#include "ffta.h"

/* Target: complete [0x080DD6B8, 0x080DD6E0), 40 bytes. */
typedef struct Unit Unit;

typedef struct {
    Unit *unit;
} UnitOwner;

extern void *func_08096D7C(void);
extern UnitOwner *func_0809961C(void *context, s8 x, s8 y);

UnitOwner *func_080DD6B8(u8 x, u8 y)
{
    return func_0809961C(func_08096D7C(), (s8)x, (s8)y);
}
