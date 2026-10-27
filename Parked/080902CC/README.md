# 080902CC: bounded natural C recovery, no match credit

The complete indexed ROM owner is `[0x080902CC, 0x08090A80)`, 1972 bytes and
847 reachable instructions. The final recovered C emits one original ELF
`func_080902CC` symbol of 1920 bytes, ending at `0x08090A4C` when linked at
the target entry. Its generated assembly contains 823 instruction statements;
this is a diagnostic assembly count, not a native-verified reachable count.
The candidate remains 52 bytes short and is not byte-identical.

The final unmodified native command exited **1**:

```text
function  0x080902CC   1972 bytes (Thumb)
source    src/080902CC.c
compiler  $HOME/agbcc/gcc/agbcc -mthumb-interwork -O2
compile failed:
software double requires exact unique nonoverlapping Thumb spans/counts
```

The diagnostic traceback identifies `software_double_profile.validate_span`
calling `span_record` with the compiled caller's extent. All pinned runtime
identity rows pass; this is a compiled caller mismatch, not a missing runtime
mapping. The gate rejects before source plausibility and complete byte-report
issuance. No native plausibility verdict or successful fresh-source replay is
claimed. The original ELF and strictly linked diagnostic bytes are retained in
the address scratch directory as `final.o`, `final.elf`, `final.s`, and
`final-linked.bin`. Linking captures 22 named data relocations and 10 guarded
switch-word relocations, with genuine canonical compiler DIV/MOD/binary64 calls.
No runtime aliases or literal substitutions were used.

The retained recovery covers the nine-state transition, both sprite entrance
paths, signed-distance quotient steps, random signed16 jitter, paired effects,
blend transitions, binary64-to-fixed-point motion initialization, motion update,
and the fourteen-sprite renderer. It preserves the ROM's first-sprite-only
vertical clamp in the render loop. Layouts use the observed 16-byte sprite,
12-byte destination record, and 24-byte motion record strides. Four signed RAM
objects provide the left count, total count, and horizontal/vertical origins.

The unresolved type/code-generation gap is concrete: the nine retained byte
load signatures at `08090590`, `08090598`, `080905A2`, `080905AA`, `08090648`,
`080908EA`, `080908F2`, `0809096C`, and `08090974` do not emerge from the tested
natural full-width register bitfields. Aligned u8/u16 fields, packed paired
u16 fields, and unsigned-word bitfields all compile byte writes without those
reads. The final source keeps the ordinary u16 register-pair bitfield view;
it does not pretend that this explains the retained reads. Other differences
include the context register allocation (r8 rather than ROM r7), address/load
scheduling, and literal pool placement. No volatile accesses, artificial reads,
assembly, flags, forced inlining, dead expressions, or padding were introduced.
This bounded result is not a proof that a genuine source representation cannot
match; it records the unclosed type inference and the exact native rejection.

Natural candidates emitted 1928 bytes initially, 1904 bytes after promoting
signed jitter locals, and 1920 bytes with the explicit inner effect-stage
switch. The last is preserved as the clearest complete recovery. The strict
same-offset diagnostic is 238 equal bytes out of 1920 compared offsets against
the 1972-byte target; it is neither a complete-match score nor aligned-LCS
similarity. `final-extent.json` records these quantities separately.

The native command was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/.codex-work/ffta-ulw PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v644-matching/matching-root --software-double-profile convert-sub-div-target-v1 0x080902CC
```

No active unmatched source or native match report remains. Shared maps, headers,
other sources, toolkit files, reservations, and Git were left untouched.
