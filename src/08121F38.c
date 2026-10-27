#include "ffta.h"

struct Queue08121F38 {
    u32 unknown_00;
    u16 entries[4];
    u8 count;
};

extern struct Queue08121F38 data_02002190;
extern void func_08009FD0(void);

/* Complete [0x08121F38, 0x08121F7E): 70 bytes, 31 instructions. */
u8 func_08121F38(void)
{
    struct Queue08121F38 *queue = &data_02002190;
    s32 index;
    u8 result;

    queue->count--;
    for (index = 0; index < queue->count; index++)
        queue->entries[index] = queue->entries[index + 1];
    queue->entries[queue->count] = 0;
    if (queue->count == 0) {
        result = 0;
    } else {
        func_08009FD0();
        result = 1;
    }
    return result;
}
