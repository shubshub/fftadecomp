// func_08141D54 - 0x08141D54, 72 bytes (0x08141D54 .. 0x08141D98 plus the
// literal pool word at 0x08141D98).
//
// Programs one flash sector and verifies the first n bytes, retrying up to
// three times.  The program routine is reached through the function pointer
// held at 0x0200F36C (called through agbcc's `bx r2` thunk at 0x0814224C);
// its u16 status is widened.  func_08141C78 verifies n bytes of the sector
// against the source.  The last status is returned: 0 on success.

#include "ffta.h"

extern u16 (*data_0200F36C)(u16 sector, void *source);
extern u32 func_08141C78(u16 sector, void *source, u32 size);

u32 func_08141D54(u16 sector, void *source, u32 size)
{
    u8 i;
    u32 result;

    for (i = 0; i < 3; i++) {
        result = data_0200F36C(sector, source);
        if (result != 0)
            continue;
        result = func_08141C78(sector, source, size);
        if (result == 0)
            break;
    }
    return result;
}
