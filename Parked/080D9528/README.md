# 0x080D9528 - background scroll command task: bytes identical, refused (variable index into stack copies of two ROM tables; CpuSet fill from a stack halfword) (274 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080D9528(task, command, state)` is a task callback. In state 0 it copies the two eight-pointer tables
`data_08149AD4` (BG scroll registers) and `data_08149AF4` (their RAM shadows) to the stack, selects entry `(layer <<
1) | axis`, creates the scroll object with `func_0800CE08(mode, *shadow, register)` (0x080D959C) and, for modes 1 and
2, fills one or three of its line buffers (`func_0800DA48`) with the next shadows' values by CpuSet fills from a stack
halfword (0x080D95EE). States 1, 0x100 and 0x101 stop and release the object. No `bl` reaches it: its address is the
literal word at 0x080D9968 in the matched `src/080D993C.c`.

The index row `080D9528 080D963A 274 137 return` has the right extent; 137 is half the byte count, and the reachable
count is 125 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080D9528.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D9528, with every callee and data symbol bound to its
ROM address (5 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 274-byte symbol equals the ROM span `[0x080D9528, 0x080D963A)`:
SHA-256 `d4373a9c353b6b2e8df9767bf6fd351fe247c5d0d1ad03ce0812c0776bebd381` for both. `.text` is 276 bytes: the symbol
and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080D9528.c` (no data symbol to add): the
default run, the two stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the
selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `named-data-buffer-rom-table-copy-v1` and `bounded-buffer-bios-fill-source-v1` (3) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |

## Cause

The default path refuses the variable index into the stack copies (`unsupported stack-alias use or escape`). Both
stack-index selectors admit the index and stop at the CpuSet wrapper (`buffer callee 0x0814186C: non-leaf calls and
interrupts require linked CFG verification`), the #200 comment's row; the #192 issue lists this function among those
that also need a variable stack index.

kit issue: shubshub/fftadecomp-kit#200 (comment); shubshub/fftadecomp-kit#192 (listed in the issue: a variable stack index beside a BIOS wrapper); related: shubshub/fftadecomp-kit#135
