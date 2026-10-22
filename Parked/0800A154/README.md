# 0800A154 — recovered, not byte-identical

## Complete symbol and mismatch

The full target is `[0x0800A154,0x0800A1A8)`: 84 bytes and 39 reachable
Thumb instructions. It contains 80 code bytes and one four-byte literal
at `0x0800A19C`, whose value is `0x0836D5A4`. There is no internal or
external alignment in this symbol. The separate `BX LR` at `0x0800A1A8`
is excluded. The incoming call at `0x0800A12A` independently establishes
the entry. Target SHA-256:

`de7ef581374fcae826b006104c6b280dbbfd0896625b354e22ccee475f3e8041`

The retained candidate emits exactly one `STT_FUNC`, with its complete
84-byte size equal to `.text`: 38 instructions, 78 code bytes, one literal
word and two internal alignment bytes. Its linked SHA-256 is:

`3597f9ddebfe5a25ce2418b6726caff596893fed615b3fd4121700c41dcc47d9`

The complete positional comparison is 52 equal bytes and 32 different
bytes out of 84. This is not an instruction-alignment score. The frozen
`2e2a664` matcher accepts the typed data/runtime-thunk linking, structural
CFG and plausibility, then correctly reports `NOT MATCHING - bytes differ`.
There is no unsupported-profile blocker, truncated comparison or MATCH
claim. No active source, private header or report remains.

Two bounded ordinary forms were checked with the standard agbcc
`-mthumb-interwork -O2` flags:

1. Direct table indexing inside the loop and the length expression in the
   position assignment: 84 bytes, with a smaller save set and a table
   address load inside the loop.
2. The retained semantic table view shared by iterations and a named
   decoded length: 84 bytes, preserving the target's saved registers and
   table-base lifetime, but still differing in generated instructions.

The candidate keeps the instruction pointer in the second argument
register while decoding the callback. The target instead reconstructs the
callback using that register and moves its saved instruction pointer into
place before the call. Byte-decoder registers, table-address operand order,
the post-call sum/store registers, branch encoding and alignment differ.
No forced register, storage, alignment, artificial control flow or inline
assembly was introduced to correct these differences.

## Interface and natural recovery

The compatible interface is `u32 func_0800A154(ScriptContext *context)`.
Only the incoming context pointer is consumed; no incoming stack argument
is read. Both bodies save 16 bytes and use no local frame. Every ordinary
returning path produces the full word one. This does not prove that a
nonzero-opcode path terminates or uniquely identify the original typedef.

The local tagged `struct ScriptContext` exactly matches the declaration
in the separately Parked `0800A10C` recovery: byte `bank` at zero, byte
`index` at one, signed halfword `position` at two, and `const u8 *script`
at four. A target-compiler probe confirms size eight and alignment four.
The interpreter itself does not read the first two fields, but handlers
receive the complete context. No shared type or existing source is changed.

The grounded table binding `g_table_0836D5A4` is an unsized array of
six-byte rows. Each iteration reloads the signed position and script
pointer, then reads the opcode at their sum. Opcode zero returns one
without reading a table row. Otherwise the opcode selects a row whose
callback address is assembled from four byte reads at offsets two, three,
four and five, in that order. Unsigned shifts avoid signed left-shift
overflow. No aligned word load or packed pointer member is invented.

The callback is invoked through the actual `BX r2` thunk at `0x0814224C`
with `(context, instruction)`. The ordinary `u32` callback result is
ignored. These two explicitly supplied arguments are an ABI boundary,
not an independent signature or behavior audit of every table handler.
The conversion from the serialized integer to a function pointer is a
target-specific representation assumption, not portable C provenance.

After the callback returns, the selected row's length bytes zero and one
are read in order. The context position is then reloaded as an unsigned
halfword, the length is added, and the low halfword is stored. The next
iteration reloads both the signed position and the possibly changed script
pointer. The handler's offset and stream mutations are not overwritten by
an earlier snapshot. Unsigned halfword operands promote to a safe sum at
most 131070; assigning it to `s16` relies on this target compiler's
implementation-defined two's-complement narrowing. The subsequent signed
offset is not replaced with an unsigned index.

## Valid domain and callback limits

The context must have valid aligned mutable storage. Signed pointer
arithmetic must stay within the actual bytecode object's permitted domain;
negative offsets can be valid for an interior script pointer, but no
arbitrary bounds or allocation size are inferred. Each selected table row
and callback must be valid for the ordinary target ABI. There is no new
opcode, callback-null, length or termination guard.

Handlers may mutate context fields and bytecode, retain the context or
instruction pointer, affect other state, or fail to return. This recovery
does not prove purity, nonretention, lifetime safety, arbitrary alias
validity or general termination. The interpreter's own only nonstack write
is the position halfword update. The declaration is const because the
dispatch table is in ROM; synthetic table mutations used below are
explicit machine-only tests, not defined writes to the declared C object.

## Reproducible bounded evidence

Run from the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/0800A154-20/check_recovery.py
```

The reproducer freshly compiles and typed-links the full parked symbol,
checks layout and plausibility, and repeats the official nonmatch in an
isolated `--no-write` tree. Generated build artifacts self-clean.

There are 187 paired fixtures / 374 executions, covering all 39 target
and 38 candidate instructions. Six fixtures execute only the actual
opcode-zero path: one uses the pristine zero byte at `0x08A1ABEB`, and
five use synthetic RAM streams with signed offsets including -32768,
-1 and 32767. The other 181 explicitly model dynamic handlers, executing
the actual caller and thunk, not claiming actual handler execution.

The 180 returning handler fixtures vary opcodes, callback addresses,
lengths zero through 65535, signed position boundaries, wraparound,
script-pointer replacement, context-byte mutations, retained pointers,
arbitrary ignored return words, caller-saved registers and condition flags.
Sixty of these mutate synthetic dispatch-table bytes after the call and
are machine-only evidence that length is loaded afterward. A separate
zero-length loop stops at the third modeled callback, providing a bounded
cyclic prefix rather than a termination claim.

An operation oracle and both binaries agree on the entire synthetic RAM
and table, ordered callback arguments, and ordered nonstack data reads
and writes. The trace excludes instruction fetches, ROM literal-pool
loads and stack accesses. Returning cases preserve `r4` through `r11`,
restore SP and return control, and return one regardless of the modeled
handler result. No real dynamic handler was enumerated, stubbed as if real,
or audited beyond this explicitly labeled model boundary.
