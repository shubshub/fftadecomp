#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 field_04;
    u8 unknown_05[4];
    u8 field_09;
    u8 unknown_0A[0xFE];
} Record080CA078;

extern Record080CA078 g_state_02000080[24];
extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete [0x080CA078, 0x080CA0BC): 68 bytes, 30 instructions.
 * 30b5002400210e48021d84256d0017231078002802d05079241801315219013b002bf5da002904d0201c78f009fb002800d101200006000e30bc02bc0847000080000002
 */
u8 func_080CA078(void)
{
    Record080CA078 *record = g_state_02000080;
    s32 total = 0;
    s32 count = 0;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        if (record->field_04 != 0) {
            total += record->field_09;
            count++;
        }
    }
    if (count != 0) {
        s32 result = func_081426B8(total, count);

        if (result != 0)
            return result;
    }
    return 1;
}
