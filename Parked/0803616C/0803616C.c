#include "ffta.h"

struct MapEntry0803616C {
    u8 x;
    u8 y;
    u8 unknown_02[0x12];
};

struct MapState0803616C {
    u8 unknown_00[0x67C];
    struct MapEntry0803616C *entries;
    u8 unknown_680[0x8BC];
    u8 dwell;
};

extern struct MapState0803616C *g_state_03002810;
extern u8 data_02002E58[];

/* Complete [0x0803616C, 0x08036282): 278 bytes, 129 instructions. */
u32 func_0803616C(s16 *x, s16 *y)
{
    s32 i = 0;
    u8 *enabled = data_02002E58;
    u32 id = 1;

    for (; i < 30; id++, i++) {
        struct MapEntry0803616C *entry = &g_state_03002810->entries[i];
        s32 entry_x = entry->x * 8;
        s32 entry_y;

        if (*x < entry_x - 4 || *x > entry_x + 20)
            continue;
        entry_y = entry->y * 8;
        if (*y < entry_y - 8 || *y > entry_y + 16)
            continue;
        if (!(enabled[0] & 1) && i == 8)
            return 0;
        if (!(enabled[0] & 2) && i == 27)
            return 0;
        if (*x == entry_x + 8 && *y == entry_y + 8) {
            if (g_state_03002810->dwell < 30)
                g_state_03002810->dwell++;
        } else if (g_state_03002810->dwell == 0) {
            if (*x < entry_x + 8)
                (*x)++;
            else if (*x > entry_x + 8)
                (*x)--;
            if (*y < entry_y + 8)
                (*y)++;
            else if (*y > entry_y + 8)
                (*y)--;
        }
        return id;
    }
    return 0;
}
