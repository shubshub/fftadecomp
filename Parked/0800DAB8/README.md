# 0x0800DAB8 - halfword row fill of a task buffer through CpuSet: bytes identical, refused (CpuSet fill from a stack halfword) (82 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0800DAB8(object, index, count, low, high)` does nothing for `index > 159`. Otherwise it takes the object's
buffer from `func_0800C614(object)`, fills `count` halfwords at `buffer + index` with `(high << 8) | low` by a CpuSet
fill from a stack halfword (`func_0814186C(&fill, buffer + index, 0x01000000 | count)` at 0x0800DAF4) and calls
`func_0800C64C(object)`. `high` is the first incoming stack word (`ldr r0, [sp, #0x1c]` at 0x0800DAC2). Callers: the
matched `src/080D9ADC.c` (0x080D9AFA) and four sites in 0x0812803C (0x08128484, 0x081284EE, 0x08128528, 0x081285C2),
which has a `Parked/` entry.

The index row `0800DAB8 0800DB0A 82 41 return` has the right extent; 41 is half the byte count, and the reachable
count is 38 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0800DAB8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800DAB8, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`). The 82-byte symbol equals the ROM span `[0x0800DAB8, 0x0800DB0A)`: SHA-256
`1c281e2739bfbf88317e721440de4457b213cdf3800683cd45e488a1ffc30023` for both. `.text` is 84 bytes: the symbol and the
`c0 46` alignment halfword after it. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0800DAB8.c` (no data symbol to add): the
default run, the BIOS buffer selectors, the two addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the
selectors the #192 comment and earlier notes name. None matched.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `named-data buffers require actual named object relocations and exclude function literals` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `local branch access leaves its established frame` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1` | `entry stack reads must cover exactly every declared incoming word` |

## Cause

The default buffer walk follows a local address into the BIOS wrapper `func_0814186C` (CpuSet) and refuses its `svc`
(`non-leaf calls and interrupts require linked CFG verification`). The BIOS fill selectors refuse earlier (`named-data
buffers require actual named object relocations and exclude function literals`: the function has no data relocation),
and the two-word fill profile its sibling uses refuses the single incoming stack word (`entry stack reads must cover
exactly every declared incoming word`). In the #192 comment's prototypes it matches with nothing else changed, in both
placements. R1 is unwritten at the next `bl` (0x0800DAFA) and carried the external destination, one of the sites the
comment's R0/R1 question is about.

## Source notes

- The fill value is written through a pointer to the local (`u16 *source = &fill; *source = ...`), the spelling merged
  sources use for the SDK fill temporary (see shubshub/fftadecomp-kit#164). With a plain `fill = ...;
  func_0814186C(&fill, ...)` 3 halfwords differ (measured).

kit issue: shubshub/fftadecomp-kit#192 (comment)
