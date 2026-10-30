#include "ffta.h"

struct Object;

struct TextContext080132B8 {
    u8 unknown_00[0x0b];
    u8 variant;
    u16 flags;
    u8 unknown_0e[0x1d];
    u8 name_flags;
    struct Object *object;
    u32 scale;
    u8 unknown_34[6];
    u16 options;
    u8 unknown_3c[0x718];
    const u8 *name;
};

extern struct TextContext080132B8 *data_0200918C;
extern const u8 *func_080CB928(struct Object *object);

/* Complete [0x080132B8, 0x08013364): 172 bytes, 76 instructions. */
void func_080132B8(struct Object *object, u8 alternate)
{
    u32 scale = 0x4800;

    data_0200918C->options |= 0x80;
    data_0200918C->object = object;
    data_0200918C->scale = scale;
    if (object)
        data_0200918C->name = func_080CB928(object);

    if (alternate) {
        data_0200918C->name_flags &= 0xfe;
        data_0200918C->name_flags |= 2;
        data_0200918C->flags |= 0x10;
        data_0200918C->variant |= 2;
    } else {
        data_0200918C->name_flags &= 0xfd;
        data_0200918C->name_flags |= 1;
        data_0200918C->flags &= 0xffef;
        data_0200918C->variant &= 0xfd;
    }
    if (!object)
        data_0200918C->name_flags = 0;
}
