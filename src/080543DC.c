#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 offset;
    u8 unknown_10;
    u8 row;
} MenuCursor;

void func_080543DC(MenuCursor *cursor, u8 row)
{
    cursor->row = row;
    cursor->offset = row * 24;
}
