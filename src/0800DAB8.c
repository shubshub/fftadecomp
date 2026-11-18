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

// Complete [0x0800DAB8, 0x0800DB0A): 82 bytes, 41 instructions.
void func_0800DAB8(void *object, s16 index, u8 count, u8 low, u8 high)
{
    u16 fill;

    if (index <= 159) {
        u16 *destination = func_0800C614(object);
        u16 *source = &fill;

        *source = (high << 8) | low;
        func_0814186C(source, destination + index, 0x01000000 | count);
        func_0800C64C(object);
    }
}
