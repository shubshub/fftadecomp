#include "ffta.h"

typedef struct {
    u8 state;
    u8 unknown_01[3];
    u8 height;
    u8 unknown_05;
    u8 width;
    u8 unknown_07;
    u8 unknown_08[0x10];
    u16 *source_first;
    u16 *source_second;
    u16 *first_buffer;
    u16 *second_buffer;
    u8 unknown_28[8];
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
    u8 unknown_34[4];
    s8 clipped_width;
    u8 unknown_39[0x13];
} Window0808A604;

extern Window0808A604 data_030009E0[];
extern int func_0808A424(int index);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x0808A604, 0x0808A830), 556 bytes.
 *
 * Requests a state for one window; func_0808B288 (src/0808B288.c) later
 * dispatches on the stored state, one arm per state.  func_0814186C is the
 * BIOS CpuSet call (`swi 0x0B; bx lr`). */
int func_0808A604(int index, u16 mode)
{
    u16 first_zero;
    u16 second_zero;
    u16 *first_buffer;

    if (data_030009E0[index].state != 0)
        return 0;

    switch (mode) {
    /* States 2 to 8 each have their own arm, as they have in the dispatcher.
     * The ROM keeps one copy of the call (0x0808A67C), which all seven
     * table words (0x0808A64C-0x0808A664) select: agbcc merges identical
     * arms after it has allocated registers.  With the seven labels on one
     * arm, index is in sl instead of r7 and the function is 544 bytes. */
    case 2:
        func_0808A424(index);
        break;
    case 3:
        func_0808A424(index);
        break;
    case 4:
        func_0808A424(index);
        break;
    case 5:
        func_0808A424(index);
        break;
    case 6:
        func_0808A424(index);
        break;
    case 7:
        func_0808A424(index);
        break;
    case 8:
        func_0808A424(index);
        break;
    case 1:
        /* Four 16-bit CpuSet fills of zero (the SDK's CpuFill16).  The
         * pointer loaded for the test (0x0808A690) is the first destination
         * (0x0808A6DC).  The first pair reads its zero from sp+0 and then
         * sp+2 (0x0808A69A, 0x0808A6E8), the second pair from sp+2 and then
         * sp+0 (0x0808A738, 0x0808A788): the order the SDK macro's four
         * block-scoped temporaries get (fftadecomp-kit#164). */
        first_buffer = data_030009E0[index].first_buffer;
        if (first_buffer != 0) {
            first_zero = 0;
            func_0814186C(&first_zero, first_buffer,
                (((data_030009E0[index].right - data_030009E0[index].left)
                  * (data_030009E0[index].bottom - data_030009E0[index].top))
                 & 0x1FFFFF) | 0x01000000);
            second_zero = 0;
            func_0814186C(&second_zero, data_030009E0[index].second_buffer,
                (((data_030009E0[index].right - data_030009E0[index].left)
                  * (data_030009E0[index].bottom - data_030009E0[index].top))
                 & 0x1FFFFF) | 0x01000000);
        } else {
            second_zero = 0;
            func_0814186C(&second_zero, data_030009E0[index].source_first,
                (((data_030009E0[index].right - data_030009E0[index].left)
                  * (data_030009E0[index].bottom - data_030009E0[index].top))
                 & 0x1FFFFF) | 0x01000000);
            first_zero = 0;
            func_0814186C(&first_zero, data_030009E0[index].source_second,
                (((data_030009E0[index].right - data_030009E0[index].left)
                  * (data_030009E0[index].bottom - data_030009E0[index].top))
                 & 0x1FFFFF) | 0x01000000);
        }
        break;
    case 11:
        func_0808A424(index);
        data_030009E0[index].height = 2;
        data_030009E0[index].width = 2;
        data_030009E0[index].unknown_07 = data_030009E0[index].clipped_width >> 1;
        break;
    case 12:
    case 13:
        func_0808A424(index);
        data_030009E0[index].height = 1;
        data_030009E0[index].width = 2;
        data_030009E0[index].unknown_07 = data_030009E0[index].clipped_width >> 1;
        break;
    }

    data_030009E0[index].state = mode;
    return 1;
}
