#include "polygon_scanline.h"

typedef union {
    u16 radius;
    struct {
        u16 horizontal;
        u16 vertical;
    } dimensions;
    PolygonPoint triangle[3];
    struct {
        const PolygonPoint *points;
        u16 count;
    } polygon;
} Shape0800E4DC;

typedef struct {
    s16 x;
    s16 y;
    u8 kind;
    u8 unknown_05[3];
    PolygonSpan spans[160];
    Shape0800E4DC shape;
} Geometry0800E4DC;

Geometry0800E4DC *func_0800C614(void *object);
void func_08010058(void *object, u16 first, u8 count, u8 left, u8 right);
void func_0800E718(s16 x, s16 y, u16 radius, PolygonSpan *spans, u8 clip);
void func_0800EA0C(s16 x, s16 y, u16 horizontal, u16 vertical,
                   PolygonSpan *spans, u8 clip);
void func_0800F068(s16 x, s16 y, u16 radius, PolygonSpan *spans, u8 clip);
void func_0800F6A8(s16 x, s16 y, u16 horizontal, u16 vertical,
                   PolygonSpan *spans, u8 clip);
void func_0800F770(s16 x, s16 y, u16 horizontal, u16 vertical,
                   PolygonSpan *spans, u8 clip);
void func_0800F860(s16 x, s16 y, u16 horizontal, u16 vertical,
                   PolygonSpan *spans, u8 clip);

void func_0800E4DC(void *object, u16 x, u16 y)
{
    u8 kind;

    {
        Geometry0800E4DC *geometry = func_0800C614(object);

        geometry->x = x;
        geometry->y = y;
        kind = geometry->kind;
    }
    switch (kind) {
    case 1: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800E718(geometry->x, geometry->y, geometry->shape.radius,
                       geometry->spans, 1);
        break;
    }
    case 2: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800EA0C(geometry->x, geometry->y,
                       geometry->shape.dimensions.horizontal,
                       geometry->shape.dimensions.vertical, geometry->spans, 1);
        break;
    }
    case 3: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F068(geometry->x, geometry->y, geometry->shape.radius,
                       geometry->spans, 1);
    }
    case 4: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F308(geometry->shape.triangle, 3, geometry->x, geometry->y,
                       geometry->spans, 1);
        break;
    }
    case 5: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F308(geometry->shape.polygon.points, geometry->shape.polygon.count,
                       geometry->x, geometry->y, geometry->spans, 1);
        break;
    }
    case 6: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F6A8(geometry->x, geometry->y,
                       geometry->shape.dimensions.horizontal,
                       geometry->shape.dimensions.vertical, geometry->spans, 1);
        break;
    }
    case 7: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F770(geometry->x, geometry->y,
                       geometry->shape.dimensions.horizontal,
                       geometry->shape.dimensions.vertical, geometry->spans, 1);
        break;
    }
    case 8: {
        Geometry0800E4DC *geometry = func_0800C614(object);
        func_08010058(object, 0, 160, 245, 250);
        func_0800F860(geometry->x, geometry->y,
                       geometry->shape.dimensions.horizontal,
                       geometry->shape.dimensions.vertical, geometry->spans, 1);
        break;
    }
    }
}
