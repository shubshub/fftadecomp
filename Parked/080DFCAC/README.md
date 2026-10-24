# 080DFCAC: interpolated audio parameter callback

**Parked, not matching.** One natural candidate, one canonical compilation,
no source revision or compiler-option search. Fixed compiler:
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.

## Exact difference

The proven ROM ownership is `[0x080DFCAC,0x080DFD68)`: 188 bytes,
76 reached Thumb instructions, 162 code bytes, five literal words and six
alignment bytes. The complete compiled ELF symbol is 192 bytes, 77 reached
instructions, 164 code bytes, five literal words and eight alignment bytes.

ROM transfers incoming payload r2 directly into r5. The candidate instead
transfers r2 to r0 and then r0 to r5, adding one instruction. The first pool
then needs another two alignment bytes. Branch displacements, call offsets
and later pool locations consequently differ. The first positional mismatch
is at function+2; only 10 of the 188 owned ROM bytes agree at the same position.
A byte-sequence alignment finds 176 equal bytes; this is not positional or
complete-function equality.

The canonical report compares the emitted 192-byte extent with 192 ROM bytes,
including the next constructor's first four bytes (`00b587b0`). Its
`176/192` diagnostic does not establish 192-byte ROM ownership. Its side-by-side
instruction display also applies compiled layout to ROM bytes; apparent
coprocessor instructions there are not target instructions. The local
`BODY.md` evidence independently classifies each body's actual code and pools.

The named data symbol links successfully: the original object's data
relocation at +0x9C resolves to `g_table_08149B88` at `0x08149B88`, with no
remaining linked relocations. ROM's equivalent pool word is at +0x98.
The canonical profile is `elf-symbol-thumb-data-v1`, source plausibility is
`plausible`, and the verdict is `NOT MATCHING - bytes differ`. No attempt to
change register allocation, source spelling, declaration order or flags was
made. This is a bounded nonmatch, not proof of impossibility.

## Recovered contract and limits

The callback retains all three pointer arguments and returns zero. Constructor
`080DFD68` registers `080DFCAD` with a 20-byte payload through `08005B6C`.
The task argument is unused. Descriptor phase is u16+0; direction is read as
u16+0x14 and narrowed to u8; duration is read as signed16+0x16.

Payload contains float value+0, u8 direction+4, three unknown bytes, and a
six-halfword interpolator at+8. The latter fields are current, remaining,
error, step, period and distance, in that order. Their signed interpretation
comes from the initializer/stepper's actual accesses, not invented padding.

Phase0 initializes interpolation 32->0 for direction0 or 0->32 otherwise.
It reloads direction after the initializer and stores 0.5f or 1.0f respectively.
Phase0x100 steps, indexes the float table using signed current, then tests the
completion result's low byte. Completion overrides the value with 1.0f for
direction0 or 0.5f otherwise and sets phase2. The resulting float is passed to
`0x08141780`. Phase1 and unknown phases have no effects.

The public `u8` completion return declaration is a local inference supported
by the caller's narrowing and the callee's 0/1 result; the original nominal
public return width is not established. Initializer and stepper are opaque
direct calls, with signed16 input/storage behavior supported by their bodies.
The float audio argument is supported by structural soft-float witnesses,
not recovery of those runtime functions' original ELF names.

Nonnegative signed16 duration is a precondition. No clamp is added. Duration0
skips stepping and forces the completed endpoint. Negative duration can make
the stepper fail to terminate or produce an invalid index. The observed
indices0..32 do not prove total table allocation: the source deliberately
declares `extern const float g_table_08149B88[]` without an invented bound.

## Retained evidence

Only this README and `080DFCAC.c` are proposed as the shared Parked payload.
Supplemental artifacts remain in
`/home/user/.codex-work/ffta-ulw/080DFCAC-author-next/`:

- `freeze.json`: exact first-source, all nine headers, tool and private maps.
- `canonical.log` and `isolatedroot/docs/match/080DFCAC.md`: unchanged canonical result.
- `elf-capture.json`: passive original/linked ELF text, symbols, sections and link bindings from the single invocation.
- `comparison.json` and `BODY.md`: true-owned-span versus complete-emitted-span evidence.
- `metadata.patch`: separate, unapplied four-file metadata proposal; it describes the true 188-byte target, not the 192-byte candidate.
- `HANDOFF.md` and `SHA256SUMS`: final scope and integrity seal.

The sealed constructor/callee/table evidence remains in
`/home/user/.codex-work/ffta-ulw/next-object-followup-inventory-2/`.
No native/emulator behavioral campaign was run for this nonmatch, and no
general behavioral-equivalence or whole-game completion claim is made.
