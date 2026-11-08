#include "ffta.h"

/* func_08126B08 [0x08126B08,0x08126B3C) 52 bytes
 * raw: 00b587b00006000e0906090e1206120e1b061b0e029068468182c2820383044848216a460023fbf72df807b001bc00472d681208 */

typedef struct Descriptor126B08 {
    u32 unknown_00;
    u32 unknown_04;
    u32 value;
    u32 unknown_0C;
    u32 unknown_10;
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Descriptor126B08;

extern int func_0812682C(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Descriptor126B08 *, void *);

void func_08126B08(u8 value, u8 first, u8 second, u8 third)
{
    Descriptor126B08 d;

    d.value = value;
    d.first = first;
    d.second = second;
    d.third = third;
    func_08121B8C(func_0812682C, 0x48, &d, 0);
}
