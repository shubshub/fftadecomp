#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} FlaggedObject;

extern void func_0813325C(FlaggedObject *object);

void func_08133244(FlaggedObject *object)
{
    if (!(object->flags & 0x10))
        func_0813325C(object);
}
