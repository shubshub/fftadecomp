#include "ffta.h"

typedef struct {
    u8 id;
    u8 unknown_01[11];
} TableEntry;

extern const TableEntry g_table_08563A70[];
u32 func_08036330(u8 id);

/* Complete target: [0x08045400, 0x08045424), 36 bytes. */
u8 func_08045400(u8 index)
{
    return func_08036330(g_table_08563A70[index].id) - 1;
}
