#include "ffta.h"

/* Window initialization at 0x0807C00C..0x0807C144, including the literal pool. */

typedef struct {
    u8 unknown_00[0x14];
    u16 *second_plane;
    u16 *first_plane;
} ResourceContext;

typedef struct {
    u8 unknown_00[0x20];
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
extern u16 data_0600C560[];

extern void *func_0808A268(s32 index, u8 mode,
    void *first_resource, void *second_resource, void *first_tiles, void *second_tiles,
    void *first_buffer, void *second_buffer, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(u16 *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *, u16 tile, u16 count, u16 flags);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* The same halfword tile fill appears in 0807BB7C and 0807C144. */
static inline void clear_tiles(u16 value)
{
    func_0814186C(&value, data_0600C560, 0x010002C0);
}

void func_0807C00C(int x)
{
    func_0808A268(8, 12, data_03002818->first_plane,
        data_03002818->second_plane, data_03002740.first_tiles,
        data_03002740.first_tiles + 0x54, 0, 0,
        20, 8, 12, 7, 20, 8, 12, 7, 12, 7);
    data_030009E0[8].x = x;
    data_030009E0[8].y = 8;
    clear_tiles(0);
    data_030009E0[8].attributes = 0x22b;
    data_030009E0[8].mode = 0;
    data_030009E0[8].source_x = 1;
    data_030009E0[8].source_y = 1;
    data_030009E0[8].width = 11;
    data_030009E0[8].height = 4;
    func_08016344(data_030009E0[8].first_text,
        data_030009E0[8].text_x - 2, data_030009E0[8].text_y - 2,
        0xc0, data_030009E0[8].text_x, 5, 12);
    func_08016560(data_030009E0[8].second_text, 10, 5, 0xc0, 12, 1, 12);
    func_0808B7C0(8, func_0808B8E4(8, 1, 1, 2), 0x22b, 11, 0xe000);
}
