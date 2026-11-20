#ifndef DEBUG_MONITOR_H
#define DEBUG_MONITOR_H

#include "ffta.h"

/* The development-cartridge debug monitor whose memory image fills
 * 0x08FE0000-0x08FE3FFF of the ROM.  The image is linked to run at its ROM
 * address plus 0x01002000 (func_08FE1810 loads its jump table as 0x09FE3840,
 * pool word 0x08FE183C, and the table is at 0x08FE1840), and nothing outside
 * the image calls into it.  Its single step follows GDB's ARM code
 * (gdb/arm-tdep.c): func_08FE1638 is shifted_reg_val, and func_08FE18F0 does
 * the work of thumb_get_next_pc.
 *
 * The monitor keeps the stopped CPU's registers as words at fixed addresses:
 * r0-r15, the CPSR, then SP, LR and SPSR of IRQ (17-19), SVC (20-22) and
 * abort (23-25) mode.  The image's own copy at 0x08FE0100 still holds the
 * values of a session: CPSR 0x6000003F, IRQ SP 0x03007FA0 and SVC SP
 * 0x03007FE0, the GBA BIOS stack tops.  The code addresses the block by
 * number: each lookup scales the register index before it loads the base,
 * and the CPSR has a pool word of its own (0x09FE2140), where a linked array
 * loads its base first. */
#define SP_REGNUM 13
#define LR_REGNUM 14
#define PS_REGNUM 16
#define DBG_REGS ((u32 *)0x09FE2100)
#define DBG_CPSR (DBG_REGS[PS_REGNUM])

/* Monitor flags; bit 2 steps over calls (tested for BL by func_08FE18F0 at
 * 0x08FE19D8 and by the ARM decoder func_08FE1B04 at 0x08FE1B32). */
#define DBG_FLAGS (*(u16 *)0x09FE20F0)

/* read_register (GDB's name): a register of the stopped CPU, with SP and LR
 * from the bank of the saved mode (CPSR & 0x1F: IRQ 0x12, SVC 0x13, abort
 * 0x17); User and System mode use r13 and r14.  Every copy compares the register number with
 * 14 and then 13 (0x08FE1662, 0x08FE16C0, 0x08FE191C, 0x08FE1AB6), the case
 * range; `regno == 13 || regno == 14` folds to one subtract and compare. */
static inline u32 read_register(u32 regno)
{
    switch (regno) {
    case SP_REGNUM:
    case LR_REGNUM:
        switch (DBG_CPSR & 0x1F) {
        case 0x12: /* IRQ */
            regno += 4;
            break;
        case 0x13: /* SVC */
            regno += 7;
            break;
        case 0x17: /* abort */
            regno += 10;
            break;
        }
    }
    return DBG_REGS[regno];
}

#endif
