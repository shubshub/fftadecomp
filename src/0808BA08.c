#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *second_plane;
    u16 *first_plane;
} ResourceContext;

typedef struct {
    u8 unknown_00[8];
    u16 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00[0x1c];
    u16 *second_plane;
    u8 unknown_20[0x14];
    u8 x;
    u8 y;
    u8 unknown_36[0x16];
} TileRenderer;

extern ResourceContext *data_03002818;
extern TileStorage data_03002740;
extern TileRenderer data_030009E0[];
extern const u8 data_0894F95C[];

extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);
extern void func_08035578(const void *resource, u16 *destination,
                          u32 first, u32 last);
extern u16 *func_0808B8E4(u32 index, u32 x, u32 y, u32 plane);
extern void func_08089F98(u16 *destination, u16 value, u16 stride,
                         u16 width, u16 height, u16 attributes, s32 step);

void func_0808BA08(void)
{
    func_0808A268(2, 12, data_03002818->first_plane,
        data_03002818->second_plane, data_03002740.tiles,
        data_03002740.tiles + 0xe0, 0, 0, 1, 11, 28, 8,
        1, 11, 28, 8, 28, 8);
    data_030009E0[2].x = 1;
    data_030009E0[2].y = 11;
    func_08035578(data_0894F95C, data_030009E0[2].second_plane, 0xe0, 0xfe);
    func_08089F98(func_0808B8E4(2, 0, 0, 0), 1, 28, 14, 8, 0xc000, 0);
    func_08089F98(func_0808B8E4(2, 0, 14, 0), 1, 28, 14, 3, 0xb000, 0);
}
