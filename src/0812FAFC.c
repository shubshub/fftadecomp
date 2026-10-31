#include "ffta.h"

/* Complete target [0x0812FAFC, 0x0812FC72): 374 bytes, 101 instructions.
 * f0b54f464646c0b481460c1c00260025291c1d310906090e484698f7c5f90135a846002800d19ce041010e480f180025
 * 381c1a3040190178301c084101221040002800d089e0101c884006433004060c481f232800d980e08000034940180068
 * 8746000080d1510868fb1208f8fb120856fc120856fc120856fc120856fc120804fc120856fc120856fc120856fc1208
 * 56fc120810fc120856fc120856fc120856fc120856fc12081cfc120856fc120856fc120856fc120856fc120828fc1208
 * 56fc120856fc120856fc120856fc120834fc120856fc120856fc120856fc120856fc120840fc120856fc120856fc1208
 * 56fc120856fc12084cfc120801202056fff774fe607028e002202056fff76efea07022e003202056fff768fee0701ce0
 * 04202056fff762fe207116e005202056fff75cfe607110e006202056fff756fea0710ae007202056fff750fee07104e0
 * 08202056fff74afe20720135022d00dc66e74546042d00dc52e718bc9846a146f0bc01bc0047
 */

typedef struct {
    u8 unknown_00[0x1A];
    u8 modifiers[3];
    u8 unknown_1D[3];
} Equipment;

typedef struct {
    u8 unknown_00;
    s8 fields_01[8];
} ModifierRecord;

extern const Equipment g_table_0851D180[];
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_0812F8E8(s8 value);

/* The variable shifts retain ordinary C shift definedness requirements.
 * No table-byte count bound or all-input numerical equivalence is asserted.
 */
void func_0812FAFC(const void *unit, ModifierRecord *record)
{
    u16 seen = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        s32 identifier = func_080C7EA4(unit, (u8)(i + 29));

        if (identifier) {
            const Equipment *equipment = &g_table_0851D180[identifier];

            for (j = 0; j < 3; j++) {
                u8 modifier = equipment->modifiers[j];

                if (!((seen >> modifier) & 1)) {
                    seen |= 1U << modifier;
                    switch (modifier) {
                    case 5:
                        record->fields_01[0] = func_0812F8E8(record->fields_01[0]);
                        break;
                    case 10:
                        record->fields_01[1] = func_0812F8E8(record->fields_01[1]);
                        break;
                    case 15:
                        record->fields_01[2] = func_0812F8E8(record->fields_01[2]);
                        break;
                    case 20:
                        record->fields_01[3] = func_0812F8E8(record->fields_01[3]);
                        break;
                    case 25:
                        record->fields_01[4] = func_0812F8E8(record->fields_01[4]);
                        break;
                    case 30:
                        record->fields_01[5] = func_0812F8E8(record->fields_01[5]);
                        break;
                    case 35:
                        record->fields_01[6] = func_0812F8E8(record->fields_01[6]);
                        break;
                    case 40:
                        record->fields_01[7] = func_0812F8E8(record->fields_01[7]);
                        break;
                    }
                }
            }
        }
    }
}
