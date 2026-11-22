#include "ffta.h"
#include "debug_monitor.h"

/* Complete [0x08FE1FCC, 0x08FE1FF8): 44 bytes, 15 instructions, one
 * alignment halfword and three literal words.
 * 074a118801200840002804d1054811880088014311800449002008807047000008020004
 * f420fe09f020fe09
 */

/* plausible: Hardware interrupt-master enable. */
#define REG_IME (*(volatile u16 *)0x04000208)

/* Leaves the monitor's stop: when IME is off, ORs the saved IME bit back
 * in, then clears the monitor flags.  Hand-written Thumb code calls it (bl
 * at 0x08FE102E), and func_08FE1F04 ends with the same code inline
 * (0x08FE1F9A-0x08FE1FB4). */
void func_08FE1FCC(void)
{
    if (!(REG_IME & 1))
        REG_IME |= DBG_SAVED_IME;
    DBG_FLAGS = 0;
}
