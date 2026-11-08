#include "ffta.h"

/* 080D9914 .. 080D993C: 40 bytes, including the callback literal. */
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_080D9488(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                         void *descriptor, void *parent);

void *func_080D9914(u8 first, u8 second, void *parent)
{
    u16 descriptor[14];

    descriptor[10] = first;
    descriptor[11] = second;
    return func_08005B6C(func_080D9488, 0xC, descriptor, parent);
}
