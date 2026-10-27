#include "ffta.h"

/* 0x08131088..0x0813109C: 20 bytes. */
typedef struct {
    void *source;
    void *target;
} UnitPair;

extern int func_0812DAB8(void *, void *);

u8 func_08131088(const UnitPair *pair)
{
    return func_0812DAB8(pair->source, pair->target);
}
