#include "ffta.h"

/* 0x080D9F60..0x080DA074: 276 bytes, 138 Thumb instructions. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

void func_080D9F60(s16 x, s16 y, u16 radius, void *buffer, u8 mode)
{
    s32 width;
    s32 offset;
    s32 decision;
    s16 left, right, row;

    if (radius == 0)
        return;
    width = radius;
    offset = 0;
    decision = width * 2;
    decision = -decision;
    decision += 3;
    while (width >= offset) {
        left = x - width;
        if (left < 0)
            left = 0;
        right = x + width + 1;
        if (right > 240)
            right = 240;
        if (mode != 1) {
            row = y + offset;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }
        if (mode != 2) {
            row = y - offset;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }
        left = x - offset;
        if (left < 0)
            left = 0;
        right = x + offset + 1;
        if (right > 240)
            right = 240;
        if (mode != 1) {
            row = y + width;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }
        if (mode != 2) {
            row = y - width;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }
        if (decision >= 0) {
            width--;
            decision -= 4 * width;
        }
        offset++;
        decision += 2 + 4 * offset;
    }
}
