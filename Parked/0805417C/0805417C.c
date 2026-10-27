#include "ffta.h"

/* 0x0805417C..0x080541AE: 50 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 top;
} ScrollList;

u8 func_0805417C(ScrollList *list, u16 keys)
{
    if (keys == 0x40) {
        if (list->top != 0)
            return 1;
    } else if (keys == 0x80) {
        if (list->top + 4 < list->count)
            return 1;
    }
    return 0;
}
