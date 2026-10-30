/* Target bytes (56):
 * 30 b5 0a 4d cc 22 04 1c 54 43 28 68 20 18 08 4a
 * 80 18 09 06 09 16 df f7 af fe 29 68 09 19 05 4a
 * 89 18 08 70 30 bc 01 bc 00 47 00 00 10 28 00 03
 * cc 09 00 00 8a 09 00 00
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

extern u8 *g_state_03002810;
extern u16 func_08017B68(ClampState08017B68 *state, u32 index);

void func_08037DF0(u32 index, s8 adjustment)
{
    u8 **state = &g_state_03002810;
    u32 offset = index * 0xCC;
    u16 value = func_08017B68(
        (ClampState08017B68 *)(offset + *state + 0x9CC),
        adjustment);
    u8 *record = *state + offset;

    record[0x98A] = value;
}
