#include "ffta.h"

typedef struct {
    void *owner;
} AllocationContext;

void *func_08007138(void *owner, u32 bytes);

/* 0x08005B00-0x08005B0C: 12 bytes. */
void *func_08005B00(AllocationContext *context, u32 byte_count)
{
    return func_08007138(context->owner, byte_count);
}
