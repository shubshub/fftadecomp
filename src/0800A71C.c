#include "ffta.h"

/* 0x0800A71C..0x0800AA52: 822 bytes, 411 instructions. */

typedef struct {
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
} TileBounds;

typedef struct {
    u8 record;
    u8 unknown_01;
    u16 flags;
    u8 unknown_04[0xA];
    s16 tileOffset;
    s16 paletteOffset;
} View;

typedef struct {
    u8 width;
    u8 compressedHeight;
    u8 height;
    u8 unknown_03;
    u8 runs[4];
    u8 data[1];
} TileLayout;

extern void func_0800A67C(View *view, TileBounds *bounds);
extern u32 func_0800C050(u8 record);
extern u8 func_0800C068(u8 record);
extern u32 func_0800C038(u8 record);
extern u16 data_02009138;

typedef u8 PackedTile[2];

typedef struct {
    u8 header[2];
    PackedTile data[1];
} TileRun;

static inline const PackedTile *run_data(const TileRun *run)
{
    return run->data;
}

static inline u16 make_le16(u8 low, u8 high)
{
    return (high << 8) | low;
}

static inline u16 read_tile(const TileRun **src, u16 *pos, u16 *skip, s32 compressed)
{
    u16 value;

    if (compressed) {
        const TileRun *run = *src;
        u16 word = make_le16(run->header[0], run->header[1]);
        u16 length = word & 0x3FFF;
        s32 mode = 0;

        if (word & 0x8000) {
            mode = 1;
            value = make_le16(run->data[0][0], run->data[0][1]) + *pos;
        } else if (word & 0x4000) {
            mode = 2;
            value = make_le16(run->data[0][0], run->data[0][1]);
            if (value == data_02009138) {
                *skip = length;
                *pos = length - 1;
            }
        } else {
            value = make_le16(run->data[*pos][0], run->data[*pos][1]);
        }
        (*pos)++;
        if (*pos == length) {
            if (mode)
                (*src)++;
            else
                *src = (const TileRun *)(run_data(*src) + make_le16(run->header[0], run->header[1]));
            *pos = 0;
        }
    } else {
        const u16 *words = (const u16 *)*src;

        value = words[*pos];
        (*pos)++;
    }
    return value;
}

static inline u16 offset_tile(u16 value, s32 tileOffset, s32 paletteOffset)
{
    s32 index = value & 0x3FF;
    u16 palette;
    u16 flips;
    u16 result;

    if (index == data_02009138)
        return value;
    palette = value >> 12;
    flips = value & 0xC00;
    result = index + tileOffset;
    palette += paletteOffset;
    result |= palette << 12;
    return result | flips;
}

void func_0800A71C(TileLayout *layout, View *view, u8 originX, u8 originY, u16 flip)
{
    u16 pos;
    u16 skip;
    TileBounds bounds;
    const TileRun *src;
    u8 stride;
    u8 rows;
    u8 width;
    u8 height;
    u8 row;
    s16 yOffset;
    s16 xOffset;
    u32 xorMask;
    s16 colStep;
    s16 rowStep;
    s16 x;
    u8 col;
    u16 *dest;
    s32 compressed;
    s32 rowVisible;
    s32 colVisible;
    u16 value;

    dest = 0;
    func_0800A67C(view, &bounds);
    stride = func_0800C050(view->record);
    rows = func_0800C068(view->record);
    compressed = 0;
    if (view->flags & 0x4000) {
        width = layout->width;
        height = layout->compressedHeight;
        src = (const TileRun *)layout->runs;
        compressed = 1;
    } else {
        width = layout->width;
        height = layout->height;
        src = (const TileRun *)layout->data;
    }
    pos = 0;
    flip ^= view->flags;
    xorMask = 0;
    colStep = 1;
    rowStep = 1;
    if (flip & 0x400) {
        xorMask = 0x400;
        colStep = -1;
        originX += width - 1;
    }
    if (flip & 0x800) {
        xorMask |= 0x800;
        rowStep = -1;
        originY += height - 1;
    }
    skip = 0;
    for (row = 0, yOffset = 0; row < height; row++, yOffset += rowStep) {
        s16 y = originY + yOffset;

        rowVisible = y >= 0;
        if (y >= rows)
            rowVisible = 0;
        if (y < bounds.top || y >= bounds.bottom)
            rowVisible = 0;
        if (rowVisible)
            dest = (u16 *)func_0800C038(view->record) + y * stride;
        for (col = 0, xOffset = 0; col < width; col++, xOffset += colStep) {
            if (skip) {
                skip--;
                continue;
            }
            x = originX + xOffset;
            colVisible = x >= 0;
            if (x >= stride)
                colVisible = 0;
            if (x < bounds.left || x >= bounds.right)
                colVisible = 0;
            value = read_tile(&src, &pos, &skip, compressed);
            if (skip) {
                skip--;
                continue;
            }
            if (rowVisible && colVisible && value != data_02009138) {
                u16 *out = dest + x;

                if (view->tileOffset || view->paletteOffset)
                    value = offset_tile(value, view->tileOffset, view->paletteOffset);
                *out = value ^ xorMask;
            }
        }
    }
}
