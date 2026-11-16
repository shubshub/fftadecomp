#include "ffta.h"

/* Complete target [0x08072130, 0x080725B8): 1160 bytes, 580 instructions. */

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07[2];
    u8 unknown_09;
    u8 unknown_0a[0x10];
    u16 unknown_1a;
    u8 unknown_1c[2];
    u16 unknown_1e;
    u8 unknown_20[0xB6];
    u16 unknown_d6;
    u8 unknown_d8[0x30];
} Unit08072130;

typedef struct {
    u8 unknown_00[0x80];
    Unit08072130 units[24];
} GlobalState08072130;

typedef struct {
    s32 key;
    s32 value;
} SortEntry08072130;

typedef struct {
    u8 flags;
    u8 status;
    u16 item;
    u16 column;
    u16 row;
    u16 x;
    u16 y;
    u8 unknown_0c[8];
} GridSlot;

typedef struct __attribute__((packed, aligned(4))) {
    u8 unknown_000[0x95C];
    u8 count;
    u8 unknown_95d[0x5D];
    u8 availability[24];
    u8 unknown_9d2[0x1C];
    GridSlot slots[24];
} GridState;

extern GlobalState08072130 g_state_02000000;
extern GridState *data_03002818;
extern void func_080891BC(void);
extern void func_08087D98(SortEntry08072130 *entries, s32 left, s32 right, s32 descending);

void func_08072130(u8 mode, u8 *order)
{
    SortEntry08072130 entries[24];
    s32 descending = !(mode & 0x80);
    s32 i;
    s32 rank;

    func_080891BC();
    for (i = 0; i < 24; i++)
        order[i] = 0xFF;

    rank = 1;
    for (i = 0; i < 24; i++) {
        if (g_state_02000000.units[i].active)
            data_03002818->slots[i].status = rank++;
    }

    switch (mode & 0x7F) {
    case 1: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = (g_state_02000000.units[i].unknown_09 << 8) + i;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    case 2: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = (g_state_02000000.units[i].unknown_1a << 8) + i;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    case 3: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = (g_state_02000000.units[i].unknown_1e << 8) + i;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    case 4: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = (g_state_02000000.units[i].unknown_d6 << 8) + i;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    case 5: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = (g_state_02000000.units[i].unknown_06 << 8) + i;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    case 6: {
        u8 n = 0;

        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active) {
                entries[n].key = g_state_02000000.units[i].active;
                entries[n++].value = i;
            }
        }
        data_03002818->count = n;
        func_08087D98(entries, 0, n - 1, descending);
        for (i = 0; i < data_03002818->count; i++)
            order[i] = entries[i].value;
        break;
    }
    default: {
        u8 n = 0;
        u8 count = 0;

        if (descending) {
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].active)
                    count++;
            }
            count--;
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].active)
                    order[n++] = count - i;
            }
        } else {
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].active)
                    order[n++] = i;
            }
        }
        break;
    }
    }
}
