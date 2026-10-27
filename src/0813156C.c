#include "ffta.h"

struct UnitState {
    u8 unknown[0xD6];
    u16 value;
};

struct UnitPair {
    void *first;
    struct UnitState *second;
};

u8 func_0813156C(const struct UnitPair *pair)
{
    if (pair->second->value != 0)
        return 1;
    return 0;
}
