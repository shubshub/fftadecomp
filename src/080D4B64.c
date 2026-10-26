#include "ffta.h"

typedef struct {
    u16 flags;
    u16 offset;
    u8 data[1];
} __attribute__((packed)) Descriptor;

typedef struct Object Object;

extern Object *func_0800B2A4(u8 group, const void *data, const void *extra, int first, int second);
extern Object *func_0800B394(u8 group, const void *data, const void *extra, int first, int second);
extern void func_0800BEDC(Object *object, u8 mode);
extern void func_0800BED8(Object *object, s16 value);
extern void func_0800BF04(Object *object, u8 first, u8 second);

Object *func_080D4B64(u8 group, const Descriptor *descriptor, u16 value, u8 mode)
{
    const void *data = descriptor->data;
    const void *extra = (const u8 *)descriptor + descriptor->offset;
    Object *object;

    if (descriptor->flags & 1)
        object = func_0800B2A4(group, data, extra, 0, 0);
    else
        object = func_0800B394(group, data, extra, 0, 0);

    func_0800BEDC(object, mode);
    func_0800BED8(object, (s16)value);
    func_0800BF04(object, descriptor->flags & 4, descriptor->flags & 8);
    return object;
}
