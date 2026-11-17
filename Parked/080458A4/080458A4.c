#include "ffta.h"

// Complete [0x080458A4, 0x08045B04): 608 bytes, 245 instructions.

typedef struct {
    u8 unknown_00[0x90];
    void *buffer_90;
    void *buffer_94;
    u8 unknown_98[0xbb4];
    u8 text_context[0];
} MenuState;

typedef struct {
    u8 unknown_00[0x18];
    u8 *buffers;
} MenuBuffers;

typedef struct {
    u8 unknown_00[0x0e];
    u16 tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[2];
    u8 columns;
    u8 rows;
    u8 unknown_2e[0x1e];
} TileRenderer;

extern MenuState *g_state_03002810;
extern MenuBuffers data_03002740;
extern TileRenderer data_030009E0[];
extern u16 data_0600C9E0[];
extern const u8 *data_085668B0[];
extern const u8 data_08391918[];

extern void *func_0808A268(s32, u8, void *, void *, void *, void *, void *, void *,
                          u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_0808AA18(s32);
extern void func_08016800(void *, u8, u8, u16, u8, u16, u16, u8);
extern u16 *func_0808B8E4(u32, u32, s32, s32);
extern void func_0808B7C0(int, u16 *, u16, u16, u16);
extern void func_0814186C(const void *, void *, u32);
extern u8 *func_0808B92C(u32 index, u8 *tiles, u32 column, u32 row);
extern u16 func_08015110(void *, void *, const u8 *, u8, u8);
extern s32 func_08038858(u16 id, u8 kind, u16 quantity);
extern const u8 *func_08037A30(u32 window, u8 *tiles, s32 x, s32 y, u16 index,
                               const u8 *initial_text, s32 kind, s32 orientation, u8 mode);
extern u16 func_080161BC(const u8 *text);
extern void func_080142DC(u16 *destination, u32 value, u32 digits);

void func_080458A4(u16 id, u8 count)
{
    func_0808A268(6, 12, g_state_03002810->buffer_94,
                 g_state_03002810->buffer_90,
                 data_03002740.buffers, data_03002740.buffers + 0x150,
                 data_03002740.buffers + 0x2a0, data_03002740.buffers + 0x3f0,
                 1, 8, 28, 6, 1, 8, 28, 6, 28, 6);
    func_0808AA18(6);
    func_08016800(data_030009E0[6].first_plane,
                  data_030009E0[6].width, data_030009E0[6].height,
                  0x800, data_030009E0[6].width, 13, 3, 11);
    data_030009E0[6].tile = 0x24f;
    data_030009E0[6].columns = 28;
    data_030009E0[6].rows = 4;
    func_0808B7C0(6, func_0808B8E4(6, 1, 0, 1), 0x24f, 28, 0xb000);
    func_0808B7C0(6, func_0808B8E4(6, 1, 0, 3), 0x24f + 56, 28, 0xb000);
    {
        u16 fill;
        u16 *source = &fill;
        *source = 0;
        func_0814186C(source, data_0600C9E0, 0x01000700);
    }
    func_08015110(g_state_03002810->text_context,
                  func_0808B92C(6, (u8 *)data_0600C9E0, 2, 0),
                  data_085668B0[16], 5, 1);
    if (id > 0x177) {
        u16 item = id - 0x177;

        func_08038858(item, 1, 1);
        func_08037A30(6, (u8 *)data_0600C9E0, 2, 2, item, 0, 1, 1, 1);
    } else {
        u16 width;
        u16 digits[8];
        s32 i;

        func_08038858(id, 0, count);
        width = func_080161BC(func_08037A30(6, (u8 *)data_0600C9E0, 2, 2, id,
                                            0, 0, 1, 1));
        func_080142DC(digits, count, 2);
        for (i = 0; i < 2; i++) {
            if (digits[i] == 0x1881)
                digits[i] = 0x7340;
            else
                break;
        }
        func_08015110(g_state_03002810->text_context,
                      func_0808B92C(6, (u8 *)data_0600C9E0, width + 4, 2),
                      data_08391918, 1, 1);
        func_08015110(g_state_03002810->text_context,
                      func_0808B92C(6, (u8 *)data_0600C9E0, width + 5, 2),
                      (const u8 *)digits, 1, 1);
    }
}
