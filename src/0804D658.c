#include "ffta.h"

typedef struct ResourceState {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[0x1A];
    void *first;
    void *second;
    void *third;
} ResourceState;

extern ResourceState *data_0201F544;
extern void func_0804E9A0(void *resource);

/* 0804D658..0804D6B0: 88 bytes, 38 instructions. */
void func_0804D658(void)
{
    if (data_0201F544->flags & 1) {
        func_0804E9A0(data_0201F544->first);
        data_0201F544->first = 0;
    }
    if (data_0201F544->flags & 2) {
        func_0804E9A0(data_0201F544->second);
        data_0201F544->second = 0;
    }
    if (data_0201F544->flags & 4) {
        func_0804E9A0(data_0201F544->third);
        data_0201F544->third = 0;
    }
}
