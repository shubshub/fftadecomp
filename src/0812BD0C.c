#include "ffta.h"

/* func_0812BD0C [0x0812BD0C,0x0812BD2C) 32 bytes
 * raw: 00b587b0002181710190044808216a460023f5f735ff07b001bc004781b91208 */

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} CompletionContext;

typedef struct {
    u16 state;
    u16 unknown_02;
    CompletionContext *context;
    u32 unknown_08[5];
} TaskDescriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_0812B980(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

void func_0812BD0C(CompletionContext *context)
{
    TaskDescriptor descriptor;

    context->complete = 0;
    descriptor.context = context;
    func_08121B8C(func_0812B980, 8, &descriptor, 0);
}
