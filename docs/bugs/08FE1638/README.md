# func_08FE1638: the debug monitor's operand decoder returns a rotated operand unrotated

**Status: unreachable in the retail game.** The function belongs to a
development-cartridge debug monitor whose memory image fills
`0x08FE0000`-`0x08FE3FFF`; no code outside the image calls into it. On
development hardware running the monitor it is reached by single-stepping an
ARM instruction that writes PC through a rotated register operand. The faulty
result is shown by executing the ROM's own bytes; `repro.py` also runs the
ROM's ARM next-PC decoder with it.

## The bug

`func_08FE1638(inst, pc_val)` is GDB's `shifted_reg_val` (`gdb/arm-tdep.c`):
the value of a data-processing or load instruction's shifted-register
operand. For shift type 3 the ROM handles only RRX:

```
08FE170A  beq  0x08FE173C        ; shifttype == 3 (ROR/RRX)
08FE173C  movs r0, #0x1f
08FE173E  ands r3, r0            ; shift &= 31
08FE1740  cmp  r3, #0
08FE1742  bne  0x08FE1762        ; shift != 0: straight to the return
08FE1744  lsrs r2, r1, #1        ; RRX: res >> 1 ...
08FE1746  ldr  r0, =0x09FE2140   ; ... with the carry of the saved CPSR
  ...
08FE1762  adds r0, r1, #0        ; return res
```

A rotate by 1-31 places therefore returns the register unrotated. GDB's
function has the rotate in the `else` arm:

```c
    case 3:			/* ROR/RRX */
      shift &= 31;
      if (shift == 0)
	res = (res >> 1) | (carry ? 0x80000000L : 0);
      else
	res = (res >> shift) | (res << (32 - shift));
      break;
```

## Trigger and how often

The monitor's ARM single step `func_08FE1B04` calls this function at two
sites, as GDB's `arm_get_next_pc` calls `shifted_reg_val`:

| call | GDB's use |
|---|---|
| 0x08FE1E20 | operand 2 of a data-processing instruction whose destination is PC (`mov pc, rm, ror #n`, `add pc, rn, rm, ror rs`, ...) |
| 0x08FE1D00 | the register offset of a pre-indexed `ldr pc, [rn, rm, ror #n]` |

The step driver `func_08FE1EC8` calls `func_08FE1B04` when the saved CPSR is
in ARM state, so the trigger is: under the monitor, single-step an ARM
instruction that writes PC with an operand rotated by 1-31 places, either an
immediate rotate or a register rotate whose low five bits are not zero.
Compilers do not produce such a PC write; only hand-written ARM code would.
In the retail game the monitor never runs (nothing outside its image calls
into it), so the trigger cannot occur there.

## Behaviour against correct behaviour

From `repro.py`; "core" is what an ARM core computes for the same shifter
operand (unicorn's ARM core running `mov r2, <operand>`):

| instruction, registers | ROM | BUGFIX | core |
|---|---|---|---|
| `mov pc, r0, ror #8`, r0 = 0x12345678 | 0x12345678 | 0x78123456 | 0x78123456 |
| `mov pc, r0, ror r1`, r1 = 4 | 0x12345678 | 0x81234567 | 0x81234567 |
| `mov pc, r0, rrx`, C = 0 / 1 | 0x091A2B3C / 0x891A2B3C | same | same |
| `lsl #4`, `lsr #12`, `asr #8`, `lsl r1` (r1 = 40) | the core's value | same | |

Run through the ROM's ARM decoder `func_08FE1B04` for `mov pc, r0, ror #8`
with r0 = 0x00020002, the predicted next PC is 0x00020002 with the ROM and
0x02000200 with the fix; the core goes to 0x02000200.

## Impact

None in the game, because the monitor never runs there. On development
hardware, `func_08FE1EC8` passes the prediction to `func_08FE176C`, which
plants the step breakpoint (the ARM word 0xE7FFFFFF) at the unrotated
address. The instruction itself goes to the rotated one, so the step does not
stop after it: the program runs on until it happens to reach the wrong
address or another breakpoint. Whether the monitor reports the failed
breakpoint write for an address with no memory behind it (`func_08FE176C`
reads the word back and returns 0 when it differs, 0x08FE179A) was not traced
further.

## Developer intent

The intent is GDB's: return the operand the CPU would compute. The function
is GDB's `shifted_reg_val`, whose text is the same from GDB 4.18 (1999) to
6.0 (2003), and everything else in it follows GDB closely:

* the 0xFF mask of a register shift amount (applied as a separate
  statement; GDB's single expression narrows the load to `ldrb`);
* `pc_val + 8` for Rs = 15, and `pc_val + 12` or `pc_val + 8` for Rm = 15;
* LSL and LSR returning 0 from 32 up;
* ASR clamped to 31 and written as `~((~res) >> shift)`
  (0x08FE1728-0x08FE1730);
* ROR's `shift &= 31` before the RRX test.

The port's one deliberate change is the carry: GDB passes it in, the monitor
reads it from the saved CPSR, and that rewrites the RRX line. The rotate line
is the `else` arm directly after it. The likely slip is that the `else` arm
was lost when the RRX line was rewritten, not a different idea of ROR.

Inherited from GDB and not part of this bug (the BUGFIX build keeps them,
and `repro.py` prints them against the core without asserting the core's
value):

* an immediate shift field of 0 is taken literally for LSR and ASR, where
  the CPU reads it as LSR #32 and ASR #32 (0x12345678 is returned for
  `lsr #0` where the core gives 0, and 0x87654321 for `asr #0` where it gives
  0xFFFFFFFF);
* a register ROR whose low five bits are 0 is taken as RRX, where the CPU
  leaves the value unrotated (ROR by 32 gives 0x12345678, not 0x091A2B3C).

## The fix

```c
    case 3: /* ROR/RRX */
        shift &= 31;
        if (shift == 0)
            res = (res >> 1) | ((read_register(PS_REGNUM) & FLAG_C) ? 0x80000000 : 0);
#ifdef BUGFIX
        else
            res = (res >> shift) | (res << (32 - shift));
#endif
```

This is GDB's line. `shift` is 1-31 in the `else` arm, so neither shift is
by 32 or more. The default build is unchanged: the source still MATCHes
141/141 instructions and `plausible.py --strict` exits 0.

## Reproduction

`repro.py`:

1. links the default build at 0x08FE1638 and requires it to equal your ROM's
   306 bytes;
2. maps the monitor image at its run address (ROM address + 0x01002000),
   where its jump tables point and its saved-register block lies;
3. runs the ROM function and the `-DBUGFIX` build from the same saved
   registers, and compares both with unicorn's ARM core;
4. runs the ROM's ARM decoder `func_08FE1B04` with each build (the fixed one
   reached through a veneer over the run copy of `func_08FE1638`).

Requires unicorn and the repository toolchain (see the docstring).

```
$ python3 docs/bugs/08FE1638/repro.py baserom.bin
source src/08FE1638.c: default build == ROM bytes [08FE1638, 08FE176A)

1. Trigger: an immediate rotate, `mov pc, r0, ror #8` (0xE1A0F460),
   r0 = 0x12345678.  ROM: the operand comes back unrotated.
  [ok] ROM    operand: '0x12345678'
  [ok] BUGFIX operand: '0x78123456'
  [ok] ARM core (mov r2, r0, ror #8): '0x78123456'

2. Trigger: a register rotate, `mov pc, r0, ror r1` (0xE1A0F170), r1 = 4.
  [ok] ROM    operand: '0x12345678'
  [ok] BUGFIX operand: '0x81234567'
  [ok] ARM core: '0x81234567'

3. Non-trigger: RRX (`ror #0`, 0xE1A0F060), carry from the saved CPSR.
  [ok] C=0: ROM, BUGFIX, ARM core: ['0x91a2b3c', '0x91a2b3c', '0x91a2b3c']
  [ok] C=1: ROM, BUGFIX, ARM core: ['0x891a2b3c', '0x891a2b3c', '0x891a2b3c']

4. Non-trigger: the other shift types agree with the core.
  [ok] lsl #4            ROM, BUGFIX, ARM core: ['0x23456780', '0x23456780', '0x23456780']
  [ok] lsr #12           ROM, BUGFIX, ARM core: ['0x12345', '0x12345', '0x12345']
  [ok] asr #8            ROM, BUGFIX, ARM core: ['0xff876543', '0xff876543', '0xff876543']
  [ok] lsl r1 (r1 = 40)  ROM, BUGFIX, ARM core: ['0x0', '0x0', '0x0']

5. Inherited from GDB, not this bug: both builds, like GDB's
   shifted_reg_val, take a shift field of 0 literally and treat a
   register rotate by a multiple of 32 as RRX.  The core differs.
  [ok] lsr #0 (= lsr #32)  ROM, BUGFIX: ['0x12345678', '0x12345678']
      ARM core: 0x0
  [ok] asr #0 (= asr #32)  ROM, BUGFIX: ['0x87654321', '0x87654321']
      ARM core: 0xffffffff
  [ok] ror r1, r1 = 32     ROM, BUGFIX: ['0x91a2b3c', '0x91a2b3c']
      ARM core: 0x12345678

6. Impact: the ROM's ARM decoder func_08FE1B04 predicts the next PC of
   `mov pc, r0, ror #8` with r0 = 0x00020002.  The core goes to 0x02000200.
  [ok] ARM core next PC: '0x2000200'
  [ok] ROM    decoder prediction (where the step breakpoint goes): '0x20002'
  [ok] BUGFIX decoder prediction: '0x2000200'

all assertions hold
```
