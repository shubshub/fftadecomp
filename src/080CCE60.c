// 0x080CCE60 - 228 bytes: 222 of code, 2 of padding and a 4-byte literal
// pool (0x0851BA84, the address of g_table_0851BA84).
//
// Reads two attribute values out of a record and hands back the row of
// g_table_0851BA84 that the record belongs to.
//
// The record layout is only known where the instructions reach it, so the
// gaps are left unnamed rather than filled in with invented members:
//   +0x06  u8  table index - the row of g_table_0851BA84
//   +0x08  u8  the id handed to func_080C8570
//   +0x35  u8  override flag for mode 1
//   +0x36  u8  override flag for mode 2
//   +0x37  u8  override flag for mode 3
#include "ffta.h"

extern const u8 *const g_table_0851BA84[];

u32 func_080C92F0(void *data, u32 selector);
u32 func_080C8570(u8 first, u8 second, u8 selector);

typedef struct {
    u8 unknown_00[6];
    u8 table_index;      /* +0x06 */
    u8 unknown_07;
    u8 entity;           /* +0x08 */
    u8 unknown_09[0x2C];
    u8 override_1;       /* +0x35 */
    u8 override_2;       /* +0x36 */
    u8 override_3;       /* +0x37 */
} Record080CCE60;

const u8 *func_080CCE60(Record080CCE60 *record, u8 mode, u8 *first, u8 *second)
{
    u8 override = 0;
    u32 index = 0;
    u8 value2 = 0;
    u8 value1 = 0;

    switch (mode) {
    case 1:
        value1 = (u8)func_080C92F0(record, 0x25);
        value2 = (u8)func_080C92F0(record, 0x26);
        override = record->override_1;
        index = record->table_index;
        break;
    case 2:
        value1 = (u8)func_080C8570(record->entity, record->entity, 0x25);
        value2 = (u8)func_080C8570(record->entity, record->entity, 0x26);
        override = record->override_2;
        index = record->table_index;
        break;
    case 3:
        value1 = (u8)func_080C8570(1, 1, 0x25);
        value2 = (u8)func_080C8570(1, 1, 0x26);
        override = record->override_3;
        break;
    default:
        break;
    }

    // Mode 3 asks for the override of entity 1 already, so it is left alone.
    if (mode != 3 && override == 1) {
        value1 = (u8)func_080C8570(1, 1, 0x25);
        value2 = (u8)func_080C8570(1, 1, 0x26);
        index = 0;
    }

    if (first)
        *first = value1;
    if (second)
        *second = value2;

    return g_table_0851BA84[index];
}
