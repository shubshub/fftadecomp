#include "ffta.h"

// 0x0801E954..0x0801EC28: 724 target bytes, including literal pool.

typedef struct {
    s16 x;
    s16 height;
    s16 z;
    s16 unknown_06;
} Position0801E954;

struct PackedEntry0801E954 {
    u32 layout;
    u16 unknown_04;
} __attribute__((packed));

typedef struct {
    u8 first;
    u8 second;
    u8 unknown_02;
    u8 unknown_03;
} Extent0801E954;

extern u8 data_0200F1D0;
extern Position0801E954 data_0200F1A0[3];
extern Position0801E954 data_0200F1B8[3];
extern const Extent0801E954 data_08149934[3][4];
extern const Extent0801E954 data_08149964[3][4];
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern void func_0814224C(void *destination, u32 size,
                          void (*callback)(void *destination, u32 size));
extern void func_0801C918(s16 first, s16 second, s16 third, s16 *first_output,
                          s16 *second_output, s16 *third_output);
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern u8 func_0801E710(s16 x, s16 z, s16 height, u8 minimum, u8 width, u8 depth);

u8 func_0801E954(s16 first, s16 second, s16 third, s16 fourth, s16 fifth,
                 const void *data, u8 flip_x, u8 flip_z)
{
    const struct PackedEntry0801E954 *entry = data;
    s16 out_x, out_z, out_height;
    u8 width, depth;
    u8 skew_x, skew_z;
    u32 layout, shape, direction;
    s16 offset;
    s16 x, z;

    func_0801C918(first, second, third, &out_x, &out_z, &out_height);
    layout = entry->layout;
    direction = layout >> 30;
    shape = (layout & 0xC000) >> 14;
    width = data_08149934[shape][direction].first;
    depth = data_08149934[shape][direction].second;
    skew_x = data_08149964[shape][direction].first;
    skew_z = data_08149964[shape][direction].second;
    offset = (layout >> 16) & 0x1FF;
    if (offset & 0x100)
        offset |= 0xFF00;
    if (flip_x)
        x = out_x - offset - skew_x;
    else
        x = offset + out_x;
    offset = entry->layout & 0xFF;
    if (offset & 0x80)
        offset |= 0xFF80;
    if (flip_z)
        z = out_z - offset - skew_z;
    else
        z = offset + out_z;
    x += fourth;
    z += fifth;

    {
        void (*const *callbacks)(void *destination, u32 size) = g_callbacks_0836D4B8;
        int column, row;

        func_0814224C(data_0200F1A0, sizeof(data_0200F1A0), callbacks[0]);
        column = first >> 5;
        row = third >> 5;

        if (column - 1 >= 0 && func_0801CC7C(column - 1, row)) {
            data_0200F1A0[0].x = column - 1;
            data_0200F1A0[0].z = row;
            data_0200F1A0[0].height = func_0801CC18(data_0200F1A0[0].x, data_0200F1A0[0].z);
        }
        if (row - 1 >= 0 && func_0801CC7C(column, row - 1)) {
            data_0200F1A0[1].x = column;
            data_0200F1A0[1].z = row - 1;
            data_0200F1A0[1].height = func_0801CC18(data_0200F1A0[1].x, data_0200F1A0[1].z);
        }
        data_0200F1A0[2].x = column;
        data_0200F1A0[2].z = row;
        data_0200F1A0[2].height = func_0801CC18(data_0200F1A0[2].x, data_0200F1A0[2].z);
    }
    data_0200F1D0 = 0;

    {
        void (*const *callbacks)(void *destination, u32 size) = g_callbacks_0836D4B8;
        int column, row;
        u8 left, right;

        func_0814224C(data_0200F1B8, sizeof(data_0200F1B8), callbacks[0]);
        column = first >> 5;
        row = third >> 5;

        left = 0;
        if (column + 1 <= 15 && func_0801CC7C(column + 1, row)) {
            data_0200F1B8[0].x = column + 1;
            data_0200F1B8[0].z = row;
            data_0200F1B8[0].height = func_0801CC18(data_0200F1B8[0].x, data_0200F1B8[0].z);
            left = 1;
        }
        right = 0;
        if (row + 1 <= 15 && func_0801CC7C(column, row + 1)) {
            data_0200F1B8[1].x = column;
            data_0200F1B8[1].z = row + 1;
            data_0200F1B8[1].height = func_0801CC18(data_0200F1B8[1].x, data_0200F1B8[1].z);
            right = 1;
        }
        if (left && right) {
            data_0200F1B8[2].x = column + 1;
            data_0200F1B8[2].z = row + 1;
            data_0200F1B8[2].height = func_0801CC18(data_0200F1B8[1].x, data_0200F1B8[1].z);
        }
    }

    return func_0801E710(x, z, out_height, (s16)second >> 4, width, depth);
}
