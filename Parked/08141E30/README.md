# 0x08141E30 - agb_flash WaitForFlashWrite_Common: bytes identical at -O1, refused by the library-unit path (`_call_via_r1` calls in the orphan-constant check) (136 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function lies in the `agb_flash FLASH512_V130` library
unit (`config/library_units.json`, toolchain `agbcc-O1-v1`) and is the SDK's `WaitForFlashWrite_Common` (in pret's
agb_flash sources). It starts the flash timer for `phase` (`func_081419C0`, 0x08141E48), then polls the status byte at
`address` through the routine pointer held at `data_0200F364` (pret's `PollFlashStatus`: `ldr r1, [r7]` and
`bl _call_via_r1` at 0x08141E7C-0x08141E80) until it reads `lastData`. Once the timeout flag `data_0200F360` (pret's
`gFlashTimeoutFlag`) is set it polls a second time (0x08141E94-0x08141E98); if that read still differs it writes 0xF0
to 0x0E005555 when the maker ID of `*data_0200F370` (pret's `gFlash`, byte 0x14) is 0xC2 (0x08141E5C-0x08141E6A), and
returns `phase | 0xC000`. Otherwise it returns 0. Both paths stop the timer (`func_08141A68`, 0x08141EA4). The
`0xC000 | phase` value is built ahead of the loop (0x08141E4E-0x08141E54). The index row
`08141E30 08141EB8 136 55 return` is right (55 reachable instructions; four literal words at 0x08141E58, 0x08141E74,
0x08141E78 and 0x08141EB4). `data_0200F360`, `data_0200F364` and `data_0200F370` are already in
`config/data_symbols.json`; no new data symbol is needed.

## Byte identity

`match.py` stops before its own byte comparison (below), so identity was shown by hand with the unit's toolchain:
`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O1` (the binary `match.py` names for the unit, SHA-256
`7ea44f90820c51ccfe53ba1cebdb736d69639fd4c8ea651809dbc58a3064d422`), `arm-none-eabi-as -mthumb-interwork`. At -O1
agbcc also writes a 12-byte `.rodata` holding copies of the pool words `data_0200F364`, `data_0200F360` and
`data_0200F370`, which nothing references; it was left out of the link, as `library_units.exclude_orphan_constants`
does once its prerequisite passes. `.text` is exactly 136 bytes. Linked at 0x08141E30 with `func_081419C0`,
`func_08141A68`, `_call_via_r1` (0x08142248) and the three data symbols bound to their ROM addresses (4
`R_ARM_THM_CALL`, 3 `R_ARM_ABS32`), the 136-byte symbol equals the ROM span `[0x08141E30, 0x08141EB8)`: SHA-256
`bf1371de7282c1433831abcda94c6df69b542b4b9245e25f7a6670ee0bf7fcd8` for both. `plausible.py --strict` exits 0.

The same source under the default `agbcc -mthumb-interwork -O2` gives a 140-byte symbol that differs from the ROM in
97 of the 136 bytes, from 0x08141E4C on.

As a diagnostic only, in a scratch copy of the kit with nothing changed except the call-name pattern at
`compiler_orphan_constants_prerequisite.py:218` widened to `func_[0-9A-F]{8}|_call_via_r[0-7]`,
`match.py --unit-toolchain agbcc-O1-v1` reports `MATCH - byte identical` (55/55 instructions, 136/136 bytes).

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08141E30.c`: the default run, the
`--unit-toolchain agbcc-O1-v1` run, and the four selectors below with and without `--unit-toolchain agbcc-O1-v1` (ten
runs). None matched.

| Run | Refusal |
|---|---|
| `--unit-toolchain agbcc-O1-v1` | `compile failed: unsupported orphan prerequisite call identity` |
| default (no toolchain option) | `refused: 0x08141E30 lies in library unit agb_flash FLASH512_V130: its default-toolchain object differs from agbcc-O1-v1's; verify it with --unit-toolchain agbcc-O1-v1` |
| `--function-address-profile canonical-thunks-v1`, `--function-address-profile umod48-r1-thunks-v1`, `--control-flow-profile mixed-return-inert-spin-v1`, `--owner-runtime-profile compiler-orphan-address-constants-O0-v1`, each with `--unit-toolchain agbcc-O1-v1` (4) | `refused: library unit toolchains are admitted on the ordinary Thumb path only, with the default WSL options` |
| the same four selectors without `--unit-toolchain` (4) | the default-run refusal above |

## Cause

Under `--unit-toolchain agbcc-O1-v1` the object carries the orphan `.rodata`, so
`library_units.exclude_orphan_constants` (`library_units.py:438`) first runs
`compiler_orphan_constants_prerequisite.verify` on it. That check accepts an `R_ARM_THM_CALL` only to a target named
`func_[0-9A-F]{8}` (`compiler_orphan_constants_prerequisite.py:216-218`). The two polls call through a function
pointer, which agbcc compiles to `bl _call_via_r1`; the ROM has those calls at 0x08141E80 and 0x08141E98, both to
0x08142248 (`bx r1`). The check therefore refuses before any byte comparison. The selectors that handle `_call_via_rN`
calls cannot be combined with a unit toolchain (`library_units.gate`, `library_units.py:326-330`), and without
`--unit-toolchain` the gate refuses the address because the default toolchain's object differs from the unit's
(`library_units.py:357-359`). With the call-name pattern widened, the rest of the unit path accepts the function
(above).

## Source notes

- The source follows pret's `WaitForFlashWrite_Common`, with the ROM names (`func_081419C0` for `StartFlashTimer`,
  `func_08141A68` for `StopFlashTimer`, `data_0200F364` for `PollFlashStatus`). `struct FlashType` is pret's layout;
  the ROM reads only the maker ID, at byte 0x14 (`ldrb r0, [r0, #0x14]` at 0x08141E60).
- The reset store is a plain `*(u8 *)0x0E005555 = 0xF0;`. pret writes it through `FLASH_WRITE`, a `vu8` store. Here a
  `*(volatile u8 *)` store compiles to the same 136 bytes, but `plausible.py --strict` refuses it (`ERROR: volatile`,
  exit 1): it admits a justified `volatile` only at I/O addresses 0x04000000-0x040003FF (`plausible.py:173-176`) and
  for RAM objects on the maintainer's allow list (`tools/volatile_allow.json`). The plain store is kept; the volatile
  spelling waits on the flash-command-window policy question in kit #214.

## Ruled out

- The previous revision of this entry (an -O2 reconstruction with the timeout value computed in a local) is not
  byte-identical at -O1: a 132-byte symbol, with 79 of the 136 bytes differing from 0x08141E43 on (this attempt's
  run). Its README described a near miss under the default -O2 toolchain; the unit row now fixes -O1.
- The default -O2 toolchain: 140 bytes, 97 bytes differ (above).
- No other spelling was needed; the source was byte-identical at -O1 as written.

kit issue: shubshub/fftadecomp-kit#214
