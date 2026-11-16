#include "ffta.h"

// func_08132064 [0x08132064,0x081320E8) 132 bytes
extern void (*data_0836D4BC)(void *, const void *, u32);
extern const u8 data_083A8C0C[];
extern u32 func_08002804(void);

struct Obj {
    u8 unknown_0[8];
    u8 *buffer;
    u8 unknown_c[0x1A];
    u16 flags;
};

void func_08132064(struct Obj *obj)
{
    u8 table[8];
    u8 count;
    s32 i;

    if (obj->flags & 0x10)
        return;
    data_0836D4BC(table, data_083A8C0C, 8);
    count = 8;
    for (i = 1; i <= 8 && count != 0; i++, count--) {
        s32 index = (s16)func_08002804() % count;

        u8 *dest = obj->buffer + 0xC;
        s32 rest;

        dest[i] = table[index];
        rest = count - index - 1;
        if (rest != 0)
            data_0836D4BC(&table[index], &table[index + 1], rest);
    }
}
