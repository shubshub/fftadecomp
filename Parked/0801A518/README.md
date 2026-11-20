# 0x0801A518 - phased record loader of module 0x0801: bytes identical, refused (a dead stack address left in R2 at the root return, beside two CpuSet fills) (1888 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_0801A518(u8 index, u8 *state)` is a task callback (signature as `src/080241B4.c`) that steps `*state` through
states 0-9 and then 0xFF. For the record `data_02007F10.index` of the resource table `data_08569104` it unpacks the
record's tiles into `data_020091A0` (`func_08141890` for types 0x10/0x12, `func_0800543C` for 0x20/0x22), queues the
transfers through the 0x1C-byte transfer records `data_02007EB0[0..2]` (`func_08000ADC`, `func_08000B68`), clears two
buffers with CpuSet fills (`func_0814186C`), scans the 64x64 tile buffer for the bounding box of the tiles that are not
the fill tile, builds the record's animation objects (`func_08019FC8`, `func_08020DA0`, `func_08020FA4`) and registers
`func_0801AC78` as a task (`func_08006ADC`).

## The index

The index row `0801A518 0801AC78 1888 781 return` is right: `push {r4-r7, lr}` plus r8-r10 and `sub sp, #0x40` pair
with `add sp, #0x40`, the r8-r10 and r4-r7 pops and `pop {r0}; bx r0` at 0x0801AC5E-0x0801AC6C, the function's only
return. No index change is needed.

## Byte identity

`0801A518.c` (SHA-256 `98af8630149b6e9eadc45020806af5d331517a612d1f2d6ef1adfe20d6e1a811`) was compiled as `match.py`
compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x0801A518 with every callee and data symbol bound to
its ROM address (89 relocations resolved, including the Thumb bit on the function literal `func_0801AC78` at
0x0801AB5C and the record addends 0x1C and 0x38 of `data_02007EB0`). The 1888 linked bytes equal the ROM span
`[0x0801A518, 0x0801AC78)`, SHA-256 `44fa6564bd95a4f2e856e4476455aef6700ee0574727420671e80650b7d913dc`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`. The literal words
0x02007ECC (five, from 0x0801A794) and 0x02007EE8 (0x0801A88C) are `&data_02007EB0[1]` and `&data_02007EB0[2]`, as
`src/0801CE6C.c` addresses the same records.

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x0801A518` with this source copied to `src/0801A518.c`. None
matched.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers; function-data-buffer proof: local stack pointer escapes through a return register` |
| `--owner-runtime-profile bounded-buffer-root-return-scratch-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-function-literals-data-v1` | `buffer callee 0x0801E68C: buffer pointer escapes through a return register` |
| `--owner-runtime-profile bounded-buffer-bios-fill-source-v1` | `local stack pointer escapes through a return register` |

Under `bounded-buffer-bios-fill-source-v1` the refusal is raised at `match.py:5065` (`verify_leaf_instructions`,
reached from `owner_admission_profile.verify`), the check that no stack alias is left in a result register at an
unconditional return.

## Cause

1. **A dead stack address in R2 at the root's return.** State 3 calls `func_0801E68C(&first, &second, &third)` with
   `add r2, sp, #0x2c` at 0x0801A720 and `bl` at 0x0801A722. `func_0801E68C` (`src/0801E68C.c`) stores through its
   three arguments and writes only r0, r3 and r4 (restored), so R2 still holds sp+0x2C, which is entry SP - 52 in this
   frame (32 bytes of saved registers plus `sub sp, #0x40`), when it returns. If the halfword at 0x02007F10 (the record
   index) is 0xFF, the function goes straight to the exit: `cmp r0, #0xff` at 0x0801A72A, `b 0x0801A82A`,
   `movs r0, #4`, `b 0x0801A8BE`, the state store at 0x0801A8C0, `b 0x0801AC5E`, and the return `bx r0` at
   0x0801AC6C. On that path R2 is dead: nothing reads it before the return. An experiment,
   not a tool result: printing the failing frame's locals at the `raise` under `bounded-buffer-bios-fill-source-v1`
   shows `current = 0x0801AC6C` and `aliases = {R2: -52}`, exactly this address at this return.
2. **No selector composes the two proofs this owner needs.** `bounded-buffer-root-return-scratch-v1` projects a dead
   R2/R3 alias away at the bound root's own normal return, but it has no proof for the two CpuSet fills: it walks
   `func_0814186C` (at 0x0801A884 and 0x0801A966, a local `u16` source at sp+6, controls `0x01000000 | (count << 4)`
   and `0x01000100`) and stops there. `bounded-buffer-bios-fill-source-v1` gets past both fills and stops at the
   return, where it has no projection. Whether it would then accept the function literal (`func_0801AC78`, literal
   word 0x0801AB5C) is untested.

## Source notes

1. **`case 0xFF: break;`.** The ROM's switch is a compare tree rooted at 5 (`cmp r0, #5` at 0x0801A528), the balance of
   eleven labels 0-9 and 255; state 9 stores 0xFF. Without the empty label the function differs (1880 bytes).
2. **One `u16 zero` at function scope**: states 4 and 6 both take its address at sp+6 (`mov r0, sp; adds r0, #6` at
   0x0801A870 and 0x0801A958) as the CpuSet fill source.
3. **State 1, type 0x12: `header++;` then the call.** The ROM adds 4 to the pointer in place (`adds r2, #4` at
   0x0801A5E4) and joins the type 0x10 call (`b 0x0801A608`). `func_08141890(header + 1, ...)` differs (1900 bytes).
4. **States 2 and 3 keep identical arms for types 0x12 and 0x22**; the ROM has both copies (0x0801A678/0x0801A6A4 and
   0x0801A76A/0x0801A7A0). Merging state 2's arms as `type == 0x12 || type == 0x22` gives 1856 bytes. In state 1 the
   two arms differ (`func_08141890` against `func_0800543C`), so the chain reads as copied.
5. **State 1, type 2 is written `else if (type != 2) { if (type == 0x10) ... else if (type == 0x20) ... }`.** The flat
   chain with an empty arm, `else if (type == 2) { } else if (type == 0x10) ...`, is byte-identical too, but
   `plausible.py --strict` refuses it (`empty-body`). This is the one place where a plausibility finding chose the form;
   a reviewer should confirm the nested form is natural.
6. **`destination`, `source` and `const u8 *base` locals** in states 4, 5 and 6, as `src/0801A320.c` and
   `src/08019FC8.c` write them.
7. **The scan loop's bounding-box trackers are `s16`** (`min_x`, `min_y`, `max_x`, `max_y`) with `s32 x, y`. `s32`
   trackers give 1880 bytes; `u8` x trackers give 1892 bytes.

No original bug is reproduced.

kit issue: none yet for the composition. Related: shubshub/fftadecomp-kit#199 (the same refusal at a root return; there
the dead address is in R1, which `bounded-buffer-root-return-scratch-v1` does not project; here it is in R2, which the
projection covers, but that selector has no proof for the CpuSet fills).
