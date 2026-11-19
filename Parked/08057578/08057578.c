#include "control_flags.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid;

typedef struct {
    u8 unknown_00[4];
    u8 field_04;
    u8 unknown_05[0x23];
    u16 field_28;
    u8 unknown_2A[0xC6];
    u8 field_F0;
    u8 unknown_F1[0x11];
    u8 field_102;
    u8 field_103;
    u8 unknown_104[4];
} MenuUnitRecord;

typedef struct {
    u8 unknown_0000[0x80];
    MenuUnitRecord records[24];
    u8 unknown_1940[0x167A];
    u8 coarse;
    u8 fine;
} MenuUnitTable;

typedef struct {
    u8 unknown_0000[0xCD4];
    u8 window[0x7A4];
    Table runner;
    u8 unknown_1488[0x540];
    u8 text_state[0x1396];
    u16 back_tiles[20];
    s16 front_tiles[20];
    u8 panel_x;
    u8 unknown_2DAF[5];
    u8 saved_control[0x50];
    u16 unit_index;
    u8 timer;
    u8 unknown_2E07[0x59];
    u16 blend_lines[160];
} MenuContext;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern MenuContext *data_0200F428;
extern MenuUnitTable g_state_02000000;
extern TileGrid data_030008B0;
extern TileGrid data_03000990;
extern InputState data_03000000;
extern BufferCopier data_0836D4BC[];
extern const u8 data_0839380E[];

extern u8 func_0802B548(u8 *window);
extern void func_0802B53C(u8 *window, u8 value);
extern void func_0802B554(u8 *window, u8 value);
extern void func_0802B2E8(TileGrid *grid, u8 x, u8 y, u8 width, u8 height);
extern void func_0802B4A8(TileGrid *grid, s32 x, s32 y, const u16 *source,
                          u8 width, u8 height);
extern void func_08057B90(u8 channel, u16 *buffer, u8 split, u16 first,
                          u16 second);
extern void func_0805862C(void *context, u8 *tiles, u8 value);
extern void func_080586E0(u16 *entries);
extern void func_0805868C(s16 *tiles, u16 firstTile);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_080D2E60(void);
extern void func_08057C88(void);
extern void func_08141540(u16 sound);
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 column, s16 row, u8 enabled);
extern void func_08000D90(u32 handle);
extern void func_08055F10(u8 index, u8 *state);

/* Complete target: [0x08057578, 0x08057B90), 1560 bytes, 599 instructions. */
void func_08057578(u8 index, u8 *state)
{
    u8 i;

    switch (*state) {
    case 0:
        if (func_0802B548(data_0200F428->window) == 5)
            func_0802B53C(data_0200F428->window, 4);
        else
            func_0802B53C(data_0200F428->window, 1);
        func_0802B554(data_0200F428->window, 0x69);
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.records[i].field_04 == 2
                || g_state_02000000.records[i].field_04 == 15) {
                data_0200F428->unit_index = i;
                break;
            }
        }
        *state = 1;
        break;
    case 1:
        if (func_0802B548(data_0200F428->window) == 0) {
            func_0802B2E8(&data_030008B0, 20, 17, 10, 3);
            func_0802B2E8(&data_03000990, 20, 17, 10, 3);
            data_0836D4BC[0](data_0200F428->saved_control, &g_control_flags_03000940,
                             sizeof(g_control_flags_03000940));
            *state = 20;
        }
        break;
    case 20:
        g_control_flags_03000940.display |= 0x6000;
        g_control_flags_03000940.winin_hi = 0x3F;
        g_control_flags_03000940.winin_lo = 0;
        g_control_flags_03000940.winout_lo = 0;
        g_control_flags_03000940.bldcnt_lo = 0xD3;
        func_08057B90(3, data_0200F428->blend_lines, 135, 0xD3, 0xC3);
        g_control_flags_03000940.bldy_lo = 0;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 240;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 160;
        *state = 21;
        break;
    case 21:
        g_control_flags_03000940.bldy_lo++;
        if (g_control_flags_03000940.bldy_lo == 9)
            *state = 100;
        break;
    case 100:
        func_0805862C(data_0200F428->text_state, (u8 *)0x06009CE0, g_state_02000000.fine);
        func_080586E0(data_0200F428->back_tiles);
        func_0805868C(data_0200F428->front_tiles, 0xE7);
        data_0200F428->panel_x = 31;
        *state = 101;
        break;
    case 101:
        data_0200F428->panel_x--;
        func_0802B4A8(&data_030008B0, (s8)data_0200F428->panel_x, 17,
                      data_0200F428->front_tiles, 10, 2);
        func_0802B4A8(&data_03000990, (s8)data_0200F428->panel_x, 17,
                      data_0200F428->back_tiles, 10, 2);
        if (data_0200F428->panel_x <= 20) {
            *state = 120;
            data_0200F428->timer = 0;
        }
        func_08001F34(data_0839380E, data_0200F428->panel_x * 8, 136, 0, 0, 0, 0, 0,
                      (g_state_02000000.coarse - 1) * 12, 0, 0);
        break;
    case 120:
        data_0200F428->timer++;
        if (data_0200F428->timer >= 30) {
            data_0200F428->timer = 0;
            if (g_state_02000000.records[data_0200F428->unit_index].field_F0 == 0) {
                *state = 140;
                break;
            }
            g_state_02000000.records[data_0200F428->unit_index].field_F0--;
            func_080D2E60();
            func_08057C88();
            func_0805862C(data_0200F428->text_state, (u8 *)0x06009CE0, g_state_02000000.fine);
            func_08141540(0x68);
        }
        func_08001F34(data_0839380E, data_0200F428->panel_x * 8, 136, 0, 0, 0, 0, 0,
                      (g_state_02000000.coarse - 1) * 12, 0, 0);
        break;
    case 140:
        data_0200F428->panel_x++;
        func_0802B2E8(&data_030008B0, 20, 17, data_0200F428->panel_x - 20, 4);
        func_0802B2E8(&data_03000990, 20, 17, data_0200F428->panel_x - 20, 4);
        func_0802B4A8(&data_030008B0, (s8)data_0200F428->panel_x, 17,
                      data_0200F428->front_tiles, 10, 2);
        func_0802B4A8(&data_03000990, (s8)data_0200F428->panel_x, 17,
                      data_0200F428->back_tiles, 10, 2);
        if (data_0200F428->panel_x > 31)
            *state = 200;
        func_08001F34(data_0839380E, data_0200F428->panel_x * 8, 136, 0, 0, 0, 0, 0,
                      (g_state_02000000.coarse - 1) * 12, 0, 0);
        break;
    case 200:
        g_control_flags_03000940.bldy_lo--;
        if (g_control_flags_03000940.bldy_lo == 0) {
            g_state_02000000.records[data_0200F428->unit_index].field_102 = 0;
            g_state_02000000.records[data_0200F428->unit_index].field_103 = 0;
            g_state_02000000.records[data_0200F428->unit_index].field_F0 = 0;
            g_state_02000000.records[data_0200F428->unit_index].field_28 &= ~0x10;
            g_state_02000000.records[data_0200F428->unit_index].field_28 &= ~0x08;
            data_0836D4BC[0](&g_control_flags_03000940, data_0200F428->saved_control,
                             sizeof(g_control_flags_03000940));
            func_08029E48(&data_030008B0, &data_03000990, 0, 20, 17, 1);
            func_0802B53C(data_0200F428->window, 1);
            func_0802B554(data_0200F428->window, 0x6A);
            *state = 220;
            func_08000D90(3);
        }
        break;
    case 220:
        if (func_0802B548(data_0200F428->window) == 5 && (data_03000000.pressed & 1))
            *state = 0xFF;
        break;
    case 0xFF:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_08055F10);
        break;
    }
}
