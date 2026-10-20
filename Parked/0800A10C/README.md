# 0800A10C: script-context initialization, not a match

## Complete-symbol disposition

This is a plausible natural-C recovery, not a byte-identical implementation.
No active source or successful match report is retained. No inherent
unmatchability or unique original-source reconstruction is claimed.

- Complete target: `[0x0800A10C,0x0800A154)`, 72 bytes / 28 instructions.
- Code occupies `[0x0800A10C,0x0800A146)`, followed by two internal zero
  alignment bytes and three literal words at `0x0800A148..0x0800A154`.
  The next function begins immediately at `0x0800A154`.
- Target SHA-256:
  `3f825d66666240dd79019672b3ce72d7c20ca97f8da9898f8a5b008e450d9289`.
- The retained candidate also has one 72-byte `STT_FUNC`, a 72-byte `.text`,
  28 instructions, 58 code bytes, two internal zero bytes and three literals.
- Linked candidate SHA-256:
  `49ef27729b0f08bfd9ed66b6428aa3d366ee1dcc9700998e8a137e0d1fa5cb78`.
- Positional comparison: 66/72 bytes and 25/28 instructions are identical.
  The six differing bytes are exactly `0x0800A110..0x0800A116`.

The target loads the table-base literal into `r3` before reading context
byte zero and doubling its index. The retained candidate reads/doubles that
index first, then loads the same literal into `r3`; its PC-relative immediate
changes accordingly. All remaining bytes, including the complete literal
pool and internal alignment, agree. The matcher's sequence-aligned display
reports 70/72 bytes and 27/28 instructions, not positional equality.

## Bounded natural attempts

Two ordinary representations were compiled with unchanged
`agbcc -mthumb-interwork -O2`:

1. The retained first-level-bank expression emits the 72-byte candidate
   described above.
2. A cursor initialized to the table base and advanced by each relative
   offset also emits 72 bytes / 28 instructions. Its initial load ordering
   agrees, but different register operands remain; the sequence-aligned
   display reports 68/72 bytes and 24/28 instructions.

The first form was retained for its clear separation of the bank and script
lookups. No additional compiler search, explicit register, artificial work,
forced storage, inline assembly, volatile access, pragma or optimization
change was used.

The frozen `kit-reviewed-2e2a664` matcher accepts the whole symbol, typed
direct-call linkage, named-data relocations, local CFG and strict source
plausibility, then reports `NOT MATCHING - bytes differ`. There is no
successful report replay or partial-match promotion. Reproduction uses an
isolated game tree containing all current headers, the parked source at
`src/0800A10C.c`, current maps, and the normal matcher with `--no-write`.

## Interface and observed effects

The compatible interface is `u8 func_0800A10C(ScriptContext *context)`.
The ordinary eight-byte context contains byte indices at offsets zero and
one, a signed-halfword position at offset two, and a stream pointer at offset
four. The signed position view follows the interpreter's actual reads;
this caller only stores zero there. No incoming register other than `r0`
or incoming stack argument is consumed. The caller saves eight bytes and
allocates no local frame. Original nominal types are not uniquely proved.

The table at `0x08A1A908` contains unsigned-halfword relative offsets.
The first index selects an offset relative to the table base. The second
index selects another offset relative to that first subtable. The resulting
script pointer is stored at context offset four **before** zero is stored
at offset two. Both table reads retain unsigned values, including offsets
with bit 15 set; neither offset is interpreted as signed.

The initialized context is passed to `0800A154`. Its compatible declaration
returns a full word, and the caller explicitly compares its low byte with
one. Only that equality path reads `g_state_02000000[0x219C]`, after the call;
other returned low-byte values yield zero. The result is a byte value, not
a normalized Boolean.

The real interpreter's ordinary returning paths produce one. It repeatedly
reads the context's signed position and stream pointer, dispatches nonzero
opcodes through dynamic handlers, reloads its row length and context position
after each handler, and stops at opcode zero. Handlers can mutate or retain
the context; this recovery adds no purity, nonretention, allocation,
termination or universal callback-safety promise.

The context must provide suitably aligned writable storage for all eight
bytes. The byte backing and aligned `u16` views require valid selected
halfword storage, subtables and stream addresses. Neither table capacity nor
an original enclosing C object identity is established. No bounds check or
context-null guard absent from the ROM is invented. The opaque global
declaration remains compatible with the existing byte-array view.

## Bounded execution evidence

80 paired fixtures / 160 executions compare the actual ROM caller with the
freshly linked candidate using explicitly synthetic context/table/RAM data:

- Eight pairs execute the real `0800A154` opcode-zero path without any
  modeled helper or handler.
- Eight pairs execute the real interpreter and real `0814224C` thunk with
  one explicitly modeled dynamic handler. The handler changes the stream,
  position, context indices and result byte, retains the context address,
  and clobbers caller-saved registers. These tests exercise interpreter
  reloads, signed positions and halfword wrap; they do not execute or verify
  any actual game handler.
- Sixty-four pairs explicitly model the `0800A154` boundary with full-word
  results including zero, one, two, `0x101`, `0xFFFFFF01`, `0xFFFFFFFF`,
  `0x100` and `0xFF`. They test the caller's low-byte comparison and post-call
  memory reads, not a claim that the real interpreter normally returns these
  other values.

The fixtures vary both indices through zero, one, 127 and 255, unsigned
relative offsets including `0x8000` and `0xFFFE`, initial/result bytes,
unrelated input registers, and callback-mutated context fields. Every pair
agrees with the explicit result/final-memory model and with the other body
on ordered context, selected-table, stream, dispatch and state accesses,
ordered non-stack writes, call arguments/order, return control, preserved
`r4-r11` and balanced SP. Initialization store order is asserted at the
interpreter entry. Full EWRAM and non-stack IWRAM are checked.

All 28 caller instructions, all 28 candidate instructions, all 39 real
interpreter instructions and the one thunk instruction execute across these
fixtures. Coverage is local to the stated real/model boundaries, not a
universal handler or termination proof.

Complete non-stack data-read traces, **including function literal-pool
loads**, differ in all 80 pairs because the table-base load moves across the
first context-byte read. The ordered-access agreement above excludes those
function literal loads and instruction fetches; it is not full trace or
byte equality. No arbitrary alias, concurrent-mutation or MMIO equivalence
is claimed. Generated ELF/binary/isolated-tree artifacts are removed; the
small scoped reproducer records these exact fixture boundaries.
