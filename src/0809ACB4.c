#include "ffta.h"

/* 0x0809ACB4..0x0809ACE4: 48 bytes / 20 instructions. */
typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ObjectPair0809ACB4;

typedef void (*ObjectRelease0809ACB4)(void *);

extern ObjectRelease0809ACB4 data_0839403C[];

u32 func_0809ACB4(ObjectPair0809ACB4 *objects)
{
    if (objects->first)
        data_0839403C[0](objects->first);
    if (objects->second)
        data_0839403C[0](objects->second);
    return 1;
}
