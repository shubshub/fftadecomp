#include "ffta.h"

extern u8 g_state_02000000[];

/* 0x08046854..0x08046910, 188 bytes:
 * f0b557464e464546e0b481b084460d1c09981206120e1b041b0c00931e1c0006000e
 * 8046074b5100074c1819401882460478622c0cd9054fd81908180021017032e00000
 * 00000002b4210000b5210000194fd81909188946097860462a308018027889180906
 * 0a0e632a0cd9101c6421fcf030f90006020e601c0006040e29880098084328804046
 * 002805d020180006040e288806432e80622c01d96324002251460c704c46227001b0
 * 38bc9846a146aa46f0bc01bc0047b5210000
 */
void func_08046854(u8 *object, u16 *flags, u8 index, u16 mask,
                   u8 extra)
{
    u8 first = g_state_02000000[0x21B4 + index * 2];
    u8 second;

    if (first > 98) {
        g_state_02000000[0x21B5 + index * 2] = 0;
        return;
    }

    second = g_state_02000000[0x21B5 + index * 2] + object[0x2A + index];
    if (second > 99) {
        second %= 100u;
        first++;
        *flags |= mask;
    }
    if (extra != 0) {
        first += extra;
        *flags |= mask;
    }
    if (first > 98) {
        first = 99;
        second = 0;
    }
    g_state_02000000[0x21B4 + index * 2] = first;
    g_state_02000000[0x21B5 + index * 2] = second;
}
