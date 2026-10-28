#include "ffta.h"

/* 0x080BA8A4..0x080BA8E2: 62 bytes. */
typedef struct {
    void *resource;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_0C[0xE];
    u16 attributes;
    u8 style;
} Object;

void func_08001F34(void *resource, s32 x, s32 y, u32 mode,
                   u32 argument5, u32 argument6, u32 argument7, u32 argument8,
                   u16 attributes, u32 argument10, u8 style);

void func_080BA8A4(const Object *object)
{
    func_08001F34(object->resource,
                  object->x + object->offset_x,
                  object->y + object->offset_y,
                  0, 0, 0, 0, 0, object->attributes, 0, object->style);
}
