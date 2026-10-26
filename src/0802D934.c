#include "ffta.h"

struct Unit0802D934 {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2a[0xc6];
    u8 event;
    u8 unknown_f1[0x17];
};

extern u8 g_state_02000080[];
extern u32 func_080C9540(u32);
extern u32 func_080C8348(struct Unit0802D934 *);
extern u32 func_080C82D8(struct Unit0802D934 *);
extern u32 func_080C8364(struct Unit0802D934 *);
extern u32 func_080C832C(struct Unit0802D934 *);

/* Target: [0x0802D934, 0x0802DA00), 204 bytes, 82 instructions. */
void func_0802D934(void)
{
    if ((u8)func_080C9540(0x40)) {
        struct Unit0802D934 *unit = (struct Unit0802D934 *)g_state_02000080;
        s32 remaining;

        for (remaining = 23; remaining >= 0; remaining--, unit++) {
            if (unit->active) {
                if ((u8)func_080C8348(unit)) {
                    unit->flags &= 0xffdf;
                    if ((u8)func_080C82D8(unit))
                        unit->flags &= 0xfff7;
                    if ((u8)func_080C8364(unit))
                        unit->flags &= 0xfeff;
                    unit->event = 0;
                }
                if ((u8)func_080C832C(unit))
                    unit->flags &= 0xffbf;
            }
        }
        unit = (struct Unit0802D934 *)(g_state_02000080 + 0x2f44);
        for (remaining = 0; remaining < 12; remaining++, unit++) {
            if (unit->active)
                unit->flags &= 0xfe97;
        }
    }
}
