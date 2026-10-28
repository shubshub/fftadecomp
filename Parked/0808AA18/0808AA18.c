#include "ffta.h"

/* Complete [0x0808AA18, 0x0808AAF0): 216 bytes, 101 instructions. */
typedef union {
    struct {
        s8 left;
        s8 top;
        s8 right;
        s8 bottom;
    } edges;
    u32 packed;
} TileRectangle;

typedef struct {
    u8 unknown_00[0x10];
    u16 *first_grid;
    u16 *second_grid;
    u8 unknown_18[8];
    u8 *first_buffer;
    u8 *second_buffer;
    u8 unknown_28[8];
    TileRectangle rectangle;
    u8 unknown_34[0x10];
    TileRectangle saved_rectangle;
    u8 unknown_48[4];
} TileState;

extern TileState data_030009E0[];
extern void func_0814186C(const void *, void *, u32);

void func_0808AA18(u32 index)
{
    if (data_030009E0[index].first_buffer) {
        s32 left = data_030009E0[index].rectangle.edges.left;
        s32 top = data_030009E0[index].rectangle.edges.top;
        s32 offset = left + top * 32;
        u16 *first_grid = data_030009E0[index].first_grid + offset;
        u16 *second_grid = data_030009E0[index].second_grid + offset;
        u8 *first_buffer = data_030009E0[index].first_buffer;
        u8 *second_buffer = data_030009E0[index].second_buffer;
        s32 width = data_030009E0[index].rectangle.edges.right - left;
        s32 height = data_030009E0[index].rectangle.edges.bottom - top;
        s32 byte_width = width * 2;
        for (; height != 0; height--) {
            func_0814186C(first_grid, first_buffer, width & 0x1fffff);
            first_grid += 32;
            first_buffer += byte_width;
            func_0814186C(second_grid, second_buffer, width & 0x1fffff);
            second_grid += 32;
            second_buffer += byte_width;
        }
        data_030009E0[index].saved_rectangle = data_030009E0[index].rectangle;
    }
}
