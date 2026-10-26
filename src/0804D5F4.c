#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[0x1A];
    void *entries[3];
} EntryState;

extern EntryState *data_0201F544;
extern s16 func_0804E1E0(void *entry);

/* Complete target: [0x0804D5F4, 0x0804D658), 100 bytes. */
u8 func_0804D5F4(void)
{
    u8 result = 1;

    if (data_0201F544->flags & 1)
        result = func_0804E1E0(data_0201F544->entries[0]) != 0;
    if ((data_0201F544->flags & 2) &&
        func_0804E1E0(data_0201F544->entries[1]) == 0)
        result = 0;
    if ((data_0201F544->flags & 4) &&
        func_0804E1E0(data_0201F544->entries[2]) == 0)
        result = 0;
    return result;
}
