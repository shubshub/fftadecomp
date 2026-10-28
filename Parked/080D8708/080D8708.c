#include "ffta.h"

/* 0x080D8708..0x080D8858: 336 bytes. */
typedef struct {
    u8 x;
    u8 height;
    u8 y;
    u8 unknown_03;
} CandidatePosition;

extern const s8 *const data_08395544[];
extern const u8 data_08395548[];
extern u8 func_0801CC18(u8 x, u8 y);
extern u8 func_0801CD7C(s16 x, s16 y);
extern u8 func_0801CC7C(u8 x, u8 y);

u8 func_080D8708(u8 origin_x, u8 origin_y, CandidatePosition *output,
                 u8 pattern, u8 max_difference, u16 flags)
{
    u8 origin_height = func_0801CC18(origin_x, origin_y);
    u8 count = 0;
    u8 i;

    for (i = 0; i < data_08395548[pattern]; i++) {
        u8 valid = 1;
        const s8 *offsets = data_08395544[pattern];
        const s8 *offset = &offsets[i * 4];
        u16 x = origin_x + offset[0];
        u16 y = origin_y + offset[1];
        u16 height;

        if (!func_0801CD7C((s16)x, (s16)y)) {
            valid = 0;
        } else {
            if (!func_0801CC7C((u8)x, (u8)y))
                valid = 0;
            if (valid) {
                s16 difference;

                height = func_0801CC18((u8)x, (u8)y);
                difference = origin_height - height;
                if (difference < 0)
                    difference = -difference;
                if (difference > max_difference)
                    valid = 0;
            }
        }
        if (!valid) {
            height = 0xFFFF;
            x = height;
            y = height;
        }
        if (flags & 1) {
            output[i].x = x;
            output[i].height = height;
            output[i].y = y;
        } else {
            output[count].x = x;
            output[count].height = height;
            output[count].y = y;
        }
        if (valid)
            count++;
    }
    return count;
}
