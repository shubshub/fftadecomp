#include "ffta.h"

/* Complete target [0x081380B8, 0x08138284): 460 bytes, 184 instructions. */

typedef struct {
    u8 unknown_00[0x10];
    const void *second;
    const void *first;
    u8 unknown_18[0xF9C - 0x18];
    u8 text_state[0x2155 - 0xF9C];
    u8 options;
} Sources081380B8;

typedef struct {
    u8 unknown_00[0x08];
    u16 *tiles;
} Buffers081380B8;

typedef struct {
    u8 unknown_00[0x0e];
    u16 tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 height;
    u8 unknown_2a[10];
    u8 x;
    u8 y;
    u8 unknown_36[22];
} Window081380B8;

extern Sources081380B8 *data_030027D8;
extern Buffers081380B8 data_03002740;
extern Window081380B8 data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_0600B560[];
extern const u8 *const data_085668B0[];

void *func_0808A268(s32 index, u8 kind, const void *first,
    const void *second, u16 *first_tiles, u16 *second_tiles,
    void *third, void *fourth, u8 left, u8 top, u8 width, u8 height,
    u8 x, u8 y, u8 first_width, u8 first_height, u8 second_width,
    u8 second_height);
void func_0814186C(const void *source, void *destination, u32 control);
void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                   u8 stride, u16 tile, u8 palette);
void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                   u8 stride, u16 tile, u8 palette);
u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
void func_0808B7C0(s32 index, u16 *destination, u16 tile, u16 count,
                   u16 flags);
void func_08015110(void *context, void *destination, const void *text,
                   u32 style, u32 spacing);
u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

void func_081380B8(void)
{
    u16 zero;
    s32 row;
    u32 enabled;
    const u8 *text;

    func_0808A268(2, 12, data_030027D8->first, data_030027D8->second,
                  data_03002740.tiles, data_03002740.tiles + 91, 0, 0,
                  8, 6, 13, 7, 8, 6, 13, 7, 13, 7);
    data_030009E0[2].x = 8;
    data_030009E0[2].y = 6;
    data_030009E0[2].tile = 0x1AB;
    zero = 0;
    func_0814186C(&zero, data_0600B560, 0x010002C0);

    for (row = 0; row < 4; row += 2) {
        if (row == 2) {
            if (data_030027D8->options & 3)
                enabled = 0;
            else
                enabled = 1;
            text = data_085668B0[0x3B];
        } else {
            if (data_030027D8->options & 4)
                enabled = 0;
            else
                enabled = 1;
            text = data_085668B0[0x3A];
        }
        func_0808B7C0(2, func_0808B8E4(2, 1, 1, row + 2),
                      row * 11 + 0x1AB, 11, 0xC000);
        *func_0808B8E4(2, 1, 0, row + 3) = 0xD00C;
        func_08015110(data_030027D8->text_state,
                      data_0600B560 + row * 0x160, text, enabled, 1);
    }

    func_08016344(data_030009E0[2].second_plane,
                  data_030009E0[2].stride, data_030009E0[2].height,
                  0xc0, data_030009E0[2].stride, 5, 12);
    func_08016560(data_030009E0[2].first_plane, 13, 7,
                  0xc0, 13, 1, 12);
    func_08035678(0xc03e, func_0808B8E4(2, 1, 1, 1),
                  func_08018524(data_02003CB0, 0x3e, 3), 1);
}
