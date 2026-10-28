/* 0x08011C60 - 100 bytes: submit the active object's render source. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 state;
    u8 unknown_09[3];
    u16 flags_0c;
    u8 unknown_0e[0x22];
    u32 flags_30;
    u8 unknown_34[6];
    u16 flags_3a;
    s16 x;
    s16 y;
    u8 unknown_40[0x714];
    const void *source;
} RenderObject08011C60;

extern RenderObject08011C60 *data_0200918C;
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                        u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                        u32 value, u8 mode, const void *transform);

void func_08011C60(void)
{
    RenderObject08011C60 *object = data_0200918C;

    if (object && object->state > 1 && (object->flags_3a & 0x100)) {
        const void *source = object->source;

        if (source)
            func_08001F34(source, object->x, object->y, 0,
                         0, 1, !(object->flags_0c & 0x10), 0,
                         object->flags_30 >> 5, 0, 0);
    }
}
