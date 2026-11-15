#include "ffta.h"

/* Complete target: [0x0802B07C, 0x0802B108), 140 bytes, 58 instructions.
 *
 * Scrolls the list's halfword buffer by width * 2 halfwords through the
 * scratch buffer data_02003CB0.  Direction 0x80 copies everything after the
 * first width * 2 halfwords to the front and increments the position;
 * direction 0x40 copies everything before the last width * 2 halfwords back
 * by that much and decrements the position.
 *
 * Target bytes:
 *   f0b5474680b4051c09040b0c0f488046697da87d400048430004040c261c4a00171c802b
 *   16d15100e8684018a41a08490c404146221c16f1dbfbe9684046221c16f1d6fb688b0130
 *   17e00000b03c0002ffff1f00402b11d1e868f41b0a490c404146221c16f1c4fb7800e968
 *   09184046221c16f1bdfb688b0138688308bc9846f0bc01bc00470000ffff1f00
 */
typedef struct {
    u8 unknown_00[0xC];
    u16 *buffer;
    u8 unknown_10[5];
    u8 width;
    u8 height;
    u8 unknown_17[3];
    u16 position;
} MenuList;

extern u16 data_02003CB0[];
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0802B07C(MenuList *list, u16 direction)
{
    u16 *temporary = data_02003CB0;
    s32 width = list->width;
    s32 rows = list->height * 2;
    u16 total = width * rows;
    u16 stride = width * 2;

    /* Each count is the copy's byte size converted to a halfword count. */
    if (direction == 0x80) {
        func_0814186C(list->buffer + stride, temporary,
                      (((total - stride) * 2) >> 1) & 0x1FFFFF);
        func_0814186C(temporary, list->buffer,
                      (((total - stride) * 2) >> 1) & 0x1FFFFF);
        list->position++;
    } else if (direction == 0x40) {
        func_0814186C(list->buffer, temporary,
                      (((total - stride) * 2) >> 1) & 0x1FFFFF);
        func_0814186C(temporary, list->buffer + stride,
                      (((total - stride) * 2) >> 1) & 0x1FFFFF);
        list->position--;
    }
}
