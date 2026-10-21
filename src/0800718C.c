// func_0800718C - 0x0800718C, 20 bytes (0x0800718C .. 0x080071A0).
//
// target  00b503490a6804213bf15af801bc0047b8d43608
//
// The function passes its argument straight through to the callback whose
// address is stored in the cartridge-ROM word at 0x0836D4B8, together with the
// constant 4.  The callback itself lives in IWRAM (the word there holds
// 0x03005E79), so the call goes through agbcc's `bx r2` thunk at 0x0814224C.
//
// The address of the table has to live in a variable: written inline, every
// access folds into its own absolute address and the ROM's single load of the
// table address disappears.
//
// The function returns through the interworking epilogue `pop {r0}; bx r0`,
// so it is void.

#include "ffta.h"

typedef void (*ObjectFunc)(void *, u32);

void func_0800718C(void *object)
{
    // plausible: a read-only table in the cartridge ROM, holding the callback
    u32 *table = (u32 *)0x0836D4B8;

    ((ObjectFunc)(*table))(object, 4);
}
