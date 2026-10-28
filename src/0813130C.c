#include "ffta.h"

struct UnitInfo {
    u8 unknown[0xF6];
    s8 x;
    s8 y;
};

struct ActionContext {
    void *first;
    struct UnitInfo *second;
};

extern u8 func_0812F0E4(struct UnitInfo *unit, s8 x, s8 y);
extern u8 func_08131220(const struct ActionContext *context);

u8 func_0813130C(const struct ActionContext *context)
{
    struct UnitInfo *unit = context->second;

    if (func_0812F0E4(unit, unit->x, unit->y) == 0)
        return 0;
    return func_08131220(context);
}
