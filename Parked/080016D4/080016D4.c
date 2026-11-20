/* 0x080016D4, 460 bytes. Emit the visible records into an OAM shadow list. */
#include "ffta.h"

typedef union SpriteEntry SpriteEntry;

typedef struct {
    s16 width, height;
} SpriteSize;

extern const SpriteSize data_08149510[16];

/* The VBlank transfer reads the published OAM shadow bank. */
union SpriteEntry {
    struct {
        u16 attr0 : 16;
        u16 attr1 : 16;
        u16 attr2 : 16;
        u16 affine;
    } raw;
    struct {
        u16 y : 8;
        u16 attr0_flags : 8;
        u16 x : 9;
        u16 attr1_flags : 7;
        u16 tile : 10;
        u16 priority : 2;
        u16 palette : 4;
        u16 affine;
    } fields;
};

static inline s32 ReadSpriteHalfword(const u8 *p)
{
    s32 low = p[0];
    s32 high = p[1];
    return (high << 8) | low;
}

s32 func_080016D4(const void *source, s32 x, s32 y, s32 tile,
                  u8 priority, u32 palette, SpriteEntry *out,
                  s32 capacity, s32 count)
{
    const u8 *record;
    s16 remaining;

    if (count >= capacity)
        return count;

    out += count;
    record = (const u8 *)source + 2;
    remaining = ReadSpriteHalfword(source);
    for (; remaining > 0; remaining--, record += 6) {
        const SpriteSize *size;
        s16 dx, dy;
        s32 screen_x;
        u8 x_low, x_high;
        s32 y_low;

        if (count >= capacity)
            return count;

        size = &data_08149510[(record[1] >> 6) * 4 + (record[3] >> 6)];
        x_low = record[2];
        x_high = record[3];
        dx = x_low;
        dx |= (x_high & 1) << 8;

        if (dx & 0x100)
            dx |= -0x100;
        screen_x = (s16)(dx + x);
        if ((screen_x < 0 && screen_x + size->width < 0) ||
            (screen_x > 239 && screen_x + size->width > 239))
            continue;

        y_low = record[0];
        dy = y_low;
        if (dy & 0x80)
            dy |= -0x80;
        dy += y;
        if ((dy < 0 && dy + size->height < 0) ||
            (dy > 159 && dy + size->height > 159))
            continue;

        out->raw.attr0 = (record[1] << 8) | y_low;
        {
            u32 x_low_byte = record[2];
            out->raw.attr1 = (record[3] << 8) | x_low_byte;
        }
        {
            u32 tile_low = record[4];
            out->raw.attr2 = (record[5] << 8) | tile_low;
        }
        out->fields.y = dy;
        out->fields.x = screen_x;
        out->fields.tile += tile;
        out->fields.priority += priority;
        out->fields.palette += palette;
        out++;
        count++;
    }
    return count;
}
