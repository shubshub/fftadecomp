#include "ffta.h"

extern u8 data_0600AFE0[];
extern u16 data_02003CB0[];
extern u8 *g_state_03002810;
extern const u16 *data_085668B0[];
extern void func_08037A30(u32, void *, u32, u32, u16, u32, u32, u32, u32);
extern void func_080142DC(u16 *, u32, u32);
extern void *func_0808B92C(u32, void *, u16, u32);
extern void func_08015110(void *, void *, const u16 *, u32, u32);
extern u32 func_080161BC(const void *);

/* 0x0803E1C0..0x0803E2E0: 288 bytes, 115 instructions. */
void func_0803E1C0(u16 id, u8 count, const u16 *label, u32 option)
{
    func_08037A30(5, data_0600AFE0, 0, 0, id, 0, option, 2, 1);
    if (count > 1) {
        u16 *number = data_02003CB0;
        s32 skipped;

        func_080142DC(number, count, 2);
        for (skipped = 0; skipped < 5 && number[skipped] == 0x1881; skipped++)
            ;
        number += skipped;
        func_08015110(g_state_03002810 + 0xc4c,
                      func_0808B92C(5, data_0600AFE0, 0, 2), number, 1, 1);
        func_08015110(g_state_03002810 + 0xc4c,
                      func_0808B92C(5, data_0600AFE0, (u16)func_080161BC(number), 2),
                      data_085668B0[17], 1, 1);
        func_08015110(g_state_03002810 + 0xc4c,
                      func_0808B92C(5, data_0600AFE0, 4, 2), label, 1, 1);
    } else {
        func_08015110(g_state_03002810 + 0xc4c,
                      func_0808B92C(5, data_0600AFE0, 0, 2), label, 1, 1);
    }
}
