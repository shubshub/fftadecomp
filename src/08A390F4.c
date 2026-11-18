#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    s16 primary;
    s16 secondary;
    u8 unknown_06[0x10];
    s8 priority;
} ObjectSortKeys;

/* The object insertion routine at 08A39774 descends right for a strict
 * greater-than result. Priorities -128 through -124 form the lower class. */
struct ObjectNode08A39774;
s32 func_08A390F4(const struct ObjectNode08A39774 *current,
                  const struct ObjectNode08A39774 *node)
{
    const ObjectSortKeys *a = (const ObjectSortKeys *)current;
    const ObjectSortKeys *b = (const ObjectSortKeys *)node;

    if (a->primary > b->primary)
        return 1;
    if (a->primary == b->primary) {
        if (b->priority <= -124 && a->priority > -124)
            return 1;
        if (a->priority <= -124 && b->priority > -124)
            return 0;
        if (a->secondary > b->secondary)
            return 1;
        if (a->secondary == b->secondary && a->priority > b->priority)
            return 1;
    }
    return 0;
}
