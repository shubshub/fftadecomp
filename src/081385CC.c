#include "ffta.h"

/* Target: complete [0x081385CC, 0x081386BA), 238 bytes. */
extern u32 func_0808B8E4(void *, u32, u32, u32);
extern void func_0808B7C0(void *, u32, u16, u32, u32);

void func_081385CC(void *context, u16 base)
{
    u32 position;

    position = func_0808B8E4(context, 1, 1, 3);
    func_0808B7C0(context, position, base, 11, 0xc000);

    position = func_0808B8E4(context, 1, 1, 5);
    func_0808B7C0(context, position, (u16)(base + 22), 3, 0xc000);

    position = func_0808B8E4(context, 1, 4, 5);
    func_0808B7C0(context, position, (u16)(base + 28), 3, 0xc000);

    position = func_0808B8E4(context, 1, 7, 5);
    func_0808B7C0(context, position, (u16)(base + 34), 2, 0xc000);

    position = func_0808B8E4(context, 1, 9, 5);
    func_0808B7C0(context, position, (u16)(base + 38), 3, 0xc000);

    position = func_0808B8E4(context, 1, 1, 8);
    func_0808B7C0(context, position, (u16)(base + 44), 11, 0xc000);

    position = func_0808B8E4(context, 1, 8, 11);
    func_0808B7C0(context, position, (u16)(base + 66), 3, 0xc000);
}
