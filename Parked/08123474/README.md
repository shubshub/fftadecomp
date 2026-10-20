# 0x08123474 — packed-coordinate script command

This is a plausible, behaviorally recovered candidate, **not a byte-exact
match**. It remains parked for another hand-matching pass; the attempts do not
establish that the function is inherently unmatchable.

## Recovered behavior and extent

The command reads two packed coordinates from script bytes 1 and 2. Each low
nibble is an x coordinate and each high nibble is a y coordinate. When the
packed endpoints differ and share an x or y coordinate, it calls
`func_08124974(start_x, start_y, end_x, end_y, script[3])`. It returns `0x110`
on every path. The callee's entry narrows all five arguments to unsigned bytes.

The ROM function occupies `0x08123474` through `0x081234B3`, with exclusive
end `0x081234B4`: **64 bytes, 31 Thumb instructions**, no literal pool. Its
entry is also referenced by the dispatch pointer at `0x083A8060`. The
provisional function index originally stopped at `0x08123486` after only
18 bytes and 9 instructions; that early conditional branch is not the end
of the function. Function-index maintenance is owned by the coordinating
session.

## Fresh verification

Before parking, the candidate was checked in `src/08123474.c` using:

```sh
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
python3 ../fftadecomp-kit/tools/match.py --root . 0x08123474
```

The compiler was agbcc with `-mthumb-interwork -O2`. Compilation, direct-call
linking, fixed-stack-frame validation, and source plausibility passed.
The verdict was **NOT MATCHING - bytes differ**, exit 1.

The candidate is **60 bytes, 29 instructions**. The verifier compared that
complete candidate against the first 60 bytes of the ROM function and
reported 45/60 bytes and 15/28 aligned instructions. Those diagnostics are
not full-function match percentages: the real ROM function has four more
bytes, including its final `pop {r1}; bx r1`.

## Exact remaining difference

- The ROM saves and restores `r6` in addition to `r4` and `r5`; the candidate
  does not need `r6`.
- After loading both packed endpoints, the ROM computes
  `lsls r2, r1, #24` and `lsls r6, r4, #24` before comparing the endpoints.
  The candidate omits these two instructions.
- The ROM then extracts high nibbles with `lsrs r1, r2, #28` and
  `lsrs r4, r6, #28`. The candidate instead uses the equivalent
  `lsrs r1, r1, #4` and `lsrs r4, r4, #4`.
- For each low-nibble mask, the ROM copies the mask into the destination
  register and ANDs with the packed byte; the candidate copies the packed
  byte and ANDs with the mask.
- The missing four instruction bytes shift the conditional targets,
  direct-call encoding, and epilogue addresses. The call still resolves
  to `0x08124974`; the logical tests, arguments, stack argument store, and
  return value agree.

## Attempts completed

Natural nested-condition and early-return forms were tried with byte, word,
and signed endpoint/coordinate types; explicit upper-nibble masks; byte
casts; mutable coordinate locals; direct script-byte expressions; and both
byte and word callee declarations. Byte and word packed-coordinate union
forms were also checked. The neighboring matched command at `0x081234B4`
supports the explicit high-nibble extraction and five-byte-argument
interpretation, but its source shape did not resolve this caller's codegen.

A bounded diagnostic pass covered 96 combinations of endpoint type
(`u8`, `u16`, `u32`, `s32`), low/high coordinate type (`u8`, `u32`), callee
argument type (`u8`, `u32`), and three natural control-flow/byte-conversion
forms. None reproduced the target. Separate byte copies of word endpoints
can produce the ROM's early `lsl #24` and later `lsr #28`, but the resulting
register lifetimes and moves still differ. The simpler natural candidate
was retained instead of those extra copies.

No inline assembly, optimization pragmas, volatile accesses, dead code,
manual shift-sequence transcription, or compiler-steering constructs were
introduced. No alternative compiler flags were swept.
