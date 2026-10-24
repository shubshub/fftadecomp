/* 0x080BDB74: 41 80 70 47 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    s16 field_02;
} Struct080BDB74;

void func_080BDB74(Struct080BDB74 *object, s16 value)
{
    object->field_02 = value;
}
