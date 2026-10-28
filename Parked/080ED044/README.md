# 080ED044 — plausible, not byte-identical

The owned target is the complete `[0x080ED044,0x080ED308)` body: 708 bytes,
338 reached instructions, 16 literal bytes and two alignment bytes. The
ordinary callback is compatible with `u32(task, descriptor, payload)` and
ignores the incoming task pointer. This candidate preserves the observed
three phases and fifteen-slot event/motion update; it is not a verified match
and is deliberately absent from `src/`.

## Final verification

The final source's raw SHA256 is
`982a6ded0708b99b445580aed8106a39b9edfaa64150d8917a565c3d0c9132ba`.
With this candidate temporarily at `src/080ED044.c`, the canonical command was:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' \
python ../fftadecomp-kit/tools/match.py --root . 0x080ED044
```

It exited 1: **NOT MATCHING — bytes differ**. The complete ELF symbol is
708 bytes, accepted under `elf-symbol-thumb-frame-data-v1`, with source
plausibility reported as `plausible`. All direct calls and the event-table
data relocations bind under the ordinary supported linker/profile.

The matcher's byte LCS score is 596/708, which is not a same-offset match
count. An independent call to the same ordinary compiler/linker/verifier
primitives found 337 reached compiled instructions versus all 338 target
instructions, with 512/708 bytes equal at their actual offsets. The compiled
708-byte function SHA256 is
`f8c6cbc85e2265a4a2771de1e00378dc34d7a432c0bee8fb8b7084b0c5e7f463`.
No target extent, compiler option or verification rule was changed.

## Exact remaining differences

- The loop's temporary index and table-base registers differ near target
  `080ED088..080ED0A4`, including an extra move before forming twice the index.
- Both waveform bodies retain the amplitude comparison against 0x100, but
  use r1 for the running sample where the target uses r0. Their final
  amplitude-8 arms move the logical shift before the comparison and use a
  conditional branch around the default zero. The target compares first,
  conditionally skips the shift, and branches past the default zero.
- Those differences alter branch encodings and the second literal-pool
  alignment. The compiled second waveform call is at `080ED1DA`, versus
  target `080ED1DC`.
- The final signed-ordinate arithmetic, unsigned ordinate limit check and
  offset subtraction have different temporary-register/conversion ordering.
  The three final object calls have recovered their target addresses
  `080ED2B6`, `080ED2C4`, and `080ED2D2`, but facing calculation and object
  load order still differ before the middle call.

## Alternatives tried

All attempts used fixed agbcc `-mthumb-interwork -O2`.

- A direct byte-field amplitude expression lets the compiler remove the
  comparison against 0x100. Loading it into a wider ordinary local retains
  that observed comparison. No artificial guard was added.
- A narrow waveform accumulator generates zero-extension and combined
  shifts different from the target. A wide unsigned sample initialized from
  signed16 retains the observed signed initial conversion and logical
  single-term shifts. Signed16 casts in the compound terms retain the
  target's arithmetic shifts.
- In-place versus separate input/result accumulators, signed versus
  unsigned result widths, statement versus conditional-expression scaling,
  and separate lexical scopes were tried. Plausible forms still differ in
  the final amplitude-8 arms, allocation and/or narrowing placement.
- Keeping a per-event pointer live across the entire update suppresses the
  target's repeated table-address calculations and changes the saved-register
  allocation. Indexing through an event-table base pointer reproduces those
  address calculations. Using the global array directly also changes the
  generated allocation and pool placement.
- Explicit signed coordinate temporaries and low16 normalization recover
  more of the target arithmetic. The final candidate has the correct complete
  byte extent but remains unmatched; no size-only success is claimed.

No helper functions, inline assembly, volatile accesses, pragmas, extra
initialization, allocation guards, phase advancement, or alternative compiler
flags were introduced. In particular, event-creation failure still leaves the
motion initialization observable, and the counter increments once after all
fifteen slots.

## Evidence and data binding

Private session evidence is under
`/home/user/.codex-work/ffta-ulw/audio-following-v8-matching/080ED044/`:
`final-match.log`, `failed-match.md`, `diagnostic.json`, `compiled.dis`,
`diagnostic.diff`, and `attempts.tsv`. The failed generated report was removed
from `docs/match/`; it is not a success report.

The coordinator added the evidence-backed mapping
`g_events_083992F8 -> 0x083992F8`. Its declaration here is an unsized extern
array. The observed fifteen records do not establish its original declared
extent. The resource pointer `0x084F71D8` is supported by the target literal.

The complete body and dependency evidence are in the sealed bundle
`/home/user/.codex-work/ffta-ulw/audio-following-region-inventory-v8-completion/`;
its manifest hash is
`74b2d728123d6d401b6198006a6a0c86063ba1097e602f3cb20bf7022a352ac3`.
The coordinator owns reservation release and any future publication.
