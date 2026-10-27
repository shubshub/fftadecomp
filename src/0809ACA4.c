#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} FlagObject;

typedef struct {
    u32 clear_mask;
    u32 set_mask;
} FlagChange;

/* 0809ACA4..0809ACB4: 16 bytes. */
u32 func_0809ACA4(FlagObject *object, const FlagChange *change)
{
    object->flags = (object->flags & ~change->clear_mask) | change->set_mask;
    return 1;
}
