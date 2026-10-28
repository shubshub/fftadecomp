#include "ffta.h"

typedef struct {
    u8 text[0x14];
    u8 status;
    u8 age;
    u8 unknown_16[6];
} CacheEntry;

typedef s32 (*Compare)(const void *first, const void *second);

extern CacheEntry data_02002948[16];
extern void *func_08022840(u32 bytes);
extern void func_08022854(void *object);
extern void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                          Compare compare);
extern s32 func_08061C24(const void *first, const void *second);

/* Complete target: [0x08061C30, 0x08061C9C), 108 bytes, 45 instructions. */
void func_08061C30(void)
{
    void *workspace = func_08022840(100);
    CacheEntry **order = func_08022840(16 * sizeof(*order));
    CacheEntry *records = data_02002948;
    CacheEntry **position;
    CacheEntry *entry;
    s32 index;
    s32 i;

    index = 15;
    position = &order[15];
    do {
        *position = &records[index];
        --index;
        --position;
    } while ((s32)position >= (s32)order);
    func_080028C8(workspace, order, 16, sizeof(*order), func_08061C24);
    for (i = 0; i < 16; ++i) {
        entry = order[i];
        if (entry->age != 0) {
            entry->age = i + 1;
        }
    }
    func_08022854(order);
    func_08022854(workspace);
}
