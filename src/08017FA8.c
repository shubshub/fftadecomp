#include "ffta.h"

typedef struct {
    u32 value;
    u16 first;
    u16 second;
} ValuePair;

/* 08017FA8..08017FB0: 8 bytes. */
void func_08017FA8(ValuePair *object, u32 value, u16 first, u16 second)
{
    object->value = value;
    object->first = first;
    object->second = second;
}
