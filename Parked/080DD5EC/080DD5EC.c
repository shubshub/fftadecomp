/* 0x080DD5EC target: 10b5021c9189c809012400232040012800d10123002b10d0201c0840002802d01e21505e05e002200840002805d02021505e002801da012000e0002010bc02bc0847 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
    u8 unknown_0e[0x10];
    s16 value_1e;
    s16 value_20;
} State080DD5EC;

static inline u8 object_enabled_flag(const State080DD5EC *object)
{
    return (object->flags >> 7) & 1;
}

static inline u8 object_is_enabled(const State080DD5EC *object)
{
    return object_enabled_flag(object) == 1;
}

u8 func_080DD5EC(const State080DD5EC *object)
{
    if (object_is_enabled(object)) {
        if (object->flags & 1) {
            if (object->value_1e < 0)
                return 1;
        } else if (object->flags & 2) {
            if (object->value_20 < 0)
                return 1;
        }
    }
    return 0;
}
