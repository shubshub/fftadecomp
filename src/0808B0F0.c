// func_0808B0F0: [0x0808B0F0, 0x0808B288), 408 bytes
// Clears the rows of a window's tile planes, then redraws its frame.
#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 disabled : 1;
    u8 mode : 3;
    u8 unknown_03 : 4;
    u8 unknown_04[6];
    u16 destination_offset;
    u8 unknown_0c[4];
    u16 *destination_first;
    u16 *destination_second;
    u8 unknown_18[0x20];
    s8 width;
    s8 height;
    u8 unknown_3a[0x12];
} Window0808B0F0;

extern Window0808B0F0 data_030009E0[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808ADD4(int index, int height, int width);

void func_0808B0F0(int index, int height, int width)
{
    /* Each CpuFill16(0, ...) is the SDK's vu16 temporary, spelled through a
     * pointer as in src/0808AAF0.c until fftadecomp-kit#164: four separate
     * halfwords at sp+0, sp+2, sp+4 and sp+6 (0x0808B15E, 0x0808B17C,
     * 0x0808B1D2, 0x0808B224). */
    u16 first_fill;
    u16 second_fill;
    u16 single_fill;
    u16 other_fill;
    u16 *first_word;
    u16 *second_word;
    u16 *single_word;
    u16 *other_word;
    u16 *first;
    u16 *second;
    int row;

    if ((data_030009E0[index].mode & 3) == 0) {
        first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset;
        second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset;
        for (row = 0; row < data_030009E0[index].height; row++) {
            first_word = &first_fill;
            *first_word = 0;
            func_0814186C(first_word, first,
                (data_030009E0[index].width & 0x1FFFFF) | 0x01000000);
            first += 0x20;
            second_word = &second_fill;
            *second_word = 0;
            func_0814186C(second_word, second,
                (data_030009E0[index].width & 0x1FFFFF) | 0x01000000);
            second += 0x20;
        }
    } else if ((data_030009E0[index].mode & 3) == 1) {
        second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset;
        for (row = 0; row < height - 1; row++) {
            single_word = &single_fill;
            *single_word = 0;
            func_0814186C(single_word, second,
                (data_030009E0[index].width & 0x1FFFFF) | 0x01000000);
            second += 0x20;
        }
    } else if ((data_030009E0[index].mode & 3) == 2) {
        first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset;
        for (row = 0; row < height - 1; row++) {
            other_word = &other_fill;
            *other_word = 0;
            func_0814186C(other_word, first,
                (data_030009E0[index].width & 0x1FFFFF) | 0x01000000);
            first += 0x20;
        }
    }
    func_0808ADD4(index, data_030009E0[index].height - height,
        data_030009E0[index].width - width + 2);
}
