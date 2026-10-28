# 080F353C: callback reconstruction, two opcode bytes different

The recovered natural C is plausible but does not byte-match. The fixed
`agbcc -mthumb-interwork -O2` build has the correct complete 592-byte extent
`[0x080F353C, 0x080F378C)`: **590/592 same-offset bytes** and **237/239
reached instructions** are identical. All 48 literal bytes and six internal
zero-alignment bytes match; 536 of 538 code bytes match. No permanent
impossibility claim is made.

## Exact remaining difference

| Address | ROM | Compiled |
| --- | --- | --- |
| `0x080F367C` | `0143`: `orrs r1, r0` | `0843`: `orrs r0, r1` |
| `0x080F367E` | `1180`: `strh r1, [r2]` | `1080`: `strh r0, [r2]` |

The differing bytes are at offsets `0x140` and `0x142`; every other byte is
equal at the same offset. Both instruction pairs store the OR of the actual
`func_080035A8(2)` return value and the halfword global. The result register
is dead before the subsequent interpolation setup. This local equivalence
does not make the complete candidate a byte-exact match.

## Bounded natural alternatives

- The first candidate initialized the phase-zero local mode before copying
  the descriptor fields. Moving its initialization after those field copies
  reproduced the observed phase-zero instructions and register reuse.
- A `u32` mask local followed by the ordinary compound OR gives the retained
  592-byte candidate and the two differences above. Reversing the operands
  in an explicit OR assignment produced the same two differences.
- A direct compound OR with the function call produced a 588-byte symbol,
  shorter than the indexed span, and was rejected before a match report.
- Narrowing the local mask to `u16` emitted an explicit shift pair and a
  596-byte symbol. It did not fix the OR destination. That change was reverted.

Only the fixed canonical flags were used. No inline assembly, `volatile`,
pragmas, dead code, fabricated helper, data binding, source padding or
verification-profile escape was added. No further source changes were made
solely to select a register or instruction order.

## Recovered behavior and limits

The callback takes constructed task, descriptor and payload pointers, reads
the phase as a halfword, and returns a zero word. It preserves the observed
phase-zero byte narrowing; phase-one `func_080D38B4` call; constructor and
poll order; result replacement; and halfword phase updates. The D4B64 handle
is a word distinct from the constructed task pointers.

The six observed interpolation halfwords begin at payload+0x18; their view
does not establish the original object's declaration extent. Coordinate
arguments retain signed halfword narrowing, including y-16 and y-24 and the
fifth outgoing argument to D49FC. Unknown descriptor and payload members
remain unknown. No object size or allocator initialization is inferred.

Both actual 35A8 calls remain. Phase0x102 clears its returned mask after
D4D2C and before D3F08/D4774, allowing repeated clears while later slots
remain live. The skipped phase0x101 construction path leaves P28/P2C/P30
without local initialization; no new guards or zeroing repair that path.
DF790(P34) stays unguarded, its result is not stored, DE328 follows, and
phase0x104 later polls P34. P3C is retained without an invented poll.

Helper declarations are compatible local views grounded in the captured
call sites and bounded support. This does not establish their original
typedefs, recursive behavior, runtime validity, allocation success or object
lifetime. In particular, the uncaptured 1443FC callee inside 35A8 is not
assumed to be a proven copy, and no observed constant replaces the mask call.

## Verification pins

The final fresh canonical command ran while this exact C content was at
`src/080F353C.c`:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x080F353C
```

It exited 1 with `NOT MATCHING - bytes differ`, source `plausible`, complete
extent 592 bytes, and profile `elf-symbol-thumb-frame-data-v1`. The native
generated report is retained in private matching evidence; it is not a
current match claim for this parked path. The unmatched source and canonical
`docs/match/080F353C.md` were removed from their accepted-source locations.

- C file SHA-256: `c1b471fa9947884aa02d54921b3b6c83894e90ba9745eaa843b422d955874020`
- Recorded source/header fingerprint: `1ba9e19e909b0dfbd2caa096ae710a4ce136a6f84795c1e697130d7493227e08`
- Native report SHA-256: `d8532e4e2636e97f8ca6510cf691a2612e3c90832726cc49995cdd8744350784`
- Target complete body SHA-256: `3791c886fb21abc249907ca20282387a5c5440af5abbfe0dcda304e3b9671783`
- Compiled complete body SHA-256: `2d0c03fc2cd0f9922a2ddb647cc0f9c11da449dd74ac90f2df67bdfe18c90c85`
- ROM SHA-256: `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`

A separate same-offset comparison checked all 239 inventory instruction
ranges, all 12 literal words, the three two-byte internal zero alignments,
their disjoint complete byte ownership, and the target body freshly read
from the approved ROM. The native report also confirms the fixed frame,
ordinary direct-call ABI profile, linked mappings and absence of unresolved
relocations. The full-byte mismatch remains the only completion gap for
this bounded reconstruction attempt.
