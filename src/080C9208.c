#include "ffta.h"

/* Complete [0x080C9208, 0x080C92F0): 232 bytes, 93 instructions, including
 * the jump-table address literal at 0x080C9228, the nine-entry jump table at
 * 0x080C922C and the table literal at 0x080C92EC.
 * Target: 70b50004000c0d1cff21a97069702970ca38082845d8800001494018006887462c920c08
 * 50920c0858920c0866920c086e920c087c920c0884920c088c920c0894920c08a2920c08
 * 00202870012027e002202870032068700420a87021e00520287006201ce0072028700820
 * 68700920a87016e00a2028700b2011e00c2028700d200de00e2028700f2009e010202870
 * 112005e00020087021e0122028701320687000262c1ca9192078ff28f2d0031c1a010c48
 * 12181178507800020843917809040143d07800060843002802d0181c03f0fefb20700134
 * 0136022ee3dd70bc01bc0047782e0002
 *
 * Fills the three output bytes with the template indices for selector
 * 0xCA..0xD2 (0xFF marks an unused slot), then replaces each index with
 * func_080CCAD8(index) when data_02002E78[index].name is non-zero and with 0
 * otherwise; the first unused slot is zeroed and ends the scan.
 */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06[2];
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

extern UnitTemplate data_02002E78[];
extern u8 func_080CCAD8(u8 index);

void func_080C9208(u16 selector, void *data)
{
    /* The typed view is a statement, as in this module's src/080C92F0.c and
     * src/080C9078.c: the ROM narrows the selector (0x080C920A) before it
     * copies data to r5 (0x080C920E); a u8 * parameter is copied first. */
    u8 *output = data;
    UnitTemplate *entry;
    s32 i;

    output[0] = output[1] = output[2] = 0xFF;
    switch (selector) {
    case 0xCA:
        output[0] = 0;
        output[1] = 1;
        break;
    case 0xCB:
        output[0] = 2;
        output[1] = 3;
        output[2] = 4;
        break;
    case 0xCC:
        output[0] = 5;
        output[1] = 6;
        break;
    case 0xCD:
        output[0] = 7;
        output[1] = 8;
        output[2] = 9;
        break;
    case 0xCE:
        output[0] = 10;
        output[1] = 11;
        break;
    case 0xCF:
        output[0] = 12;
        output[1] = 13;
        break;
    case 0xD0:
        output[0] = 14;
        output[1] = 15;
        break;
    case 0xD1:
        output[0] = 16;
        output[1] = 17;
        break;
    case 0xD2:
        output[0] = 18;
        output[1] = 19;
        break;
    }

    for (i = 0; i < 3; i++) {
        if (output[i] == 0xFF) {
            output[i] = 0;
            return;
        }
        /* Element pointer as src/08058C48.c takes into the same table: the
         * ROM shifts the index (0x080C92B8) before loading the table address
         * inside the loop (0x080C92BA); direct indexing hoists it to r7. */
        entry = &data_02002E78[output[i]];
        if (entry->name != 0)
            output[i] = func_080CCAD8(output[i]);
        else
            output[i] = 0;
    }
}
