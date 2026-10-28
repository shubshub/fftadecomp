#include "ffta.h"

/* 0x080BC8C4..0x080BC8E8: 36 bytes / 12 instructions. */
typedef struct {
    u8 unknown_00[0x74];
    void *context;
    u8 unknown_78[0x48];
} State080BC8C4;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern State080BC8C4 data_02010130;
extern BufferInitializer const g_callbacks_0836D4B8[];

void func_080BC8C4(void *context)
{
    g_callbacks_0836D4B8[0](&data_02010130, sizeof(data_02010130));
    data_02010130.context = context;
}
