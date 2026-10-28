#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x24];
    u32 value;
} FlaggedValue;

typedef struct {
    u8 unknown_00[0x44];
    FlaggedValue *value;
} ValueOwner;

extern u32 func_08021DA8(const FlaggedValue *object, u8 *first, u8 *second);

/* 0x08099C04..0x08099C10: 12 bytes. */
u32 func_08099C04(const ValueOwner *owner, u8 *first, u8 *second)
{
    return func_08021DA8(owner->value, first, second);
}
