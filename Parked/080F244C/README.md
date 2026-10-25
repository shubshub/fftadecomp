# 080F244C: bounded unmatched reconstruction

The complete target is `[0x080F244C, 0x080F2572)`: 294 bytes, with 117
reached instructions, 258 code bytes and 36 referenced literal bytes. The
following two alignment bytes are outside this body. No endpoint was changed.

The parked C preserves the three-pointer callback and fullword zero return,
the 32-byte payload layout, phase-zero input/coordinate stores, every real
call and returned mask, phase-100 call/store order, byte counter increment
before polling, and phase-101 polling/clearing order. Unknown fields are not
initialized, and no array-helper substitution or extra null guard is used.
Resource addresses remain opaque observed pointers.

## Final parked source: actual result

The final source uses the direct `payload->counter = 0` reset. It compiled
without diagnostics and passed the matcher's plausibility and complete ordinary
direct-call/frame/data checks, but **did not byte-match**. The complete compiled
symbol is 294 bytes. The matcher's aligned summary is **74/113 instructions
identical (250/294 bytes)**; direct comparison at fixed byte offsets is
**209/294 equal bytes**, with 85 differences. These are different metrics.

The target saves r4-r7, keeps task/descriptor/payload in r7/r6/r5, and holds a
zero in r4 from 080F24B4 through the counter store at 080F24F0. The final source
saves r4-r6, keeps those pointers in r6/r5/r4, and materializes zero in r0 just
before the counter store. This changes register operands, several literal-load
offsets and relocated call encodings; call targets and semantic order remain
the observed ones.

The exact command was run from the game root while these same source bytes
were at `src/080F244C.c`:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x080F244C
```

The fixed compiler flags were **`-mthumb-interwork -O2`**, with the ordinary
control-flow profile and verification schema `elf-symbol-thumb-frame-data-v1`.
No optimization or profile alternatives were used.

| Identity | SHA-256 |
| --- | --- |
| Final parked source bytes | `6716d7b7308a6147d78c1721eba127a26b8dc19430751fa60c4b937d2baa3529` |
| Source fingerprint in the final pre-parking report | `83b490db4889cc54041de8a96cc57e678980e974f5604f36ada19a12c6a83b90` |
| Final compiled complete body | `481740045039c3b5c4cb1831698709f0c27f4148508e33770c525b087d3d419f` |
| ROM complete body | `48ff58d9a4c666cf9faf904cc202f27bdb8c1bf51cbd0d8b04c2d9c41e2228bd` |

The pre-parking source fingerprint includes the original source path; it is
historical evidence, not a claim that the parked path has the same fingerprint.
The final unmatched generated report was removed with the unmatched source.

## Natural forms tried and the closer result

- Direct global `|=` uses r0 as the OR/store result. Reading a u16 flags
  temporary and then applying `flags |= mask` recovers the target's r1 OR/store
  operands, and is retained in the parked source.
- Declaring 080035A8's return as u16 rather than u32 did not resolve register
  allocation. The final declaration retains the wider compatible observed ABI.
- A scoped u8 reset temporary initialized at the beginning of phase 100
  recovered r4-r7 allocation but placed `MOVS r4,#0` at phase entry.
- Initializing that temporary after the completed flag update instead placed
  the MOVS just after the global STRH. It still did not match.
- Grouping mask, flags and zero counter initializers before the child setup
  placed the MOVS immediately before ORRS. This was the closest in-place OR
  form: **116/117 aligned instructions, 292/294 aligned bytes**, and
  **290/294 equal bytes at fixed offsets**. At 080F24B2..080F24B5, compiled
  `0024 0143` is the target's `0143 0024` in reverse order. Every other byte
  matches. This result belongs to the temporary-variable variant, not the
  final parked source.
- Initializing flags directly with `global | mask` placed the MOVS correctly,
  but selected r0 rather than r1 for ORRS and STRH. Reversing the expression's
  operands produced the same output. This variant also did not match.

Placing the reset temporary's zero initialization specifically between
`flags |= mask` and the global flag store would merely force the two remaining
instructions into the ROM order. There is no recovered semantic reason for
interleaving an unrelated counter initialization there. That proposed rewrite
was not used because it would be compiler steering.

This is a bounded unsuccessful attempt, not a claim that the function is
permanently unmatchable. A future natural reconstruction can be retried with
new evidence. No asm, volatile, pragmas, dead code, changed flags, invented
data binding or unsupported profile was introduced.
