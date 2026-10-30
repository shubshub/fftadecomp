#include "ffta.h"

typedef struct {
    const void *data;
    u16 count;
    u16 current;
    u16 target;
    u8 unknown_0A[10];
    u16 first;
    u16 second;
} RangeData08147124;

typedef struct Interval08147124 {
    u16 kind;
    u16 setting;
    u16 flags;
    u16 first;
    u16 last;
    u8 unknown_0A[2];
    RangeData08147124 range;
    struct Interval08147124 *previous;
    struct Interval08147124 *next;
} Interval08147124;

typedef struct {
    void *allocator;
    Interval08147124 *head;
} IntervalList08147124;

typedef void (*BufferInitializer08147124)(void *, u32);

extern IntervalList08147124 data_03003C60;
extern BufferInitializer08147124 g_callbacks_0836D4B8[];
extern void func_08146DC8(u16 first, u16 last, u16 flags);
extern void *func_08007138(void *allocator, u32 size);
extern void *func_0814873C(Interval08147124 *entry);

static inline Interval08147124 *allocate_interval(void)
{
    IntervalList08147124 *list = &data_03003C60;
    Interval08147124 *entry = func_08007138(list->allocator, sizeof(*entry));
    Interval08147124 *tail;

    g_callbacks_0836D4B8[0](entry, sizeof(*entry));
    if (list->head == 0) {
        list->head = entry;
        entry->previous = 0;
        entry->next = 0;
    } else {
        tail = list->head;
        while (tail->next != 0)
            tail = tail->next;
        tail->next = entry;
        entry->previous = tail;
        entry->next = 0;
    }
    return entry;
}

static inline void initialize_range(RangeData08147124 *range, u16 amount,
                                    u16 value, const void *data)
{
    range->current = range->target = amount;
    range->first = range->second = value;
    range->data = data;
    range->count = 0;
}

/* Target: complete [0x08147124, 0x081471E0), 188 bytes.
 * f0b557464e464546e0b4089c0004000c81460904090c88461204160c1b041b0c9a46
 * 2404270c1f22fff73cfe084d28682c21bff6efff041c06480268201c2c21fbf772f8
 * 6868002806d16c6060620ce0603c0003b8d43608011c00e0896a886a0028fbd18c62
 * 61620020a062002c01d100201ce0002e00d10126002f00d10127211c0c3100220e81
 * ce80cf828f820998e0608a804846e08040462081504660800820a08001202080201c
 * 01f0b5fa38bc9846a146aa46f0bc02bc0847
 */
void *func_08147124(u16 first, u16 last, u16 amount, u16 setting,
                    u16 value, const void *data)
{
    Interval08147124 *entry;

    func_08146DC8(first, last, 31);
    entry = allocate_interval();
    if (entry == 0)
        return 0;
    if (amount == 0)
        amount = 1;
    if (value == 0)
        value = 1;
    initialize_range(&entry->range, amount, value, data);
    entry->first = first;
    entry->last = last;
    entry->setting = setting;
    entry->flags = 8;
    entry->kind = 1;
    return func_0814873C(entry);
}
