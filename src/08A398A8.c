#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 value_14;
    u8 value_15;
} Object08A398A8;

/* Installed at 0x03006CF4. func_080D3024 calls it through slot 0x0839404C. */
void func_08A398A8(Object08A398A8 *object, u8 first, u8 second)
{
    object->value_14 = first;
    object->value_15 = second;
}
