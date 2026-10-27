#include "ffta.h"

typedef struct Object Object;

typedef struct {
    u8 unknown_00;
    u8 option;
} Configuration;

typedef struct {
    Object *source;
    Object *target;
    u8 unknown_08[0x28];
    const Configuration *configuration;
} Context;

extern u8 func_0812D358(Object *source, Object *target, u8 option);

/* Complete [0x08131260, 0x08131278): 24 bytes, 11 instructions. */
u8 func_08131260(const Context *context)
{
    return func_0812D358(context->source, context->target,
                         context->configuration->option);
}
