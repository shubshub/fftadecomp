#include "ffta.h"

// Complete target [0x08023130, 0x0802317A): 74 bytes, 37 instructions.

typedef struct {
    void *unit;
} Entry08023130;

extern void func_0802292C(u32 value);
extern void *func_08096D7C(void);
extern s32 func_08099CDC(void *context, Entry08023130 **entries);
extern u8 func_080C8240(void *unit);
extern u8 func_080CB65C(void *unit, u8 mode);
extern void func_0801AECC(void);

void func_08023130(void)
{
    Entry08023130 *entries[13];
    s32 count;
    s32 i;

    func_0802292C(2);
    count = func_08099CDC(func_08096D7C(), entries);
    for (i = 0; i < count; i++) {
        void *unit = entries[i]->unit;

        func_080CB65C(unit, func_080C8240(unit) == 0);
    }
    func_0801AECC();
}
