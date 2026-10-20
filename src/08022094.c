#include "ffta.h"

typedef struct {
    u16 value;
    u16 unknown_02;
} InputHeader;

typedef struct {
    u32 flags;
    u8 unknown_04[6];
    u16 value_0A;
    u16 value_0C;
    u16 value_0E;
    u8 value_10;
    u8 unknown_11[0xF];
    s32 value_20;
    u8 unknown_24[0x10];
    const void *begin;
    const void *end;
} InitializedObject;

void func_08022094(InitializedObject *object, const InputHeader *header)
{
    object->flags = 0x45;
    object->value_0A = 0;
    object->value_0C = 0;
    object->value_0E = header->value;
    object->begin = header + 1;
    object->end = header + 1;
    object->value_20 = -1;
    object->value_10 = 0;
}
