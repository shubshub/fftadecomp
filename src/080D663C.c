#include "ffta.h"

/* Complete [0x080D663C, 0x080D66EE): 178 bytes, 87 instructions, one literal
 * word.
 * f0b5071c0d1c1206002a47d03a681178507803020b430c49081c1e1c0640002084468020
 * 0002011c181c0840141c00280cd001218c46a078e178090201432888411809040b0c17e0
 * ff3f00008021c901081c0340002b07d002208446a178e07803020b43288807e02a885000
 * 20188178c07803020b43101c013028800004000cb04212d16146002901d0201d02e0a01c
 * 7100401838600020288006e03a68298848008018038801312980181cf0bc02bc0847
 */

/* Read the next halfword of a plain or run-encoded halfword stream.  An
 * encoded stream is a sequence of runs.  Each starts with a little-endian
 * halfword, read a byte at a time, whose low 14 bits give the run length;
 * then comes either one halfword (bit 15: values count up from it, bit 14:
 * it repeats) or the halfwords themselves, also read a byte at a time. */
typedef struct __attribute__((packed)) {
    u16 header;
    u16 data[0];
} HalfwordRun;

u16 func_080D663C(const u16 **stream, u16 *index, u8 encoded)
{
    u16 result;

    if (encoded) {
        const HalfwordRun *run = (const HalfwordRun *)*stream;
        u16 length = run->header & 0x3FFF;
        u32 mode = 0;

        if (run->header & 0x8000) {
            mode = 1;
            result = run->data[0] + *index;
        } else if (run->header & 0x4000) {
            mode = 2;
            result = run->data[0];
        } else {
            result = run->data[*index];
        }
        (*index)++;
        if (*index == length) {
            if (mode) {
                *stream += 2;
            } else {
                *stream += 1;
                *stream += length;
            }
            *index = 0;
        }
    } else {
        const u16 *data = *stream;

        result = data[*index];
        (*index)++;
    }
    return result;
}
