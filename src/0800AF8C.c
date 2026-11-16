#include "ffta.h"

/* Target: complete [0x0800AF8C, 0x0800AFAA), 30 bytes, 15 instructions.
 * 00b5021c5188082008408020000208409069017840780002084302bc0847
 *
 * Returns the entry count kept in the two-byte header of the table's data;
 * src/0800B2A4.c, src/0800B394.c and src/0800B47C.c store it less one.  The
 * two flag bits choose the record layout as in src/0800ACA8.c and
 * src/0800B13C.c, whose entry structs these are: 0x8000 selects byte records
 * and 8 the long ones.
 */

struct __attribute__((packed)) ByteEntry6_0800AF8C {
    u8 unknown_00;
    u8 value;
    u8 unknown_02[4];
};

struct __attribute__((packed)) ByteEntry2_0800AF8C {
    u8 unknown_00;
    u8 value;
};

struct __attribute__((packed)) WordEntry8_0800AF8C {
    u8 unknown_00[2];
    s16 value;
    u8 unknown_04[4];
};

struct __attribute__((packed)) WordEntry4_0800AF8C {
    u8 unknown_00[2];
    s16 value;
};

struct __attribute__((packed)) ByteData6_0800AF8C {
    u16 count;
    struct ByteEntry6_0800AF8C entries[1];
};

struct __attribute__((packed)) ByteData2_0800AF8C {
    u16 count;
    struct ByteEntry2_0800AF8C entries[1];
};

struct __attribute__((packed)) WordData8_0800AF8C {
    u16 count;
    struct WordEntry8_0800AF8C entries[1];
};

struct __attribute__((packed)) WordData4_0800AF8C {
    u16 count;
    struct WordEntry4_0800AF8C entries[1];
};

struct Table0800AF8C {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[0x14];
    const u8 *data;
};

u16 func_0800AF8C(const struct Table0800AF8C *table)
{
    /* Every layout has the count at offset 0, so the four reads compile to
     * one; the ROM keeps the flag load and both tests, whose results are
     * never used (ands at 0x0800AF94 and 0x0800AF9A), and saves lr. */
    if (table->flags & 8) {
        if (table->flags & 0x8000) {
            const struct ByteData6_0800AF8C *data =
                (const struct ByteData6_0800AF8C *)table->data;

            return data->count;
        } else {
            const struct WordData8_0800AF8C *data =
                (const struct WordData8_0800AF8C *)table->data;

            return data->count;
        }
    } else {
        if (table->flags & 0x8000) {
            const struct ByteData2_0800AF8C *data =
                (const struct ByteData2_0800AF8C *)table->data;

            return data->count;
        } else {
            const struct WordData4_0800AF8C *data =
                (const struct WordData4_0800AF8C *)table->data;

            return data->count;
        }
    }
}
