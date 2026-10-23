# 08009FF8 — conditional clear of flag 0x21F

**Parked: plausible first natural source, not byte-identical.** The source
was frozen before compilation and never changed in response to compiler
output. Only agbcc `-mthumb-interwork -O2` was tested.

The function queries flag `0x21F` using `u8 func_080C9540(u16)`. When the
result is nonzero, it clears that flag with
`void func_080C9574(u16, u16)` and a zero second argument. Both declarations
agree with existing matched helper sources. The consumed state byte is
`0x02001FB3`, mask `0x80`. No C argument or result is consumed by this caller.

The complete original function owns `[0x08009FF8,0x0800A018)`: 26 code bytes
containing 11 instructions, two zero alignment bytes, and one four-byte
literal `0x0000021F` at `0x0800A014`, reached by both loads. The old index
ended at `0x0800A012` and counted 13 instructions; it omitted the pool.
The next function starts at `0x0800A018` and is excluded. The proposed
metadata correction changes only this row in the two indexes.

The first source produces a complete **36-byte/13-instruction** symbol.
It preserves the flag ID in `r4`, saves/restores `r4`, and copies it to `r0`
before each call. The ROM reloads the literal into `r0` and saves only `lr`.
There are **27 positional differences in the 32-byte overlap**, five equal
bytes, and four additional candidate bytes. The official diagnostic's
`25/36` is sequence-aligned similarity, not positional equality. Its 36-byte
ROM comparison includes four bytes of the following function because the
candidate is longer; that does not enlarge the recovered ROM ownership.

Fresh official verification exits 1 with `NOT MATCHING - bytes differ` and
plausible source. The old and corrected index extents both reject it. This
is a genuine compiler-output mismatch; no verifier workaround, helper alias,
source-spelling search, flag search, assembly, or steering change was used.

Author evidence executes both caller images with the complete actual helper
bodies for all 256 possible target-byte values and both ARM/Thumb returns:
1,024 executions. It checks helper arguments/order, ordered data reads and
writes, all EWRAM/IWRAM bytes including guards, initialized stack reads,
callee-saved registers, and SP restoration. Twelve deliberately incorrect
images fail those checks. Four target width assertions and two compatible
function-pointer assignments compile; two conflicting helper declarations
are rejected. Both existing helper sources independently compile to their
ROM bytes. These are finite sequential tests requiring valid byte-addressable
state and stack backing, not universal C lifetime/aliasing or concurrency
proofs. The setter's nonzero-enabled path is unreachable from this caller.

To reproduce the mismatch, copy this C file into `src/08009FF8.c` in an owned
fixture containing the project's headers and indexes and a symlink to the
approved ROM, then run the toolkit's `tools/match.py --root <fixture>
0x08009FF8` with the fixed compiler flags. The author-only `audit.py`,
`runtime.py`, `CONTRACT.md`, logs, and manifests are retained in the local
frozen evidence bundle; they are not files shipped beside this Parked source.
