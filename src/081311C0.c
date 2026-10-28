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

extern u8 func_0812DA0C(void *first, void *second, u8 mode);

u8 func_081311C0(const struct ActionContext *context)
{
    return func_0812DA0C(context->first, context->second,
                         context->config->mode);
}
