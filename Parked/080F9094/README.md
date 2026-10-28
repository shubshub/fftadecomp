# 080F9094 — plausible C, eight bytes short

The retained `080F9094.c` reconstructs the complete callback's observed
effects, but does not byte-match. It belongs in `Parked`, not `src`.
The approved target is `[0x080F9094, 0x080F9166)`: 210 bytes,
95 reached Thumb instructions, 202 code bytes and eight literal bytes.
The natural candidate compiles to 202 bytes and 91 reached instructions,
with eight literal bytes. Its ordinary typed direct-call verification passes.
The canonical matcher rejects its shorter ELF symbol before issuing a match
report or running the source plausibility gate.

## Remaining difference

The ROM retains a mask in `r7` across `080DCFE4`. Before that call it emits
`movs r7, #1; adds r0, r7, #0`; the candidate emits `movs r0, #1`.
After storing the call result at payload+0x18, the ROM's instructions at
`080F912C`, `080F912E`, and `080F9130` reload the selector byte, copy the
retained mask, and AND them. The following descriptor phase load overwrites
that result without using it. The candidate has no source-level effect
requiring this discarded calculation and does not emit those three
instructions.

Together these differences account for four instructions/eight bytes.
The candidate consequently saves/restores only `r4-r6` instead of `r4-r7`,
places its literal pool at `080F9130/080F9134` instead of
`080F9138/080F913C`, and moves phase-0x101/return code eight bytes earlier.
Branch and PC-relative literal displacements change accordingly. Both bodies
retain the same fixed 16-byte outgoing argument frame. No inert expression,
dead conditional, volatile access, assembly, or pragma was added to force the
discarded ROM calculation.

## Bounded alternatives tried

Only the fixed `-mthumb-interwork -O2` configuration was used.

1. A phase switch with a local `u16 flags = selector & 1 ? 4 : 2`, followed
   by `080DCFE4(..., flags | 8, task, 0)`: the retained 202-byte candidate.
2. A natural `if/else` with separate `080DCFE4` calls using `4 | 8` and
   `2 | 8`: 214 bytes and substantially different allocation/control flow.
   The matcher reports plausible source and `NOT MATCHING`. Its comparison
   extends four bytes beyond the approved body, so those bytes receive no
   callback credit. This alternative also does not emit the discarded
   post-call selector computation.

No cosmetic permutation search or alternate flags were attempted.

## Preserved semantic limits

Entry is conditional on the approved constructor witness:
`r0=task`, `r1=copied descriptor`, `r2=32-byte payload`. Initial construction
forces descriptor phase 0; a separate later parent phase 0x104 remains an
explicit premise rather than a scheduler guarantee.

Phase 0 copies descriptor+0x14's low byte and descriptor+4, passes signed
coordinate storage at payload+2/+4 to `080DD748`, and retains its result at
payload+0x0C without polling it. Phase 0x100 tests only `080DD580`'s low
byte; a nonzero result creates payload+0x14 with `080D6098` arguments
`(x, y, 0, 1, 1, &payload+0x10, 0x0839C410, task)`. Either route creates
payload+0x18 with `080DCFE4(object, 0x0839C428, 12, 0,
(selector & 1 ? 4 : 2) | 8, task, 0)` and freshly reloads/increments phase.
The literal values establish no data object type or extent.

Phase 0x101 unconditionally polls/replaces payload+0x14 first, then polls
payload+0x18 only when the first result is zero; two zero results set phase 2.
Phase 1 is a no-op. Phase 0 and the phase-0x100 skip path leave
payload+0x14 untouched; no allocator-zeroing or safety repair is assumed.
Storage validity, disjointness, helper returns and coordinate output/lifetime
remain conditional as in the sealed semantic inventory.

## Reproduction and evidence

From the game root, while the candidate is installed as `src/080F9094.c`:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x080F9094
```

The retained source's raw SHA-256 is
`14a0cac72c54d479d683f2bb3e608a773889ea4f555f51eabb86e09e43abfc3e`.
The compiled complete-body SHA-256 is
`38e4435508af9d977a087437e931f0e00f83db9d473980a9698f59db02e48123`;
the approved ROM body's is
`91f2c385222c9e769b10d400ff5d927bb909ea0714d565e4bbb87f810eed596e`.

Session evidence is retained under
`/home/user/.codex-work/ffta-ulw/audio-following-v19-matching/080F9094`:
`attempt-01.log`, `attempt-02.log`, `candidate-comparison.md` (complete
candidate disassembly and exact instruction diff), `alternatives.diff`,
`command-log.md`, and `park-manifest.json`. No unmatched canonical source
or match report remains. The coordinator owns lease release as unmatchable.
