#include "ffta.h"

/* 0x0809AD1C..0x0809AD48: 44 bytes / 17 instructions. */
typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ObjectPair0809AD1C;

typedef void (*ObjectUpdate0809AD1C)(void *, u8);

extern ObjectUpdate0809AD1C data_08394048[];

u32 func_0809AD1C(ObjectPair0809AD1C *objects, u8 value)
{
    data_08394048[0](objects->first, value);
    data_08394048[0](objects->second, value);
    return 1;
}
