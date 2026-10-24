#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags_0c;
    u8 unknown_0e[0x10];
    s16 field_1e;
    s16 field_20;
} Struct080DD5A8;

static inline u8 object_flag7(const Struct080DD5A8 *object)
{
    return (object->flags_0c >> 7) & 1;
}

static inline s8 object_flag7_is_set(const Struct080DD5A8 *object)
{
    s8 result = 0;

    if (object_flag7(object) == 1)
        result = 1;
    return result;
}

/* 0x080DD5A8 - 66 bytes: enabled, selected signed field is positive.
 * Target bytes:
 * 10b5021c9189c809012400232040012800d10123002b10d0201c0840002802d0
 * 1e21505e05e002200840002805d02021505e002801dd012000e0002010bc02bc0847
 */
s8 func_080DD5A8(const Struct080DD5A8 *object)
{
    if (object_flag7_is_set(object)) {
        if (object->flags_0c & 1) {
            if (object->field_1e > 0)
                return 1;
        } else if (object->flags_0c & 2) {
            if (object->field_20 > 0)
                return 1;
        }
    }
    return 0;
}
