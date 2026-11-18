#include "ffta.h"

/* Complete 0x08034FFC..0x08035174: 376 bytes. */
typedef struct {
    u8 unknown_00[0x90];
    u16 *first;
    u16 *second;
} MenuResources;

typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00[0x0e];
    u16 attributes;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[2];
    u8 content_width;
    u8 content_height;
    u8 unknown_2e[0x1e];
} TileRenderer;

extern MenuResources *g_state_03002810;
extern TileStorage data_03002740;
extern TileRenderer data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_06009960[];
extern void *func_0808A268(s32 index, u8 mode,
    void *first_resource, void *second_resource, void *first_tiles, void *second_tiles,
    void *first_buffer, void *second_buffer, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08016344(u16 *destination, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *destination, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
    u16 count, u16 flags);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

/* Both CpuSet fills initialize the source halfword through the pointer passed
 * in R0 (0803500C..08035026 and 08035026..0803503C). The same source
 * initialization and call appear in the tile fills in src/0807B858.c. */
#define CLEAR_TILE_PLANE(destination) do { \
    u16 fill; \
    u16 *source = &fill; \
    *source = 0; \
    func_0814186C(source, (destination), 0x01000134); \
} while (0)

void func_08034FFC(void)
{
    u8 *buffer = data_02003CB0;
    s32 row;
    u16 graphics_zero;

    CLEAR_TILE_PLANE(data_030009E0[4].second_plane);
    CLEAR_TILE_PLANE(data_030009E0[4].first_plane);
    func_0808A268(4, 12, g_state_03002810->second,
        g_state_03002810->first, data_03002740.tiles,
        data_03002740.tiles + 0x134, 0, 0,
        1, 1, 28, 11, 1, 1, 28, 11, 28, 11);
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].width, data_030009E0[4].height - 4,
        0xc0, data_030009E0[4].width, 5, 12);
    func_08016560(data_030009E0[4].first_plane,
        28, 7, 0xc0, 28, 1, 12);
    data_030009E0[4].attributes = 0xcb;
    data_030009E0[4].content_width = 26;
    data_030009E0[4].content_height = 6;
    for (row = 0; row < 4; row += 2)
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, row + 2),
            0xcb + row * 26, 26, 0xc000);
    func_08035678(0xc03e, func_0808B8E4(4, 1, 1, 1),
        func_08018524(buffer, 0x3e, 23), 1);
    graphics_zero = 0;
    func_0814186C(&graphics_zero, data_06009960, 0x01000d00);
}
