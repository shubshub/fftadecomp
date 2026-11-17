# 0x08006720 - BLDALPHA interpolation event handler: bytes identical, refused (volatile semantic check stops at 32 decisions in the record search loop) (344 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function is the event handler of a blend-alpha
transition task, the keyframed sibling of the matched `0x0800664C` (`src/0800664C.c`). It switches on the event's
`u16` state (`ldrh` at 0x08006730). State 0 copies the event's record pointer (+4) and sign-extended count (+0x14)
into the payload (0x0800674C-0x08006758). State 1 and every other state do nothing. State 0x100 searches the 4-byte
records for the interval holding the payload's signed cursor (+0xA) (loop 0x08006766-0x080067A6). Each record's time
is a little-endian halfword read a byte at a time and sign-extended. On the last record the handler stores the
record's two bytes into BLDALPHA (0x080067B2-0x080067C6). Otherwise it interpolates both bytes linearly between the
two records with two signed divisions (`__divsi3`, 0x081426B8, `bl` at 0x08006816 and 0x08006830) and stores them
(0x08006824, 0x08006842). It then advances the cursor (0x08006844-0x0800684A). At the last record it either rewinds
the cursor when the payload's loop byte (+8) is set (0x08006856) or sets the event state to 2 (0x08006860-0x08006864).
It always returns 0. The outputs are `g_control_flags_03000940.bldalpha_lo` / `bldalpha_hi` (+0x4C / +0x4D of
0x03000940), and every store to them is preceded by a discarded load of the same byte (0x080067BA, 0x080067C4,
0x08006822, 0x08006840). That is the read-before-write pattern that `include/control_flags.h` declares as
`volatile`. The index row `08006720 08006878 344 164 return` is right: 164 reachable instructions, and the two
literal words at 0x080067CC and 0x0800685C (both 0x03000940) each follow a zero alignment halfword (0x080067CA,
0x0800685A). `g_control_flags_03000940` is already in `config/data_symbols.json`; no new data symbol is needed.

## Byte identity

`08006720.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08006720. `__divsi3` was bound to 0x081426B8 and
`g_control_flags_03000940` to 0x03000940 (2 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 344-byte symbol equals the ROM
span `[0x08006720, 0x08006878)`: SHA-256 `ef57997e8064759e162a95d674db181d793a6e610f334d9f427ef382394709a9` for both.
`.text` is exactly 344 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0. The volatile semantic check that blocks the selectors runs inside `match.py`, not in `plausible.py`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08006720.c`: the default run and all 213
selector values. None matched. A selector run that fails the volatile check prints `source    IMPLAUSIBLE`,
`verdict NOT VERIFIED - the selector was not run` and the finding quoted below.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values and the ten `--switch-data-profile` values (13) | `signed quotient excludes other runtime, literal, switch and thunk profiles` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` and the other 41 `--addressed-signed-runtime-profile` values, both `--signed-runtime-profile` values, `--unsigned-runtime-profile unsigned-divmod-ten-v1`, the three `--switch-profile` values and 141 of the 144 owner-runtime selectors (189) | not run; finding `allowlisted volatile semantic check: real compile of func_08006720: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1`, `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | not run; finding `allowlisted volatile semantic check: division runtime requires its canonical versioned proof` |
| the six `--function-address-profile` values | `signed quotient requires its canonical positive-constant profile` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `function address requires a canonical addressed function` |
| `--software-double-profile convert-sub-div-target-v1` | `software double requires at least one canonical binary64 runtime call` |
| `--software-double-remainder-profile target-state-v1` | `target-state remainder requires its explicit software-double profile` |

These rows cover all 214 runs.

## Cause

A source that uses an allowlisted volatile object (here `g_control_flags_03000940` from `include/control_flags.h`)
must pass the kit#90 semantic check once before any selector runs (`tools/match.py:5594-5601` at 18dcc516). If that
check fails, each selector run that goes through it prints `source    IMPLAUSIBLE` and `verdict NOT VERIFIED - the
selector was not run`. The
check compiles the source as written and again with `volatile` stripped from the pinned declaration. It then walks
both compiles path by path, and every branch condition whose outcome it cannot derive is one decision. A path may
hold at most `MAX_DECISIONS = 32` decisions (`tools/volatile_semantics.py:157`, raised at 1295-1298). The comment
above the bound (lines 150-154) says that a loop whose exit is unknown is refused at any bound. This function's
record search (0x08006766-0x080067A6) is such a loop: whether it continues depends on the record count and on the
timestamps read from the records, so a path that goes round it passes 32 decisions. The sibling
`src/0800664C.c` uses the same object without a loop and passes the check on 10 paths.

The default run and the quotient and switch-data selectors refuse on another ground: their signed-quotient binding
excludes literal data (`tools/match.py:1038-1041`), and this function loads `g_control_flags_03000940` from two
literal words.

As a diagnostic only, `match.py` was run in a Python process that replaced `allowlisted_volatile_semantics` with a
function returning no records. The kit files were not changed. In that run
`--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` printed `verdict MATCH - byte identical` for this
source. That is not a verification, because the replaced function is the check the selectors require. It only shows
that the semantic check is the one remaining obstacle under that selector.

## Source notes

- `record_time` is a `static inline` helper with the same body as `read_le16_0801075C` in `src/0801075C.c`, but it
  returns `u32` where that one returns `u16`. With a `u16` return the bytes differ (below). Every use casts the result
  to `s16`.
- `s32 start = (s16)record_time(current);` and `s32 end = (s16)record_time(next);` hold sign-extended times in full
  registers. `end` may equally be declared `s16 end = record_time(next);`: that form is also byte-identical, so the
  bytes do not pin the type of `end`. They do pin `start` (below).
- `first_delta` and `second_delta` are `s16`. The declaration order `start`, `elapsed`, `end`, `duration` is
  load-bearing (below).
- The output members come from `include/control_flags.h` (BLDALPHA's low and high bytes). The source does not repeat
  the declaration.
- The record, event and payload layouts follow the immediate offsets: record time bytes at +0/+1 and the two channel
  bytes at +2/+3; event state at +0, records at +4, count (`s16`) at +0x14; payload records at +0, count (`s32`) at +4,
  loop byte at +8, cursor (`s16`) at +0xA. The first parameter (`task`) is unused, as in `src/0800664C.c`.

## Ruled out

- `record_time` returning `u16`: 344 bytes, 8 differ, first at 0x08006770.
- `s16 start = record_time(current);`: 344 bytes, 8 differ, first at 0x080067DA.
- `s32 first_delta`: 344 bytes, 13 differ, first at 0x080067F6.
- `end` declared before `elapsed`: 344 bytes, 17 differ, first at 0x080067DE.
- The previously parked copy (no `control_flags.h`; the output bytes through a private non-volatile struct) is
  324 bytes. Against the 344-byte ROM span, 286 bytes differ or are missing, the first at 0x0800672A. Its frame is
  4 bytes instead of 8, and it has none of the discarded loads before the output stores.

kit issue: shubshub/fftadecomp-kit#137
