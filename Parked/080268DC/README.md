# 0x080268DC - unit template slot test: bytes identical, refused (a word switch, a framed local byte buffer read at a register index, named data) (252 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_080268DC(kind)` switches on `kind` over 0xCA..0xD2
through a 9-entry word jump table (`subs r0, #0xca; cmp r0, #8; bhi`, dispatch at 0x08026904, table at 0x0802690C)
that fills a local `u8 slots[3]`, set to 0xFF first, with up to three indices into `data_02002E78`, the 16-byte
`UnitTemplate` table also used by `src/08058C48.c`. It then returns 1 when one of the listed templates has a non-zero
name word, and 0 at the first 0xFF slot or after three. The matched `src/08026D44.c` calls it. This entry refreshes
the earlier one; the source is unchanged.

The index row `080268DC 080269D8 252 126 return` has the right extent; 126 is half the byte count, and the reachable
count is 103 (the kit's own refinement and an independent CFG walk agree). Of the refusals below only
`restoring-owner-switch-entry-word-v1` reads that count.

## Byte identity

`080268DC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080268DC, with every callee and data symbol bound to its
ROM address (11 `R_ARM_ABS32`). The 252-byte symbol equals the ROM span `[0x080268DC, 0x080269D8)`: SHA-256
`00b0f1609a7d1237e3386e837659cc78bf0604b17ca9e0359a59b89f37945ac2` for both. `.text` is exactly 252 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080268DC.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `--switch-data-profile u16-scalars-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-guarded-switch-v1` | `named-data buffer caller excludes local BL and word switches` |
| `--switch-profile two-constants-frame-v1` | `unsupported compiler assembly statement: '.word\tdata_02002E78'` |
| `numeric-data-switch-source-v1` | `numeric switch requires ordinary calls, zero-addend data and local table words` |
| `ordinary-multiple-switch-source-v1` | `data target must be an undefined mapped object` |
| `canonical-integer-private-locals-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` |
| `restoring-owner-switch-entry-word-v1` | `complete-owner text reachable instruction count differs` |

## Cause

The loop reads `slots[i]` at a register index (`mov r0, sp; adds r1, r0, r3; ldrb r0, [r1]` at 0x0802699E-0x080269A2),
which the default switch path refuses as an escape. The stack-index selectors, which bound such an index, refuse the
word switch (`named-data buffer caller excludes local BL and word switches`); the switch and switch-data selectors
refuse the index, the data word or the layout. Verifying it needs the stack index on the switch path, with the one
named data word.

## Source notes

- The chained `slots[0] = slots[1] = slots[2] = 0xFF;` gives the three `mov rN, sp` copies (0x080268E4-0x080268E8).
- `return 0` inside the loop at the first 0xFF slot, rather than `break` to the final `return 0`, is needed against
  strength reduction of the loop; the two are equivalent, and a reviewer has to accept the choice.

## History

The earlier entry recorded the same refusals at an older kit, with two strings that read differently at 18dcc516:
`canonical-integer-private-locals-data-source-v1` now reports `six-word integer source requires canonical integer
calls and zero-addend named objects`, and `--switch-profile two-constants-frame-v1` quotes the pool word as
`'.word\tdata_02002E78'`. The two stack-index rows are new.

kit issue: shubshub/fftadecomp-kit#200 (comment); shubshub/fftadecomp-kit#74 (the word switch with a framed buffer)
