#include "ffta.h"

/* Complete [0x08141A68, 0x08141AAC): 68 bytes, 23 instructions and five
 * literal-pool words.  agb_flash FLASH512_V130 (config/library_units.json):
 * StopFlashTimer.  With IME cleared, zeroes the reload and control halfwords
 * of the flash timer whose registers start at the pointer in 0x03005E44,
 * clears that timer's bit (8 << timer number at 0x03005E40) in IE, and
 * restores IME from the copy at 0x03005E48. */

extern u8 data_03005E40;
extern u16 *data_03005E44;
extern u16 data_03005E48;

void func_08141A68(void)
{
    *(u16 *)0x04000208 = 0;
    *data_03005E44++ = 0;
    *data_03005E44-- = 0;
    *(u16 *)0x04000200 &= ~(8 << data_03005E40);
    *(u16 *)0x04000208 = data_03005E48;
}
