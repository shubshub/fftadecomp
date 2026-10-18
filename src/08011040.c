#include "ffta.h"

u8 func_08011040(Struct08011040 *source, u16 *first, u16 *second, u16 *third) {
    *first = source->fields[0];
    *second = source->fields[1];
    *third = source->fields[2];
    return source->value;
}
