#include "ffta.h"

/* Complete [0x08141AAC, 0x08141AB0): 4 bytes, 2 instructions.
 * agb_flash FLASH512_V130 (config/library_units.json): ReadFlash1, reads one
 * byte of flash.  func_08141AB0 (SetReadFlash1) copies these two halfwords
 * into a RAM buffer; its copy length is func_08141AB0 - func_08141AAC
 * (literals at 0x08141AD0 and 0x08141AD4). */

u8 func_08141AAC(u8 *addr)
{
    return *addr;
}
