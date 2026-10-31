# 0802C830

One natural C form was compiled with the fixed agbcc Thumb defaults
`-mthumb-interwork -O2` under accepted lease 6538587297 (sol-C830).
The original native R3 callback selector run exited 1 before creating a report:
`ValueError: inert-spin complete body differs from ROM`.

The single authorized unchanged-source compiler-only diagnostic linked the full
148-byte symbol. Exactly 132/148 bytes agree at the same offsets; 16 bytes differ.
This is positional equality, not a native MATCH or an alignment metric.

The first difference is at 0x0802C832. The ROM first loads the source pointer,
forms source+0x79C in r6, then retains destination in r5. This source's output
first retains destination in r6 and forms the source base in r5. The later
callback arguments use those opposite saved-register assignments. The
arithmetic, conditional branch positions, addressed runtime calls, R3 callback
calls, return sequence and four pool words occupy the same positions. Complete
linked bytes, ELF, disassembly and positional differences are retained under
state/matching-0802C830-author/compiler-only-diagnostic/.

The source retains the actual mapped u8 pointer, typed three-input callback,
signed16 input view, absolute magnitude/clamp, and addressed signed-word runtime
calls with unknown conditional ABI results. It claims no historical prototype
certainty, numeric division/remainder theorem, callback memory effects or
allocation/readability guarantee.

No source correction, second form, register/lifetime/declaration steering,
second native run or successful proof replay was attempted. No complete native
report exists, so this contributes zero matches. No impossibility claim is made.
The unchanged attempted source is parked here; parent owns release/integration.
