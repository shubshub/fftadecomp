#include "ffta.h"

typedef struct {
    u8 unknown_00[0x5C];
    void *buffer;
} BufferState08022E24;

extern BufferState08022E24 g_state_0200F390;
extern u8 data_03003860[];
extern void (*data_0836D4BC)(void *destination, const void *source, u32 length);
extern void *func_08022840(u32 size);

/* 0x08022E24: 52 bytes; lazily allocate and populate the cached buffer. */
void func_08022E24(void)
{
    if (!g_state_0200F390.buffer) {
        g_state_0200F390.buffer = func_08022840(0x400);
        data_0836D4BC(g_state_0200F390.buffer, data_03003860, 0x400);
    }
}
