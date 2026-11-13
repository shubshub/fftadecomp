// func_08141D10 - 0x08141D10, 68 bytes (0x08141D10 .. 0x08141D50 plus the
// literal pool word at 0x08141D50).
//
// Programs one flash sector and verifies it, retrying up to three times.
// The program routine is reached through the function pointer held at
// 0x0200F36C (called through agbcc's `bx r2` thunk at 0x0814224C); its u16
// status is widened.  func_08141BE0 verifies the sector against the source.
// The last status is returned: 0 on success.

#include "ffta.h"

extern u16 (*data_0200F36C)(u16 sector, void *source);
extern u32 func_08141BE0(u16 sector, void *source);

u32 func_08141D10(u16 sector, void *source)
{
    u8 i;
    u32 result;

    for (i = 0; i < 3; i++) {
        result = data_0200F36C(sector, source);
        if (result != 0)
            continue;
        result = func_08141BE0(sector, source);
        if (result == 0)
            break;
    }
    return result;
}
