#include "ffta.h"

/* Complete [0x080751AC, 0x080753C8), 540 bytes. */
typedef struct {
    u8 unknown_00;
    u8 field_01;
    u8 unknown_02[12];
    u16 tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 height;
    u8 unknown_2A[10];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 flag_48;
    u8 flag_49;
    u8 width_4A;
    u8 height_4B;
} TileRenderer;

typedef struct {
    u8 unknown_00[0x14];
    void *second;
    void *first;
    u8 unknown_1C[0x68C - 0x1C];
    u8 text[0xBF5 - 0x68C];
    u8 ready;
} State;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;

extern u8 data_02003CB0[];
extern State *data_03002818;
extern Graphics data_03002740;
extern TileRenderer data_030009E0[];
/* BG character block 2, tile 0x1A7 in 4bpp format. */
#define MENU_TEXT_TILES ((u8 *)(0x06008000 + 0x1A7 * 32))
extern const u8 *data_085668B0[];

extern TileRenderer *func_0808A268(s32 index, u8 style, void *first, void *second,
    void *plane0, void *plane1, void *extra0, void *extra1,
    u8 x0, u8 y0, u8 width0, u8 height0,
    u8 x1, u8 y1, u8 width1, u8 height1, u8 width, u8 height);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(int index, u16 *destination, u16 tile, u16 count, u16 flags);
extern u16 func_08015110(void *context, u8 *destination, const u8 *text, u8 mode, u8 reset);
extern void func_08016344(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

typedef struct {
    u8 unknown_00[6];
    u8 kind;
} Unit;

u32 func_080751AC(Unit *unit)
{
    u32 available = 0;
    u8 *buffer = data_02003CB0;
    u16 fill;
    s32 i;
    const u8 *text;

    data_03002818->ready = 1;
    func_0808A268(4, 12, data_03002818->first, data_03002818->second,
        data_03002740.tiles, data_03002740.tiles + 0x108, 0, 0,
        17, 8, 12, 9, 17, 8, 12, 9, 12, 9);
    data_030009E0[4].x = 17;
    data_030009E0[4].y = 8;
    data_030009E0[4].tile = 0x1A7;
    data_030009E0[4].field_01 = 0;
    data_030009E0[4].flag_48 = 1;
    data_030009E0[4].flag_49 = 1;
    data_030009E0[4].width_4A = 11;
    data_030009E0[4].height_4B = 6;
    fill = 0;
    func_0814186C(&fill, MENU_TEXT_TILES, 0x01000580);
    for (i = 0; i < 6; i += 2) {
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, i + 2),
            i * 11 + 0x1A7, 11, 0xC000);
        *func_0808B8E4(4, 1, 0, i + 3) = 0xD00C;
        text = data_085668B0[(i >> 1) + 0x31];
        if (i == 4)
            available = unit->kind <= 5;
        if (i != 4 || available) {
            func_08015110(data_03002818->text, MENU_TEXT_TILES + i * 352,
                text, 0, 1);
        } else {
            func_08015110(data_03002818->text, MENU_TEXT_TILES + i * 352,
                text, 1, 1);
        }
    }
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].stride, data_030009E0[4].height,
        0xC0, data_030009E0[4].stride, 5, 12);
    func_08016560(data_030009E0[4].first_plane, 12, 9, 0xC0, 12, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
        func_08018524(buffer, 0x3E, 3), 1);
    data_03002818->ready = 1;
    return available;
}
