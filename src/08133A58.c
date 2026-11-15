#include "ffta.h"

/* Complete [0x08133A58, 0x08133ADC): 132 bytes, 63 instructions.
 * The 44 flag bits live in the two words at +0xE8 and +0xEC; both words are
 * saved before the calls and written back after the check. */
typedef struct {
    u8 unknown_00[0xE8];
    u32 flags[2];
} Unit;

extern u8 func_08131030(u32 unit);
extern void func_080CDE80(Unit *object, u8 enabled);
extern u8 func_081339A8(u32 record_index, s32 bit_index, u8 second);

static inline u8 bit_is_set(const u8 *flags, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;
    u8 value = flags[byte_index];

    if ((value >> bit_index) & 1)
        return 1;
    return 0;
}

/* An inlined copy of func_081339F0 (src/081339F0.c). */
static inline u8 inlined_081339F0(const u8 *flags, u32 record_index)
{
    s32 index;

    for (index = 0; index < 44; index++) {
        if (bit_is_set(flags, index)) {
            if (func_081339A8(record_index, index, 0) == 0)
                return 0;
        }
    }
    return 1;
}

u8 func_08133A58(Unit *unit, u32 record_index)
{
    u32 saved[2];
    u8 result;

    saved[0] = unit->flags[0];
    saved[1] = unit->flags[1];
    if (func_08131030((u32)unit))
        func_080CDE80(unit, 1);
    result = inlined_081339F0((const u8 *)unit->flags, record_index);
    unit->flags[0] = saved[0];
    unit->flags[1] = saved[1];
    return result;
}
