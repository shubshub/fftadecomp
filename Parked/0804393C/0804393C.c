#include "ffta.h"

/* 0x0804393C..0x08043DF4: 1208 bytes / 487 instructions. */
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
    u8 unknown_00[0x30];
    u16 object_id;
    u8 result;
    u8 state;
    u8 unknown_34[0x0a];
    u16 buttons;
    u16 selection;
    u8 unknown_42[0x86];
    void *source;
} MenuSlot0804393C;

typedef struct {
    void *owner;
    MenuWindow0804393C *window;
    u8 unknown_08[0x78];
    u8 mode;
    u8 unknown_81[0x0f];
    u16 *second_resource;
    u16 *first_resource;
    u8 unknown_98[0x420];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x490];
    MenuSlot0804393C slots[6];
    u8 unknown_e1c[0x122];
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
    u16 tile_attributes;
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
    u8 first_enabled;
    u8 second_enabled;
    u8 first_style;
    u8 second_style;
} TileRenderer0804393C;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} TileStorage0804393C;

extern MenuContext0804393C *g_state_03002810;
extern TileRenderer0804393C data_030009E0[];
extern TileStorage0804393C data_03002740;
extern u8 data_0201F4E5;
extern u8 data_02003CB0[];
extern void func_0808A268(u32, u32, u16 *, u16 *, u16 *, u16 *,
                         u16 *, u16 *, u32, u32, u32, u32,
                         u32, u32, u32, u32, u32, u32);
extern void func_0808A604(u32, u32);
extern void func_08043ECC(void *, u32);
extern void func_08037C84(s32, void *, u32, u32, u32, u32, u32, u32);
extern void func_08016344(void *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(void *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32, u32, s32, s32);
extern u32 func_08018524(u8 *, u16, u8);
extern void func_08035678(u16, u16 *, u32, u16);
extern u32 func_08040388(s32, u16);
extern void func_08141540(u32);
extern void func_08141748(u32);
extern void func_08035844(u32);

void func_0804393C(s32 index)
{
    switch (g_state_03002810->slots[index].state) {
    case 0:
        g_state_03002810->active[index] = 0;
        func_0808A268(5, 12, g_state_03002810->first_resource,
            g_state_03002810->second_resource, data_03002740.tiles,
            data_03002740.tiles + 0x84, data_03002740.tiles + 0x108,
            data_03002740.tiles + 0x18c, 11, 3, 8, 11, 11, 3, 8, 11, 8, 11);
        func_0808A604(5, 9);
        data_030009E0[5].x = 11;
        data_030009E0[5].y = 3;
        data_030009E0[5].tile_attributes = 0x24b;
        data_030009E0[5].state = 0;
        data_030009E0[5].first_enabled = 1;
        data_030009E0[5].second_enabled = 1;
        data_030009E0[5].first_style = 6;
        data_030009E0[5].second_style = 8;
        func_08043ECC(g_state_03002810->slots[index].source, 8);
        func_08037C84(index, g_state_03002810->slots[index].source,
                      5, 0, 0, 0, 0x83, 1);
        func_08016344(data_030009E0[5].second_plane,
            data_030009E0[5].width, data_030009E0[5].height, 0xc0,
            data_030009E0[5].width, 5, 12);
        func_08016560(data_030009E0[5].first_plane, 11, 3, 0xc0, 8, 1, 12);
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
                func_08141748(3);
                func_0808A604(5, 1);
                g_state_03002810->mode = 25;
                g_state_03002810->slots[index].result = 6;
                g_state_03002810->slots[index].state = 0xfe;
            } else if (g_state_03002810->slots[index].selection == 1) {
                func_08141540(100);
                func_08141748(3);
                func_0808A604(5, 1);
                g_state_03002810->mode = 26;
                g_state_03002810->slots[index].result = 6;
                g_state_03002810->slots[index].state = 0xfe;
            } else if (g_state_03002810->slots[index].selection == 2) {
                func_08141540(100);
                g_state_03002810->window->flag_20 = 0;
                g_state_03002810->window->flag_40 = 0;
                data_030009E0[3].priority = 6;
                data_030009E0[2].priority = 6;
                func_08035844(0);
                g_state_03002810->window->refresh = 1;
                g_state_03002810->display_mode = 30;
                g_state_03002810->slots[index].selection = 0;
                func_0808A604(5, 1);
                g_state_03002810->slots[index].result = 6;
                data_0201F4E5 = 0xfe;
                g_state_03002810->slots[index].state = 0xfd;
            } else if (g_state_03002810->slots[index].selection == 3) {
                g_state_03002810->window->special = 1;
                func_08035844(0);
                g_state_03002810->window->refresh = 1;
                g_state_03002810->display_mode = 30;
                g_state_03002810->slots[index].selection = 0;
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
