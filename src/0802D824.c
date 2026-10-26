#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit;

extern u8 g_state_02000080[];
extern u32 func_080C8348(Unit *unit);
extern u32 func_080C82D8(Unit *unit);
extern u32 func_080C832C(Unit *unit);
extern void func_080CB4C0(Unit *unit);
extern u8 func_080C7EA4(Unit *unit, u32 mode);
extern void func_080C9574(u32 notification, u32 enabled);

/* Complete target: [0x0802D824, 0x0802D934), 272 bytes, 111 instructions. */
void func_0802D824(void)
{
    Unit *unit = (Unit *)g_state_02000080;
    s32 remaining;

    for (remaining = 23; remaining >= 0; remaining--, unit++)
    {
        if (unit->active)
        {
            if ((u8)func_080C8348(unit))
            {
                unit->flags &= 0xFFDF;
                if ((u8)func_080C82D8(unit))
                {
                    u8 status;

                    func_080CB4C0(unit);
                    status = func_080C7EA4(unit, 1);
                    switch (status)
                    {
                    case 8:
                        func_080C9574(0x38, 1);
                        break;
                    case 94:
                        func_080C9574(0x46, 1);
                        break;
                    case 4:
                        func_080C9574(0x47, 1);
                        break;
                    case 12:
                        func_080C9574(0x48, 1);
                        break;
                    case 9:
                        func_080C9574(0x49, 1);
                        break;
                    }
                    func_080C9574(0x5AC, 1);
                }
            }
            if ((u8)func_080C832C(unit))
                unit->flags &= 0xFFBF;
        }
    }

    unit = (Unit *)(g_state_02000080 + 0x2F44);
    for (remaining = 11; remaining >= 0; remaining--, unit++)
    {
        if (unit->active)
        {
            if ((u8)func_080C8348(unit))
                unit->flags &= 0xFFDF;
            if ((u8)func_080C832C(unit))
                unit->flags &= 0xFFBF;
        }
    }
}
