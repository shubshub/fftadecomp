#include "ffta.h"

// Complete target: [0x0800B0AC, 0x0800B13C), 144 bytes.

typedef struct {
    u8 *buffer;
    u32 source;
    u8 format;
    u8 unknown_09;
    u16 size;
    u8 width;
    u8 height;
    u16 byte_count;
    u16 field_10;
    u16 unknown_12;
    u32 field_14;
    s16 x;
    s16 y;
    u8 layer;
    u8 unknown_1D;
    s16 scroll_x;
    s16 scroll_y;
    u8 unknown_22[6];
} Record02009000;

typedef struct {
    s32 tex_x;
    s32 tex_y;
    s16 scr_x;
    s16 scr_y;
    s16 sx;
    s16 sy;
    u16 alpha;
} BgAffineSource;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} BgAffineDest;

extern Record02009000 g_records_02009000[];

extern void func_08141864(BgAffineSource *src, BgAffineDest *dest, s32 count);
extern void func_080032F8(const BgAffineDest *transform, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);

void func_0800B0AC(u8 index)
{
    Record02009000 *record = &g_records_02009000[index];
    s32 dx = record->scroll_x;
    s32 dy = record->scroll_y;
    u8 layer;
    u8 format;
    BgAffineSource src;
    BgAffineDest dest;

    dx -= record->x;
    dy -= record->y;
    layer = record->layer;
    format = record->format;

    if (layer == 0xFF)
        return;

    if (format == 1) {
        src.tex_x = record->scroll_x << 8;
        src.tex_y = record->scroll_y << 8;
        src.scr_x = record->x;
        src.scr_y = record->y;
        src.sx = 0x100;
        src.sy = 0x100;
        src.alpha = 0;
        func_08141864(&src, &dest, 1);
        func_080032F8(&dest, layer);
    } else {
        func_08003508(dx, layer);
        func_08003558(dy, layer);
    }
}
