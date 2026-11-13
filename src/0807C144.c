#include "ffta.h"

// Complete [0x0807C144,0x0807C28C): 328 bytes including the literal pool.

typedef struct {
    u8 unknown_00[0x14];
    u16 *second_resource;
    u16 *first_resource;
} Resources0807C144;

typedef struct {
    u8 unknown_00;
    u8 field_01;
    u8 unknown_02[12];
    u16 border_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[10];
    u8 x;
    u8 y;
    u8 unknown_36[18];
    u8 field_48;
    u8 field_49;
    u8 field_4a;
    u8 field_4b;
} Window0807C144;

extern Resources0807C144 *data_03002818;
extern u8 *data_03002740[];
extern Window0807C144 data_030009E0[];
extern u16 data_0600C560[];

extern void *func_0808A268(s32 index, u8 mode,
    u16 *first_resource, u16 *second_resource,
    u8 *first_tiles, u8 *second_tiles, u8 *first_text, u8 *second_text,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(u16 *, u8, u8, u16, u8, u16, u8);
extern void func_0814186C(const void *, void *, u32);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B858(s32 index, u16 *destination, u16 tile, u16 count);

/* The same 16-bit fill of 0x2C0 halfwords at 0x0600C560 recurs in at least
 * 0807BB7C, 0807BDF8, 0807C00C, 0807C7E8 (x6) and 08080EF8, which suggests a
 * shared helper.  Only the by-value parameter form reproduces the ordering of
 * `add r0, sp, #56` here; a plain local or a void helper schedules it later. */
static inline void clear_tiles(u16 value)
{
    func_0814186C(&value, data_0600C560, 0x010002C0);
}

void func_0807C144(u32 x)
{
    func_0808A268(8, 12, data_03002818->first_resource,
        data_03002818->second_resource,
        data_03002740[8], data_03002740[8] + 0xa8, 0, 0,
        20, 8, 12, 7, 20, 8, 12, 7, 12, 7);
    data_030009E0[8].x = x;
    data_030009E0[8].y = 8;
    clear_tiles(0);
    data_030009E0[8].border_tile = 0x22b;
    data_030009E0[8].field_01 = 0;
    data_030009E0[8].field_48 = 1;
    data_030009E0[8].field_49 = 1;
    data_030009E0[8].field_4a = 11;
    data_030009E0[8].field_4b = 4;
    func_0808B858(8, func_0808B8E4(8, 1, 0, 2), 0, 12);
    func_0808B858(8, func_0808B8E4(8, 1, 0, 4), 0, 12);
    func_08016344(data_030009E0[8].second_plane,
        data_030009E0[8].width - 2, data_030009E0[8].height - 2,
        0xc0, data_030009E0[8].width, 5, 12);
    func_08016560(data_030009E0[8].first_plane, 10, 5, 0xc0, 12, 1, 12);
}
