#include "ffta.h"

/* Complete 0x0808C53C..0x0808C630: 244 bytes. */
extern u8 data_02003CB0[];
extern const u8 data_083C5744[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08005318(const void *table, void *destination, u32 index, u32 flag);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0808C53C(s32 mode)
{
    u8 *buffer = data_02003CB0;
    u32 palette;
    void *vram = (void *)0x0600EFA0;

    if (mode == 1) {
        *func_0808B8E4(6, 1, 8, 3) = 0xd37f;
        *func_0808B8E4(6, 1, 9, 3) = 0xd381;
        palette = 0;
    } else if (mode == 2) {
        *func_0808B8E4(6, 1, 8, 3) = 0xe37f;
        *func_0808B8E4(6, 1, 9, 3) = 0xe381;
        palette = 1;
    } else if (mode == 3) {
        *func_0808B8E4(6, 1, 8, 3) = 0xd37f;
        *func_0808B8E4(6, 1, 9, 3) = 0xd381;
        palette = 2;
    } else {
        *func_0808B8E4(6, 1, 8, 3) = 0xe37f;
        *func_0808B8E4(6, 1, 9, 3) = 0xe381;
        palette = 3;
    }
    func_08005318(data_083C5744, buffer, palette, 1);
    func_0814186C(buffer, vram, 0xa0);
}
