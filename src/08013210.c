#include "ffta.h"

typedef struct Object08013210 Object08013210;

typedef struct {
    u8 unknown_00[0x0b];
    u8 flags_0b : 8;
    u16 flags_0c;
    u8 unknown_0e[0x1d];
    u8 control : 8;
    Object08013210 *object;
    u32 value;
    u8 unknown_34[6];
    u16 flags_3a;
    u8 unknown_3c[0x718];
    const u8 *name;
} State08013210;

extern State08013210 *data_0200918C;
extern const u8 *func_080CB928(Object08013210 *object);

/* Target: complete [0x08013210, 0x080132B8), 168 bytes, 74 instructions. */
void func_08013210(Object08013210 *object, u8 second, u32 value)
{
    data_0200918C->flags_3a |= 0x80;
    data_0200918C->object = object;
    data_0200918C->value = value;
    if (object != 0)
        data_0200918C->name = func_080CB928(object);

    if (second != 0) {
        data_0200918C->control &= ~1;
        data_0200918C->control |= 2;
        data_0200918C->flags_0c |= 0x10;
        data_0200918C->flags_0b |= 2;
    } else {
        data_0200918C->control &= ~2;
        data_0200918C->control |= 1;
        data_0200918C->flags_0c &= ~0x10;
        data_0200918C->flags_0b &= ~2;
    }
    if (object == 0)
        data_0200918C->control = 0;
}
