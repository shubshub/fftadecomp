#include "ffta.h"

/* Complete [0x08141984, 0x081419BE): 58 bytes, 21 instructions and four
 * literal-pool words.  agb_flash FLASH512_V130 (config/library_units.json):
 * SetFlashTimerIntr.  A timer number above 3 returns 1; otherwise the number
 * is stored at 0x03005E40, the address of its TMCNT_L register (0x04000100 +
 * number * 4) at 0x03005E44, and the countdown handler func_0814195C is
 * written through the output pointer; returns 0. */

extern u8 data_03005E40;
extern u16 *data_03005E44;
extern void func_0814195C(void);

u16 func_08141984(u8 timerNum, void (**intrFunc)(void))
{
    if (timerNum >= 4)
        return 1;

    data_03005E40 = timerNum;
    data_03005E44 = (u16 *)(0x04000100 + data_03005E40 * 4);
    *intrFunc = func_0814195C;
    return 0;
}
