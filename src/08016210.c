#include "ffta.h"

/* 0x08016210..0x08016234: 36 bytes. */
typedef struct {
    u8 unknown_00[0x12];
    u8 width;
    u8 height;
} Window08016210;

extern void func_08015C90(void *object, const void *content, u8 width,
                        u8 height, u16 first, u16 second);

void func_08016210(void *object, const void *content, u16 first, u16 second)
{
    const Window08016210 *window = object;

    func_08015C90(object, content, window->width, window->height, first, second);
}
