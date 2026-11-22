#include "ffta.h"

/* Complete target: [0x0804393C, 0x08043DF4), 1208 bytes, 487 instructions. */

typedef struct {
    u8 unknown_00 : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[0x8d];
    u8 unknown_8e : 7;
    u8 refresh : 1;
    u8 special : 1;
    u8 unknown_8f : 7;
} MenuWindow0804393C;

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u16 selection;
    u8 unknown_12[0x86];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot0804393C;

typedef struct {
    void *owner;
    MenuWindow0804393C *window;
    u8 unknown_008[0x78];
    u8 mode;
    u8 unknown_081[0x0f];
    u16 *second_resource;
    u16 *first_resource;
    u8 unknown_098[0x4b8 - 0x98];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x984 - 0x4c4];
    MenuSlot0804393C slots[6];
    u8 unknown_e4c[0xf3e - 0xe4c];
    u8 display_mode;
} MenuContext0804393C;

typedef struct {
    u8 busy;
    u8 state;
    u8 priority : 3;
    u8 unknown_02 : 5;
    u8 unknown_03[2];
    u8 status;
    u8 unknown_06[8];
    u16 border_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[0x0a];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 field_48;
    u8 field_49;
    u8 field_4A;
    u8 field_4B;
} TileWindow0804393C;

extern MenuContext0804393C *g_state_03002810;
extern TileWindow0804393C data_030009E0[];
extern u8 *data_03002740[];
extern u8 data_0201F4E5;
extern u8 data_02003CB0[];
extern TileWindow0804393C *func_0808A268(u32 index, u8 mode,
    u16 *first_resource, u16 *second_resource, u8 *first_tiles,
    u8 *second_tiles, u8 *first_text, u8 *second_text,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08037C84(u32 index, void *panel, u32 renderer, u32 x,
                         u32 y, u32 row, u8 value, u32 enabled);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_0808A604(u32 renderer, u16 command);
extern u32 func_08040388(u32 index, u16 mask);
extern void func_08141540(u16 song_id);
extern void func_08141748(u16 fade);
extern void func_08035844(u32 mode);
extern void func_08043ECC(void *panel, u32 count);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

/* Statement macros, the agbcc-era do { } while (0) form of a multi-statement
 * macro.  LEAVE_TO_MODE is the body selections 0 and 1 share, written twice in
 * the ROM with only the mode differing (0x08043B7E-0x08043B94 sets 25,
 * 0x08043BC6-0x08043BDC sets 26).  SET_WINDOW_FLAGS sets the window's two flag
 * bits together (0x08043C0A-0x08043C28); src/08043468.c, src/0803BAE8.c and
 * src/0803D550.c set the same pair together.  The wrappers are byte-visible:
 * agbcc weights the references inside each loop twice when it ranks registers,
 * which puts the address of g_state_03002810 in sb ahead of the slot offset in
 * sl (0x0804394C, 0x08043956). */
#define LEAVE_TO_MODE(next)                     \
    do {                                        \
        func_08141748(3);                       \
        func_0808A604(5, 1);                    \
        g_state_03002810->mode = (next);        \
    } while (0)

#define SET_WINDOW_FLAGS(value)                     \
    do {                                            \
        g_state_03002810->window->flag_20 = (value);\
        g_state_03002810->window->flag_40 = (value);\
    } while (0)

void func_0804393C(u32 index)
{
    u8 width;
    u8 height;

    switch (g_state_03002810->slots[index].state) {
    case 0:
        g_state_03002810->active[index] = 0;
        /* The ROM sets 11 (0x08043996) before it loads the call's register
         * arguments (0x08043998), and builds field_4A's 6 (0x08043A1E)
         * before its address: both are the window size, held in locals. */
        width = 8;
        height = 11;
        func_0808A268(5, 12, g_state_03002810->first_resource,
            g_state_03002810->second_resource, data_03002740[5],
            data_03002740[5] + 0x108, data_03002740[5] + 0x210,
            data_03002740[5] + 0x318, 11, 3, width, height,
            11, 3, width, height, width, height);
        func_0808A604(5, 9);
        data_030009E0[5].x = 11;
        data_030009E0[5].y = 3;
        data_030009E0[5].border_tile = 0x24b;
        data_030009E0[5].state = 0;
        data_030009E0[5].field_48 = 1;
        data_030009E0[5].field_49 = 1;
        data_030009E0[5].field_4A = width - 2;
        data_030009E0[5].field_4B = height - 3;
        func_08043ECC(g_state_03002810->slots[index].source, 8);
        func_08037C84(index, g_state_03002810->slots[index].source,
                      5, 0, 0, 0, 0x83, 1);
        func_08016344(data_030009E0[5].second_plane,
            data_030009E0[5].width, data_030009E0[5].height,
            0xc0, data_030009E0[5].width, 5, 12);
        func_08016560(data_030009E0[5].first_plane, width, height, 0xc0,
                      width, 1, 12);
        func_08035678(0xc03e, func_0808B8E4(5, 1, 1, 1),
                      func_08018524(data_02003CB0, 0x3e, 3), 1);
        data_030009E0[5].status = 2;
        func_0808A604(5, 11);
        data_0201F4E5 = 1;
        g_state_03002810->slots[index].state = 0xfd;
        break;
    case 1:
        if (func_08040388(index, 0xffff) == 0xff) {
            g_state_03002810->slots[index].result = 6;
            g_state_03002810->slots[index].state = 0xff;
        } else if (g_state_03002810->slots[index].buttons & 1) {
            if (g_state_03002810->slots[index].selection == 0) {
                func_08141540(100);
                LEAVE_TO_MODE(25);
                g_state_03002810->slots[index].result = 6;
                g_state_03002810->slots[index].state = 0xfe;
            } else if (g_state_03002810->slots[index].selection == 1) {
                func_08141540(100);
                LEAVE_TO_MODE(26);
                g_state_03002810->slots[index].result = 6;
                g_state_03002810->slots[index].state = 0xfe;
            } else if (g_state_03002810->slots[index].selection == 2) {
                func_08141540(100);
                SET_WINDOW_FLAGS(0);
                data_030009E0[3].priority = 6;
                data_030009E0[2].priority = 6;
                func_08035844(0);
                g_state_03002810->window->refresh = 1;
                g_state_03002810->display_mode = 30;
                g_state_03002810->slots[index].buttons = 0;
                func_0808A604(5, 1);
                g_state_03002810->slots[index].result = 6;
                data_0201F4E5 = 0xfe;
                g_state_03002810->slots[index].state = 0xfd;
            } else if (g_state_03002810->slots[index].selection == 3) {
                g_state_03002810->window->special = 1;
                func_08035844(0);
                g_state_03002810->window->refresh = 1;
                g_state_03002810->display_mode = 30;
                g_state_03002810->slots[index].buttons = 0;
                func_0808A604(5, 1);
                g_state_03002810->slots[index].result = 6;
                data_0201F4E5 = 0xfe;
                g_state_03002810->slots[index].state = 0xfd;
            } else {
                func_0808A604(5, 10);
                data_0201F4E5 = 0xff;
                g_state_03002810->slots[index].state = 0xfd;
            }
        } else if (g_state_03002810->slots[index].buttons & 2) {
            func_08141540(105);
            data_030009E0[5].status = 3;
            func_0808A604(5, 13);
            data_0201F4E5 = 0xff;
            g_state_03002810->slots[index].state = 0xfd;
        } else if (g_state_03002810->slots[index].result == 3) {
            func_0808A604(5, 2);
        }
        break;
    case 0xfd:
        if (!data_030009E0[5].busy)
            g_state_03002810->slots[index].state = data_0201F4E5;
        break;
    case 0xfe:
        g_state_03002810->closed[index] = 0;
        break;
    case 0xff:
        g_state_03002810->closed[index] = 0;
        break;
    }
}
