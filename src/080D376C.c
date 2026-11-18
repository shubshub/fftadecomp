#include "ffta.h"

typedef struct {
    u16 command;
    u16 unknown_02;
    void *first;
    void *second;
    void *context;
    u32 unknown_10;
    u16 id;
    u16 unknown_16;
    u32 unknown_18;
} TaskDescriptor;

typedef int (*TaskCallback)(void *, TaskDescriptor *, void *);

extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern void *data_0200F430;
extern void *data_020159C0;
extern int func_080D3208(void *, TaskDescriptor *, void *);
extern void *func_08005954(void *, TaskCallback, u16, TaskDescriptor *, void *);

/* Create the root task with an empty descriptor and no parent. */
void func_080D376C(void)
{
    TaskDescriptor descriptor;

    g_callbacks_0836D4B8[0](&descriptor, sizeof(descriptor));
    data_020159C0 = func_08005954(data_0200F430, func_080D3208, 0xB28,
                                  &descriptor, 0);
}
