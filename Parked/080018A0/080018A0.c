#include "oam_lists.h"

typedef struct {
    s16 width, height;
} SpriteSize;

typedef struct {
    u32 scale_x : 16;
    u32 scale_y : 16;
    u32 angle : 16;
} ObjAffineSource;

typedef union {
    struct {
        u16 attr0 : 16;
        u16 attr1 : 16;
        u16 attr2 : 16;
        u16 affine;
    } raw;
    struct {
        u16 y : 8;
        u16 affine_mode : 2;
        u16 object_mode : 2;
        u16 mosaic : 1;
        u16 color_mode : 1;
        u16 shape : 2;
        u16 x : 9;
        u16 matrix : 5;
        u16 size : 2;
        u16 tile : 10;
        u16 priority : 2;
        u16 palette : 4;
        u16 affine;
    } fields;
} SpriteEntry;

extern const SpriteSize data_08149510[16];
extern void func_08141894(const ObjAffineSource *, AffineMatrix *, s32, s32);
extern int func_08000FC8(const volatile AffineMatrix *);

static inline s32 read_sprite_halfword(const u8 *record)
{
    s32 low = record[0];
    s32 high = record[1];
    return (high << 8) | low;
}

static inline void build_matrix(AffineMatrix *matrix, s16 scale_x, s16 scale_y, u16 angle)
{
    ObjAffineSource transform;
    AffineMatrix result;

    transform.scale_x = scale_x;
    transform.scale_y = scale_y;
    transform.angle = angle;
    func_08141894(&transform, &result, 1, 2);
    matrix->pa = result.pa;
    matrix->pb = result.pb;
    matrix->pc = result.pc;
    matrix->pd = result.pd;
}

/* Complete [0x080018A0, 0x08001BBC), 796 bytes. */
void func_080018A0(const void *source, s32 x, s32 y, u8 object_mode,
                   u8 mosaic, u8 color_mode, u32 tile, u8 priority,
                   u32 palette, s16 scale_x, s16 scale_y, u16 angle,
                   u8 double_size)
{
    AffineMatrix matrix;
    const u8 *record;
    SpriteEntry *out;
    s16 remaining;
    s32 slot;
    s32 count = data_03000020[data_03000028];

    if (count >= 128)
        return;

    build_matrix(&matrix, scale_x, scale_y, angle);
    slot = func_08000FC8(&matrix);

    out = (SpriteEntry *)data_03000030[data_03000028];
    out += count;
    record = (const u8 *)source + 2;
    remaining = read_sprite_halfword(source);
    for (; remaining > 0; remaining--, record += 6) {
        const SpriteSize *size;
        s16 dx, dy;
        s16 extent;
        s32 y_low;
        u8 x_low, x_high;

        if (count >= 128) {
            data_03000020[data_03000028] = count;
            return;
        }
        size = &data_08149510[(record[1] >> 6) * 4 + (record[3] >> 6)];
        x_low = record[2];
        x_high = record[3];
        dx = x_low;
        dx |= (x_high & 1) << 8;
        if (dx & 0x100)
            dx |= -0x100;
        dx += (s16)x;

        /* The renderer uses height as the clip extent on both axes. */
        extent = size->height;
        if (double_size) {
            dx -= size->width >> 1;
            extent *= 2;
        }
        if ((dx < 0 && dx + extent < 0) || dx > 239)
            continue;

        y_low = record[0];
        dy = y_low;
        if (dy & 0x80)
            dy |= -0x80;
        dy += (s16)y;
        extent = size->height;
        if (double_size) {
            dy -= extent >> 1;
            extent *= 2;
        }
        if ((dy < 0 && dy + extent < 0) || dy > 159)
            continue;

        out->raw.attr0 = (record[1] << 8) | y_low;
        out->raw.attr1 = read_sprite_halfword(record + 2);
        out->raw.attr2 = read_sprite_halfword(record + 4);
        out->fields.affine_mode = double_size ? 3 : 1;
        if (object_mode != 3)
            out->fields.object_mode = object_mode;
        out->fields.mosaic = mosaic;
        out->fields.color_mode = color_mode;
        out->fields.y = dy;
        out->fields.x = dx;
        out->raw.attr1 &= 0xC1FF;
        out->raw.attr1 |= slot << 9;
        out->fields.tile += tile;
        out->fields.priority += priority;
        out->fields.palette += palette;
        out++;
        count++;
    }
    data_03000020[data_03000028] = count;
}
