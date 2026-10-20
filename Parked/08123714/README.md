# 0x08123714 — selected-byte-lane script command

This candidate is plausible and behaviorally recovered, but **not
byte-identical**. It is parked for a later hand-matching pass; no inherent
unmatchability is claimed.

## Behavior and complete extent

The command reads a byte value from script offset 1, a little-endian halfword
from offsets 2 and 3, and flags from offset 4. For each of the four low flag
bits, it inserts the value into the corresponding byte lane of a word. If
flag bit 0 is set and the assembled word is nonzero, it obtains a byte from
`func_08121D9C()` and passes it to `func_08141728()`. It then dispatches the
context, assembled word, decoded halfword, and flags to `func_0812800C()`,
and returns `0x115`. The name `duration` for the decoded halfword is
provisional; its exact game-level meaning has not been established.

The full extent is **[0x08123714, 0x08123770): 92 bytes and 41 reachable
Thumb instructions**. A trailing literal at `0x0812376C` contains `0x115`.
The dispatch word at `0x083A80B4` contains the Thumb entry `0x08123715`.
The old 32-byte index stopped at a conditional branch inside the loop.

The coordinating session corrected that mapping and added the missing
callee at **[0x08121D9C, 0x08121DA8)**: four instructions followed by a
pointer literal, 12 bytes total. Its body loads a pointer, reads the byte
at offset `0xF`, and returns.

## Fresh verification

The checked-in candidate was verified while temporarily installed as
`src/08123714.c`, using reviewed toolkit commit `35278f3` during concurrent
toolkit development. The equivalent command from the decomp checkout is:

```sh
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
python3 ../fftadecomp-kit/tools/match.py \
  --root . 0x08123714
```

Compiler: agbcc, `-mthumb-interwork -O2`. Complete-symbol extraction,
closed-loop CFG validation, direct-call linking, and source plausibility
passed. The required proof profile is `elf-symbol-thumb-calls-v1`; there
is no stack frame or external-data relocation.

The verdict was **NOT MATCHING - bytes differ**, exit 1. The candidate is
also 92 bytes, but contains 40 instructions, two alignment bytes, and the
same four-byte trailing literal. The verifier's alignment diagnostics
reported **87/92 bytes and 36/39 instructions**; those are its aligned
comparison statistics, not the ROM's true 41-instruction count.

## Exact remaining difference

Every instruction through the call at `0x08123752` matches.

At `0x08123756`, the ROM zero-extends the decoded halfword with:

```text
lsls r2, r5, #16
lsrs r2, r2, #16
```

The candidate emits only:

```text
adds r2, r5, #0
```

The decoded value is already confined to 16 bits, so the scalar candidate
does not retain the redundant extension. This single instruction-count
difference moves the final call and epilogue two bytes earlier, changes
the call displacement and literal-load offset, and introduces two
alignment bytes before the literal. The full symbol still ends at
`0x08123770`.

## Attempts

The natural scalar forms tried included `u16`, `u32`, and `s16` decoded
locals, narrow and wide callee parameter declarations, explicit halfword
casts and masks, and a two-stage byte/OR assignment. These forms either
removed the extension or also changed register allocation. The loop's
index and byte shift belong together in the `for` update expression;
placing the byte shift in the body reverses the ROM's update order.

A byte-overlay union produced the final extension, but also introduced
unwanted field-preservation masks and literals while assembling the
halfword. It was discarded in favor of the simpler scalar candidate.
No forced shift sequence, inline assembly, volatile access, dead code,
optimization pragma, compiler flag sweep, or artificial helper was used.
