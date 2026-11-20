#include "ffta.h"
#include "debug_monitor.h"

/* Complete [0x08FE1638, 0x08FE176A): 306 bytes, 141 instructions, two
 * alignment halfwords and five literal words.
 * 70b5041c8c466609032006400f21251c0d4010202040002828d0200a08400f2802d163460833
 * 1de0021c0e2a16d80d2a14d3054801681f20014013290bd0132904d8122905d009e04021fe09
 * 172904d004e0043202e0073200e00a329000024940180368ff2003e00021fe09e3091f200340
 * 0f2d07d11020204061460831002820d004311ee02a1c0e2a17d80d2a15d3054801681f200140
 * 13290cd0132905d8122906d00ae000004021fe09172904d004e0043202e0073200e00a329000
 * 064940180168012e0bd0012e07d3022e0cd0032e17d029e000000021fe09994000e0d9401f2b
 * 21d900211fe01f2b00d91f23002903dac843d840c04301e0081cd840011c12e01f200340002b
 * 0ed14a0805480068802189050840002805d080210906114302e04021fe09111c081c70bc02bc
 * 0847
 */

/* GDB's shifted_reg_val (gdb/arm-tdep.c; the same text from GDB 4.18 to
 * 6.0): the value of a data-processing instruction's shifted-register
 * operand, which the monitor's ARM single step func_08FE1B04 (calls at
 * 0x08FE1D00 and 0x08FE1E20) uses to predict where a step lands.  GDB's
 * carry and status_reg parameters are gone: the carry comes from the saved
 * CPSR.  The register reads are two copies of read_register
 * (0x08FE1660-0x08FE169A, 0x08FE16BE-0x08FE16FA; see debug_monitor.h).  The
 * RRX carry read is a call of it too: the shifted value is computed before
 * the CPSR test (0x08FE1744) and both arms assign the result (0x08FE1758,
 * 0x08FE1760), the expansion of `x | (c ? 0x80000000 : 0)` when c has side
 * effects.  A plain read of the CPSR word gives `x; if (c) x |= 0x80000000`
 * with one arm.  The fields are extracted with GDB's bits(); the bit 4
 * tests are masks (`inst & 0x10` at 0x08FE164A-0x08FE164C), not GDB's
 * bit(), which shifts first. */
#define submask(x) ((1L << ((x) + 1)) - 1)
#define bits(obj, st, fn) (((obj) >> (st)) & submask((fn) - (st)))
#define FLAG_C 0x20000000

u32 func_08FE1638(u32 inst, u32 pc_val)
{
    u32 res, shift;
    u32 shifttype = bits(inst, 5, 6);
    int rm = bits(inst, 0, 3);

    if (inst & 0x10) {
        int rs = bits(inst, 8, 11);

        shift = rs == 15 ? pc_val + 8 : read_register(rs);
        shift &= 0xFF;
    } else {
        shift = bits(inst, 7, 11);
    }

    res = (rm == 15
           ? (pc_val + ((inst & 0x10) ? 12 : 8))
           : read_register(rm));

    switch (shifttype) {
    case 0: /* LSL */
        res = shift >= 32 ? 0 : res << shift;
        break;
    case 1: /* LSR */
        res = shift >= 32 ? 0 : res >> shift;
        break;
    case 2: /* ASR */
        if (shift >= 32)
            shift = 31;
        res = ((res & 0x80000000)
               ? ~((~res) >> shift) : res >> shift);
        break;
    case 3: /* ROR/RRX */
        shift &= 31;
        if (shift == 0)
            res = (res >> 1) | ((read_register(PS_REGNUM) & FLAG_C) ? 0x80000000 : 0);
#ifdef BUGFIX
        else
            res = (res >> shift) | (res << (32 - shift));
#endif
        /* BUG: a rotate by a nonzero amount returns the operand unrotated:
         * the test at 0x08FE1740 branches straight to the return at
         * 0x08FE1762.  GDB rotates here, so stepping over a PC write whose
         * operand is `Rm, ROR #n` predicts the wrong next PC.  See
         * docs/bugs/08FE1638/. */
        break;
    }
    return res;
}
