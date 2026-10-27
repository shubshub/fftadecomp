#include "ffta.h"

typedef struct Context0805F4AC {
    void *manager;
} Context0805F4AC;

extern Context0805F4AC *data_0200F44C;
extern void func_08005A24(void *manager);
extern s32 func_0805F604(void);

/* Complete [0x0805F4AC, 0x0805F4D8): 44 bytes, 17 instructions. */
s16 func_0805F4AC(void)
{
    Context0805F4AC *context = data_0200F44C;

    if (context == 0 || context->manager == 0)
        return -1;
    func_08005A24(context->manager);
    return func_0805F604();
}
