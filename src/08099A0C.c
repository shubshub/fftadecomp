#include "ffta.h"

/* Complete [0x08099A0C, 0x08099A46): 58 bytes, 28 instructions.
 * 30b5041c0d1ca54210d0201c80300068211c002204f006ff011c201c5c300180
 * 002d06d0002904d1002003e05c3100200880012030bc02bc0847
 */
typedef struct {
    u8 unknown_00[0x5C];
    s16 counter;
    u8 unknown_5E[0x22];
    void *owner;
} SceneObject;

s32 func_0809E830(void *context, SceneObject *entry, u16 steps);

s32 func_08099A0C(SceneObject *object, SceneObject *other)
{
    s32 result;

    if (other == object) {
        other->counter = 0;
        return 1;
    }
    result = func_0809E830(object->owner, object, 0);
    object->counter = result;
    if (other != 0 && result == 0)
        return 0;
    return 1;
}
