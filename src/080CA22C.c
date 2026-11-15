#include "ffta.h"

typedef struct {
    u8 unknown_00[7];
    u8 field_07;
    u8 unknown_08[0x20];
    u16 flags;
    u8 unknown_2A[0x16];
    u8 values[0];
} Unit;

extern u32 func_080C92F0(void *object, u32 selector);

/* Complete [0x080CA22C, 0x080CA268): 60 bytes, 29 instructions.
 * 10b5041c2121fff75df8011c002904d0201c40304018e4210170e07900280ad0
 * 44380006000e012805d8218d80221201101c0843208510bc01bc0047
 */
void func_080CA22C(Unit *unit)
{
    u32 index = func_080C92F0(unit, 0x21);

    if (index != 0)
        unit->values[index] = 0xE4;
    if (unit->field_07 != 0) {
        if (unit->field_07 == 0x44 || unit->field_07 == 0x45)
            unit->flags |= 0x800;
    }
}
