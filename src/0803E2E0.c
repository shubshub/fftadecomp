#include "ffta.h"

extern u16 data_02003CB0[];
extern u8 data_0600AFE0[];
extern u8 *g_state_03002810;
extern const u16 *const g_table_085567F0[];
extern void func_080142DC(u16 *destination, u32 value, u32 digits);
extern void *func_0808B92C(u32 width, void *tiles, u16 x, u32 y);
extern void func_08015110(void *context, void *tiles, const u16 *text,
                         u32 style, u32 spacing);
extern u16 func_080161BC(const void *text);

/* 0x0803E2E0..0x0803E3B4: 212 bytes, 86 reachable Thumb instructions. */
void func_0803E2E0(u32 value, const u16 *label)
{
    u16 *number = data_02003CB0;
    s32 skipped;

    func_080142DC(number, (u16)value, 5);
    for (skipped = 0; skipped < 5 && number[skipped] == 0x1881; skipped++)
        ;
    number += skipped;
    func_08015110(g_state_03002810 + 0xC4C,
                  func_0808B92C(5, data_0600AFE0, 0, 0), number, 1, 1);
    func_08015110(g_state_03002810 + 0xC4C,
                  func_0808B92C(5, data_0600AFE0, (u16)func_080161BC(number), 0),
                  g_table_085567F0[0x2DC], 1, 1);
    func_08015110(g_state_03002810 + 0xC4C,
                  func_0808B92C(5, data_0600AFE0, 0, 2), label, 1, 1);
}
