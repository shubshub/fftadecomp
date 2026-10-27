#include "ffta.h"

struct UnitPair {
    void *first;
    void *second;
};

extern u8 func_0812D388(void *first, void *second);

u8 func_08131174(const struct UnitPair *pair)
{
    return func_0812D388(pair->first, pair->second);
}
