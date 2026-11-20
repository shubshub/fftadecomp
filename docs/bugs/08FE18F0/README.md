# func_08FE18F0: the debug monitor's Thumb step predicts that MOV PC, PC goes to itself

**Status: unreachable in the retail game.** The function belongs to a
development-cartridge debug monitor whose memory image fills
`0x08FE0000`-`0x08FE3FFF`; no code outside the image calls into it. On
development hardware running the monitor it is reached by single-stepping
the Thumb instruction `mov pc, pc` (0x46FF). The faulty prediction is shown
by executing the ROM's own bytes, and the misplaced breakpoint by running
the ROM's single step `func_08FE1EC8` with it.

## The bug

`func_08FE18F0(pc, &is_arm)` predicts where the stopped CPU goes after the
Thumb instruction at `pc`, so that the monitor can plant its step breakpoint
there. Both register-to-PC instructions read the register through the same
banked lookup (`read_register`, `include/debug_monitor.h`). The saved r15 is
the address of the stopped instruction: `func_08FE1EC8` passes it as `pc`,
and the monitor's own data in the image still has 0x08000428 there. The BX
path corrects it to what the CPU reads, the address + 4; the MOV path does
not:

```
; BX Rm
08FE1956  lsls r0, r3, #2        ; (read_register(rm))
08FE1958  ldr  r1, =0x09FE2100
08FE195A  adds r0, r0, r1
08FE195C  ldr  r5, [r0]
08FE195E  cmp  r2, #0xf          ; rm == 15:
08FE1960  bne  0x08FE1964
08FE1962  adds r5, #4            ;   pc += 4

; MOV PC, Rm
08FE1AE8  lsls r0, r2, #2        ; (read_register(rm))
08FE1AEA  ldr  r1, =0x09FE2100
08FE1AEC  adds r0, r0, r1
08FE1AEE  ldr  r5, [r0]          ; returned as read
08FE1AF0  b    0x08FE1AFA        ; return
```

For `mov pc, pc` the MOV path returns `pc` itself.

## Trigger and how often

Under the monitor, single-step `mov pc, pc` (0x46FF) in Thumb state.
`func_08FE1EC8` calls this function whenever the saved CPSR has the T bit
set (0x08FE1ED4-0x08FE1EE0). Compiled code does not contain the instruction:
agbcc writes PC only as `mov pc, %0` from an ordinary register (its
`thumb.md` tablejump and indirect jump patterns). Hand-written Thumb code
could. In the retail game the monitor never runs, so the trigger cannot
occur there.

## Behaviour against correct behaviour

From `repro.py`, with the instruction at 0x02000100; "core" is unicorn's
Thumb core running it:

| instruction | ROM | BUGFIX | core |
|---|---|---|---|
| `mov pc, pc` | 0x02000100 | 0x02000104 | 0x02000104 |
| `mov pc, r3`, r3 = 0x02000201 | 0x02000201 | 0x02000201 | 0x02000200 (`func_08FE176C` clears bit 0) |
| `mov pc, lr` in IRQ mode | the IRQ LR (word 18) | same | |
| `bx pc` | 0x02000104, ARM | same | 0x02000104, ARM |
| `b` forward, `pop {r0, pc}` | equal | same | |

Run through the ROM's `func_08FE1EC8`, which hands the prediction to
`func_08FE176C`:

| | ROM | BUGFIX |
|---|---|---|
| breakpoint address (0x09FE20EC) | 0x02000100 | 0x02000104 |
| halfword saved from under it (0x09FE20E8) | 0x46FF, the MOV | 0x46C0, the next instruction |
| halfword at 0x02000100 afterwards | 0xEFFF, the breakpoint | 0x46FF |
| resumed CPU stops at, instructions executed first | 0x02000100, 0 | 0x02000104, 1 |

## Impact

None in the game, because the monitor never runs there. On development
hardware the breakpoint replaces the instruction being stepped, so the CPU
traps before executing it and the step ends where it began. The monitor
saves the replaced halfword (0x09FE20E8) to put it back; the code that
restores it was not traced. Once it is back, the next step starts from the
same state and makes the same prediction, so single steps never get past the
instruction.

## Developer intent

GDB's `thumb_get_next_pc` of the period (GDB 4.18 to 6.0, 1999-2003) decodes
POP with PC, B\<cond\>, B and BL only. The monitor's author added BX and MOV
PC, Rm, and wrote both register decodes the same way: `(insn >> 3) & 7`, plus
8 when bit 6 is set, then `read_register`. The BX path then applies GDB's
`pc_val`, the instruction address + 4, for r15; GDB's own BX decoding,
added in GDB 7.0 (2009), does the same (`if (bits (inst1, 3, 6) == 0x0f)
nextpc = pc_val;`). The MOV path stops after the read. The likely slip is
copy-and-edit: the register decode was carried over from the BX path and the
r15 correction after it was not.

Related, not separate cases:

* B is tested with the mask 0xF000 (0x08FE1970-0x08FE197C), where GDB
  uses 0xF800, so the encodings 0xE800-0xEFFF decode as B. They are undefined
  on the GBA's ARM7TDMI, which traps them at the instruction itself, so the
  step stops in the same place whatever was predicted; only the planted
  breakpoint lands elsewhere.
* A condition field of 14 (0xDExx, undefined) counts as taken, because the
  condition test returns 1 for 14 (`func_08FE1810`, table entry 14 at
  0x08FE18E6): GDB's `condition_true` does the same.
* `add pc, rm` is not decoded and steps by two, as in GDB 4.18 to 6.0,
  which decode no PC-writing ALU instruction in Thumb.
* The monitor's ARM decoder `func_08FE1B04` adds 4, not 8, for BX PC in ARM
  state (0x08FE1BC4-0x08FE1BC8). That is the ARM decoder's question.

## The fix

```c
            pc = read_register(rm);
#ifdef BUGFIX
            if (rm == 15)
                pc += 4;
#endif
```

This is the BX path's correction, applied to MOV. The default build is
unchanged: the source still MATCHes 234/234 instructions and `plausible.py
--strict` exits 0.

## Reproduction

`repro.py`:

1. links the default build at 0x08FE18F0 and requires it to equal your ROM's
   530 bytes;
2. maps the monitor image at its run address (ROM address + 0x01002000),
   where its jump tables point and its saved-register block lies;
3. runs the ROM function and the `-DBUGFIX` build from the same saved
   registers, and compares both with unicorn's Thumb core;
4. runs the ROM's single step `func_08FE1EC8` with each build (the fixed one
   reached through a veneer over the run copy of `func_08FE18F0`), then lets
   the CPU resume until it reaches the planted breakpoint.

Requires unicorn and the repository toolchain (see the docstring).

```
$ python3 docs/bugs/08FE18F0/repro.py baserom.bin
source src/08FE18F0.c: default build == ROM bytes [08FE18F0, 08FE1B02)

1. Trigger: `mov pc, pc` (0x46FF) at 0x2000100.  The core reads PC
   as the address + 4.
  [ok] Thumb core next PC: '0x2000104'
  [ok] ROM    prediction (the MOV itself): '0x2000100'
  [ok] BUGFIX prediction: '0x2000104'

2. Impact: the ROM's single step func_08FE1EC8 plants its breakpoint,
   then the CPU resumes until it reaches it.
  [ok] ROM    breakpoint address (0x09FE20EC): '0x2000100'
  [ok] ROM    halfword saved from under it (0x09FE20E8): '0x46ff'
  [ok] ROM    halfword at the MOV now: '0xefff'
  [ok] ROM    resumed CPU stops at, instructions executed first: ('0x2000100', 0)
  [ok] BUGFIX breakpoint address (0x09FE20EC): '0x2000104'
  [ok] BUGFIX halfword saved from under it (0x09FE20E8): '0x46c0'
  [ok] BUGFIX halfword at the MOV now: '0x46ff'
  [ok] BUGFIX resumed CPU stops at, instructions executed first: ('0x2000104', 1)
   ROM: the breakpoint replaces the MOV, so the CPU traps before
   executing it and the step ends where it began.  BUGFIX: the MOV
   runs and the step stops after it.

3. Non-trigger: `mov pc, r3` (0x469F), r3 = 0x02000201.
  [ok] ROM, BUGFIX (bit 0 kept; func_08FE176C clears it): ('0x2000201', '0x2000201')
  [ok] Thumb core next PC: '0x2000200'

4. Non-trigger: `mov pc, lr` (0x46F7) in IRQ mode: LR from the IRQ bank (18).
  [ok] ROM, BUGFIX: ('0x2000301', '0x2000301')

5. Non-trigger: `bx pc` (0x4778), the BX path's own + 4.
  [ok] ROM    (next PC, ARM flag): ('0x2000104', 1)
  [ok] BUGFIX (next PC, ARM flag): ('0x2000104', 1)
  [ok] Thumb core (next PC, ARM state): ('0x2000104', True)

6. Non-trigger: `b` forward (0xE002) and `pop {r0, pc}` (0xBD01).
  [ok] b:   ROM, BUGFIX: ('0x2000108', '0x2000108')
  [ok] pop: ROM, BUGFIX: ('0x2000401', '0x2000401')

all assertions hold
```
