#include "ffta.h"

typedef struct {
    s8 left, top, right, bottom;
} TileRect;

typedef struct {
    u8 unknown_00[0x10];
    u16 *first_tiles;
    u16 *second_tiles;
    u8 unknown_18[8];
    const u16 *first_buffer;
    const u16 *second_buffer;
    u8 unknown_28[8];
    TileRect current;
    u8 unknown_34[0x10];
    TileRect saved;
    u8 unknown_48[4];
} TileWindow;

extern TileWindow data_030009E0[];
extern s32 func_08000F48(const void *source, void *destination, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x0808AAF0, 0x0808AC34), 324 bytes. */
void func_0808AAF0(int index)
{
    s32 offset, width, height;
    u16 *first_destination, *second_destination;
    const u16 *first_source, *second_source;

    if (data_030009E0[index].first_buffer) {
        s32 x = data_030009E0[index].saved.left;
        s32 y = data_030009E0[index].saved.top;
        offset = x + y * 32;
        first_destination = data_030009E0[index].first_tiles + offset;
        second_destination = data_030009E0[index].second_tiles + offset;
        first_source = data_030009E0[index].first_buffer;
        second_source = data_030009E0[index].second_buffer;
        width = data_030009E0[index].saved.right - x;
        height = data_030009E0[index].saved.bottom - y;

        while (height != 0) {
            func_08000F48(first_source, first_destination, width);
            first_destination += 32;
            first_source += width;
            func_08000F48(second_source, second_destination, width);
            second_destination += 32;
            second_source += width;
            height--;
        }
    } else {
        /* The CpuSet calls at 0808AC00 and 0808AC12 read separate stack
         * halfwords. Each fill writes zero through its source pointer. */
        u16 first_fill, second_fill;
        u16 *first_word, *second_word;
        s32 x = data_030009E0[index].current.left;
        s32 y = data_030009E0[index].current.top;
        offset = x + y * 32;
        first_destination = data_030009E0[index].first_tiles + offset;
        second_destination = data_030009E0[index].second_tiles + offset;
        width = data_030009E0[index].current.right - x;
        height = data_030009E0[index].current.bottom - y;

        while (height != 0) {
            first_word = &first_fill;
            *first_word = 0;
            func_0814186C(first_word, first_destination, (width & 0x1FFFFF) | 0x01000000);
            first_destination += 32;
            second_word = &second_fill;
            *second_word = 0;
            func_0814186C(second_word, second_destination, (width & 0x1FFFFF) | 0x01000000);
            second_destination += 32;
            height--;
        }
    }
}
