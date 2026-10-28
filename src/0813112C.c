#include "ffta.h"

struct UnitPair {
    void *first;
    void *second;
};

extern u8 func_0812EF94(void *first, void *second, u32 mode,
                       u32 option, u32 flags);

u8 func_0813112C(const struct UnitPair *pair)
{
    return func_0812EF94(pair->first, pair->second, 0, 0, 0);
}
