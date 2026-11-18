# 0x0800CF08 - affine window task creation (kind 0): bytes identical, refused (a variable index into a stack copy of a ROM table) (192 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0800CF08(target, x, y, width, height)` copies the two-pointer table `data_08149820` (the BG2 and BG3 affine
register blocks 0x04000020 and 0x04000030) to the stack and creates the affine wave task with
`func_0800C3CC(func_0800D3BC, 0x2B8, 0x10, targets[target - 2])` (0x0800CF4C). It fills the task's state
(`func_0800C614`) with kind 0, the rectangle, its 8.8 fixed-point origin, the right and bottom edges and scale 0x100,
copies them to the start fields, and sets the 160 line scales to 0x100. No `bl` or literal word in the ROM reaches it.

The index row `0800CF08 0800CFC8 192 87 return` is right: 87 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`0800CF08.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800CF08, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 192-byte symbol equals the ROM span `[0x0800CF08, 0x0800CFC8)`:
SHA-256 `13c547cbf222c46889eab5c25f01e560574a54e7b6140424394edbf4bcc1adb0` for both. `.text` is exactly 192 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0800CF08.c` and `data_08149820` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the two stack-index selectors and
the ROM-table-copy selector the #200 comment discusses, and the selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default and `named-data-buffer-rom-table-copy-v1` (2) | `unsupported stack-address materialization` |
| `named-data-buffer-stack-index-v1` | `stack index: the premise rows of 0x0800CF08 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)`; the row it prints: site `0x0800CF46`, expression `(((entry_R0 << 24) >> 22) - 8)`, bound 5 |
| `named-data-buffer-stack-index-v2` | `stack index: the premise rows of 0x0800CF08 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)`; the row it prints: site `0x0800CF46`, expression `(u32)(((entry_R0 << 24) >> 22) - 8)`, bound 5 |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2`, each with the row it prints added to `config/stack_index_premises.json` as a throwaway entry (not reviewed) | `ROM table copy owner requires named data or an object initialiser and excludes function literals and switches` |

## Cause

The default path refuses the variable index into the stack copy (`unsupported stack-address materialization`). Both
stack-index selectors ask for a premise row for the index at 0x0800CF46 (bound 5); with that row added as a throwaway
entry they refuse the function literal (`ROM table copy owner requires named data or an object initialiser and
excludes function literals and switches`), as the #200 comment says.

## Source notes

- Needs `data_08149820` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#200 (comment); related: shubshub/fftadecomp-kit#135

## Entry-domain check, 2026-11-19

The kind-0 constructor still compiles to the same 192 bytes with the callback
signature and helper return types from 0800C3CC and 0800C614. Signed
coordinate multiplication by 256 also reproduces both fixed-point origins.

The two table words at 08149820 and 08149824 name BG2PA and BG3PA. The
constructor copies them into an eight-byte local, then loads the word at local
offset `4 * ((u8)target - 2)` at 0800CF46. Execution of this original prefix
for every one of the 256 low-byte values reached the registration call at
0800CF4C. Inputs 2 and 3 passed 04000020 and 04000030 respectively. Inputs
0 and 1 read below SP, input 4 read saved R8, and input 9 read saved LR.
Only inputs 2 and 3 are in the copied table.

There is no direct Thumb BL, B or conditional B, ARM immediate branch, or
even or odd absolute pointer to the constructor in the original ROM. The
preceding routine returns at 0800CF04. The exact two-value API domain is
known, but a caller establishing it has not been recovered. The four
constructors contain the only four pointer words to 08149820 and to the
shared callback 0800D3BD. With merged kit #292 the ordinary selector still
refuses the indexed local; the stack-index v2 selector independently requires
a reviewed execution bound and excludes the callback literal.
