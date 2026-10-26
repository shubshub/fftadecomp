#include "ffta.h"

/* 0x080BDD5C..0x080BDD6E: 18 bytes, 9 Thumb instructions. */
typedef struct {
    u8 unknown_00[0x0F];
    u8 kind;
} TypedObject;

u32 func_080BDD5C(const TypedObject *object)
{
    u32 result = 0;
    if (object->kind == 1) {
        result = 1;
    }
    return result;
}
