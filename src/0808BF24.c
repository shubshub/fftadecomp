#include "ffta.h"

// Complete [0x0808BF24,0x0808C16C): 584 bytes including the literal pool.

typedef struct {
    u8 unknown_00[0x0c];
    u16 *third_resource;
    u8 unknown_10[4];
    u16 *second_resource;
    u16 *first_resource;
    u8 unknown_1c[0x2d50 - 0x1c];
    void *text_resource;
} ResourceContext0808BF24;

typedef struct {
    u8 unknown_00[0x14];
    u16 *first_tiles;
    u8 unknown_18[0x0c];
    u16 *third_tiles;
    u8 unknown_28[4];
    u16 *second_tiles;
} TileStorage0808BF24;

typedef struct {
    u8 unknown_00;
    u8 mode;
    u8 unknown_02[0x0c];
    u16 attributes;
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
    u8 source_x;
    u8 source_y;
    u8 source_width;
    u8 source_height;
} TileWindow0808BF24;

extern ResourceContext0808BF24 *data_03002818;
extern TileStorage0808BF24 data_03002740;
extern TileWindow0808BF24 data_030009E0[];
extern u8 data_02003CB0[];
extern const u8 data_083AEEA4[];
extern u8 data_0600AB60[];
extern const u16 data_0895527C[];

extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width,
    u32 height, u32 source_x, u32 source_y, u32 source_width,
    u32 source_height, u32 stride, u32 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0800543C(void *destination, const void *source);
extern void func_08035578(const u16 *source, u16 *destination, u32 count,
                          u16 offset);
extern void func_0808136C(u32 slot, void *resource, u32 renderer, u32 column,
                          u32 row, u8 mode);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                          u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                          u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

void func_0808BF24(void)
{
    u16 first_zero;
    u16 second_zero;
    u16 tile_base;

    func_0808A268(5, 12, data_03002818->first_resource,
        data_03002818->second_resource, data_03002740.first_tiles,
        data_03002740.first_tiles + 0xf2, 0, 0,
        2, 0, 22, 11, 2, 0, 22, 11, 22, 11);
    first_zero = 0;
    func_0814186C(&first_zero, data_030009E0[5].first_plane, 0x01000079);
    func_0808A268(11, 12, data_03002818->second_resource,
        data_03002818->second_resource, data_03002740.second_tiles,
        data_03002740.second_tiles + 0xbe, 0, 0,
        3, 2, 20, 8, 3, 2, 20, 8, 20, 8);
    func_0808A268(9, 12, data_03002818->third_resource,
        data_03002818->second_resource, data_03002740.third_tiles,
        data_03002740.third_tiles + 0x1e, 0, 0,
        19, 17, 10, 3, 19, 17, 10, 3, 10, 3);
    second_zero = 0;
    func_0814186C(&second_zero, data_030009E0[9].first_plane, 0x0100000f);
    func_0800543C(data_02003CB0, data_083AEEA4);
    func_0814186C(data_02003CB0, data_0600AB60, 0x110);
    /* 0x15b is the tile number of data_0600AB60 in the 0x06008000 character
     * block, i.e. where the 0x220 bytes just uploaded land. */
    tile_base = 0x15b;
    func_08035578(data_0895527C, data_030009E0[9].first_plane, 0x1e, tile_base);
    data_030009E0[5].x = 2;
    data_030009E0[5].y = 0;
    data_030009E0[5].attributes = 0x229;
    data_030009E0[5].mode = 0;
    data_030009E0[5].source_x = 1;
    data_030009E0[5].source_y = 1;
    data_030009E0[5].source_width = 19;
    data_030009E0[5].source_height = 10;
    func_0808136C(0, data_03002818->text_resource, 5, 0, 0, 0);
    func_08016344(data_030009E0[5].second_plane,
        data_030009E0[5].width, data_030009E0[5].height, 0xc0,
        data_030009E0[5].width, 5, 12);
    func_08016560(data_030009E0[5].first_plane, 22, 11, 0xc0, 22, 1, 12);
    func_08035678(0xc03e, func_0808B8E4(5, 1, 14, 1),
        func_08018524(data_02003CB0, 0x3e, 0x1e) - 3, 1);
    func_08035678(0xc044, func_0808B8E4(5, 1, 18, 1),
        func_08018524(data_02003CB0, 0x44, 6), 1);
}
