# 0x080D963C - affine scanline task with a line template: bytes identical, refused (variable index into a stack copy of a ROM table; CpuSet copies of a local record) (180 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080D963C(task, command, state)` is a task callback. In state 0 it copies the register-pair table `data_08149B24`
to the stack and creates the scanline task with `func_0800C3CC(func_080D9BC0, 0xC80, 0x10, pair[background - 2])`
(0x080D9684); it copies the command's 20-byte template into a local record with CpuSet (0x080D9696), then copies the
record into the 160 line records, adding 0x100 to its offset each line (0x080D96A2). States 1, 0x100 and 0x101 stop
and release the task. No `bl` reaches it: its address is the literal word at 0x080D9A10 in the matched
`src/080D99C0.c`.

The index row `080D963C 080D96F0 180 90 return` has the right extent; 90 is half the byte count, and the reachable
count is 79 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080D963C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D963C, with every callee and data symbol bound to its
ROM address (6 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 180-byte symbol equals the ROM span `[0x080D963C, 0x080D96F0)`:
SHA-256 `2d588afdffe583cc0e6dfe1f8969f08a60d1e223dda38c9809e39b1a7da11bd4` for both. `.text` is exactly 180 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080D963C.c` and `data_08149B24` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the two stack-index selectors and
the ROM-table-copy selector the #200 comment discusses, and the selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `named-data-buffer-rom-table-copy-v1` and `bounded-buffer-bios-fill-source-v1` (3) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |

## Cause

The default path refuses the variable index into the stack copy (`unsupported stack-alias use or escape`). Both
stack-index selectors admit it and stop at the CpuSet wrapper, the #200 comment's row.

## Source notes

- Needs `data_08149B24` in `config/data_symbols.json`. The callback `func_080D9BC0` now has its index row (`080D9BC0
  080D9BCC 12 5 return`), which an earlier note asked for.

kit issue: shubshub/fftadecomp-kit#200 (comment); related: shubshub/fftadecomp-kit#135
