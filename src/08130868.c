#include "ffta.h"

/* 0x08130868..0x081308F4: 140 bytes. */
extern u8 func_0812F3CC(void *unit);
extern u8 func_080C95A8(u32 flag);
extern u8 func_080C8240(void *unit);
extern u8 func_080C82B8(void *unit);
extern u8 func_080C9540(u32 ability);
extern u8 func_08133BC4(void *unit);

static inline u8 target_conditions_hold(void *target)
{
    if (!func_080C95A8(13))
        return 0;
    if (!func_080C8240(target))
        return 0;
    if (!func_080C82B8(target))
        return 0;
    return 1;
}

u8 func_08130868(void *unit, void *target)
{
    if (func_0812F3CC(target) == 1)
        return 1;

    if (!target_conditions_hold(target))
        return 0;
    if (!func_080C9540(65))
        return 0;
    if (func_080C8240(unit))
        return 0;

    if (func_080C9540(66)) {
        if (func_08133BC4(unit))
            return 0;
        return 1;
    }
    if (func_08133BC4(unit))
        return 1;
    return 0;
}
