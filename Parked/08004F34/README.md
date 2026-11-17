# 0x08004F34 - link packet poll (IWRAM probe, checksums, CpuSet copies): bytes identical, refused (a variable index into a local u8[4]; a call through _call_via_r0) (192 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_08004F34(destination)` calls the IWRAM routine at 0x03002B70 through `_call_via_r0` (0x08004F44) and keeps its
word result as four ready bytes on the stack. For each of the two packets of `data_030028A0` it sums ten halfwords; if
the packet is ready (`ready[i]`, a variable index into the local bytes) and the sum is 0xFFFF it copies the 16-byte
payload to `destination[i]` with CpuSet (0x08004F9E) and sets bit `i` of the result; then it clears the payload by a
CpuSet fill from a stack zero (0x08004FBE). It returns the result bits, also ORed into `field_02`. Its caller is the
matched `src/08004E10.c` (0x08004E86).

The index row `08004F34 08004FF4 192 85 return` is right: 85 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`08004F34.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08004F34, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 192-byte symbol equals the ROM span `[0x08004F34, 0x08004FF4)`:
SHA-256 `7d1ceb851419f34ec87229549d6b9ca42dd3cb4cdd03b591369732e3e637ab86` for both. `.text` is exactly 192 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/08004F34.c` (no data symbol to add): the
default run, the two stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the
selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` (3) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |

## Cause

The default path refuses the variable index into the local bytes (`unsupported stack-alias use or escape`). Both
stack-index selectors and the ROM-table-copy selector refuse the owner for its `_call_via_r0` call (`acyclic owner
excludes arithmetic runtimes and indirect thunks`), which is the #200 comment's row for this function.

## Source notes

- The IWRAM routine is called through a raw cast, `((ReadyProbe08004F34)0x03002B70)()`, since there is no symbol for
  RAM code; and its word result is stored with `*(u32 *)ready = ...` into a `u8[4]`. Both are review questions.

kit issue: shubshub/fftadecomp-kit#200 (comment)
