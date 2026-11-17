#include "ffta.h"

// Complete [0x080DAAC4, 0x080DAB84): 192 bytes, 96 instructions.
// Build a square of the given radius rotated by angle, centred on (x, y),
// and draw its outline with func_080DA77C.

struct Point080DAAC4 {
    u16 x;
    u16 y;
};

typedef struct {
    u32 unknown_00;
    void *object;
} Payload080DAAC4;

extern Payload080DAAC4 *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern s16 func_08007A60(u8 angle);
extern s16 func_08007A4C(u8 angle);
extern void func_080DA77C(const struct Point080DAAC4 *points, u16 count,
                          void *context);

static inline int offset_coordinate(s16 origin, u16 value)
{
    return origin + value;
}

void func_080DAAC4(void *task, u16 x, u16 y, u16 radius, u8 angle)
{
    struct Point080DAAC4 points[4];
    void *context = func_0800C614(func_08005BFC(task)->object);
    u8 i;

    points[0].x = (func_08007A60(angle) * radius) >> 8;
    points[0].y = (func_08007A4C(angle) * radius) >> 8;
    points[2].x = -points[0].x;
    points[2].y = -points[0].y;
    points[1].x = -points[0].y;
    points[1].y = points[0].x;
    points[3].x = -points[1].x;
    points[3].y = -points[1].y;

    for (i = 0; i < 4; i++) {
        points[i].x = offset_coordinate(x, points[i].x);
        points[i].y = offset_coordinate(y, points[i].y);
    }

    func_080DA77C(points, 4, context);
}
