#include "ffta.h"

/* A tile position; the previous one is saved as a whole (0x0802514E-0x08025154). */
typedef struct {
    u16 column;
    u16 unknown_02;
    u16 row;
    u16 unknown_06;
} TilePosition08024AD8;

/* The record func_08024758 (src/08024758.c) initialises: right and bottom
 * are left + width and top + height, one past the last tile. */
typedef struct {
    u8 unknown_00[0x0A];
    u8 moved;
    u8 unknown_0B;
    TilePosition08024AD8 current;
    TilePosition08024AD8 previous;
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
} TileCursor08024AD8;

/* The filtered key state at 0x0200F3A4 (filtered_held and filtered_pressed
 * of the state src/08022C64.c fills). */
typedef struct {
    u16 held;
    u16 pressed;
} FilteredInput08024AD8;

/* The raw key state; src/08022C64.c copies its held and pressed words. */
typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
} InputState08024AD8;

extern u8 g_state_02000000[];
extern FilteredInput08024AD8 data_0200F3A4;
extern InputState08024AD8 data_03000000;
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern void func_08141540(u32 sound);

/* Whether the cursor may stop on a tile: the tile exists and its flags do
 * not have bit 3 set.  The ROM has 22 inlined copies for the 24 calls and
 * no out-of-line copy; each copy forms its 0 or 1 after both tests and only
 * then compares it (for example 0x08024B4C-0x08024B5A).  It returns u8 like
 * valid_position in src/0812EA44.c, whose ROM forms its 0 or 1 the same
 * way (0x0812EA9A-0x0812EAA0), and it takes the cursor's u16 coordinates. */
static inline u8 tile_is_open(u16 column, u16 row)
{
    if (!func_0801CC7C(column, row))
        return 0;
    if (func_0801CD08(column, row) & 8)
        return 0;
    return 1;
}

/* Moves the map cursor one tile on a d-pad press.  A move that runs into a
 * closed tile tries the two diagonals beside it; when the map is viewed
 * rotated (bit 0 of 0x02002FC0) the keys are turned a quarter.
 * The first range test of a move towards the right or bottom edge puts the
 * bound first (cmp r0, sl at 0x08024BE4; cmp r0, sb at 0x08024CC2); every
 * other range test puts the coordinate first (0x08024B1A, 0x08024B64).
 * The keys are read through a pointer to 0x0200F3A4, as the next function,
 * src/08025174.c, reads them; the ROM loads that address afresh for each
 * group of key tests (0x08024B0A, 0x08024CB0, 0x08024E1C, 0x08024FC2).
 *
 * Complete target [0x08024AD8, 0x08025174): 1692 bytes, 786 instructions,
 * literal words 0x02000000, 0x0200F3A4 and 0x03000000.
 * f0b557464e464546e0b481b00090808982460099098a89460020009a90721648
 * bf2189014018017801200840002800d088e1124a51882020084000285fd00098
 * 007f824500d8c7e05546013d2806070e49460806060e381c311cf8f7a3f80006
 * 002807d0381c311cf8f7e2f808210140002905d0002004e000000002a4f30002
 * 012000285fd1009ad07f013881451ada4f4601372806040e3806060e201c311c
 * f8f780f80006002807d0201c311cf8f7bff808210140002901d0002000e00120
 * 002800d082e00098407f814500d883e04f46013f2806000e80463806060e4046
 * 311cf8f75ff8000600286ad04046311cf8f79ef808210140002962d163e01020
 * 0840002868d00099887f0138504563dd554601352806070e4a461006060e381c
 * 311cf8f73ff80006002807d0381c311cf8f77ef808210140002901d0002000e0
 * 0120002803d02804000c824644e00099c87f013881451ada4f4601372806000e
 * 80463806060e4046311cf8f71bf80006002807d04046311cf8f75af808210140
 * 002901d0002000e0012000281ed1009a527f914520d94f46013f2806000e8046
 * 3806060e4046311cf7f7fcff0006002807d04046311cf8f73bf8082101400029
 * 01d0002000e00120002805d02804000c82463804000c81461148418880200840
 * 002862d00099c87f0138484500dc2ee24f46013752461006060e3806050e301c
 * 291cf7f7cfff0006002807d0301c291cf8f70ef808210140002903d0002002e0
 * a4f300020120002800d00de20099887f013882451bda554601352806000e8046
 * 3806060e4046311cf7f7acff0006002807d04046311cf7f7ebff082101400029
 * 01d0002000e00120002800d0e9e1009a127f924500d8eae15546013d2806000e
 * 80463806060e4046311cf7f78bff0006002800d1d0e14046311cf7f7c9ff0821
 * 0140002900d0c7e1c8e140200840002800d1cce10098407f814500d8c7e14f46
 * 013f51460806060e3806050e301c291cf7f768ff0006002807d0301c291cf7f7
 * a7ff08210140002901d0002000e00120002800d0a8e1009a907f013882451bda
 * 554601352806000e80463806060e4046311cf7f747ff0006002807d04046311c
 * f7f786ff08210140002901d0002000e00120002800d084e10098007f824500d8
 * 85e199e7114a51884020084000285fd00098007f824500d8c7e05546013d2806
 * 070e49460806060e381c311cf7f71aff0006002807d0381c311cf7f759ff0821
 * 0140002904d0002003e00000a4f300020120002860d1009ad07f013881451bda
 * 4f4601372806000e80463806060e4046311cf7f7f7fe0006002807d04046311c
 * f7f736ff08210140002901d0002000e00120002800d082e00098407f814500d8
 * 83e04f46013f2806000e80463806060e4046311cf7f7d6fe000600286ad04046
 * 311cf7f715ff08210140002962d163e080200840002868d00099887f01385045
 * 63dd554601352806070e4a461006060e381c311cf7f7b6fe0006002807d0381c
 * 311cf7f7f5fe08210140002901d0002000e00120002803d02804000c824644e0
 * 0099c87f013881451ada4f4601372806000e80463806060e4046311cf7f792fe
 * 0006002807d04046311cf7f7d1fe08210140002901d0002000e0012000281ed1
 * 009a527f914520d94f46013f2806000e80463806060e4046311cf7f773fe0006
 * 002807d04046311cf7f7b2fe08210140002901d0002000e00120002805d02804
 * 000c82463804000c81461248418820200840002843d00099c87f0138484500dc
 * a5e04f46013752461006060e3806050e301c291cf7f746fe0006002807d0301c
 * 291cf7f785fe08210140002904d0002003e00000a4f300020120002800d083e0
 * 0099887f0138824500db90e6554601352806000e80463806060e4046311cf7f7
 * 21fe0006002800d17be64046311cf7f75ffe08210140002900d072e673e61020
 * 0840002863d00098407f81455fd94f46013f51460806060e3806050e301c291c
 * f7f700fe0006002807d0301c291cf7f73ffe08210140002901d0002000e00120
 * 002841d1009a907f013882451ada554601352806000e80463806060e4046311c
 * f7f7e0fd0006002807d04046311cf7f71ffe08210140002901d0002000e00120
 * 00281ed10098007f824520d95546013d2806000e80463806060e4046311cf7f7
 * c1fd0006002807d04046311cf7f700fe08210140002901d0002000e001200028
 * 05d02804000c82463804000c814612498888002801d000208880009988895045
 * 02d1088a484505d06c201cf1fdf90120009a9072009ad0681169506191615046
 * 90814946118201b038bc9846a146aa46f0bc01bc0047000000000003
 */
void func_08024AD8(TileCursor08024AD8 *cursor)
{
    FilteredInput08024AD8 *input = &data_0200F3A4;
    u16 x = cursor->current.column;
    u16 y = cursor->current.row;

    cursor->moved = 0;
    if (!(g_state_02000000[0x2FC0] & 1)) {
        if (input->pressed & 0x20) {
            if (x > cursor->left) {
                if (tile_is_open(x - 1, y)) {
                    x--;
                } else if (y < cursor->bottom - 1 && tile_is_open(x - 1, y + 1)) {
                    x--;
                    y++;
                } else if (y > cursor->top && tile_is_open(x - 1, y - 1)) {
                    x--;
                    y--;
                }
            }
        } else if (input->pressed & 0x10) {
            if (cursor->right - 1 > x) {
                if (tile_is_open(x + 1, y)) {
                    x++;
                } else if (y < cursor->bottom - 1 && tile_is_open(x + 1, y + 1)) {
                    x++;
                    y++;
                } else if (y > cursor->top && tile_is_open(x + 1, y - 1)) {
                    x++;
                    y--;
                }
            }
        }
        if (input->pressed & 0x80) {
            if (cursor->bottom - 1 > y) {
                if (tile_is_open(x, y + 1)) {
                    y++;
                } else if (x < cursor->right - 1 && tile_is_open(x + 1, y + 1)) {
                    x++;
                    y++;
                } else if (x > cursor->left && tile_is_open(x - 1, y + 1)) {
                    x--;
                    y++;
                }
            }
        } else if (input->pressed & 0x40) {
            if (y > cursor->top) {
                if (tile_is_open(x, y - 1)) {
                    y--;
                } else if (x < cursor->right - 1 && tile_is_open(x + 1, y - 1)) {
                    x++;
                    y--;
                } else if (x > cursor->left && tile_is_open(x - 1, y - 1)) {
                    x--;
                    y--;
                }
            }
        }
    } else {
        /* The rotated view: up and down move along x, left and right
         * along y. */
        if (input->pressed & 0x40) {
            if (x > cursor->left) {
                if (tile_is_open(x - 1, y)) {
                    x--;
                } else if (y < cursor->bottom - 1 && tile_is_open(x - 1, y + 1)) {
                    x--;
                    y++;
                } else if (y > cursor->top && tile_is_open(x - 1, y - 1)) {
                    x--;
                    y--;
                }
            }
        } else if (input->pressed & 0x80) {
            if (cursor->right - 1 > x) {
                if (tile_is_open(x + 1, y)) {
                    x++;
                } else if (y < cursor->bottom - 1 && tile_is_open(x + 1, y + 1)) {
                    x++;
                    y++;
                } else if (y > cursor->top && tile_is_open(x + 1, y - 1)) {
                    x++;
                    y--;
                }
            }
        }
        if (input->pressed & 0x20) {
            if (cursor->bottom - 1 > y) {
                if (tile_is_open(x, y + 1)) {
                    y++;
                } else if (x < cursor->right - 1 && tile_is_open(x + 1, y + 1)) {
                    x++;
                    y++;
                } else if (x > cursor->left && tile_is_open(x - 1, y + 1)) {
                    x--;
                    y++;
                }
            }
        } else if (input->pressed & 0x10) {
            if (y > cursor->top) {
                if (tile_is_open(x, y - 1)) {
                    y--;
                } else if (x < cursor->right - 1 && tile_is_open(x + 1, y - 1)) {
                    x++;
                    y--;
                } else if (x > cursor->left && tile_is_open(x - 1, y - 1)) {
                    x--;
                    y--;
                }
            }
        }
    }
    if (data_03000000.pressed)
        data_03000000.pressed = 0;
    if (cursor->current.column != x || cursor->current.row != y) {
        func_08141540(0x6C);
        cursor->moved = 1;
    }
    cursor->previous = cursor->current;
    cursor->current.column = x;
    cursor->current.row = y;
}
