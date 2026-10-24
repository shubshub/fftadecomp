# 080E28C4 — preserved first candidate, NONMATCH

This is the sole natural candidate, unchanged after one canonical compile with
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. It receives **zero match credit**.
The canonical main return, SystemExit and process status were all 1. Source
plausibility passed. There were no source/type/flag retries or native tests.

Qualified ROM ownership is [080E28C4,080E29C4), **256 bytes / 122 instructions**:
252 code bytes and the four-byte literal at E2914. The compiled ELF function
owns **260 bytes / 121 instructions**: 250 code bytes, eight literal bytes and
two zero alignment bytes. Both original and linked .text are exactly 260 bytes;
no external section filler is counted. Four typed direct calls link to D7A70,
D7ABC, 11058 and 11484 in the observed order, with no residual relocations.

Only **55/256 bytes** and **18/122 complete instructions** match at the same
owned positions. Thus 201 owned byte positions differ, and the compiler symbol
has four excess bytes. The canonical report's **190/260 bytes** and **66/119
instructions** are alignment diagnostics, not positional equality or ownership.
Its compiler-sized ROM window includes `f0 b5 57 46` at E29C4..E29C8, belonging
to the next function; those bytes receive no ownership or match credit.

Observed differences include phase-dispatch shape, register allocation and phase
update placement. The compiler adds a 0x101 literal at E28F0 and places the
record-address literal at E291C instead of E2914. The source still expresses
the observed callback state machine, two eight-slot loops, inter-call slot reload,
byte completion count, and wrapped-halfword subtraction followed by signed clamp.
No attempt was made to force the ROM's register allocation or switch spelling.
This does not establish that the function is impossible to recover naturally.

The compatible public ABI is u32(void *, void *, void *), supported by the
actual ID 0x15B table registration with 0x38 payload bytes and scheduler
dispatcher. Original nominal types are not uniquely proven. The descriptor is
a partial phase view, and unused payload bytes remain unknown. No allocation,
initialization, object lifetime or recursive callee-equivalence proof is claimed.

Source SHA256:
`626a01878fbb8db249cf42e4216b7f9d7338ffb80652731135c574a6e2acbb36`.
This file is byte-identical to the precompile frozen source, including its
required target-byte comment. No postcompile source adaptation was made.

Durable evidence bundle:
`/home/user/.codex-work/ffta-ulw/080E28C4-author-next`.
It contains the independent READY pins, precompile ABI decisions, preserved
original inputs, freeze/start chronology, sole canonical log/report, full raw
original/linked ELF as textual hex with every section/symbol/relocation, exact
target/candidate decodes and positional differences, and SHA256SUMS. The
canonical report is `isolatedroot/docs/match/080E28C4.md`; verification.json
distinguishes the 256-byte owned target from the 260-byte diagnostic window.
The original inventory and independent review remain separate sealed bundles.
