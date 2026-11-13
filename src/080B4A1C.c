#include "ffta.h"

typedef struct {
    void *unit;
    s8 x;
    s8 y;
    s8 end_x;
    s8 end_y;
    u16 first;
    u16 second;
} RangeRequest;

extern u8 data_08394590[];
extern u8 data_08394594[];
extern u32 func_080C92F0(void *, u32);
extern int func_080B7C2C(u16, u16, u8);
extern int func_080B7C94(u16, u16, u8);
extern void func_0809D66C(s8, s8 *, s8 *);
extern int func_080B479C(void *, s8, s8, s8, s8, u16, u16, u8, u32 *);
extern int func_080B48CC(void *, s8, s8, s8, s8, u16, u16, u32 *);
extern int func_080B4678(void *, s8, s8, u16, u16, u32 *);
extern int func_080B44F8(void *, s8, s8, s8, s8, u16, u16, u32 *);

static inline u16 range_shape(void *unit, u16 first, u16 second, u8 mode)
{
    if (unit && (func_080C92F0(unit, 0x28) & 4)) {
        if (mode == 0)
            return 0x1c0;
        else
            return 0x1c2;
    }
    return func_080B7C2C(first, second, mode);
}

static inline u8 range_extent(void *unit, u16 first, u16 second)
{
    if (unit && (func_080C92F0(unit, 0x28) & 4))
        return 1;
    return func_080B7C94(first, second, 1);
}

static inline s8 normalize_direction(int direction)
{
    s8 d = direction;
    if (d < 0)
        d += 4;
    if (d > 3)
        d -= 4;
    return d;
}

/* 0x080B4A1C: target [0x080B4A1C, 0x080B4C8E), 626 bytes. */
int func_080B4A1C(RangeRequest *request, u8 direction, u8 mode, u32 *output)
{
    int shape;
    u32 count;
    shape = range_shape(request->unit, request->first, request->second, mode);
    shape &= 0x70;
    count = 0;
    switch (shape) {
    case 0:
        {
            s8 x, y;
            u32 i;
            for (i = 0; i < 4; i++) {
                s8 d = normalize_direction((s8)direction + data_08394590[i]);
                func_0809D66C(d, &x, &y);
                count += func_080B479C(request->unit, request->x, request->y,
                    x, y, request->first, request->second, mode, output + count);
            }
        }
        break;
    case 0x10:
        {
            s8 x, y;
            u32 i;
            for (i = 0; i < 2; i++) {
                s8 d = normalize_direction((s8)direction + data_08394594[i]);
                func_0809D66C(d, &x, &y);
                count += func_080B479C(request->unit, request->x, request->y,
                    x, y, request->first, request->second, mode, output + count);
            }
        }
        break;
    case 0x20:
        {
            u8 extent = range_extent(request->unit, request->first, request->second);
            if (extent == 4)
                extent = 2;
            count = func_080B48CC(request->unit, request->x, request->y,
                (s8)direction, (s8)extent, request->first, request->second, output);
        }
        break;
    case 0x30:
        {
            s8 x, y;
            func_0809D66C((s8)direction, &x, &y);
            count = func_080B479C(request->unit, request->x, request->y,
                x, y, request->first, request->second, mode, output);
        }
        break;
    case 0x40:
        if (mode == 0)
            count = func_080B4678(request->unit, request->x, request->y,
                request->first, request->second, output);
        else
            count = func_080B44F8(request->unit, request->x, request->y,
                request->end_x, request->end_y, request->first, request->second, output);
        break;
    }
    return count;
}
