#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    u8 unknown_08[8];
    u32 saved_mode;
} State08121E9C;

typedef struct {
    u8 unknown_00[0xC];
    u8 mode;
} GlobalState08121E9C;

typedef void (*BufferInitializer08121E9C)(void *destination, u32 size);

extern State08121E9C *data_020159CC;
extern void *data_020159C4;
extern GlobalState08121E9C g_state_0200F390;
extern BufferInitializer08121E9C const g_callbacks_0836D4B8[];
extern void *func_08007138(void *owner, u32 size);
extern void *func_08005C14(void *storage, u32 size);

/* Target bytes [08121E9C, 08121EF0):
 * 30 B5 0F 4C 0F 4D 28 68 0F 49 E5 F6 47 F9 20 60
 * 0E 4A 0D 49 12 68 20 F0 CB F9 28 68 80 21 49 01
 * E5 F6 3C F9 21 68 48 60 80 21 49 01 E3 F6 A4 FE
 * 21 68 08 60 06 48 00 7B 08 61 30 BC 01 BC 00 47
 * CC 59 01 02 C4 59 01 02 58 09 00 00 B8 D4 36 08
 * 90 F3 00 02.
 */
void func_08121E9C(void)
{
    data_020159CC = func_08007138(data_020159C4, 0x958);
    g_callbacks_0836D4B8[0](data_020159CC, 0x958);
    data_020159CC->allocation = func_08007138(data_020159C4, 0x1000);
    data_020159CC->manager = func_08005C14(data_020159CC->allocation, 0x1000);
    data_020159CC->saved_mode = g_state_0200F390.mode;
}
