#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *first;
    void *second;
    void *unknown_0C;
    u32 unknown_10;
    u16 id;
    u16 unknown_16;
    u32 unknown_18;
} Descriptor080D3818;

typedef int (*Callback080D3818)(void *, void *, void *);

typedef struct {
    Callback080D3818 callback;
    u16 size;
    u16 unknown_06;
} Entry080D3818;

extern Entry080D3818 data_08395320[];
extern void *data_0200F430;
extern void *data_020159C0;
extern void *func_08005954(void *, Callback080D3818, u16, void *, void *);

// Complete [0x080D3818, 0x080D3864): 76 bytes, including four literal words.
void *func_080D3818(u16 id, void *first, void *second)
{
    Descriptor080D3818 descriptor;
    Callback080D3818 callback;
    u16 size;
    void *task;
    task = 0;
    descriptor.id = id;
    descriptor.first = first;
    descriptor.second = second;
    descriptor.unknown_0C = task;
    callback = data_08395320[id - 0x16B].callback;
    size = data_08395320[id - 0x16B].size;
    task = func_08005954(data_0200F430, callback, size, &descriptor, data_020159C0);
    return task;
}
