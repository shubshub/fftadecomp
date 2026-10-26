#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 palette;
    u8 dimensions;
    u16 tile;
    u8 unknown_06[2];
} Rectangle0808B58C;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    const Rectangle0808B58C *rectangles;
} List0808B58C;

typedef struct {
    u8 unknown_00[0x1c];
    u16 *tiles;
    u8 unknown_20[8];
    u8 width;
    u8 unknown_29[0x23];
} Panel0808B58C;

extern Panel0808B58C data_030009E0[];

/* Complete [0x0808B58C, 0x0808B66C): 224 bytes, 108 instructions. */
void func_0808B58C(u32 index, const List0808B58C *list)
{
    s32 i;

    for (i = 0; i < list->count; i++) {
        u8 dimensions = list->rectangles[i].dimensions;
        s32 signed_dimensions = (s8)list->rectangles[i].dimensions;
        u16 width;
        u16 height;
        u16 tile;
        u16 *destination;
        u16 row;

        if (signed_dimensions >= 0) {
            width = list->rectangles[i].dimensions;
            height = 1;
        } else {
            width = dimensions & 15;
            height = (dimensions & 0x70) >> 4;
        }

        tile = (list->rectangles[i].palette << 12) | list->rectangles[i].tile;
        destination = data_030009E0[index].tiles;
        destination += list->rectangles[i].x;
        destination += list->rectangles[i].y * data_030009E0[index].width;
        for (row = 0; row < height; row++) {
            u16 column;

            for (column = 0; column < width; column++)
                destination[column] = tile + column;
            destination += data_030009E0[index].width;
        }
    }
}
