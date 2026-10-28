#include "ffta.h"

struct SelectionState {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
};

struct BufferState {
    u8 unknown_000[0xA1C];
    u16 first[256];
    u16 second[256];
};

extern struct SelectionState g_state_02000000;
extern struct BufferState *data_030027D8;
extern const u16 *data_083A8E44[];
extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete target: [0x08137C4C, 0x08137CC4), 120 bytes. */
void func_08137C4C(void)
{
    func_0814186C(data_083A8E44[g_state_02000000.mode * 2],
                  data_030027D8->first, 256);
    func_0814186C(data_083A8E44[g_state_02000000.mode * 2 + 1],
                  data_030027D8->second, 256);
    data_030027D8->first[0] = 0;
}
