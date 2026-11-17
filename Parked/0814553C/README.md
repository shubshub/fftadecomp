# 0x0814553C - m4a SoundInit (sound state and DMA set-up): bytes identical, refused (a CpuSet fill from a stack word on the function-literal path; volatile MMIO casts) (204 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0814553C(state)` initialises the sound state: it clears the signature, rewrites the DMA 1 control word if its
repeat bit is set, programs the sound and DMA registers (0x040000C6, 0x04000084, 0x04000082, 0x04000089, the DMA 1
source 0x040000BC and destination 0x040000C0 = FIFO A), stores `state` to `data_03007FF0`, clears 0x980 bytes of the
state by a 32-bit CpuSet fill from a stack zero (`func_0814186C(&zero, state, 0x05000260)` at 0x0814559A), sets two
fields, installs `func_08144E08` and the empty handler `func_081465E4` in the handler table, calls
`func_0814492C(data_02008E60)` and `func_08145608(0x40000)` and stamps the signature 0x68736D53. It lies in the
`m4a.c` library unit; its caller is the matched `src/0814513C.c` (0x08145150).

The index row `0814553C 08145608 204 72 return` is right: 72 reachable instructions, the count the kit's own CFG
refinement gives. `config/functions.json` has the same extent and count.

## Byte identity

`0814553C.c` was compiled with the toolchain of its library unit, `old-agbcc-O2-v1` (`cpp -nostdinc -undef -I
include`, `old_agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0814553C,
with every callee and data symbol bound to its ROM address (3 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 204-byte symbol
equals the ROM span `[0x0814553C, 0x08145608)`: SHA-256
`e94a015e3d7b691e0c020e05509c3b94b334005bfc67a3c0c5dbed792bab04d7` for both. `.text` is exactly 204 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 1 (see Source notes).

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0814553C.c` and `data_02008E60` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the BIOS buffer selectors, the two
addressed BIOS-fill-buffer selectors, `named-data-buffer-v1`, and the selectors the #192 comment and earlier notes
name. None matched.

| Selector | Result |
|---|---|
| default and `--unit-toolchain old-agbcc-O2-v1` (2) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `discarded return scratch excludes callback literals and switches` |
| `bounded-buffer-bios-fast-fill-source-v1`, `bounded-buffer-bios-mixed-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bounded-buffer-guarded-bios-division-v1` and `named-data-buffer-v1` (2) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-v1` | `addressed signed runtimes exclude data and irregular relocations` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `addressed data requires a mapped object and signed32 addend` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-function-literals-data-v1` | `addressed data requires exact typed coverage of reached address words` |

## Cause

The function literals and the data words put it on a path without a buffer proof, where the stack zero passed to
CpuSet is refused as a live alias across the call (`stack aliases cannot cross calls in caller-clobbered registers`);
`--unit-toolchain old-agbcc-O2-v1` gives the same. The BIOS fill selectors refuse the literals or the data words. With
the #192 comment's call-site fill rule the verifier gets past the fill and finds the bytes identical, and the source
is then refused by its static `volatile` findings.

## Source notes

- The MMIO accesses are `volatile` casts with `plausible:` comments. `plausible.py --strict` exits 1 with 3 `volatile`
  errors: the read of 0x040000C4 in the `if` (line 38), the store under it (line 39, whose comment is two lines up)
  and the read-modify-write of 0x04000089 (line 47). The other five justified stores pass. It does not ship until
  those three are spelled or justified in a form the checker admits.
- Byte identity holds both with the unit's `old_agbcc` and with the default agbcc (match.py's unit consistency check
  passes, so its default run compiles with agbcc).
- Needs `data_02008E60` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#192 (comment)
