#include "ffta.h"

/* Complete [0x080D66F0, 0x080D6798): 168 bytes, 81 instructions, one literal
 * word.
 * f0b5071c0c1c1206002a43d03a681178507803020b430b49081c1e1c0640002084468020
 * 0002011c181c0840151c00280ad001218c462188a87808180006030e11e00000ff3f0000
 * 8021c901081c0340002b04d002208446ab78218803e02188a81c40180378481c20800004
 * 000cb04216d16146002901d0281d07e0321c01201040002800d00132a81c801838600020
 * 208005e0386821884018037801312180181cf0bc02bc0847
 */

/* Read the next byte of a plain or run-encoded byte stream.  An encoded
 * stream is a sequence of runs.  Each starts with a little-endian halfword,
 * read a byte at a time, whose low 14 bits give the run length; then comes
 * either one byte and a padding byte (bit 15: values count up from that byte,
 * bit 14: it repeats) or the bytes themselves, padded to an even count. */
typedef struct __attribute__((packed)) {
    u16 header;
    u8 data[0];
} ByteRun;

u8 func_080D66F0(const u8 **stream, u16 *index, u8 encoded)
{
    u8 result;

    if (encoded) {
        const ByteRun *run = (const ByteRun *)*stream;
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
                *stream += 4;
            } else {
                u32 size = length;

                if (size & 1)
                    size++;
                *stream += 2;
                *stream += size;
            }
            *index = 0;
        }
    } else {
        const u8 *data = *stream;

        result = data[*index];
        (*index)++;
    }
    return result;
}
