#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[14];
    u16 tile;
    u8 unknown_14[4];
    s16 x;
    s16 y;
    u8 offset;
    u8 parameter;
    u8 unknown_1e[10];
    const void *image;
    u8 unknown_2c[4];
    u16 scale_x;
    u16 scale_y;
} SpriteNode;

typedef struct {
    s16 x, y;
    u8 variant, flip_x, flip_y;
    u8 flag_7, flag_8, offset, mode;
} DrawArguments;

extern void func_080018A0(const void *, s32, s32, u8, u8, u8,
                          u32, u8, u32, s16, s16, u16, u8);
extern void func_08001F34(const void *, s32, s32, u8, u8, u8,
                          u8, u8, u32, u8, const void *);

/* Position and scale are also exposed by 08021D48 and 08021D14. */
static inline void sprite_position(const SpriteNode *node, s16 *x, s16 *y)
{
    *x = node->x;
    *y = node->y;
    if (node->flags & 0x20)
        *x *= -1;
    if (node->flags & 0x200)
        *x *= -1;
    if (node->flags & 0x400)
        *x *= -1;
}

static inline void sprite_scale(const SpriteNode *node, u16 *x, u16 *y)
{
    if ((node->flags & 0x800) == 0) {
        *x = *y = 0x100;
    } else {
        *x = node->scale_x;
        *y = node->scale_y;
    }
}

/* Complete [0x080216F8, 0x08021854), 348 bytes. */
void func_080216F8(SpriteNode *node, void *argument)
{
    const DrawArguments *args = argument;
    s16 x, y;
    u16 scale_x, scale_y;

    sprite_position(node, &x, &y);
    if (node->image != 0 && (node->flags & 0x40)) {
        if (node->flags & 0x800) {
            u16 tile;
            u32 parameter;

            sprite_scale(node, &scale_x, &scale_y);
            tile = node->tile;
            parameter = node->parameter;
            func_080018A0(node->image, args->x + x, args->y + y,
                          0, 0, 0, tile, 0, parameter,
                          (s16)scale_x, (s16)scale_y, 0, 0);
        } else {
            func_08001F34(node->image, args->x + x, args->y + y,
                          args->variant, args->flip_x, args->flip_y,
                          ((node->flags & 8) != 0) ^ ((node->flags & 0x20) != 0) ^
                              args->flag_7,
                          args->flag_8 ^ ((node->flags & 0x10) != 0),
                          node->tile, args->mode,
                          (const void *)(node->offset + args->offset + node->parameter));
        }
    }
}
