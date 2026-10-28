#include "ffta.h"

typedef struct {
    u8 *table;
} RecordContext080376AC;

extern RecordContext080376AC *g_state_03002810;

s32 func_080376AC(u8 start)
{
    s32 index;

    for (index = start; index < 30; index++) {
        u8 *flags = g_state_03002810->table + index * 12 + 0xB1;

        if ((*flags & 0x11) == 0x11) {
            *flags ^= 0x10;
            return index + 1;
        }
    }

    return 0;
}
