#include "ffta.h"

// 0x0800AA54..0x0800ACA8: 596 bytes, 298 instructions.

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
extern u8 func_0800C050(u8 record);
extern u8 func_0800C068(u8 record);
extern u8 *func_0800C038(u8 record);
extern u8 data_0200913A;

typedef struct {
    u8 header[2];
    u8 data[2];
} TileRun;

static inline const u8 *run_data(const TileRun *run)
{
    return run->data;
}

static inline u16 read_le16(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

static inline u8 read_tile(const TileRun **src, u16 *pos, u16 *skip, s32 compressed)
{
    u8 value;

    if (compressed) {
        u16 word = read_le16((*src)->header);
        u16 length = word & 0x3FFF;
        s32 mode = 0;

        if (word & 0x8000) {
            mode = 1;
            value = (*src)->data[0] + *pos;
        } else if (word & 0x4000) {
            mode = 2;
            value = (*src)->data[0];
            if (value == data_0200913A) {
                *skip = length;
                *pos = length - 1;
            }
        } else {
            value = run_data(*src)[*pos];
        }
        (*pos)++;
        if (*pos == length) {
            if (mode)
                (*src)++;
            else {
                s32 size = length;

                if (size & 1)
                    size++;
                *src = (const TileRun *)(run_data(*src) + size);
            }
            *pos = 0;
        }
    } else {
        const u8 *bytes = (const u8 *)*src;

        value = bytes[*pos];
        (*pos)++;
    }
    return value;
}

void func_0800AA54(TileLayout *layout, View *view, u8 originX, u8 originY)
{
    u16 pos;
    u16 skip;
    TileBounds bounds;
    const TileRun *src;
    u8 stride;
    u8 rows;
    u8 width;
    u8 height;
    s16 row;
    s16 col;
    s16 x;
    u8 *dest;
    s32 compressed;
    s32 rowVisible;
    s32 colVisible;
    u8 value;

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
    skip = 0;
    for (row = 0; row < height; row++) {
        s16 y = originY + row;

        rowVisible = y >= 0;
        if (y >= rows)
            rowVisible = 0;
        if (y < bounds.top || y >= bounds.bottom)
            rowVisible = 0;
        if (rowVisible)
            dest = func_0800C038(view->record) + y * stride;
        for (col = 0; col < width; col++) {
            if (skip) {
                skip--;
                continue;
            }
            x = originX + col;
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
            if (rowVisible && colVisible && value != data_0200913A) {
                u8 *out = dest + x;

                if (view->tileOffset) {
                    s32 offset = view->tileOffset;

                    value += offset;
                }
                *out = value;
            }
        }
    }
}
