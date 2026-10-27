#include "ffta.h"

struct Interval08146DC8 {
    u16 kind;
    u16 unknown_02;
    u16 flags;
    u16 first;
    u16 last;
    u8 unknown_0a[0x1E];
    struct Interval08146DC8 *next;
};

struct IntervalList08146DC8 {
    u32 unknown_00;
    struct Interval08146DC8 *head;
};

extern struct IntervalList08146DC8 data_03003C60;
extern void *func_0814873C(struct Interval08146DC8 *entry);
extern void func_08148498(void *handle);

/* Complete [0x08146DC8, 0x08146E52): 138 bytes, 63 instructions. */
void func_08146DC8(u16 first, u16 last, u16 flags)
{
    struct Interval08146DC8 *entry;

    for (entry = data_03003C60.head; entry != 0; entry = entry->next) {
        if (entry->kind == 1 && (flags & entry->flags) == entry->flags) {
            u32 entry_first = entry->first;
            u32 entry_last = entry->last;

            if (entry_first >= first && entry_last <= last) {
                func_08148498(func_0814873C(entry));
            } else if ((u16)entry_last >= first && (u16)entry_last <= last) {
                entry->last = first - 1;
            } else if ((u16)entry_first >= first && (u16)entry_first <= last) {
                entry->first = last + 1;
            } else if ((u16)entry_first <= first && (u16)entry_last >= last) {
                func_08148498(func_0814873C(entry));
            }
        }
    }
}
