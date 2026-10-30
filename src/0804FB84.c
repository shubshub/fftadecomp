#include "ffta.h"

typedef u16 Entry0804FB84[2];

typedef struct {
    u8 unknown_000[0x424];
    Entry0804FB84 entries[0];
} Table0804FB84;

typedef struct {
    const Table0804FB84 *table;
} Context0804FB84;

extern u8 func_080CB99C(u16 id);

/* Target [0x0804FB84, 0x0804FBB0), 44 complete bytes:
 * 00b500688900084a801840180088c5214900552800d80139081c
 * 7bf0fdfe0006000e0d3002bc084724040000
 */
u32 func_0804FB84(const Context0804FB84 *context, u32 index)
{
    u16 value = context->table->entries[index][0];
    u16 id = 0x18A;

    if (value <= 0x55)
        id = 0x189;
    return func_080CB99C(id) + 13;
}
