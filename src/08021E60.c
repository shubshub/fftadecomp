#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1D];
    u8 field_1d;
} Struct08021E60;

/* 0x08021E60 - 4 bytes: unsigned byte at object offset 0x1D. */
u8 func_08021E60(const Struct08021E60 *object)
{
    return object->field_1d;
}
