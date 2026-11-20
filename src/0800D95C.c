/* 0x0800D95C: complete 132-byte owner. */
#include "ffta.h"

struct Object0800C614 {
    u8 unknown_00[0x10];
    u16 active;
    void *data;
};

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} Struct0800C64C;

void *func_0800C614(const struct Object0800C614 *object);
void func_0800C64C(Struct0800C64C *object);
void func_0814186C(const void *source, void *destination, u32 control);

void func_0800D95C(void *object, u8 mode, u8 row, u8 column, u8 count,
                   s16 value)
{
    u16 *destination = 0;
    u16 fill;

    switch (mode) {
    case 0:
        destination = func_0800C614(object);
        break;
    case 1:
        destination = (u16 *)func_0800C614(object) + row * 160;
        break;
    case 2:
        destination = (u16 *)func_0800C614(object) + row * 160;
        break;
    }
    fill = value;
    func_0814186C(&fill, destination + column, 0x01000000 | count);
    func_0800C64C(object);
}
