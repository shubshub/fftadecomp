#include "ffta.h"

typedef struct Node08003888 {
    struct Node08003888 *next;
    u16 id;
} Node08003888;

typedef void (*BufferInitializer08003888)(void *destination, u32 size);

extern BufferInitializer08003888 g_callbacks_0836D4B8[];
extern Node08003888 data_030034C0[2];
extern u8 data_030034D0;
extern Node08003888 *data_030034B8;

/* Complete [0x08003888, 0x080038C8): 64 bytes, 22 instructions. */
void func_08003888(void)
{
    g_callbacks_0836D4B8[0](data_030034C0, sizeof(data_030034C0));
    data_030034D0 = 1;
    data_030034B8 = &data_030034C0[0];
    g_callbacks_0836D4B8[0](data_030034B8, sizeof(*data_030034B8));
    data_030034B8->id = 11;
}
