#include "ffta.h"

/* 0x080204D0..0x08020538: 104 bytes. */
extern u8 data_02003CB0[];
extern void func_08141890(const void *, void *);
extern void func_0801F098(const u8 *, const u8 *);

void func_080204D0(const u32 *table, u16 index)
{
    const u32 *entry = table;
    u16 last;
    u32 last_offset;
    const u8 *end;
    u32 offset;

    while (!*entry)
        entry++;
    last = (*entry - 4) / 4;
    end = 0;
    last_offset = table[last];
    if (last_offset != (u32)-1)
        end = (const u8 *)table + last_offset;
    offset = table[index];
    if (offset) {
        const u8 *payload = (const u8 *)table + offset;

        if (*payload) {
            func_08141890(payload, data_02003CB0);
            payload = data_02003CB0;
        } else {
            payload += 4;
        }
        func_0801F098(payload, end);
    }
}
