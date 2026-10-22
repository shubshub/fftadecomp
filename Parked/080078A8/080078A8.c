/* 0x080078A8 - 420 bytes */
#include "ffta.h"

typedef struct LinePoint {
    s16 horizontal;
    s16 vertical;
} LinePoint;

u32 func_080078A8(s16 start_horizontal, s16 start_vertical,
                  s16 end_horizontal, s16 end_vertical, LinePoint *points)
{
    s32 horizontal_distance = end_horizontal - start_horizontal;
    s32 vertical_distance = end_vertical - start_vertical;
    s32 length;
    s16 original_horizontal = start_horizontal;
    s16 original_vertical = start_vertical;
    s32 direction = -1;
    s32 error;
    s16 temporary;
    s32 horizontal_offset;
    s32 vertical_offset;
    s32 index;

    if (horizontal_distance < 0) {
        horizontal_distance = -horizontal_distance;
    }
    if (vertical_distance < 0) {
        vertical_distance = -vertical_distance;
    }
    length = (horizontal_distance > vertical_distance ? horizontal_distance : vertical_distance) + 1;
    if (start_horizontal < end_horizontal && start_vertical < end_vertical) {
        direction = 1;
    }

    if (horizontal_distance > vertical_distance) {
        if (start_horizontal > end_horizontal) {
            temporary = start_horizontal;
            start_horizontal = end_horizontal;
            end_horizontal = temporary;
            if (start_vertical > end_vertical) {
                direction = 1;
            }
            start_vertical = end_vertical;
        }
        error = horizontal_distance / 2;
        for (; start_horizontal <= end_horizontal; start_horizontal++) {
            horizontal_offset = original_horizontal - start_horizontal;
            if (horizontal_offset < 0) {
                horizontal_offset = -horizontal_offset;
            }
            vertical_offset = original_vertical - start_vertical;
            if (vertical_offset < 0) {
                vertical_offset = -vertical_offset;
            }
            index = horizontal_offset > vertical_offset ? horizontal_offset : vertical_offset;
            points[index].horizontal = start_horizontal;
            points[index].vertical = start_vertical;
            error -= vertical_distance;
            if (error < 0) {
                error += horizontal_distance;
                start_vertical += direction;
            }
        }
    } else {
        if (start_vertical > end_vertical) {
            temporary = start_vertical;
            start_vertical = end_vertical;
            end_vertical = temporary;
            if (start_horizontal > end_horizontal) {
                direction = 1;
            }
            start_horizontal = end_horizontal;
        }
        error = vertical_distance / 2;
        for (; start_vertical <= end_vertical; start_vertical++) {
            horizontal_offset = original_horizontal - start_horizontal;
            if (horizontal_offset < 0) {
                horizontal_offset = -horizontal_offset;
            }
            vertical_offset = original_vertical - start_vertical;
            if (vertical_offset < 0) {
                vertical_offset = -vertical_offset;
            }
            index = horizontal_offset > vertical_offset ? horizontal_offset : vertical_offset;
            points[index].horizontal = start_horizontal;
            points[index].vertical = start_vertical;
            error -= horizontal_distance;
            if (error < 0) {
                error += vertical_distance;
                start_horizontal += direction;
            }
        }
    }
    return length;
}
