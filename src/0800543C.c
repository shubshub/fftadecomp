#include "ffta.h"

/* 0x0800543C-0x0800588C: 1104 bytes.  Decompresses a big-endian length and a
 * command stream: back-references (0x80, 0x10, 0), literal runs (0x40), zero
 * runs (0x20, 2) and 0xFF runs (1).  Returns the decompressed length. */

/* The ROM holds this aligned copy four times (0x080054A0, 0x08005540,
 * 0x08005674, 0x08005718) and the fill below three times (0x080055E8,
 * 0x080057BA, 0x0800581C).  In the back-reference callers the trailing
 * `*input++` takes effect after the size argument is bound and before the
 * size test (mov r3, ip then adds r7, #1 at 0x080054A0, 0x08005674,
 * 0x08005718): the argument sequence point of a call. */
static inline void copy_bytes(void *destination, const u8 *from, u32 size)
{
    if (size) {
        u8 *to = destination;

        if (((u32)from - (u32)to) & 3) {
            while (size--)
                *to++ = *from++;
        } else {
            u32 words;

            if ((u32)to & 1) {
                *to++ = *from++;
                size--;
            }
            if (size > 1 && ((u32)to & 2)) {
                *(u16 *)to = *(const u16 *)from;
                from += 2;
                to += 2;
                size -= 2;
            }
            words = size >> 2;
            while (words--) {
                *(u32 *)to = *(const u32 *)from;
                from += 4;
                to += 4;
            }
            if (size & 2) {
                *(u16 *)to = *(const u16 *)from;
                from += 2;
                to += 2;
            }
            if (size & 1)
                *to = *from;
        }
    }
}

/* The fill word is formed after the size test (0x080055F0, 0x080057C0,
 * 0x08005822). */
static inline void fill_bytes(void *destination, u8 value, u32 size)
{
    if (size) {
        u32 fill = value * 0x01010101u;
        u8 *to = destination;
        u32 words;

        if ((u32)to & 1) {
            *to++ = fill;
            size--;
        }
        if (size > 1 && ((u32)to & 2)) {
            *(u16 *)to = fill;
            to += 2;
            size -= 2;
        }
        words = size >> 2;
        while (words--) {
            *(u32 *)to = fill;
            to += 4;
        }
        if (size & 2) {
            *(u16 *)to = fill;
            to += 2;
        }
        if (size & 1)
            *to = fill;
    }
}

u32 func_0800543C(void *destination, const u8 *source)
{
    u32 size = (u32)source[0] << 24;
    const u8 *input;
    u8 *base;
    u32 produced;

    size |= (u32)source[1] << 16;
    size |= (u32)source[2] << 8;
    size |= (u32)source[3];
    input = source + 4;
    base = destination;
    produced = 0;
    /* Every command adds its own output length; the ROM keeps one shared
     * `add sb, ip` tail at 0x08005870. */
    while (produced < size) {
        u8 command = *input++;
        u32 length;
        u32 high;

        if (command & 0x80) {
            u8 *output;

            length = ((command >> 3) & 15) + 3;
            output = base + produced;
            copy_bytes(output, output - ((command & 7) << 8) - *input++ - 1, length);
            produced += length;
        } else if (command & 0x40) {
            u8 *output;

            length = (command & 63) + 1;
            output = base + produced;
            copy_bytes(output, input, length);
            produced += length;
            input += length;
        } else if (command & 0x20) {
            u8 *output;

            length = (command & 31) + 2;
            output = base + produced;
            fill_bytes(output, 0, length);
            produced += length;
        } else if (command & 0x10) {
            u8 *output;

            high = *input++;
            length = ((command & 15) | ((high >> 2) & 0x30)) + 4;
            output = base + produced;
            copy_bytes(output, output - (((high & 63) << 8) | *input++) - 1, length);
            produced += length;
        } else {
            switch (command) {
            case 0: {
                u8 *output;

                length = *input++ + 5;
                high = *input++;
                output = base + produced;
                copy_bytes(output, output - ((high << 8) | *input++) - 1, length);
                produced += length;
                break;
            }
            case 1: {
                u8 *output;

                length = *input++ + 3;
                output = base + produced;
                fill_bytes(output, 0xFF, length);
                produced += length;
                break;
            }
            case 2: {
                u8 *output;

                length = *input++ + 3;
                output = base + produced;
                fill_bytes(output, 0, length);
                produced += length;
                break;
            }
            }
        }
    }
    return size;
}
