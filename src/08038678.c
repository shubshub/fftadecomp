#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} State08038678;

extern State08038678 g_state_02000000;

/* 0x08038678..0x08038694: 28 bytes, including the object and offset literals. */
void func_08038678(u16 index)
{
    g_state_02000000.entries[index] = 0;
}
