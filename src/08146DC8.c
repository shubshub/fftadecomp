#include "ffta.h"

typedef struct Interval08146DC8 {
    u16 kind;
    u16 setting;
    u16 flags;
    u16 first;
    u16 last;
    u8 unknown_0a[0x1A];
    struct Interval08146DC8 *previous;
    struct Interval08146DC8 *next;
} Interval08146DC8;

typedef struct {
    void *allocator;
    Interval08146DC8 *head;
} IntervalList08146DC8;

extern IntervalList08146DC8 data_03003C60;
extern void *func_0814873C(Interval08146DC8 *entry);
extern void func_08148498(void *handle);

/* Complete [0x08146DC8, 0x08146E52): 138 bytes, 63 instructions.
 * f0b50004060c09040d0c1204170c0c484468002c36d02088012830d1a188381c
 * 084088422bd1e088021c2189b24209d3a94207d8201c01f09dfc01f049fb1ee0
 * 603c00030804000cb04204d3a84202d8701e208113e01004000cb04206d3a842
 * 02d8681ce0800ae0b04208d80804000ca84204d3201c01f07dfc01f029fba46a
 * 002cc8d1f0bc01bc0047
 */
void func_08146DC8(u16 first, u16 last, u16 flags)
{
    Interval08146DC8 *entry;

    for (entry = data_03003C60.head; entry != 0; entry = entry->next) {
        if (entry->kind == 1 && (flags & entry->flags) == entry->flags) {
            if (entry->first >= first && entry->last <= last)
                func_08148498(func_0814873C(entry));
            else if (entry->last >= first && entry->last <= last)
                entry->last = first - 1;
            else if (entry->first >= first && entry->first <= last)
                entry->first = last + 1;
            else if (entry->first <= first && entry->last >= last)
                func_08148498(func_0814873C(entry));
        }
    }
}
