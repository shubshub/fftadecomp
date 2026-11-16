#include "ffta.h"

/* Complete [0x0800ADD8, 0x0800AE9E): 198 bytes, 99 instructions, no literal
 * pool.
 * f0b5474680b4051c141c069e079f0898804689048a0c9446698801200840002806d08020
 * c0010840002806d1696920e08020c0010840002819d069695000401800880918002c00d0
 * 2060002b01d008781880002e01d048783080002f01d0887838804246002a29d0c8781080
 * 26e0696962469000401800680a18002c00d02060002b04d011785078000208431880002e
 * 04d09178d078000208433080002f04d0117950790002084338804046002805d09179d079
 * 000208434146088008bc9846f0bc01bc0047
 *
 * Looks up frame `index` (low 14 bits) in the table's frame data and returns
 * its offset and header: flag 0x4000 selects halfword offsets to records
 * with a four-byte header, otherwise word offsets to records whose header is
 * four little-endian halfwords, read through packed structs as
 * src/0800B13C.c does.  The header is width and height (as src/0800A71C.c
 * and src/0800AA54.c read it) and the origin that src/0800C0AC.c subtracts.
 */

struct __attribute__((packed)) ByteFrame_0800ADD8 {
    u8 width;
    u8 height;
    u8 origin_x;
    u8 origin_y;
};

struct __attribute__((packed)) WordFrame_0800ADD8 {
    u16 width;
    u16 height;
    u16 origin_x;
    u16 origin_y;
};

struct Table0800ADD8 {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[0x10];
    const u8 *frames;
};

void func_0800ADD8(const struct Table0800ADD8 *table, u16 index, u32 *offset,
                   u16 *first, u16 *second, u16 *third, u16 *fourth)
{
    index &= 0x3FFF;
    /* Bit 0 picks func_0800B568's renderer (set: func_0800A71C, halfword
     * cells; clear: func_0800AA54, byte cells) but not this header, so the
     * halves are the same code.  The ROM keeps the bit-0 test
     * (0x0800ADF0-0x0800ADF8), a 0x4000 test on each side (0x0800ADFA,
     * 0x0800AE08) and `mov r2, ip` (0x0800AE48) on the clear side only. */
    if (table->flags & 1) {
        if (table->flags & 0x4000) {
            const u8 *frames = table->frames;
            u32 entry_offset = ((const u16 *)frames)[index];
            const struct ByteFrame_0800ADD8 *frame =
                (const struct ByteFrame_0800ADD8 *)(frames + entry_offset);

            if (offset)
                *offset = entry_offset;
            if (first)
                *first = frame->width;
            if (second)
                *second = frame->height;
            if (third)
                *third = frame->origin_x;
            if (fourth)
                *fourth = frame->origin_y;
        } else {
            const u8 *frames = table->frames;
            u32 entry_offset = ((const u32 *)frames)[index];
            const struct WordFrame_0800ADD8 *frame =
                (const struct WordFrame_0800ADD8 *)(frames + entry_offset);

            if (offset)
                *offset = entry_offset;
            if (first)
                *first = frame->width;
            if (second)
                *second = frame->height;
            if (third)
                *third = frame->origin_x;
            if (fourth)
                *fourth = frame->origin_y;
        }
    } else {
        if (table->flags & 0x4000) {
            const u8 *frames = table->frames;
            u32 entry_offset = ((const u16 *)frames)[index];
            const struct ByteFrame_0800ADD8 *frame =
                (const struct ByteFrame_0800ADD8 *)(frames + entry_offset);

            if (offset)
                *offset = entry_offset;
            if (first)
                *first = frame->width;
            if (second)
                *second = frame->height;
            if (third)
                *third = frame->origin_x;
            if (fourth)
                *fourth = frame->origin_y;
        } else {
            const u8 *frames = table->frames;
            u32 entry_offset = ((const u32 *)frames)[index];
            const struct WordFrame_0800ADD8 *frame =
                (const struct WordFrame_0800ADD8 *)(frames + entry_offset);

            if (offset)
                *offset = entry_offset;
            if (first)
                *first = frame->width;
            if (second)
                *second = frame->height;
            if (third)
                *third = frame->origin_x;
            if (fourth)
                *fourth = frame->origin_y;
        }
    }
}
