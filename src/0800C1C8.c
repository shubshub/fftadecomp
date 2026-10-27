#include "ffta.h"

struct Allocation0800C1C8 {
    u8 unknown_00[0x24];
    struct Allocation0800C1C8 *next;
};

struct Record0800C1C8 {
    void *allocation;
    u8 unknown_04[0x20];
    struct Allocation0800C1C8 *head;
};

extern void *data_02008FF8;
extern struct Record0800C1C8 g_records_02009000[];
extern void func_08007170(void *allocator, void *allocation);

/* Complete [0x0800C1C8, 0x0800C224): 92 bytes, 39 instructions. */
void func_0800C1C8(u8 index)
{
    struct Allocation0800C1C8 *node = g_records_02009000[index].head;

    while (node != 0) {
        struct Allocation0800C1C8 *next = node->next;

        func_08007170(data_02008FF8, node);
        node = next;
    }
    g_records_02009000[index].head = 0;
    if (g_records_02009000[index].allocation != 0) {
        func_08007170(data_02008FF8, g_records_02009000[index].allocation);
        g_records_02009000[index].allocation = 0;
    }
}
