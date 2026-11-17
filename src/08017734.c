/* Complete target [0x08017734, 0x0801784C), 280 bytes, 128 instructions
 * (literal pools 0x00000FFF, 0x001FFFFF at 0x080177D0 and 0x001FFFFF at
 * 0x08017848):
 * f0b557464e464546e0b484b0051c0904090c884640460290281c00f0fff94004697d0091
 * ab7c0193af68000c8146002867d01a4eb246181c023840000390e97d490040462bf1eaf8
 * 0004000c80460099404648434000e9680e182b68002b21d0686802994a1c1204120c0292
 * 49082af155fd0006328851461140000b0143398072885146114001437980301d391d039b
 * 5a10034b1a402af14ff80ae0ff0f0000ffff1f00019a301c391c1a4b1a402af143f8298a
 * 04200840002814d000984100cb191c1f8919081f028850461040d0263602321c10432080
 * 023b023909885046084010431880a87f40003f18012040428144404601300004000c8046
 * 494600299dd104b038bc9846a146aa46f0bc01bc00470000ffff1f00
 *
 * Copies func_08017B50(region) * 2 tile rows of a region record (the layout
 * of src/08017618.c and src/0801799C.c) out to its destination.  Each source
 * row is `row + n` wrapped by rows * 2 through func_08142950 (signed
 * remainder).  With a palette callback the first two tiles of the row get
 * the callback's palette for item index / 2 and the rest is copied from the
 * third tile on; without one the whole row is copied.  `flags & 4` gives the
 * last two tiles palette 0xD.
 */

#include "ffta.h"

typedef struct {
    u8 (*row_palette)(void *context, u16 line);
    void *context;
    u16 *destination;
    u16 *tiles;
    u16 flags;
    u8 width;
    u8 unknown_13[2];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[6];
    u8 field_1E;
} TileRegion;

/* The int return of an implicit declaration: this call precedes the u16
 * definition (src/08017B50.c) in its module, and with u16 here r5 and r6
 * swap (22 halfwords, every declaration order).  0x08017E28, the module's
 * other caller, follows the definition and needs u16; src/0804F948.c needs
 * the int view too. */
s32 func_08017B50(TileRegion *region);
s32 func_08142950(s32 numerator, s32 denominator);
void func_0814186C(const void *source, void *destination, u32 control);

void func_08017734(TileRegion *region, u16 row)
{
    u16 *source;
    u32 stride;
    s32 width;
    u16 index = row;
    u16 count = func_08017B50(region) * 2;
    s32 i;
    u16 *destination;

    stride = region->stride;
    width = region->width;
    destination = region->destination;
    for (i = count; i != 0; i--, row++) {
        row = func_08142950(row, region->rows * 2);
        source = region->tiles + row * stride;
        if (region->row_palette) {
            u8 palette = region->row_palette(region->context, index++ >> 1);
            s32 size;

            destination[0] = (source[0] & 0xFFF) | (palette << 12);
            destination[1] = (source[1] & 0xFFF) | (palette << 12);
            /* The byte size of the copy: the ROM forms (width - 2) << 1
             * before the loop (0x0801776A-0x08017770) and halves it with
             * asrs #1 at the call (0x080177C4), as src/0801799C.c halves
             * its byte size for the same CpuSet call. */
            size = (width - 2) * 2;
            func_0814186C(source + 2, destination + 2, (size / 2) & 0x1FFFFF);
        } else {
            /* The same byte size for the whole row; the halving folds here,
             * as in src/0801799C.c, and the ROM loads width into r2 ahead of
             * the source and destination moves (0x080177D8). */
            s32 size = width * 2;

            func_0814186C(source, destination, (size / 2) & 0x1FFFFF);
        }
        if (region->flags & 4) {
            destination[stride - 2] = (source[stride - 2] & 0xFFF) | 0xD000;
            destination[stride - 1] = (source[stride - 1] & 0xFFF) | 0xD000;
        }
        destination += region->field_1E;
    }
}
