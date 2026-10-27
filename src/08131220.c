#include "ffta.h"

struct ActionConfig {
    u8 unknown;
    u8 mode;
};

struct ActionContext {
    void *first;
    void *second;
    u8 unknown8[0x1E];
    u16 flags;
    u8 unknown28[8];
    struct ActionConfig *config;
};

extern u32 func_0812F008(void *first, void *second, u8 mode);
extern u8 func_080CD8FC(void *unit);

u8 func_08131220(const struct ActionContext *context)
{
    u32 value = func_0812F008(context->first, context->second,
                              context->config->mode);

    if (func_080CD8FC(context->second) != 0) {
        if ((context->flags & 0x10) == 0) {
            if (value != 0)
                return 100;
        } else {
            return 0;
        }
    }
    return value;
}
