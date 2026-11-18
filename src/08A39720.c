#include "ffta.h"

typedef struct {
    u8 unknown_00[0x154];
    const u8 *data_154;
    const void *data_158;
} ObjectData;

/* 0x08A39720..0x08A39734, 20 bytes. Slot 08394038 points to this
 * routine in IWRAM. The object walker at 08A38D4A reads bytes through
 * the pointer returned here.
 */
const u8 *func_08A39720(void *object, const void *data)
{
    ObjectData *state = object;

    state->data_158 = data;
    return state->data_154;
}
