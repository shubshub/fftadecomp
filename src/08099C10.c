#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1E];
    u8 field_1e;
} Struct08099C10;

u8 func_08099C10(const Struct08099C10 *object)
{
    return object->field_1e;
}
