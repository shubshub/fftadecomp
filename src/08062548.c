#include "ffta.h"

typedef struct Entry08062548 Entry08062548;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 selection;
    u8 unknown_50[8];
    s32 mode;
    u8 unknown_5C[0x10];
    u8 input[0x7E];
    s16 requested_mode;
    u8 unknown_EC[0x79C];
    Entry08062548 *entry;
} State08062548;

typedef struct {
    Entry08062548 *current;
} Cache08062548;

extern State08062548 *data_0200F450;
extern Cache08062548 g_state_020020D0;
extern u8 func_080C73D8(void *context);
extern void func_080C71B4(u16 request);
extern u8 func_080C9540(u16 bit_index);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern Entry08062548 *func_08061C9C(void);

/* 0x08062548..0x0806261C: 212 bytes, 89 instructions. */
void func_08062548(void)
{
    Entry08062548 *entry;

    switch (func_080C73D8(data_0200F450->input)) {
    case 2:
        data_0200F450->current = 0x44;
        data_0200F450->entries[data_0200F450->count++] = 0x44;
        data_0200F450->current = 0x34;
        data_0200F450->entries[data_0200F450->count++] = 0x34;
        data_0200F450->current = 0x36;
        break;
    case 0:
        func_080C71B4(3);
        if (func_080C9540(0x243))
            func_080C9574(0x3A, 1);

        if (data_0200F450->requested_mode != data_0200F450->mode) {
            data_0200F450->selection = 0xAC;
            switch (data_0200F450->mode) {
            case 1:
                data_0200F450->selection = 0xAC;
                break;
            case 2:
                data_0200F450->selection = 0xB8;
                break;
            case 3:
                data_0200F450->selection = 0xC0;
                break;
            }
            data_0200F450->current = 0x2F;
        } else {
            entry = func_08061C9C();
            g_state_020020D0.current = entry;
            data_0200F450->entry = entry;
            data_0200F450->current = 7;
        }
        break;
    }
}
