#include "ffta.h"

// Complete target: 0x08146E54..0x08146FB8, 356 bytes, 178 instructions.

typedef struct {
    u16 current;
    u16 target;
    u8 unknown_04[20];
} RangeData;

typedef struct Interval {
    u16 kind;
    u16 setting;
    u16 flags;
    u16 first;
    u16 last;
    u8 unknown_0a[2];
    RangeData range;
    struct Interval *previous;
    struct Interval *next;
} Interval;

typedef struct {
    void *allocator;
    Interval *head;
} IntervalList;

typedef struct {
    u16 color;
    u16 step[3];
    s8 delta[3];
    u8 unknown_0b;
} PaletteFade;

typedef void (*BufferInitializer)(void *, u32);
extern IntervalList data_03003C60;
extern BufferInitializer g_callbacks_0836D4B8[];
extern u16 data_03003860[];
extern PaletteFade data_03003E68[];
extern void func_08146DC8(u16 first, u16 last, u16 flags);
extern void *func_08007138(void *allocator, u32 size);

static inline Interval *allocate_interval(void)
{
    IntervalList *list = &data_03003C60;
    Interval *entry = func_08007138(list->allocator, sizeof(*entry));
    Interval *tail;

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

static inline void initialize_range(RangeData *range, u16 amount)
{
    range->target = range->current = amount;
}

Interval *func_08146E54(u16 first, u16 last, u16 duration, u16 setting)
{
    Interval *entry;
    u8 current[3];
    u8 target[3];
    u16 index;
    u16 channel;

    func_08146DC8(first, last, 29);
    entry = allocate_interval();
    if (entry == 0)
        return 0;
    for (index = first; index <= last; index++) {
        current[0] = data_03003860[index] & 0x1f;
        current[1] = (data_03003860[index] & 0x3e0) >> 5;
        current[2] = (data_03003860[index] & 0x7c00) >> 10;
        target[0] = data_03003E68[index].color & 0x1f;
        target[1] = (data_03003E68[index].color & 0x3e0) >> 5;
        target[2] = (data_03003E68[index].color & 0x7c00) >> 10;
        for (channel = 0; channel <= 2; channel++) {
            data_03003E68[index].step[channel] = duration >> 1;
            data_03003E68[index].delta[channel] = target[channel] - current[channel];
        }
    }
    if (duration == 0)
        duration = 1;
    initialize_range(&entry->range, duration);
    entry->first = first;
    entry->last = last;
    entry->setting = setting;
    entry->flags = 1;
    entry->kind = 1;
    return entry;
}
