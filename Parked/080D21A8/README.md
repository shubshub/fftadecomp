# 080D21A8 — natural recovery, not a byte match

The complete target is `[0x080D21A8, 0x080D2300)`: **344 bytes and 147
reachable Thumb instructions**. Its code occupies
`[0x080D21A8, 0x080D227C)`, `[0x080D2298, 0x080D22BA)`, and
`[0x080D22C0, 0x080D2300)`. Literal words occupy
`[0x080D227C, 0x080D2298)` and `[0x080D22BC, 0x080D22C0)`; the two bytes
at `0x080D22BA` are zero alignment. This accounts for 310 code bytes,
32 literal bytes, and two alignment bytes. The next actual prologue starts
at `0x080D2300`, immediately after the return.

## Grounded contract

The compatible interface is `u16 func_080D21A8(void)`. No incoming argument
registers or stack arguments are consumed. Every return value is
zero-extended from 16 bits; the nominal original typedef is not uniquely
recoverable. The target saves 28 bytes of registers, including `r8` and
`r9`, and has no allocated local frame.

The six ordered `func_080C9540` calls query `0x206`, `0x209`, `0x20C`,
`0x211`, `0x215`, and `0x21D`. The highest enabled flag determines how
many groups participate, from one through seven; all six queries execute
even when an earlier flag is set. Each group contains twenty halfword IDs
at `0x08528E1C`, with a 40-byte group stride. The IDs select 16-byte
descriptors at `0x08528F34`, whose observed flags are the halfword at
offset `0x2`. The declarations use unsized outer arrays and do not assert
an unobserved total descriptor allocation. Unknown descriptor bytes remain
byte arrays.

The first scan counts one base choice per group, then independently counts
descriptor flags `0x80` and `0x40` for each of its twenty IDs. The count
is therefore positive and at most 287. One `func_08002804(void)` call
follows. The source explicitly converts its result to `s16`, then uses
ordinary signed C remainder, `% count`. The actual RNG returns a value
from zero through 32767, so the narrowing is exact and the remainder is
nonnegative. The ordinary helper interfaces are `u8 func_080C9540(u16)`
and `u32 func_08002804(void)`; the generated remainder runtime consumes
two signed words and returns a signed remainder, not a quotient.

The second scan consumes choices in the same group/entry order. A group
base returns `group + 0xAB`; flag `0x80` returns the original ID; flag
`0x40` returns the ID plus `0x55`, converted to `u16`. Both flags can add
separate choices for the same descriptor. The ID addition fits a signed
32-bit intermediate, and the unsigned conversion handles wrap normally.
The structural fallback returns zero. Under the actual helper contracts
and stable valid tables, the selected ordinal always belongs to a counted
choice, so that fallback is not reached.

The function itself only reads data. The RNG updates its existing state
word at `0x030034B0`; the flag getter reads its existing state byte array.
The valid domain requires the seven potentially accessed ID groups and
every referenced descriptor to exist with the declared layout, and the
ordinary helper/global contracts to hold. This is not a claim about
arbitrary pointers, concurrent table mutation, or unique original source
provenance.

## Two separate limitations

One natural two-scan implementation was tried with standard agbcc
`-mthumb-interwork -O2`. Its unknown leading descriptor bytes were later
spelled as a byte array instead of an unobserved halfword; this did not
change the emitted code.

The frozen `kit-reviewed-2e2a664` official matcher rejects the compiler's
ordinary `__modsi3` relocation:

```text
compile failed:
call target must be an undefined addressed function
```

That is an unsupported signed-remainder proof profile, not evidence that
the source failed to compile. The source retains `%`; it does not call a
named runtime function to bypass this restriction.

A separate scratch-only typed diagnostic binds that runtime name to the
actual Thumb entry `0x08142950`, links the two known helper functions and
the two grounded data symbols, and checks the complete resulting body.
It emits exactly one **376-byte `STT_FUNC`**, a 376-byte `.text`, and
**160 instructions**: 336 code bytes, nine literal words (36 bytes),
and four zero alignment bytes. There are no unresolved relocations or
linker veneers. The candidate ends at `0x080D2320`, 32 bytes beyond the
target boundary; it cannot replace the target symbol.

The candidate saves 32 bytes, including `r8`, `r9`, and `r10`, rather
than the target's 28 bytes. Neither body allocates a local frame. Register
allocation, loop setup, instruction scheduling, and pool placement differ;
the candidate also has an extra ID-table literal. These are 26 extra code
bytes, four extra literal bytes, and two extra alignment bytes. Only 18
of the 344 overlapping byte positions agree. This positional diagnostic
is not an official match percentage.

Target SHA-256:
`15bdcf4a445fe98764c51003b35e692975d9a936f67876cc12ba20f2a4a6a0ca`.
Diagnostic candidate SHA-256:
`64524b7f460ca2db7f1cfec68fe4677fa3022ee4c048e96215bdb924bcf980e1`.

The frozen local CFG verifier accepts both byte bodies when supplied their
exact ordinary direct-call summaries, and source plausibility has zero
findings. This does not supply the missing versioned runtime proof or
make the complete bytes equal. No verifier extension is warranted merely
to promote this size-different candidate. No assembly, volatile accesses,
forced registers/storage, artificial control flow, or repeated-load tricks
were added to reproduce the target layout. There is no active source or
normal MATCH report.

## Bounded behavioral evidence

The retained diagnostic is
`/home/user/.codex-work/ffta-ulw/080D21A8/check_recovery.py`, accompanied by
its scratch-only `known.s` and `diagnostic.ld`. Run from the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080D21A8/check_recovery.py Parked/080D21A8/080D21A8.c
```

It freshly compiles and links the source, then runs **104 paired cases
(208 executions)** using the actual ROM target, the compiled candidate,
and the actual complete flag getter, RNG, and signed-remainder routines.
There are no helper stubs or modeled callee side effects. An independent
choice-list model checks each returned value and the remainder arguments.

Twenty-four cases use pristine ROM ID/descriptor values with synthetic
flag and RNG state. Eighty cases use explicitly synthetic table fixtures:
one or seven groups, absent/either/both descriptor flags, irrelevant upper
flag bits, IDs `0`, `1`, `0xFFAA`, `0xFFAB`, and `0xFFFF`, and selected
ordinals at early, middle, and last choices. Seeds are chosen so the real
RNG produces those ordinals; the actual RNG instructions still execute.
These fixtures test descriptor addressing and defined `u16` result wrap,
not the allocation size of the original ROM table.

All cases agree on the returned value, exact ordered helper calls and
consumed arguments, RNG state transition, unchanged other data, saved
`r4` through `r11`, SP, and return destination. The only nonstack write
is the actual RNG state update. The target executes 146 of 147 caller
instructions and the candidate 159 of 160; each unexecuted instruction is
its structural fallback-zero assignment. No full instruction-coverage
claim is made.

There are zero differences in measured ordered state/table read traces:
24,078 reads per body across the cases. The measured region includes
EWRAM flag state, the IWRAM RNG word, ID-table reads, and referenced
descriptor flag halfwords. It excludes instruction and ROM literal-pool
fetches, whose locations differ. Both compiled bodies happen to preserve
the descriptor reread before the second selection flag in these fixtures;
the source does not enforce volatile-style read semantics. Maximum stack
depth including real helpers is 36 bytes for the target and 40 for the
candidate. Each run permits only its bounded stack writes plus the RNG
state write, and checks final SP and preserved registers.

These bounded cases support the natural recovery but do not establish
arbitrary-storage validity or a byte match. The reproducer removes its
generated builds and binaries. The source remains parked.
