#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u8 width;
    u8 height;
    u8 unknown_0e[6];
    const void *data;
} Image0806FFE4;

extern void func_0814186C(const void *source, void *destination, u32 size);

/* 0x0806FFE4..0x0806FFF8: 20 bytes, 9 instructions. */
void func_0806FFE4(const Image0806FFE4 *image, void *destination)
{
    func_0814186C(image->data, destination, image->width * image->height);
}
