#include "ffta.h"

/* 0x0812EBD0..0x0812ED02: 306 bytes, 145 reachable instructions. */
typedef struct {
    u32 identifier;
    u8 active;
    u8 kind;
    u8 unknown_06[2];
    u16 value_14 : 10;
    u16 value_16 : 10;
    u16 value_17 : 11;
    u16 value_18 : 11;
    u16 value_19 : 11;
    u16 value_1A : 11;
} __attribute__((packed)) PackedValues;

extern u32 func_080C7EA4(const void *, u32);

void func_0812EBD0(PackedValues *destination, const void *source)
{
    u16 value;

    destination->identifier = func_080C7EA4(source, 0);
    destination->active = 1;
    destination->kind = func_080C7EA4(source, 6);
    value = func_080C7EA4(source, 0x14);
    destination->value_14 = value;
    value = func_080C7EA4(source, 0x16);
    destination->value_16 = value;
    value = func_080C7EA4(source, 0x17);
    destination->value_17 = value;
    value = func_080C7EA4(source, 0x18);
    destination->value_18 = value;
    value = func_080C7EA4(source, 0x19);
    destination->value_19 = value;
    value = func_080C7EA4(source, 0x1A);
    destination->value_1A = value;
}
