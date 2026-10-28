#include "ffta.h"

typedef struct RingEntry0804CA8C {
    u32 unknown_00[7];
} RingEntry0804CA8C;

typedef struct RingBuffer0804CA8C {
    u32 unknown_00[4];
    RingEntry0804CA8C entries[32];
    u32 next_index;
} RingBuffer0804CA8C;

extern RingBuffer0804CA8C *data_0201F540;

/* Complete target [0x0804CA8C, 0x0804CAB0): 36 bytes, 16 instructions. */
RingEntry0804CA8C *func_0804CA8C(void)
{
    RingBuffer0804CA8C *buffer = data_0201F540;
    u32 index = buffer->next_index;
    RingEntry0804CA8C *entry = &buffer->entries[index];

    buffer->next_index = (index + 1) & 31;
    return entry;
}
