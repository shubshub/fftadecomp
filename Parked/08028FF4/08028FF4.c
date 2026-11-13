#include "ffta.h"

// Complete [0x08028FF4, 0x08029188): 404 bytes.

typedef struct {
    u16 mode;
} MenuEvent;

typedef struct {
    s16 result;
    u8 confirmed;
    u8 unknown_03[0x480 - 3];
    u8 order[6];
} MenuShared;

typedef struct {
    u8 unknown_0000[0x2190];
    u8 phase;
    u8 unknown_2191[0x2FC1 - 0x2191];
    u8 unknown_2FC1_0 : 2;
    u8 category : 3;
    u8 unknown_2FC1_5 : 3;
    u8 unknown_2FC2[0x3C2A - 0x2FC2];
    u8 entry;
} GlobalState;

typedef struct {
    u8 unknown_00[7];
    u8 locked;
    u8 unknown_08[4];
} TableEntry;

extern MenuShared *data_0200F438;
extern GlobalState g_state_02000000;
extern const TableEntry g_table_08563A70[];
extern u8 func_080C9540(u16 bit_index);
extern u8 func_080C95A8(u32 selector);
extern u8 func_08027AE8(void);
extern void *func_08096D7C(void);
extern u32 func_08099544(void *state);
extern void func_08141570(s32 player_id, u16 song_id);

u32 func_08028FF4(void *owner, MenuEvent *event)
{
    switch (event->mode) {
    case 0:
        data_0200F438->order[0] = 1;
        data_0200F438->order[1] = 2;
        data_0200F438->order[2] = 3;
        data_0200F438->order[3] = 4;
        data_0200F438->order[4] = 5;
        data_0200F438->order[5] = 6;
        break;
    case 1:
        break;
    case 0x100:
        {
            const TableEntry *entry;

            data_0200F438->result = g_state_02000000.category + 1;
            switch (g_state_02000000.category) {
            case 2:
                if (func_080C9540(2) || !func_08027AE8())
                    data_0200F438->result = -1;
                break;
            case 4:
                entry = &g_table_08563A70[g_state_02000000.entry];
                if (func_080C9540(2) || !func_08099544(func_08096D7C()) ||
                    g_state_02000000.phase == 2 || entry->locked)
                    data_0200F438->result = -1;
                break;
            case 5:
                if (func_080C95A8(13) == 1 || func_080C9540(2))
                    data_0200F438->result = -1;
                break;
            case 1:
                if (func_080C9540(2))
                    data_0200F438->result = -1;
                break;
            case 0:
            case 3:
                break;
            }
            if (data_0200F438->result == -1)
                func_08141570(1, 0x6B);
            event->mode = 0x104;
        }
        break;
    case 0x104:
        data_0200F438->confirmed = 1;
        event->mode = 3;
        break;
    }
    return 0;
}
