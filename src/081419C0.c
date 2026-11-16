#include "ffta.h"

/* Complete [0x081419C0, 0x08141A68): 168 bytes, 65 instructions and nine
 * literal-pool words.  agb_flash FLASH512_V130 (config/library_units.json):
 * starts the flash timeout timer for one phase.  Saves and clears IME, stops
 * the timer, enables its interrupt, clears the timeout flag at 0x0200F360,
 * loads the countdown at 0x03005E42 and the timer's reload and control from
 * the phase's three halfwords of the max-time table, then acknowledges the
 * timer interrupt and re-enables IME. */

extern const u16 *data_0200F380;
extern u16 data_03005E48;
extern u16 *data_03005E44;
extern u8 data_03005E40;
extern u8 data_0200F360;
extern u16 data_03005E42;

void func_081419C0(u8 phase)
{
    const u16 *maxTime = &data_0200F380[phase * 3];

    data_03005E48 = *(u16 *)0x04000208;
    *(u16 *)0x04000208 = 0;
    data_03005E44[1] = 0;
    *(u16 *)0x04000200 |= 8 << data_03005E40;
    data_0200F360 = 0;
    data_03005E42 = *maxTime++;
    *data_03005E44++ = *maxTime++;
    *data_03005E44-- = *maxTime++;
    *(u16 *)0x04000202 = 8 << data_03005E40;
    *(u16 *)0x04000208 = 1;
}
