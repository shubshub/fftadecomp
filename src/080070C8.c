// func_080070C8 - 0x080070C8, 112 bytes (0x080070C8 .. 0x08007138).
//
// target  70b50c1c061c114d2a6808213bf1baf8083ca408b471240af471341c08342a68
//         201c0c213bf1aef87020207173206071b179f079000208430338a071000ae071
//         002c05d0a01b8003010c02e0b8d436080021ff20084000223070090a7170b070
//         f1700012030717271301c70bc02bc0847
//
// The indexed span stops at 0x080070D6, in the middle of the first call, so
// the body has to be read out of the ROM: it ends at the interworking return
// `pop {r1}; bx r1` at 0x08007136.
//
// The function works on a 16-byte object made of two 8-byte records.  The
// first record gets the index of the second record inside the object (in
// units of four bytes, so 2 here) in both of its halfwords, a flag pair 1/0
// and a count; the second record gets the pair 0x70/0x73 and the count minus
// three.  A callback taken from a table in the cartridge ROM is invoked once
// for each record, with the record pointer and the constant 8 or 12.
//
// The literal pool holds one word, 0x0836D4B8, at 0x08007114 - agbcc flushes
// it there because the branch at 0x08007112 skips over it.  The word it points
// at is the callback address 0x03005E79, so the table is read for a function
// pointer and the call goes through the `bx r2` thunk at 0x0814224C.

#include "ffta.h"

typedef void (*ObjectFunc)(void *, u32);

typedef struct {
    u8 unknown_00;      /* +0 - low byte of the index halfword */
    u8 unknown_01;      /* +1 - high byte of the index halfword */
    u8 unknown_02;      /* +2 - low byte of the second index halfword */
    u8 unknown_03;      /* +3 - high byte of the second index halfword */
    u8 unknown_04;      /* +4 - set to 1 */
    u8 unknown_05;      /* +5 - set to 0 */
    u8 unknown_06;      /* +6 - low byte of the count halfword */
    u8 unknown_07;      /* +7 - high byte of the count halfword */
} Record080070C8;

u8 *func_080070C8(u8 *a, u32 b)
{
    Record080070C8 *object = (Record080070C8 *)a;
    // plausible: a read-only table in the cartridge ROM, holding a callback
    u32 *table = (u32 *)0x0836D4B8;
    u8 *second;
    u16 count;
    u32 value;
    u32 index;
    u32 low;
    u32 byte;

    ((ObjectFunc)(*table))(object, 8);

    count = (b - 8) >> 2;
    object->unknown_06 = count;
    object->unknown_07 = count >> 8;

    second = a + 8;
    ((ObjectFunc)(*table))(second, 12);

    second[4] = 0x70;
    second[5] = 0x73;

    byte = object->unknown_06;
    value = (object->unknown_07 << 8) | byte;
    value -= 3;
    second[6] = value;
    second[7] = value >> 8;

    index = second ? ((u32)(second - a) << 14) >> 16 : 0;
    low = index & 0xff;
    object->unknown_00 = low;
    object->unknown_01 = index >> 8;
    object->unknown_02 = low;
    object->unknown_03 = index >> 8;
    object->unknown_04 = 1;
    object->unknown_05 = 0;

    return (u8 *)object;
}
