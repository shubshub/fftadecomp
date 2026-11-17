# 0x0801B630 - map layer descriptor by kind: bytes identical, refused (a stack descriptor that reaches a DMA0 fill from a callee local) (152 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801B630(x, y, kind, a, b)` builds a 0x30-byte
descriptor on its stack at sp+8: `kind` at +4; the halfwords `data_0836DA74[kind]`, `data_0836DA7C[kind]` and
`data_0836DA84[kind]` at +6, +8 and +0xA; +0 and +1 cleared and set to 0x80 when `a` or `b` is null; `x << 3` and `y
<< 3` at +0x28 and +0x2A; and the halfword at `g_state_02007F40 + 0x1E` at +0x1E. It then calls
`func_0801AF08(&descriptor, a, b, func_0801AD1C(0), func_0801AD1C(1), 0)` directly (0x0801B6AA). Callers: the matched
`src/080D8384.c`, and 0x0801F80C and 0x080EC7DC.

The index row `0801B630 0801B6C8 152 76 return` has the right extent; 76 is half the byte count, and the reachable
count is 64 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0801B630.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801B630, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 152-byte symbol equals the ROM span `[0x0801B630, 0x0801B6C8)`:
SHA-256 `cf9c1bd521bc6ff5d4c6292d0c1aac71eb2b274a57295e3fc4e12fc01ae0effd` for both. `.text` is exactly 152 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801B630.c` and `data_0836DA74`,
`data_0836DA7C`, `data_0836DA84` added to `config/data_symbols.json` (each at the address its name gives): the default
run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x0801AF08: unsupported stack-alias use or escape` |

## Cause

`func_0801AF08` (1,740 bytes, unmatched) fills from a local of its own through DMA0: `mov r0, sp; strh r1, [r0]; ldr
r1, =0x040000B0; str r0, [r1]` at 0x0801AFC8-0x0801AFCE. The buffer walk follows this function's descriptor into
`func_0801AF08` and refuses that store, the callee-side form of the DMA fixed-source fill. The kit issue's proposed
rule covers the owner's own store only; it lists this case under "Not covered".

kit issue: shubshub/fftadecomp-kit#239 (this function is its "Not covered" case, the same store inside a walked callee)
