#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ObjectData;

typedef struct {
    ObjectData *data;
} SceneObject;

u8 func_080C8298(const ObjectData *data);

s32 func_0809AB3C(SceneObject *object, SceneObject **result)
{
    s32 status;

    if (func_080C8298(object->data)) {
        *result = object;
        status = 0;
    } else {
        status = 1;
    }
    return status;
}
