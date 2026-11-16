#include "ffta.h"

// Complete [0x080D2AD0, 0x080D2BF4): 292 bytes.
// f0b557464e464546e0b482b081468a4600921f1c4c460020804600210191d045
// 70da0026207862780321114009020143031c002960d0044d481908284bd88000
// 024940180068874693feffff202b0d08aa2b0d08522b0d08522b0d08aa2b0d08
// 522b0d08522b0d08442b0d08522b0d08522b0d083620f6f7fbfc000600282ad0
// 2be003252a4010021843234940180004000c012805d83620f6f7eafc00060028
// 19d0217860782840000208431b494018f6f7defc0006002800d0012621786078
// 284000020843164d4019f6f7d1fc0006002800d00126002e0ed0009810c00090
// 012188444d46a8781e39014004200143a970013f002f05d00198013001901034
// 50458edb404602b038bc9846a146aa46f0bc02bc084700008cfefffffe020000
// ff020000

typedef struct {
    u16 id : 10;
    u16 unknown_01 : 8;
    u8 status : 3;
    u8 unknown_02 : 3;
    u8 unknown_03[13];
} __attribute__((packed)) Record080D2AD0;

extern u8 func_080C9540(u16 bit_index);

u32 func_080D2AD0(Record080D2AD0 *records, s32 count, Record080D2AD0 **output,
                  s32 limit)
{
    Record080D2AD0 *record = records;
    s32 i;
    u32 found_count = 0;

    for (i = 0; i < count; i++, record++) {
        u8 found = 0;

        if (record->id == 0)
            continue;
        switch (record->id) {
        case 0x16D:
        case 0x170:
            found = 1;
            break;
        case 0x173:
            if (func_080C9540(0x36))
                found = 1;
            break;
        case 0x16E:
        case 0x16F:
        case 0x171:
        case 0x172:
        case 0x174:
        case 0x175:
            if ((record->id == 0x174 || record->id == 0x175) &&
                !func_080C9540(0x36))
                break;
            if (func_080C9540(record->id + 0x2FE))
                found = 1;
            if (func_080C9540(record->id + 0x2FF))
                found = 1;
            break;
        }
        if (found) {
            *output++ = record;
            found_count++;
            records->status = 1;
            if (--limit == 0)
                return found_count;
        }
    }
    return found_count;
}
