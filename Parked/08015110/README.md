# 0x08015110 - text script renderer: bytes identical, refused (a jump table with backward cases beside local buffers) (652 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08015110(state, buffer, text, style, mode)` draws a
text script and returns the number of bytes consumed. It optionally binds the target buffer (`func_08013528`) and sets
the style (`func_080137C0`), then reads the script: byte 1 switches to raw bytes, 0 ends it (or resumes after an
inserted name), a byte with bit 7 set and the next byte form a glyph (`func_0801360C`), and `@` starts an escape. The
escape letter selects one of 88 cases (`subs r0, #0x21; cmp r0, #0x57; bhi`, dispatch `mov pc, r0` at 0x08015188,
table at 0x08015190): `c` and `n` end the script, `s`, `<` and `>` move the cursor (`func_08013728`), `%` draws a name
that `func_08018CEC` writes into a local 0x2C-byte buffer, and `g` draws an icon through `func_08015DAC(data_02003CB0,
code, &missing)` and a 0x40-unit CpuSet copy. Cases `u` and `x` jump back to 0x08015166, before the dispatch. It has
95 callers, 59 of them matched on main (for example `src/08008F94.c`, `src/0802C034.c`, `src/080601D0.c`).

The index row `08015110 0801539C 652 326 return` has the right extent; 326 is half the byte count. The kit's
refinement stops at the dispatch; an independent CFG walk through the 88-entry table gives 132 reachable instructions.
No refusal below depends on it.

## Byte identity

`08015110.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08015110, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`, 90 `R_ARM_ABS32`). The 652-byte symbol equals the ROM span `[0x08015110,
0x0801539C)`: SHA-256 `6e3fc4e251d30f4d5c882864a74935b9159d14a1097886f6a26923e23c6a2889` for both. `.text` is exactly
652 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08015110.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `structural inventory is not closed` |
| `ordinary-multiple-switch-source-v1` | `data target must be an undefined mapped object` |

## Cause

With a switch the default path has no buffer proof, so the local `name` buffer and `&missing` refuse at the first call
they cross (`stack aliases cannot cross calls in caller-clobbered registers`). The guarded-switch selectors do not
close the inventory with these backward case targets (`structural inventory is not closed`), and
`ordinary-multiple-switch-source-v1`, the route the earlier notes name for backward cases, refuses with `data target
must be an undefined mapped object`. As a callee, its table stops the buffer walk of callers that pass it a local,
such as 0x080153FC once the copy helper there is summarised (per the copy-helper issue).

## Source notes

Open questions from the attempt, for a reviewer: the `for (;;)` loop with a `done` flag, the placement of the raw
path, and `func_08013728` declared with an `s32` amount.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout); (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors) (there as the next callee of 0x080153FC)
