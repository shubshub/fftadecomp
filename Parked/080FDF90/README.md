# 0x080FDF90 - projectile effect task (ROM tables, Sqrt, Div, _call_via_r3): bytes identical, refused (variable index into a stack copy of a ROM table; thunks and BIOS calls in the owner) (674 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_080FDF90(task, descriptor, payload)` is a task callback. Phase 0 copies the start and end points into the
payload through `data_0836D4BC[0]` (`_call_via_r3`, 0x080FE002 and 0x080FE010). 0x100 offsets the start by the entry
of the stack copy of `data_08149DB4` selected by `direction` and creates the sprite and four parts. 0x101 computes the
distance with two Sqrt calls (`func_08141898`, 0x080FE12C and 0x080FE146), the duration with Div (`func_08141870`,
0x080FE150) and starts the motion. 0x102 copies `data_08149DC4` to a local `u16[4]` with `func_081443FC` (0x080FE1A4)
and attaches the parts; 0x104 releases everything. No `bl` reaches it: its address is the literal word at 0x080FE440
in 0x080FE2E8, which has a `Parked/` entry.

The index row `080FDF90 080FE232 674 337 return` has the right extent; 337 is half the byte count, and the reachable
count is 299 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`080FDF90.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FDF90, with every callee and data symbol bound to its
ROM address (20 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 674-byte symbol equals the ROM span `[0x080FDF90,
0x080FE232)`: SHA-256 `38f53dbb06f9d55ca28d1314a5b7010a0ac861941651b733f47a6addcd6c21ec` for both. `.text` is 676
bytes: the symbol and the `c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/080FDF90.c` and `data_08149DB4`,
`data_08149DC4` added to `config/data_symbols.json` (each at the address its name gives): the default run, the two
stack-index selectors and the ROM-table-copy selector the #200 comment discusses, and the selectors earlier notes
name. None matched.

| Selector | Result |
|---|---|
| default | `unsupported stack-address materialization` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` (3) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |

## Cause

The default path refuses the variable index into the stack copy (`unsupported stack-address materialization`). The
stack-index and ROM-table-copy selectors refuse the owner for its `_call_via_r3` calls (`acyclic owner excludes
arithmetic runtimes and indirect thunks`), the #200 comment's row.

## Source notes

- Needs `data_08149DB4` and `data_08149DC4` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#200 (comment)
