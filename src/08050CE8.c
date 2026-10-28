#include "ffta.h"

/* 0x08050CE8..0x08050D50: 104 bytes, 44 instructions. */
typedef struct {
    u8 unknown_00[0x14];
    u8 active;
    u8 unknown_15[7];
} MenuEntry;

typedef struct {
    u8 unknown_00[8];
    void *heap;
} MenuOwner;

typedef struct {
    MenuOwner *owner;
} MenuContext;

typedef s32 (*EntryComparator)(const void *first, const void *second);

extern MenuEntry data_02002948[];
extern void *func_08005B00(void *heap, u32 size);
extern void func_08005B0C(void *heap, void *allocation);
extern void func_080028C8(void *scratch, void *items, u32 count, u32 width,
                         EntryComparator compare);
extern s32 func_08050CDC(const void *first, const void *second);

u32 func_08050CE8(MenuContext *context, MenuEntry **output)
{
    MenuEntry *entry = data_02002948;
    u32 count = 0;
    s32 remaining;

    for (remaining = 15; remaining >= 0; remaining--, entry++) {
        if (entry->active) {
            if (output) {
                output[count] = entry;
            }
            count++;
        }
    }
    if (count && output) {
        void *scratch = func_08005B00(context->owner->heap, 100);

        func_080028C8(scratch, output, count, 4, func_08050CDC);
        func_08005B0C(context->owner->heap, scratch);
    }
    return count;
}
