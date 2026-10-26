#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE];
    s16 x;
    s16 y;
    u8 unknown_12[0xA];
    u8 flags;
    u8 direction;
} Movement0809C8C8;

/* 0x0809C8C8..0x0809C9E8: 288 bytes, 144 instructions. */
s32 func_0809C8C8(Movement0809C8C8 *movement, s32 step)
{
    u8 finished = movement->flags & 2;

    if (finished) {
        return 0;
    }
    switch (movement->direction) {
    case 1:
        if (!(movement->flags & 1)) {
            if (movement->x < 12) {
                movement->x += step;
            } else {
                movement->flags |= 1;
            }
        } else {
            movement->flags |= 1;
            movement->x -= step;
            if (movement->x <= 0) {
                movement->x = 0;
                movement->direction = 0;
                movement->flags |= 2;
            }
        }
        return 1;
    case 2:
        if (!(movement->flags & 1)) {
            if (movement->x > -12) {
                movement->x -= step;
            } else {
                movement->flags |= 1;
            }
        } else {
            movement->flags |= 1;
            movement->x += step;
            if (movement->x >= 0) {
                movement->x = 0;
                movement->direction = 0;
                movement->flags |= 2;
            }
        }
        return 1;
    case 3:
        if (!(movement->flags & 1)) {
            if (movement->y < 12) {
                movement->y += step;
            } else {
                movement->flags |= 1;
            }
        } else {
            movement->flags |= 1;
            movement->y -= step;
            if (movement->y <= 0) {
                movement->y = 0;
                movement->direction = 0;
                movement->flags |= 2;
            }
        }
        return 1;
    case 4:
        if (!(movement->flags & 1)) {
            if (movement->y > -12) {
                movement->y -= step;
            } else {
                movement->flags |= 1;
            }
        } else {
            movement->y += step;
            if (movement->y >= 0) {
                movement->y = 0;
                movement->direction = 0;
                movement->flags |= 2;
            }
        }
        return 1;
    default:
        break;
    }
    return 0;
}
