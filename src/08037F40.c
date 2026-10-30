#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 current;
} Selection08037F0C;

typedef struct {
    Selection08037F0C selection;
    u16 field_1C;
} Record08037F40;

extern u16 func_08037F0C(const Selection08037F0C *selection, s8 offset);
extern s32 func_08142950(s32 numerator, s32 denominator);

/* Complete [0x08037F40, 0x08037F72): 50 bytes, 23 instructions.
 * 30b5051c141c2404240c09060916fff7ddff0004000ce97d0af1fafc0004000c
 * 64006043ad8b40190004000c30bc02bc0847
 */
u16 func_08037F40(const Record08037F40 *record, s8 offset, u16 stride)
{
    u16 value = func_08037F0C(&record->selection, offset);

    return (u16)func_08142950(value, record->selection.unknown_00[0x17])
           * (stride << 1) + record->field_1C;
}
