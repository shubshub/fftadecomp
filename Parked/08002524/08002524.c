#include "ffta.h"

typedef s32 (*SortCompare)(const void *, const void *);
typedef void (*SortCopy)(void *, const void *, u32);

extern SortCopy data_0836D4BC[];

/* 0x08002524: 492 bytes. Iterative partition sort with an insertion finish. */
void func_08002524(void *workspace, u8 *base, s32 width, s32 count,
                   SortCompare compare)
{
    s32 left;
    s32 right;
    s32 top;
    u8 *pivot;
    s32 *lower;
    s32 *upper;
    u8 *temporary;

    lower = workspace;
    upper = (s32 *)((u8 *)workspace + 0x30);
    left = 0;
    right = count - 1;
    top = 0;
    while (right - left > 10 || top != 0) {
        if (right - left <= 10) {
            --top;
            left = lower[top];
            right = upper[top];
        }
        {
            s32 i;
            s32 j;
            pivot = base + ((left + right) / 2) * width;
            i = left;
            j = right;
            for (;;) {
                u8 *first;
                u8 *second;
                s32 remaining;

                while (compare(base + i * width, pivot) < 0)
                    ++i;
                while (compare(pivot, base + j * width) < 0)
                    --j;
                if (i >= j)
                    break;
                first = base + i * width;
                second = base + j * width;
                remaining = width - 1;
                while (remaining != -1) {
                    u8 saved = *first;
                    *first++ = *second;
                    *second++ = saved;
                    --remaining;
                }
                --j;
                ++i;
            }
            if (i - left > right - j) {
                if (i - left > 10) {
                    lower[top] = left;
                    upper[top] = i - 1;
                    ++top;
                }
                left = j + 1;
            } else {
                if (right - j > 10) {
                    lower[top] = j + 1;
                    upper[top] = right;
                    ++top;
                }
                right = i - 1;
            }
        }
    }

    temporary = (u8 *)workspace + 0x60;
    {
    s32 i;
    for (i = 1; i < count; ++i) {
        s32 j;
        u8 *source;
        data_0836D4BC[0](temporary, base + i * width, width);
        for (j = i - 1; j >= 0; --j) {
            source = base + j * width;
            if (compare(temporary, source) >= 0)
                break;
            data_0836D4BC[0](base + (j + 1) * width, source, width);
        }
        data_0836D4BC[0](base + (j + 1) * width, temporary, width);
    }
    }
}
