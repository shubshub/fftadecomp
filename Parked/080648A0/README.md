# 0x080648A0 — parked natural recovery

This is **not a byte match**. The retained natural C is plausible and has a closed leaf CFG, but its complete 116-byte function contains 49 instructions instead of the ROM's 50. The discrepancy is real, not a verifier limitation. No active source or match report remains for this address.

## Complete target and candidate

- Target: `[0x080648A0, 0x08064914)`, 116 bytes / 50 instructions.
- Target SHA256: `ef4c58f8ef11bb3bca1bbf9454b1dc4f855dd02e99870a7ef926fbfeca1d2892`.
- Target code: `[0x080648A0, 0x080648BC)` and `[0x080648C8, 0x08064910)`, totaling 100 bytes. There is no internal alignment gap or external alignment suffix.
- Literal words: `0x080648BC = 0x03000ED0`, `0x080648C0 = 0x0200F450`, `0x080648C4 = 0x020020D0`, and `0x08064910 = 0x020020D0`.
- Candidate: exactly one `STT_FUNC` and `.text` of 116 bytes, 49 instructions / 98 code bytes, the same four literal words, and an internal zero halfword at `[0x080648BA, 0x080648BC)`.
- Candidate SHA256: `8879eea59fac9d1453fa329a647bd222b8cb99a0cea883b0ea68ae88dde1a1d5`.
- Retained source SHA256: `9e96988d7b9c6ca7d8ac2407e63c242ec51461fd2d45146ec2590c984874cdb3`.

The frozen `kit-reviewed-4847c93` official matcher reports `NOT MATCHING - bytes differ`, with complete-symbol validation, no relocations, and a plausible source verdict. Its aligned display reports 109 / 116 bytes and 46 / 49 instructions; those are not positional equality counts. Direct comparison of the two complete 116-byte bodies gives **97 / 116 positional bytes equal**. All 88 bytes beginning at `0x080648BC` are identical.

The candidate loads the state-slot literal early into `r2`. The ROM loads it after the control-byte store into `r1`, then copies the pointer-slot address into `r2` after reading the mode byte. The candidate omits that copy, changes the preceding register operands and branch displacements, and fills the resulting two-byte space with internal alignment. No artificial copy or alignment manipulation was added to reproduce it.

## Bounded natural forms

All attempts used agbcc `-mthumb-interwork -O2` with the standard preprocessor and assembler. No flag sweep, assembly, volatile access, register binding, artificial control flow, forced storage, or padding was used.

1. Function-scope record and pointer-slot views: 110-byte function. The compiler hoisted the record pointer and retained one record literal. The official matcher stopped at the short-symbol rejection; no official byte-equality count was available for that form.
2. Branch-local record views with repeated literal pointer-slot expressions: 124-byte function. This represented the same ordered record stores but introduced another pointer-slot literal/load.
3. Branch-local record views and a reused pointer-slot view: the retained 116-byte / 49-instruction form. Its record views describe the object only where the conditional stores use it; the shared slot pointer describes the repeatedly read global slot. These are ordinary source organizations, not forced-register constructs. The remaining difference was preserved rather than forcing a match.

This is a local, bounded recovery result, not a claim that the function is inherently unmatchable.

## Behavior and compatible types

Compatible interface: `void func_080648A0(void)`. The ROM consumes no incoming arguments, calls no helpers, saves `r4` and LR (8 bytes), and has no local frame. The return uses the restored LR through `r0`; no meaningful scalar return is inferred.

Ordered operations:

1. Write byte 1 at `0x03000ED5`.
2. Read the state pointer at `0x0200F450`, then its byte `+0x52`. Store halfword `0x001C` at `0x020020DC` when the byte is zero, otherwise `0x001B`.
3. Reload the state slot, write byte `+0x4D = 0x0B`; reload it again, write byte `+0x51 = 0x5A`; reload it a third time for the append operations.
4. Write current `0x003F`, read and increment the count, then store `0x003F` at the entry indexed by the old count.
5. Write current `0x0037`, reload and increment the count, then store `0x0037` at the entry indexed by the old count.
6. Write current `0x0031` and return.

The source uses the existing canonical `ScriptState` and `Record` types through literal-backed local views, with no incompatible named-global redeclaration. A fresh target-compiler probe confirms `ScriptState` size `0x68`, alignment 4, and offsets current `0`, count `2`, entries `4`, byte `0x4D`, byte `0x51`, and byte-array member `0x52`. `Record` has size `0x10`, alignment 4, and halfword `field_0c` at `0x0C`.

The ordinary declared-array domain is a valid aligned `ScriptState` with initial count 0 through 32, allowing both appends within its 34 entries, plus valid control-byte and record storage. This is not a recovered allocation invariant, a bounds guard, or a claim that arbitrary overlapping objects have valid C lifetimes. Counts outside that range, malformed pointers, and overlap fixtures are separately qualified machine diagnostics. Entry evidence is the indexed prologue, closed CFG, return, pools, and following distinct prologue; no inbound reference was established by this bounded work.

## Bounded actual-ROM / fresh-candidate evidence

Reproducer: `/home/user/.codex-work/ffta-ulw/080648A0-author/check.py`.

It freshly compiles the retained source, verifies its sole full function and absent relocations, checks both raw CFGs and target layouts, then executes actual ROM and fresh candidate with a separately specified ordered-operation oracle. There are no helpers, stubs, or modeled call effects. All RAM fixtures are synthetic.

- 165 ordinary pairs cover every initial count 0 through 32 with mode bytes `0`, `1`, `0x7F`, `0x80`, and `0xFF`.
- 16 explicitly machine-only pairs cover counts 33, 34, `0xFFFE`, and `0xFFFF`, state/control/record overlaps, byte stores that mutate the pointer slot before a later reload, unaligned backing, and two invalid pointers.
- Total: 181 pairs / 362 executions, including four expected faulting executions. All 179 returning pairs satisfy the independent oracle.
- All 50 ROM and 49 candidate instructions are exercised. Ordered state/control/record data reads and writes, full non-stack RAM, and return behavior agree. Returning executions preserve `r4` through `r11` and SP; maximum stack use is 8 bytes.
- The separately recorded sequence of pool reads also agrees. **Their timing relative to data operations does not**: the candidate loads the state-slot literal before the control-byte store, while the ROM loads it afterward. No equality of combined instruction/literal/data traces is claimed. The ordered-data oracle excludes instruction fetches and stack traffic.
- Invalid pointers compare only the bounded fault prefix. Unaligned or overlapping raw-memory cases describe emulator machine behavior, not arbitrary valid ISO C aliases or a general GBA unaligned-access model.

Run from the game repository with `FFTA_ROM` unset, `PYTHONDONTWRITEBYTECODE=1`, `TMPDIR=/home/user/tmp`, and `/home/user/armtc/root/usr/bin` prepended to PATH:

```sh
python3 /home/user/.codex-work/ffta-ulw/080648A0-author/check.py
```

`match.log` retains the official full-symbol nonmatch; `check.log` retains the reproducible behavioral and layout results. Generated compiler and binary artifacts are removed after each build. No active `src/080648A0.c` or `docs/match/080648A0.md` remains, and no MATCH or replay claim is made for this recovery.
