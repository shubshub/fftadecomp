#include "ffta.h"

/* 480 bytes. Window rows hold the right endpoint first. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

static inline s16 clamp_x(s16 x)
{
    if (x < 0)
        x = 0;
    else if (x >= 240)
        x = 240;
    return x;
}

void func_080DA3B8(s16 x1, s16 y1, s16 x2, s16 y2, void *buffer)
{
    s16 upper_x, lower_x, upper_y, lower_y;
    s16 height, error, direction, dx, adjustment, temp;

    if (y1 == y2) {
        if ((u16)y1 < 160) {
            x1 = clamp_x(x1);
            x2 = clamp_x(x2);
            if (x1 < x2) {
                ((WindowLine *)buffer)[y1].left = x1;
                ((WindowLine *)buffer)[y1].right = x2;
            } else {
                ((WindowLine *)buffer)[y1].left = x2;
                ((WindowLine *)buffer)[y1].right = x1;
            }
        }
        return;
    }

    if (y1 >= y2) {
        temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    upper_x = x1;
    lower_x = x2;
    height = y2 - y1 + 1;
    error = height >> 1;
    adjustment = height;
    dx = x2 - x1;
    if (dx < 0) {
        direction = -1;
        dx = -dx;
    } else {
        direction = 1;
    }
    upper_y = y1;
    lower_y = y2;
    if (height & 1)
        height = (height >> 1) + 1;
    else
        height >>= 1;

    /* Advance inward from both ends of the edge. */
    while (height) {
        if (upper_y < 160)
            if (upper_y >= 0)
                ((WindowLine *)buffer)[upper_y].left = clamp_x(upper_x);
        if (lower_y < 160)
            if (lower_y >= 0)
                ((WindowLine *)buffer)[lower_y].left = clamp_x(lower_x);
        error -= dx;
        while (error < 0) {
            upper_x += direction;
            lower_x -= direction;
            error += adjustment;
        }
        height--;
        upper_y++;
        lower_y--;
    }
}
