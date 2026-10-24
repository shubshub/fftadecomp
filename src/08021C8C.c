#include "ffta.h"

/* 0x08021C8C - 4 bytes. */
typedef struct {
    u8 unknown_00[0x12];
    u16 field_12;
} Struct08021C8C;

u16 func_08021C8C(const Struct08021C8C *object)
{
    return object->field_12;
}
