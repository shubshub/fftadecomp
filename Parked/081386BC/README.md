# 0x081386BC - stat panel draw: bytes identical, refused (a BIOS CpuSet fill from a stack halfword and a stack text buffer passed to func_080142DC) (896 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes the earlier `Parked/081386BC/` (kit fcdf2d45) at kit 18dcc516; the source is unchanged
(same file). `func_081386BC` draws a status panel into a tile buffer (its third argument; it takes six, the last two in the
incoming stack words). It clears 0x600 halfwords of the buffer with BIOS CpuSet in fill mode from a zero halfword on the
stack (`func_0814186C`, 0x081386E8), then draws the labels and numbers through `func_08015110` (8 calls, with the text
context at `*data_030027D8 + 0xF9C` and strings from the table `data_085668B0`), `func_080142DC` (8 calls, with a local
text buffer; `func_080142DC` calls the digit routine `func_08002FB8`), `func_0808B8E4` (14), `func_0808B7C0`,
`func_08035678` (6) and `func_08035A68` (4). Its callers are `func_08138EFC` (eight sites) and `func_08139C70` (three
sites). The index row `081386BC 08138A3C 896 368 return` is right.

## The index

`symbols/functions.txt` has `081386BC 08138A3C 896 368 return` and `config/functions.json` the same extent with 368 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 368 reachable instructions, so the row is right.

## Byte identity

`081386BC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081386BC, with every callee bound to its ROM address and every data word to the address its symbol names (40 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 896-byte symbol equals the ROM span `[0x081386BC, 0x08138A3C)`: SHA-256 `71c79a4cc4fa8ce0ba38979d525942d9339b7c9fe76bdae84da233d51a75eca7` for both. `.text` is exactly 896 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081386BC.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-code-image-data-v1` and 7 other addressed-runtime selectors (10) | `buffer callee 0x080142DC: stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 20 other selectors (23) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 7 other selectors (10) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `buffer callee 0x080142DC: buffer callee 0x08002FB8: signed remainder requires numeric proof or fresh addressed-call provenance` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 141 selector values are not listed one by one (none matched); by family: scheduler (25), addressed-runtime (19), callback and closure (19), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (2), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run walks the fill source into the BIOS CpuSet wrapper and stops there: `buffer callee 0x0814186C:
non-leaf calls and interrupts require linked CFG verification`. The selectors that summarise the fill go further and
stop in the text calls: `bounded-buffer-bios-fill-source-v1` and its two relatives at the digit routine reached through
`func_080142DC` (`buffer callee 0x080142DC: buffer callee 0x08002FB8: signed remainder requires numeric proof or fresh
addressed-call provenance`), `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1` (the selector of
the matched siblings `0x081384B0`, `0x08138A3C` and `0x08138B4C`) at `buffer callee 0x080142DC: stack aliases cannot
cross calls in caller-clobbered registers`.

The #192 comment reports that with its BIOS summaries in the buffer walk this function passes the fill and stops at
the digit loop of `func_08002FB8`, which stores below its buffer. These refusals are the same as at kit fcdf2d45.

## Source notes

Choices the bytes do not fully pin, from the earlier attempt:

- `text` is assigned before each of five calls (the ROM loads the string pointer before the text context at
  0x081386F2, 0x08138766, 0x081387FA, 0x08138816 and 0x08138A04; an inline form puts it after); possibly a spare
  temporary.
- One `s32 value` for five numbers (signed `ble` at 0x0813871C, 0x0813879A, 0x08138842; R5 throughout).
- The if/else form of `one_digit` (the field load comes first at 0x08138780-0x0813878E).
- The association `(offset + 11 + one_digit)` (0x081387E0-0x081387E4).
- `func_080142DC(void *, u16, u32)` is declared as `src/08025B54.c` declares it (the callee narrows R1 at
  0x080142E6).

kit issue: shubshub/fftadecomp-kit#192 (comment) (the digit loop of 08002FB8, which stores below its buffer)
