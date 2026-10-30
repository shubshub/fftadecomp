#include "ffta.h"

/* 0x080CB27C..0x080CB2B4: 56 bytes, 20 instructions.
 * 30b581b0051c01f0fdfb0006040e002c09d001f011f8064906480090281c221c
 * 022337f713fb01b030bc01bc004700003c1f00023db60c08
 */
typedef s32 (*Compare)(const void *first, const void *second);

extern u16 data_02001F3C[];
extern u32 func_080CCA80(void);
extern void func_080CC2B4(void);
extern s32 func_080CB63C(const void *first, const void *second);
extern void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                          Compare compare);

void func_080CB27C(u8 *workspace)
{
    u8 count = func_080CCA80();

    if (count) {
        func_080CC2B4();
        func_080028C8(workspace, data_02001F3C, count, 2, func_080CB63C);
    }
}
