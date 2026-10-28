#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 disabled : 1;
    u8 mode : 3;
    u8 unknown_03 : 4;
    u8 unknown_04[4];
    u16 source_offset;
    u16 destination_offset;
    u8 unknown_0c[4];
    u16 *destination_first;
    u16 *destination_second;
    u16 *source_first;
    u16 *source_second;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x0f];
    s8 width;
    s8 height;
    u8 unknown_3a[0x12];
} TileRenderer;

extern TileRenderer data_030009E0[];
extern void func_08000F48(const u16 *source, u16 *destination, u16 count);

void func_0808ADD4(u32 index, s32 height, s32 width)
{
    u16 *source_first;
    u16 *destination_first;
    u16 *source_second;
    u16 *destination_second;
    s32 half_width;
    s32 count;
    s32 row;

    if (data_030009E0[index].disabled)
        return;
    if (data_030009E0[index].width == 0)
        return;

    half_width = data_030009E0[index].width >> 1;
    if (width >= data_030009E0[index].width) {
        count = data_030009E0[index].width;
        source_first = data_030009E0[index].source_first
            + data_030009E0[index].source_offset
            + data_030009E0[index].stride * (data_030009E0[index].height - 1);
        destination_first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset + (height - 1) * 32;
        source_second = data_030009E0[index].source_second
            + data_030009E0[index].source_offset
            + data_030009E0[index].stride * (data_030009E0[index].height - 1);
        destination_second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset + (height - 1) * 32;
    } else {
        count = width;
        source_first = data_030009E0[index].source_first
            + data_030009E0[index].source_offset
            + data_030009E0[index].stride * (data_030009E0[index].height - 1)
            + (half_width - (width >> 1));
        destination_first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset + (height - 1) * 32
            + (half_width - (width >> 1));
        source_second = data_030009E0[index].source_second
            + data_030009E0[index].source_offset
            + data_030009E0[index].stride * (data_030009E0[index].height - 1)
            + (half_width - (width >> 1));
        destination_second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset + (height - 1) * 32
            + (half_width - (width >> 1));
    }

    if ((data_030009E0[index].mode & 3) == 0) {
        func_08000F48(source_first, destination_first, count);
        func_08000F48(source_second, destination_second, count);
    } else if ((data_030009E0[index].mode & 3) == 1) {
        func_08000F48(source_second, destination_second, data_030009E0[index].width);
    } else if ((data_030009E0[index].mode & 3) == 2) {
        func_08000F48(source_first, destination_first, data_030009E0[index].width);
    }

    if (width >= data_030009E0[index].width) {
        count = data_030009E0[index].width;
        source_first = data_030009E0[index].source_first
            + data_030009E0[index].source_offset;
        source_second = data_030009E0[index].source_second
            + data_030009E0[index].source_offset;
        destination_first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset;
        destination_second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset;
    } else {
        count = width;
        source_first = data_030009E0[index].source_first
            + data_030009E0[index].source_offset + (half_width - (count >> 1));
        destination_first = data_030009E0[index].destination_first
            + data_030009E0[index].destination_offset + (half_width - (count >> 1));
        source_second = data_030009E0[index].source_second
            + data_030009E0[index].source_offset + (half_width - (count >> 1));
        destination_second = data_030009E0[index].destination_second
            + data_030009E0[index].destination_offset + (half_width - (count >> 1));
    }

    if ((data_030009E0[index].mode & 3) == 0) {
        for (row = 0; row < height - 1; row++) {
            func_08000F48(source_first, destination_first, count);
            destination_first += 32;
            source_first += data_030009E0[index].stride;
            func_08000F48(source_second, destination_second, count);
            destination_second += 32;
            source_second += data_030009E0[index].stride;
        }
    } else if ((data_030009E0[index].mode & 3) == 1) {
        for (row = 0; row < height - 1; row++) {
            func_08000F48(source_second, destination_second, data_030009E0[index].width);
            destination_second += 32;
            source_second += data_030009E0[index].stride;
        }
    } else if ((data_030009E0[index].mode & 3) == 2) {
        for (row = 0; row < height - 1; row++) {
            func_08000F48(source_first, destination_first, data_030009E0[index].width);
            destination_first += 32;
            source_first += data_030009E0[index].stride;
        }
    }
}
