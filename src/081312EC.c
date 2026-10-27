#include "ffta.h"

struct ActionConfig {
    u8 unknown;
    u8 mode;
};

struct ActionContext {
    void *first;
    void *second;
    u8 unknown[0x28];
    struct ActionConfig *config;
};

extern u32 func_0812DB5C(void *first, void *second, u8 mode);

u8 func_081312EC(const struct ActionContext *context)
{
    if (func_0812DB5C(context->first, context->second,
                      context->config->mode) == 0)
        return 0;
    return 100;
}
