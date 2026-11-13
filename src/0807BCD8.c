#include "ffta.h"

// Complete 0x0807BCD8..0x0807BDF8: 288 bytes.
extern u8 data_02003CB0[];
extern const u8 data_083C5744[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *, u16 tile, u16 count, u16 flags);
extern void func_08005318(const void *table, void *destination, u32 index, u32 flag);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0807BCD8(s32 mode)
{
    u8 *buffer = data_02003CB0;
    u32 palette;
    void *vram = (void *)0x0600C820;

    func_0808B7C0(8, func_0808B8E4(8, 1, 0, 2), 0x241, 5, 0xe000);
    if (mode == 2) {
        *func_0808B8E4(8, 1, 2, 2) = 0xe245;
        *func_0808B8E4(8, 1, 3, 2) = 0xe247;
        palette = 1;
    } else if (mode == 3) {
        *func_0808B8E4(8, 1, 2, 2) = 0xd245;
        *func_0808B8E4(8, 1, 3, 2) = 0xd247;
        palette = 2;
    } else if (mode == 5) {
        *func_0808B8E4(8, 1, 2, 2) = 0xe245;
        *func_0808B8E4(8, 1, 3, 2) = 0xe247;
        palette = 3;
    } else {
        *func_0808B8E4(8, 1, 2, 2) = 0xd245;
        *func_0808B8E4(8, 1, 3, 2) = 0xd247;
        palette = 0;
    }
    func_08005318(data_083C5744, buffer, palette, 1);
    func_0814186C(buffer, vram, 0xa0);
}
