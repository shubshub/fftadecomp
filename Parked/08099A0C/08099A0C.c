#include "ffta.h"

typedef struct {
    u8 unknown_00[0x5C];
    u16 result;
    u8 unknown_5E[0x22];
    void *owner;
} SceneObject;

s32 func_0809E830(void *owner, SceneObject *object, s32 mode);

s32 func_08099A0C(SceneObject *object, SceneObject *other)
{
    if (other != object) {
        s32 result = func_0809E830(object->owner, object, 0);

        object->result = result;
        if (other != 0 && result == 0)
            return 0;
    } else {
        other->result = 0;
    }
    return 1;
}
