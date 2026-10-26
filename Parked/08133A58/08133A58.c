#include "ffta.h"

/* Target: complete [0x08133A58, 0x08133ADC), 132 bytes, 63 instructions.
 * The two saved flag words are observed at +0xe8 and +0xec. */
typedef struct {
    u8 unknown_00[0xe8];
    u32 flags[2];
} Object08133A58;

extern u8 func_08131030(Object08133A58 *);
extern void func_080CDE80(Object08133A58 *, u8);
extern u8 func_081339A8(u32, s32, u8);

static inline u8 flag_is_set(const u8 *flags, s32 index)
{
    s32 byteIndex = index >> 3;
    s32 bitOffset = index & 7;

    if ((flags[byteIndex] >> bitOffset) & 1)
        return 1;
    return 0;
}

static inline u8 flags_supported(u32 selector, const u8 *flags)
{
    s32 index;

    for (index = 0; index < 44; index++) {
        if (flag_is_set(flags, index)) {
            if (!func_081339A8(selector, index, 0))
                return 0;
        }
    }
    return 1;
}

u8 func_08133A58(Object08133A58 *object, u32 selector)
{
    u32 first = object->flags[0];
    u32 second = object->flags[1];
    u8 result;

    if (func_08131030(object))
        func_080CDE80(object, 1);
    result = flags_supported(selector, (const u8 *)object->flags);
    object->flags[0] = first;
    object->flags[1] = second;
    return result;
}
