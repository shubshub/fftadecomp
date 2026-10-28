#include "ffta.h"

/* Target: complete [0x0812D5A0, 0x0812D5F4), 84 bytes, 39 instructions.
 * The table stride is 32 bytes; the three inspected bytes start at +0x1a. */
typedef struct {
    u8 unknown_00[0x1a];
    u8 attributes[3];
    u8 unknown_1d[3];
} Entry0812D5A0;

extern const Entry0812D5A0 g_table_0851D180[];
extern s32 func_080C7EA4(const void *, u32);

u8 func_0812D5A0(const void *object)
{
    s32 count = 0;
    s32 slot;

    for (slot = 0; slot < 5; slot++) {
        u16 entry = func_080C7EA4(object, (u8)(slot + 0x1d));
        if (entry != 0) {
            const Entry0812D5A0 *record = &g_table_0851D180[entry];
            s32 attribute;

            for (attribute = 0; attribute < 3; attribute++) {
                if (record->attributes[attribute] == 0x3c) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}
