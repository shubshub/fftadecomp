#include "ffta.h"

/* 0x080DBC08..0x080DBC16: 14 bytes, 6 instructions. */
typedef struct ObjectStatus ObjectStatus;

extern u8 func_08099C10(const ObjectStatus *object);

u8 func_080DBC08(const ObjectStatus *object)
{
    return func_08099C10(object);
}
