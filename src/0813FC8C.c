#include "control_flags.h"

extern u8 *data_0200F3B0;
extern u8 data_06008000[];
extern u8 data_0899973C[];
extern struct {
    u8 unknown_00[0x14];
    void *destination;
} data_03000E60;
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const void *, void *, u32, u32, u32);

/* Target bytes: 00b581b0104800688022120281180a68510840180d4bc9181202d20a01f0defd0b480c494969c0225200002300930c23fff726ff084948890848488188890848888101b001bc0047b0f30002008000063c979908600e000340090003b8ff0000f8ff0000 */
void func_0813FC8C(void)
{
    u8 *base = data_0200F3B0;
    u32 descriptor = *(u32 *)(base + 0x8000);
    u32 offset = descriptor >> 1;
    func_08141868(base + offset, data_06008000 + offset,
                  (descriptor & 0xFFFFFF) >> 3);
    func_0813FB0C(data_0899973C, data_03000E60.destination, 0x180, 12, 0);
    g_control_flags_03000940.bg0hofs = -72;
    g_control_flags_03000940.bg0vofs = -8;
}
