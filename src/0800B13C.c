#include "ffta.h"

/* Complete [0x0800B13C, 0x0800B2A4): 360 bytes, 175 instructions, two literal
 * words in two pools.
 * f0b5021c002651888020400008400027002800d0578994890b1c08201840002850d08020
 * 00021840002819d095693b1c190420040214814200dd8ee0ec1c18040014410009184900
 * 61180978891909040e0c01300004030c00149042efdd7ce095693b0424041814a34276dc
 * c0002818017940790002084300040014104988426bd00f1c1b14d8002818027941790902
 * 1143090409143004001440180004060c01331b041814a34257dcc0002818017940790002
 * 084300040014b842e2d14ce0e7030000802000020840002816d095693b1c190420040214
 * 81423edcec1c18040014410061180978891909040e0c01300004030c00149042f1dd2ee0
 * 95693b0424041814a34228dc80002818017940790002084300040014124988421dd00f1c
 * 1b14980028180279417909021143090409143004001440180004060c01331b041814a342
 * 09dc80002818017940790002084300040014b842e2d1301cf0bc02bc08470000e7030000
 *
 * Sums the `value` of entries first..last of the table's data, where first
 * is `loop_start` under flag 0x100 and 0 otherwise, and last is `end`.  Two
 * flag bits choose the record layout, as in src/0800ACA8.c (which returns
 * the same field as its `second` output): after a two-byte header, 0x8000
 * selects byte records and 8 the long ones, giving strides of 6, 8, 2 and 4
 * bytes.  The halfword layouts stop at a value of 999, the marker that
 * src/0800AF04.c and src/0800AEA0.c test for; `loop_start` and `end` are
 * the names of src/0800AF04.c.
 *
 * The byte loops have their entry test written apart from the do-while.
 * agbcc carries `i << 16` round the back edge of a `for` loop, which is
 * what the ROM's two 999 loops show and its two byte loops do not.
 */

struct __attribute__((packed)) ByteEntry6_0800B13C {
    u8 unknown_00;
    u8 value;
    u8 unknown_02[4];
};

struct __attribute__((packed)) ByteEntry2_0800B13C {
    u8 unknown_00;
    u8 value;
};

struct __attribute__((packed)) WordEntry8_0800B13C {
    u8 unknown_00[2];
    s16 value;
    u8 unknown_04[4];
};

struct __attribute__((packed)) WordEntry4_0800B13C {
    u8 unknown_00[2];
    s16 value;
};

struct __attribute__((packed)) ByteData6_0800B13C {
    u8 unknown_00[2];
    struct ByteEntry6_0800B13C entries[1];
};

struct __attribute__((packed)) ByteData2_0800B13C {
    u8 unknown_00[2];
    struct ByteEntry2_0800B13C entries[1];
};

struct __attribute__((packed)) WordData8_0800B13C {
    u8 unknown_00[2];
    struct WordEntry8_0800B13C entries[1];
};

struct __attribute__((packed)) WordData4_0800B13C {
    u8 unknown_00[2];
    struct WordEntry4_0800B13C entries[1];
};

struct Table0800B13C {
    u16 unknown_00;
    u16 flags;
    u16 unknown_04[3];
    u16 loop_start;
    u16 end;
    u8 unknown_0e[10];
    const u8 *data;
};

u16 func_0800B13C(const struct Table0800B13C *table)
{
    s16 total = 0;
    u16 first;
    s16 last;
    s16 i;

    if (table->flags & 0x100)
        first = table->loop_start;
    else
        first = 0;
    last = table->end;
    if (table->flags & 8) {
        if (table->flags & 0x8000) {
            const struct ByteData6_0800B13C *data =
                (const struct ByteData6_0800B13C *)table->data;

            i = first;
            if (i <= last) {
                do {
                    total += data->entries[i].value;
                    i++;
                } while (i <= last);
            }
        } else {
            const struct WordData8_0800B13C *data =
                (const struct WordData8_0800B13C *)table->data;

            for (i = first; i <= last && data->entries[i].value != 999; i++)
                total += data->entries[i].value;
        }
    } else {
        if (table->flags & 0x8000) {
            const struct ByteData2_0800B13C *data =
                (const struct ByteData2_0800B13C *)table->data;

            i = first;
            if (i <= last) {
                do {
                    total += data->entries[i].value;
                    i++;
                } while (i <= last);
            }
        } else {
            const struct WordData4_0800B13C *data =
                (const struct WordData4_0800B13C *)table->data;

            for (i = first; i <= last && data->entries[i].value != 999; i++)
                total += data->entries[i].value;
        }
    }
    return total;
}
