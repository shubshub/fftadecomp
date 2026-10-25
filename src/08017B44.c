#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 field_15;
} Object08017B44;

/* 0x08017B44: 407d7047 */
u8 func_08017B44(const Object08017B44 *object)
{
    return object->field_15;
}
