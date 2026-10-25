#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 field_0e;
} Struct08011030;

u16 func_08011030(const Struct08011030 *object)
{
    return object->field_0e;
}
