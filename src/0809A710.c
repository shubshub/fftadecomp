#include "ffta.h"

typedef struct ObjectPair0809A710 {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ObjectPair0809A710;

typedef void (*ObjectCallback0809A710)(void *object);

extern ObjectCallback0809A710 const data_0839403C;

/* Complete [0x0809A710, 0x0809A740): 48 bytes, 19 instructions. */
void func_0809A710(ObjectPair0809A710 *objects)
{
    if (objects->first)
        data_0839403C(objects->first);
    if (objects->second)
        data_0839403C(objects->second);
}
