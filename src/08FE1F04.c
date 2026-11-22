#include "ffta.h"
#include "debug_monitor.h"

extern u32 func_08FE1EC8(void);

/* Complete [0x08FE1F04, 0x08FE1FCC): 200 bytes, 88 instructions, one
 * alignment halfword and five literal words.
 * 10b50a4a101cf03001880120084000284fd0012402200840002809d0101cec30016804380068
 * 088008e000000020fe09101cec300168043800680860111cf03108880d2303400b80101cb230
 * 018880200002084000281ed1101cc230018803200840002817d008201840002811d012480168
 * 101ce030006888420ad8101ce4300068814205d8fff79dff0024002800d10124002c0dd0094a
 * 118801200840002804d10748118800880143118005490020088010bc01bc00473c21fe090802
 * 0004f420fe09f020fe09
 */

/* plausible: Hardware interrupt-master enable. */
#define REG_IME (*(volatile u16 *)0x04000208)

/* The monitor's work area (see debug_monitor.h).  func_08FE176C plants a
 * step breakpoint: it stores the address at +0xEC and the instruction it
 * replaces at +0xE8, and sets flags bit 0, with bit 1 for a Thumb one.  Bit 3
 * of the flags steps while the PC stays within [+0xE0, +0xE4]; the flags are
 * DBG_FLAGS and +0xB2 is DBG_CMD_ARG.  The halfword at +0xC2 is not known. */
typedef struct {
    u8 unknown_000[0xB2];
    u16 cmd_arg;
    u8 unknown_0B4[0xC2 - 0xB4];
    u16 unknown_0C2;
    u8 unknown_0C4[0xE0 - 0xC4];
    u32 step_start;
    u32 step_end;
    u32 saved_insn;
    u32 bp_address;
    u16 flags;
} Monitor08FE1F04;

#define MONITOR ((Monitor08FE1F04 *)0x09FE2000)

/* An inlined copy of func_08FE1FCC (src/08FE1FCC.c): 0x08FE1F9A-0x08FE1FB4
 * repeats 0x08FE1FCC-0x08FE1FE6 instruction for instruction, in the same
 * registers and with the same three pool words.  It addresses the flags as
 * DBG_FLAGS, by number (pool word 0x08FE1FC8), where the rest of this
 * function adds +0xF0 to the work area's base in r2.  func_08FE1FCC itself,
 * which hand-written Thumb code calls (bl at 0x08FE102E), is the last
 * function of this Thumb run, where agbcc writes the out-of-line copy of an
 * inline function. */
static inline void end_step(void)
{
    if (!(REG_IME & 1))
        REG_IME |= DBG_SAVED_IME;
    DBG_FLAGS = 0;
}

/* The monitor's step breakpoint was hit: put back the instruction it
 * replaced, and when a range step (flags bit 3) is still inside its range,
 * plant the next step breakpoint (func_08FE1EC8 returns nonzero when it
 * did) and let the target run on; otherwise the step ends. */
void func_08FE1F04(void)
{
    Monitor08FE1F04 *m = MONITOR;

    if (m->flags & 1) {
        u32 stop = 1;

        if (m->flags & 2)
            *(u16 *)m->bp_address = m->saved_insn;
        else
            *(u32 *)m->bp_address = m->saved_insn;
        m->flags &= 0xD;
        if (!(m->cmd_arg & 0x8000) && (m->unknown_0C2 & 3)) {
            if (m->flags & 8) {
                u32 pc = DBG_REGS[PC_REGNUM];

                if (m->step_start <= pc && pc <= m->step_end)
                    stop = !func_08FE1EC8();
            }
            if (!stop)
                return;
        }
        end_step();
    }
}
