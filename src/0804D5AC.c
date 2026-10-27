#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 enabled;
    u8 unknown_02[0x1A];
    void *first;
    void *second;
    void *third;
} EnabledObjects;

extern EnabledObjects *data_0201F544;
extern void func_0804E9B0(void *object);

/* 0804D5AC..0804D5F4: 72 bytes. */
void func_0804D5AC(u8 enabled)
{
    data_0201F544->enabled = enabled;
    if (data_0201F544->enabled & 1)
        func_0804E9B0(data_0201F544->first);
    if (data_0201F544->enabled & 2)
        func_0804E9B0(data_0201F544->second);
    if (data_0201F544->enabled & 4)
        func_0804E9B0(data_0201F544->third);
}
