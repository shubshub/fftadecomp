#include "ffta.h"

typedef struct {
    u8 unknown_000[0x144];
    u8 value;
} Object;

extern void func_08000D90(u8 value);

void func_080920BC(Object *object)
{
    func_08000D90(object->value);
}
