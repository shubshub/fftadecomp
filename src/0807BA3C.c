#include "ffta.h"

/* Complete 0x0807BA3C..0x0807BB7C: 320 bytes, including the literal pool. */

typedef struct {
    u8 unknown_00[0x14];
    u16 *second_plane;
    u16 *first_plane;
} ResourceContext;

typedef struct {
    u8 unknown_00[0x1c];
    u16 *first_tiles;
} TileStorage;

typedef struct {
    u8 unknown_00;
    u8 mode;
    u8 unknown_02[0x0c];
    u16 attributes;
    u8 unknown_10[8];
    u16 *second_text;
    u16 *first_text;
    u8 unknown_20[8];
    u8 text_x;
    u8 text_y;
    u8 unknown_2a[0x0a];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 source_x;
    u8 source_y;
    u8 width;
    u8 height;
} TileRenderer;

extern ResourceContext *data_03002818;
extern TileStorage data_03002740;
extern TileRenderer data_030009E0[];
extern u16 data_0600B4E0[];

extern void *func_0808A268(u32 index, u8 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(u16 *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u8 data_02003CB0[];
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 tile, u16 *destination, u32 count, u16 step);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* This window uses the same halfword fill as the next window at 0807BB7C. */
static inline void clear_tiles(u16 value)
{
    func_0814186C(&value, data_0600B4E0, 0x01000840);
}

void func_0807BA3C(void)
{
    u8 *buffer = data_02003CB0;

    func_0808A268(7, 12, data_03002818->first_plane,
        data_03002818->second_plane, data_03002740.first_tiles,
        data_03002740.first_tiles + 0x104, 0, 0,
        0, 6, 20, 13, 0, 6, 20, 13, 20, 13);
    data_030009E0[7].x = 0;
    data_030009E0[7].y = 6;
    clear_tiles(0);
    data_030009E0[7].attributes = 0x1A7;
    data_030009E0[7].mode = 0;
    data_030009E0[7].source_x = 1;
    data_030009E0[7].source_y = 1;
    data_030009E0[7].width = 11;
    data_030009E0[7].height = 12;
    func_08016344(data_030009E0[7].first_text,
        data_030009E0[7].text_x, data_030009E0[7].text_y,
        0xC0, data_030009E0[7].text_x, 5, 12);
    func_08016560(data_030009E0[7].second_text, 20, 13, 0xC0, 20, 1, 12);
    func_08035678(0xC044, func_0808B8E4(7, 1, 1, 1),
        func_08018524(buffer, 0x44, 4), 1);
}
