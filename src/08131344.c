#include "ffta.h"

struct UnitPair {
    void *first;
    void *second;
};

extern u8 func_0812F1CC(void *unit);
extern u8 func_08130868(void *source, void *target);
extern u8 func_0813112C(const struct UnitPair *pair);

/* Action evaluator table 0x083A8678, slot 31. */
u8 func_08131344(const struct UnitPair *pair)
{
    if (!func_0812F1CC(pair->second) && !func_08130868(pair->first, pair->second))
        return func_0813112C(pair);
    return 0;
}
