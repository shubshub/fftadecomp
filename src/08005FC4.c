#include "ffta.h"

/* Complete target [0x08005FC4, 0x0800620C): 584 bytes, 288 instructions,
 * including the literal word 0x000003FF at 0x08006148.
 * Target bytes:
 * f0b557464e464546e0b486b0041c0e980f9e0906090e00911204120c01921b04
 * 1b0c02930004000c0390a179e07900020843012181464a460a40914640080840
 * 04900020824671798a4500d3f4e0627992450ed3a079e1790902014308200140
 * 002906d0101c51463bf126fc0004000c00e05046071c049a002a06d061798f42
 * 03d2781c081a0004070c002080465146013105913279904500d3b9e022799045
 * 0ed3a079e1790902014304200140002906d0101c41463bf1fffb0004000c00e0
 * 4046031c4846002806d021798b4203d2581c081a0004030c61798f4254d22579
 * ab4251d2a079e1790902014380221202101c0140002912d02178607800020843
 * a27812040243e17809061143381c6843c01809180b780298834236d134e02178
 * 607800020843a17809040143e27812060a43381c6843c018400080180388114a
 * 111c181c0840029988421dd0019a98180004030c0099080318180004030c4a46
 * 002a05d08021c900081c43401804030c049a002a09d080210901081c43401804
 * 030c02e0ff030000039bb079f1790902014380221202101c0140002911d03178
 * 707800020843b17809040143f27812060a43307951464143081c404412181370
 * 11e03178707800020843b17809040143f27812060a43307951464143081c4044
 * 400080180380a079e1790902014310200140002903d001204a46424091464046
 * 01300004000c80463079804500d245e7a079e1790902014320200140002903d0
 * 0120049941400491059a1004000c82467079824500d20ae706b038bc9846a146
 * aa46f0bc01bc0047
 */

/* Every member, the data pointer included, is read a byte at a time
 * (ldrb at +0..+7), as for the packed TransferDescriptor in src/08005E7C.c.
 * The only caller, func_0800620C (Parked), fills both on its stack, decoding
 * the source from a 16-byte record a byte at a time. */
typedef struct __attribute__((packed)) {
    void *data;
    u8 width;
    u8 height;
    u16 flags;
} TileDescriptor;

s32 func_0814187C(s32 denominator, s32 numerator);

void func_08005FC4(const TileDescriptor *source, u8 palette,
                   u16 tile_offset, u16 transparent, u16 fill,
                   const TileDescriptor *destination)
{
    u32 horizontal_flip = source->flags & 1;
    u32 vertical_flip = (source->flags >> 1) & 1;
    u16 row;
    u16 column;
    u16 source_row;
    u16 source_column;
    u16 value;

    for (row = 0; row < destination->height; row++) {
        source_row = (row >= source->height && (source->flags & 8))
            ? func_0814187C(source->height, row) : row;
        if (vertical_flip && source_row < source->height)
            source_row = source->height - 1 - source_row;

        for (column = 0; column < destination->width; column++) {
            source_column = (column >= source->width && (source->flags & 4))
                ? func_0814187C(source->width, column) : column;
            if (horizontal_flip && source_column < source->width)
                source_column = source->width - 1 - source_column;

            if (source_row < source->height && source_column < source->width) {
                if (source->flags & 0x8000) {
                    value = ((u8 *)source->data)[source_row * source->width + source_column];
                    if (value == transparent)
                        value = fill;
                } else {
                    value = ((u16 *)source->data)[source_row * source->width + source_column];
                    if ((value & 0x3FF) == transparent) {
                        value = fill;
                    } else {
                        value += tile_offset;
                        value += palette << 12;
                        if (horizontal_flip)
                            value ^= 0x400;
                        if (vertical_flip)
                            value ^= 0x800;
                    }
                }
            } else {
                value = fill;
            }

            if (destination->flags & 0x8000)
                ((u8 *)destination->data)[row * destination->width + column] = value;
            else
                ((u16 *)destination->data)[row * destination->width + column] = value;
            if (source->flags & 0x10)
                horizontal_flip ^= 1;
        }
        if (source->flags & 0x20)
            vertical_flip ^= 1;
    }
}
