#include "ffta.h"

typedef struct {
    u8 unknown_00[0x424];
    u16 *entries[0];
} Table08067504;

typedef struct {
    Table08067504 *table;
} Context08067504;

extern u8 func_080CB99C(u16 id);

/* Complete target: [0x08067504, 0x08067528), 36 bytes. */
u32 func_08067504(Context08067504 *context, u32 index)
{
    return func_080CB99C(*context->table->entries[index]) + 13;
}
