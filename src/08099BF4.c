#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    void *child;
} Object08099BF4;

extern u32 func_08021C8C(void *object);

/* 0x08099BF4..0x08099C04: 16 bytes, 7 instructions. */
u16 func_08099BF4(Object08099BF4 *object)
{
    return func_08021C8C(object->child);
}
