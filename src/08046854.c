#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2A];
    u8 gains[16];
} Object08046854;

typedef struct {
    u8 unknown_0000[0x21B4];
    u8 slots[16][2];
} State08046854;

extern State08046854 g_state_02000000;

/* 0x08046854..0x08046910, 188 bytes:
 * f0b557464e464546e0b481b084460d1c09981206120e1b041b0c00931e1c0006000e
 * 8046074b5100074c1819401882460478622c0cd9054fd81908180021017032e00000
 * 00000002b4210000b5210000194fd81909188946097860462a308018027889180906
 * 0a0e632a0cd9101c6421fcf030f90006020e601c0006040e29880098084328804046
 * 002805d020180006040e288806432e80622c01d96324002251460c704c46227001b0
 * 38bc9846a146aa46f0bc01bc0047b5210000
 */
void func_08046854(Object08046854 *object, u16 *flags, u8 index, u16 mask,
                   u8 extra)
{
    u8 level = g_state_02000000.slots[index][0];
    u8 exp;
    u8 current;

    if (level > 98) {
        g_state_02000000.slots[index][1] = 0;
        return;
    }

    /* exp starts as the gain: the ROM reads the stored byte first (ldrb r1
     * at 0x080468AC), then loads the gain into r2 (0x080468B4), the register
     * that holds exp through the store at 0x080468FA, and adds stored + gain
     * (adds r1, r1, r2). */
    current = g_state_02000000.slots[index][1];
    exp = object->gains[index];
    exp = current + exp;
    if (exp > 99) {
        exp %= 100u;
        level++;
        *flags |= mask;
    }
    if (extra != 0) {
        level += extra;
        *flags |= mask;
    }
    if (level > 98) {
        level = 99;
        exp = 0;
    }
    g_state_02000000.slots[index][0] = level;
    g_state_02000000.slots[index][1] = exp;
}
