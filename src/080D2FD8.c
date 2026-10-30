/* Target bytes (76):
 * 10 b5 04 1c 24 06 24 0e 60 00 00 19 80 00 0d 49
 * 40 18 42 78 f5 21 11 40 00 22 41 70 82 70 20 1c
 * 14 30 00 21 f6 f7 e0 fa 07 48 00 21 f6 f7 b6 fa
 * b0 20 c0 00 24 18 20 1c 01 21 f6 f7 af fa 10 bc
 * 01 bc 00 47 b4 2c 00 02 9f 05 00 00
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 value;
    u8 unknown_03[9];
} Record080D2FD8;

extern Record080D2FD8 g_state_02002CB4[];
extern void func_080C95C0(u16 index, u32 value);
extern void func_080C9574(u16 bitIndex, u16 enabled);

void func_080D2FD8(u8 index)
{
    Record080D2FD8 *record = &g_state_02002CB4[index];

    record->flags &= 0xF5;
    record->value = 0;
    func_080C95C0(index + 0x14, 0);
    func_080C9574(0x59F, 0);
    func_080C9574(index + 0x580, 1);
}
