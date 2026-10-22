#include "ffta.h"

typedef struct {
    void *manager;
} TaskContext;

void func_08005A24(void *manager);

s32 func_08065028(void)
{
    TaskContext *context = *(TaskContext **)0x0200F454;

    if (context == 0 || context->manager == 0)
        return -1;
    func_08005A24(context->manager);
    return 0;
}
