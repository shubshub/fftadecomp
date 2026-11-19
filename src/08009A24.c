#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 unknown_03;
} Entry08009A14;

typedef struct {
    u8 unknown_0000[0x2192];
    u16 current;
    u8 unknown_2194[0x3C2A - 0x2194];
    u8 index;
} State08009A24;

/* Archive entry 0x3D (g_table_089C1484 + 0x30D38) is itself a table of 26 word
 * offsets, each measured from the start of g_table_089C1484; its first offset,
 * 0x30DA0, is where the 26 words end.  The ROM indexes it base first
 * (`adds r0, r4, r0` at 0x08009A72), while the archive's own offset table is
 * indexed offset first (`adds r0, r0, r6` at 0x08009A48). */
typedef struct {
    u32 offsets[26];
} Bank08009A24;

extern State08009A24 g_state_02000000;
extern const u8 g_table_089C1484[];

const Entry08009A14 *func_08009A14(u16 index);

/* Target [0x08009A24, 0x08009A90), 108 complete bytes:
 * 70b50004050cef2d03d9aa20fff7f0ff05e01248124940180088fff7e9ff8178
 * 8800104e801900688419ef2d12d83d2910d10a480c4940180078002802d00138
 * 0006000e0a2139f121f80006800d201800688419201c70bc02bc084700000002
 * 9221000084149c082a3c0000
 */
const u8 *func_08009A24(u16 index)
{
    const Entry08009A14 *entry;
    const u8 *result;
    u8 value;

    if (index >= 0xF0)
        entry = func_08009A14(0xAA);
    else
        entry = func_08009A14(g_state_02000000.current);

    result = g_table_089C1484 + ((const u32 *)g_table_089C1484)[entry->field_02];
    if (index < 0xF0 && entry->field_02 == 0x3D) {
        value = g_state_02000000.index;
        if (value != 0)
            value--;
        result = g_table_089C1484 + ((const Bank08009A24 *)result)->offsets[value / 10];
    }
    return result;
}
