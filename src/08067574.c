#include "ffta.h"

typedef struct {
    u8 unknown_00[0x424];
    u16 entries[0][2];
} Table08067574;

typedef struct {
    Table08067574 *table;
} Context08067574;

extern u8 func_080CB99C(u16 id);

/* 08067574..080675A0: 44 bytes, including the 0x424 table-offset literal. */
u32 func_08067574(Context08067574 *context, u32 index)
{
    u16 value = context->table->entries[index][0];
    u16 id = 0x18A;

    if (value <= 0x55)
        id = 0x189;
    return func_080CB99C(id) + 13;
}
