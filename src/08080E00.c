#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *entries;
} MenuDisplay;

typedef struct {
    u8 unknown_000[0x95c];
    u8 count;
} MenuState;

extern MenuDisplay data_03000E30;
extern MenuState *data_03002818;
extern u16 *func_0808B8E4(u32 window, u32 layer, s32 x, s32 y);
extern void func_0804C7A0(void *entries, u16 index);

/* 0x08080E00..0x08080E80: 128 bytes, 50 instructions. */
void func_08080E00(void)
{
    s32 index;

    *func_0808B8E4(0, 1, 26, 19) = 0;
    *func_0808B8E4(0, 1, 27, 19) = 0;
    *func_0808B8E4(0, 1, 28, 19) = 0;
    *func_0808B8E4(0, 1, 29, 19) = 0;
    func_0804C7A0(data_03000E30.entries, 26);
    for (index = 0; index < data_03002818->count; index++)
        *func_0808B8E4(0, 1, index + 2, 19) = 0;
}
