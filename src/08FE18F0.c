#include "ffta.h"
#include "debug_monitor.h"

extern s32 func_08FE1810(u32 cond);

/* Complete [0x08FE18F0, 0x08FE1B02): 530 bytes, 234 instructions, four
 * alignment halfwords and thirteen literal words.
 * f0b5051c0f1c2c88261c002038600f4820408e21c901884232d1e2080720024040200440002c
 * 00d00832131c0e2a1ad80d2a18d3064801681f20014013290ed0132907d8122908d00de00000
 * 80ff00004021fe09172904d005e0131d03e0d31d01e0131c0a3398000449401805680f2a00d1
 * 04350120a8433860c6e00021fe09f02109022140e020000281420cd104480440610001300840
 * 00281ad0014817e0ff07000000f0ffffd0200002814215d1200a0f210840fff733ff002800d1
 * a3e0ff202040410080200440002c01d002480143281d451898e000fefffff8210902201c0840
 * 88421fd10c48018804200840002800d088e0a81e00880949084000030c40610041188020c003
 * 0840002801d004480143a81c451877e00000f020fe09ff070000000080fffe2000022040bc21
 * 090288422ed1802040000440002c63d00d22054801681f20014013290bd0132904d8122905d0
 * 09e04021fe09172904d004e0112202e0142200e01722900008494018016800230122301c1040
 * 002800d0043152000133072bf6d90d683de000000021fe09ff20000220408c21c901884232d1
 * 0721214080200440002c00d008310f2929d1f1080720014040200640002e00d008310a1c0e2a
 * 16d80d2a14d3054801681f20014013290bd0132904d8122905d009e04021fe09172904d004e0
 * 043202e0073200e00a32900002494018056803e000000021fe090235281cf0bc02bc0847
 */

/* The debug monitor's Thumb single step (see debug_monitor.h), doing the
 * work of GDB's thumb_get_next_pc: returns the address of the instruction
 * that runs after the Thumb instruction at pc, and sets *is_arm when a BX
 * enters ARM state.  func_08FE1EC8 passes the saved PC and hands the result
 * to func_08FE176C, which plants the step breakpoint there (an ARM one when
 * is_arm is set).  The three register reads are copies of read_register
 * (0x08FE191A-0x08FE195C, 0x08FE1A30-0x08FE1A62 with SP_REGNUM folded in,
 * 0x08FE1AB4-0x08FE1AEE). */
u32 func_08FE18F0(u32 pc, u32 *is_arm)
{
    u16 insn = *(u16 *)pc;

    *is_arm = 0;
    if ((insn & 0xFF80) == 0x4700) {
        /* BX Rm */
        u32 rm = (insn >> 3) & 7;
        if (insn & 0x40)
            rm += 8;
        pc = read_register(rm);
        if (rm == 15)
            pc += 4;
        *is_arm = !(pc & 1);
    } else if ((insn & 0xF000) == 0xE000) {
        /* B */
        u32 offset = (insn & 0x7FF) << 1;
        if (offset & 0x800)
            offset |= 0xFFFFF000;
        pc += offset + 4;
    } else if ((insn & 0xF000) == 0xD000) {
        /* B<cond> */
        if (func_08FE1810((insn >> 8) & 0xF)) {
            u32 offset = (insn & 0xFF) << 1;
            if (insn & 0x80)
                offset |= 0xFFFFFE00;
            pc += offset + 4;
        } else
            pc += 2;
    } else if ((insn & 0xF800) == 0xF800) {
        /* The second half of BL; the first half is the halfword before. */
        if (!(DBG_FLAGS & 4)) {
            u16 prefix = *(u16 *)(pc - 2);
            u32 offset = ((prefix & 0x7FF) << 12) + ((insn & 0x7FF) << 1);
            if (offset & 0x400000)
                offset |= 0xFF800000;
            pc += offset + 2;
        } else
            pc += 2;
    } else if ((insn & 0xFE00) == 0xBC00) {
        /* POP with PC in the list: PC is the word above the low registers */
        if (insn & 0x100) {
            u32 sp, bit, i;
            sp = read_register(SP_REGNUM);
            for (i = 0, bit = 1; i < 8; i++) {
                if (insn & bit)
                    sp += 4;
                bit <<= 1;
            }
            pc = *(u32 *)sp;
        } else
            pc += 2;
    } else if ((insn & 0xFF00) == 0x4600) {
        /* MOV Rd, Rm with a high register */
        u32 rd = insn & 7;
        if (insn & 0x80)
            rd += 8;
        if (rd == 15) {
            u32 rm = (insn >> 3) & 7;
            if (insn & 0x40)
                rm += 8;
            pc = read_register(rm);
            /* BUG: for MOV PC, PC (0x46FF) this is the saved r15, the address
             * of the MOV itself, so the step breakpoint replaces the
             * instruction being stepped and the step stops before the MOV
             * runs.  The CPU reads PC as the address + 4, which the BX path
             * above adds (0x08FE195E-0x08FE1962); this path returns the
             * register as read (0x08FE1AE8-0x08FE1AEE).  See
             * docs/bugs/08FE18F0/. */
#ifdef BUGFIX
            if (rm == 15)
                pc += 4;
#endif
        } else
            pc += 2;
    } else
        pc += 2;
    return pc;
}
