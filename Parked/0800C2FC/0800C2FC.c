#include "ffta.h"

/* 0x0800C2FC..0x0800C344: 72 bytes. */
typedef struct {
    void *allocation;
    u8 unknown_04[0x20];
    void *head;
} AllocationRecord;

extern AllocationRecord g_records_02009000[];
extern void *data_02008FF8;
extern void func_0800C1C8(u8 index);
extern void func_08007170(void *allocator, void *allocation);

static inline void release_record_allocation(u16 index)
{
    void *allocation = g_records_02009000[index].allocation;

    if (allocation != 0)
        func_08007170(data_02008FF8, allocation);
}

void func_0800C2FC(void)
{
    u16 index;

    for (index = 0; index < 2; index++)
        func_0800C1C8(index);

    for (index = 0; index < 2; index++)
        release_record_allocation(index);
}
