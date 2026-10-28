#include "ffta.h"

/* 0x0809A63C..0x0809A664: 40 bytes / 16 instructions. */
typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ObjectPair0809A63C;

typedef void (*ObjectUpdate0809A63C)(void *, u8);

extern ObjectUpdate0809A63C data_08394048[];

void func_0809A63C(ObjectPair0809A63C *objects, u8 value)
{
    data_08394048[0](objects->first, value);
    data_08394048[0](objects->second, value);
}
