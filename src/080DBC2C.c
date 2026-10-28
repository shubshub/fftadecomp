#include "ffta.h"

extern u8 func_08099C10(const void *object);
extern u32 func_08099C14(void *object, u32 value);

/* 080DBC2C..080DBC58: 44 bytes. */
u8 func_080DBC2C(void *object, u8 change)
{
    u8 current = func_08099C10(object);
    u16 value = (s8)change + current;

    return func_08099C14(object, value);
}
