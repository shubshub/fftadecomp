#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 offset;
    u8 unknown_20[0x14];
    u16 x;
    u16 y;
    u8 unknown_38[0xC];
    void *sprite;
} Object0809A27C;

extern void func_0802158C(void *sprite, s32 x, s32 y, u32 flags);

/* 0x0809A27C..0x0809A298: 28 bytes, 13 instructions. */
void func_0809A27C(Object0809A27C *object, s32 offset)
{
    object->offset = offset;
    func_0802158C(object->sprite, object->x, object->y + offset, 0);
}
