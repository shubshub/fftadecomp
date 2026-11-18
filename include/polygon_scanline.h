#ifndef POLYGON_SCANLINE_H
#define POLYGON_SCANLINE_H

#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} PolygonPoint;

typedef struct {
    u16 left;
    u16 right;
} PolygonSpan;

typedef struct {
    s16 center_x;
    s16 center_y;
    s16 scale_x;
    s16 scale_y;
} PolygonScale;

u32 func_0800DECC(const PolygonPoint *points, u16 count, u16 *minimum_index);
void func_0800DFB0(s16 x0, s16 y0, s16 x1, s16 y1, PolygonSpan *spans);
void func_0800E05C(s16 x0, s16 y0, s16 x1, s16 y1, PolygonSpan *spans);
void func_0800F308(const PolygonPoint *vertices, u16 count, s16 x_offset,
                   s16 y_offset, PolygonSpan *ranges, u8 mode);
void func_0800F480(const PolygonPoint *vertices, u16 count, s16 x_offset,
                   s16 y_offset, PolygonSpan *ranges, u8 mode,
                   const PolygonScale *scale);

#endif
