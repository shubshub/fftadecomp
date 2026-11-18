#include "ffta.h"

/* Field names at 0x09, 0x1A, 0x1E and 0xD6 follow src/0802C270.c. */
typedef struct {
    u8 unknown_00[4];
    u8 enabled;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07[2];
    u8 level;
    u8 unknown_0a[0x10];
    u16 first;
    u8 unknown_1c[2];
    u16 second;
    u8 unknown_20[0xb6];
    u16 value;
    u8 unknown_d8[0x30];
} Unit08071DC8;

typedef struct {
    u8 unknown_00[0x80];
    Unit08071DC8 units[24];
} UnitTable08071DC8;

typedef struct {
    s32 key;
    s32 value;
} SortEntry08071DC8;

extern UnitTable08071DC8 g_state_02000000;
extern void func_08087D98(SortEntry08071DC8 *entries, s32 left, s32 right, s32 descending);

/* Complete [0x08071DC8, 0x08072130), 872 bytes and 392 reachable instructions. */
void func_08071DC8(u8 mode, u8 *order)
{
    SortEntry08071DC8 list[24];
    s32 i;
    u8 count;
    s32 descending = (mode >> 7) ^ 1;

    for (i = 0; i < 24; i++)
        order[i] = 0xFF;

    switch (mode & 0x7F) {
    case 1: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = (g_state_02000000.units[i].level << 8) + i;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    case 2: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = (g_state_02000000.units[i].first << 8) + i;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    case 3: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = (g_state_02000000.units[i].second << 8) + i;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    case 4: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = (g_state_02000000.units[i].value << 8) + i;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    case 5: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = (g_state_02000000.units[i].unknown_06 << 8) + i;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    case 6: {
        u8 n = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].enabled) {
                list[n].key = g_state_02000000.units[i].enabled;
                list[n++].value = i;
            }
        }
        count = n;
        func_08087D98(list, 0, count - 1, descending);
        for (i = 0; i < count; i++)
            order[i] = list[i].value;
        break;
    }
    default: {
        u8 n = 0;
        u8 last = 0;
        if (descending) {
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].enabled)
                    last++;
            }
            last--;
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].enabled)
                    order[n++] = last - i;
            }
        } else {
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].enabled)
                    order[n++] = i;
            }
        }
        break;
    }
    }
}
