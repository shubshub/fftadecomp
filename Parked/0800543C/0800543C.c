#include "ffta.h"

/* Target: complete [0x0800543C, 0x0800588C), 1104 bytes. */
#define COPY_ALIGNED_BYTES(destination, source, length)                       \
    do {                                                                     \
        const u8 *from = (source);                                           \
        u32 remaining = (length);                                            \
        if (remaining) {                                                     \
            u8 *to = (destination);                                          \
            u32 words;                                                       \
            if (((u32)from - (u32)to) & 3) {                                 \
                while (remaining--)                                          \
                    *to++ = *from++;                                         \
            } else {                                                         \
                if ((u32)to & 1) {                                           \
                    *to++ = *from++;                                         \
                    remaining--;                                             \
                }                                                            \
                if (remaining > 1 && ((u32)to & 2)) {                         \
                    *(u16 *)to = *(const u16 *)from;                          \
                    from += 2;                                               \
                    to += 2;                                                 \
                    remaining -= 2;                                          \
                }                                                            \
                words = remaining >> 2;                                      \
                while (words--) {                                            \
                    *(u32 *)to = *(const u32 *)from;                          \
                    from += 4;                                               \
                    to += 4;                                                 \
                }                                                            \
                if (remaining & 2) {                                         \
                    *(u16 *)to = *(const u16 *)from;                          \
                    from += 2;                                               \
                    to += 2;                                                 \
                }                                                            \
                if (remaining & 1)                                           \
                    *to = *from;                                             \
            }                                                                \
        }                                                                    \
    } while (0)

#define FILL_ALIGNED_BYTES(destination, value, length)                         \
    do {                                                                     \
        u32 remaining = (length);                                            \
        if (remaining) {                                                     \
            u32 fill = (value);                                              \
            u8 *to = (destination);                                          \
            u32 words;                                                       \
            if ((u32)to & 1) {                                               \
                *to++ = fill;                                                \
                remaining--;                                                 \
            }                                                                \
            if (remaining > 1 && ((u32)to & 2)) {                             \
                *(u16 *)to = fill;                                           \
                to += 2;                                                     \
                remaining -= 2;                                              \
            }                                                                \
            words = remaining >> 2;                                          \
            while (words--) {                                                \
                *(u32 *)to = fill;                                           \
                to += 4;                                                     \
            }                                                                \
            if (remaining & 2) {                                             \
                *(u16 *)to = fill;                                           \
                to += 2;                                                     \
            }                                                                \
            if (remaining & 1)                                               \
                *to = fill;                                                  \
        }                                                                    \
    } while (0)

u32 func_0800543C(u8 *destination, const u8 *source)
{
    u32 size = ((u32)source[0] << 24) | ((u32)source[1] << 16) |
               ((u32)source[2] << 8) | source[3];
    const u8 *input = source + 4;
    u8 *base = destination;
    u32 produced = 0;

    while (produced < size) {
        u8 command = *input++;
        u32 length;

        if (command & 0x80) {
            u32 count = (command >> 3) & 15;
            u8 *output;
            const u8 *match;

            length = count + 3;
            output = base + produced;
            match = output - ((command & 7) << 8) - *input++ - 1;
            COPY_ALIGNED_BYTES(output, match, length);
        } else if (command & 0x40) {
            u32 count = command & 63;
            u8 *output;

            length = count + 1;
            output = base + produced;
            COPY_ALIGNED_BYTES(output, input, length);
            produced += length;
            input += length;
            continue;
        } else if (command & 0x20) {
            u32 count = command & 31;
            u8 *output;

            length = count + 2;
            output = base + produced;
            FILL_ALIGNED_BYTES(output, 0, length);
        } else if (command & 0x10) {
            u32 next = *input++;
            u32 count = (command & 15) | ((next >> 2) & 0x30);
            u8 *output;
            const u8 *match;

            length = count + 4;
            output = base + produced;
            match = output - (((next & 63) << 8) | *input++) - 1;
            COPY_ALIGNED_BYTES(output, match, length);
        } else {
            switch (command) {
            case 0: {
                u32 count = *input++;
                u32 high;
                u8 *output;
                const u8 *match;

                length = count + 5;
                high = *input++;
                output = base + produced;
                match = output - ((high << 8) | *input++) - 1;
                COPY_ALIGNED_BYTES(output, match, length);
                break;
            }
            case 1: {
                u32 count = *input++;
                u8 *output;

                length = count + 3;
                output = base + produced;
                FILL_ALIGNED_BYTES(output, ~0U, length);
                break;
            }
            case 2: {
                u32 count = *input++;
                u8 *output;

                length = count + 3;
                output = base + produced;
                FILL_ALIGNED_BYTES(output, 0, length);
                break;
            }
            default:
                continue;
            }
        }
        produced += length;
    }
    return size;
}
