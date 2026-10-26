#include "ffta.h"

typedef struct {
    u8 unknown_00[0xc8];
    void *data;
} Record0804A4CC;

typedef struct {
    u8 unknown_00[0x90];
    void *graphics;
    void *palette;
    u8 unknown_98[0x8bc];
    Record0804A4CC records[1];
} State0804A4CC;

typedef struct {
    u8 unknown_00[0x18];
    u8 *data;
} Resource0804A4CC;

typedef struct {
    u8 unknown_00;
    u8 state;
    u8 unknown_02[0xc];
    u16 text_offset;
    u8 unknown_10[8];
    u16 *first_map;
    u16 *second_map;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[2];
    s8 x;
    s8 y;
    u8 unknown_2e[6];
    u8 inner_width;
    u8 inner_height;
    u8 unknown_36[0x12];
    u8 enabled_a;
    u8 enabled_b;
    s8 inner_x;
    s8 inner_y;
} Object0804A4CC;

extern u8 data_02003CB0[];
extern State0804A4CC *g_state_03002810;
extern Resource0804A4CC data_03002740;
extern Object0804A4CC data_030009E0[];
extern void func_0808A268(u32, u32, void *, void *, const void *,
                          const void *, u32, u32, u32, u32, u32, u32,
                          u32, u32, u32, u32, u32, u32);
extern void func_08016344(u16 *, u8, u8, u32, u32, u32, u32);
extern void func_08016560(u16 *, u32, u32, u32, u32, u32, u32);
extern void func_0808AA18(u32);
extern u16 *func_0808B8E4(u32, u32, u32, u32);
extern u32 func_08018524(u8 *, u32, u32);
extern void func_08035678(u32, u16 *, u32, u32);
extern void func_08037C84(s32, void *, u32, u32, u32, u32, u32, u32);

/* 0x0804A4CC..0x0804A6B0: 484 bytes, 199 instructions. */
void func_0804A4CC(s32 index, s32 mode)
{
    u8 *text = data_02003CB0;

    func_0808A268(6, 12, g_state_03002810->palette,
                  g_state_03002810->graphics,
                  data_03002740.data, data_03002740.data + 0x1c2,
                  0, 0, 16, 5, 15, 15, 16, 5, 15, 15, 15, 15);
    func_08016344(data_030009E0[6].second_map + 1,
                  data_030009E0[6].width - 2,
                  data_030009E0[6].height, 0xc0,
                  data_030009E0[6].width, 5, 12);
    func_08016560(data_030009E0[6].first_map + 1,
                  13, 15, 0xc0, 15, 1, 12);
    func_0808AA18(6);
    if (mode == 1) {
        func_08035678(0xc044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 15), 1);
    } else if (mode == 2) {
        func_08035678(0xc044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 16), 1);
    } else {
        func_08035678(0xc044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 10), 1);
    }
    data_030009E0[6].inner_width = 16;
    data_030009E0[6].inner_height = 5;
    data_030009E0[6].x = 13;
    data_030009E0[6].y = 12;
    data_030009E0[6].text_offset = data_030009E0[6].x +
                                  (data_030009E0[6].y + 1) * 32;
    data_030009E0[6].state = 0;
    data_030009E0[6].enabled_a = 1;
    data_030009E0[6].enabled_b = 1;
    data_030009E0[6].inner_x = 13;
    data_030009E0[6].inner_y = 14;
    func_08037C84(index, g_state_03002810->records[index].data,
                  6, 0, 0, 0, 11, 0);
}
