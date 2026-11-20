#include "positioned_equipment.h"

struct UnitPair {
    void *first;
    void *second;
};

u8 func_0813112C(const struct UnitPair *pair)
{
    return func_0812EF94(pair->first, pair->second, 0, 0, 0);
}
