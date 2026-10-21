/* func_08013728 - 0x08013728, 108 bytes (102 code + 2 pad + 4 literal pool)
 *
 * Moves a cursor inside an 8x8 cell block: the cell index lives in the u16
 * at +0x08 of the object, the pixel offset in the u32 at +0x04.
 *
 *   30b5 051c 0904 0914 0029 29d0 2889 0724 0440 6418 0818 2881
 *   072c 04dd 281c 0021 0022 00f085f8 002c 08db 0348 0440 e100 6868
 *   4018 6860 13e0 f8ff0000 6442 0834 0948 0440 e100 6868 401a 6860
 *   281c 0121 0722 00f0c9f8 281c 0021 0622 00f0c4f8 30bc 01bc 0047
 *   0000 f8ff0000
 *   pool 0x08013760: 0x0000FFF8
 *   pool 0x08013790: 0x0000FFF8
 *
 * Four build notes, all of them load-bearing:
 *
 *   - The index is built in two steps, `index = value & 7; index += amount;`.
 *     Written as one expression the compiler allocates the masked value to a
 *     scratch register and copies it into the index register, and the s16
 *     parameter then lands in r2 instead of staying in r1: the difference is
 *     `asrs r2, r1, #0x10` against the ROM's `asrs r1, r1, #0x10`.
 *
 *   - `value` is a 32-bit local, not a u16.  With a u16 the sum stored back
 *     into the u16 field is narrowed to 16 bits, the amount is then taken
 *     unsigned, and the compiler adds a `lsrs r3, r1, #0x10` of its own.
 *
 *   - The negative branch negates first and adds eight after
 *     (`index = -index; index += 8;`), which is `rsbs r4, r4, #0` followed by
 *     `adds r4, #8`; `index = 8 - index` gives `movs r0, #8; subs r0, r0, r4`
 *     instead.
 *
 *   - The mask is applied after the move, so it clears the three low bits of
 *     the cell column before it is scaled by eight.  0xFFF8 does not fit a
 *     Thumb immediate, so it comes from the literal pool - once for each of
 *     the two branches, which is why the ROM carries the word twice.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u32 field_04;       /* pixel offset */
    u16 field_08;       /* cell index */
} Struct08013728;

void func_08013858(Struct08013728 *obj, s32 first, s32 second);
void func_08013910(Struct08013728 *obj, s32 first, s32 second);

void func_08013728(Struct08013728 *obj, s16 amount)
{
    s32 value;
    int index;

    if (amount == 0)
        return;

    value = obj->field_08;
    index = value & 7;
    index += amount;
    obj->field_08 = value + amount;

    if (index > 7) {
        func_08013858(obj, 0, 0);
    }

    if (index >= 0) {
        index &= 0xFFF8;
        obj->field_04 += index << 3;
    } else {
        index = -index;
        index += 8;
        index &= 0xFFF8;
        obj->field_04 -= index << 3;
        func_08013910(obj, 1, 7);
        func_08013910(obj, 0, 6);
    }
}
