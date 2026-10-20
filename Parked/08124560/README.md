# 0x08124560

Status: natural recovery preserved, not byte-identical. This remains a
matching task; it is not classified as inherently unmatchable.

## Complete target

The ROM symbol is `[0x08124560, 0x08124648)`, 232 bytes and 101 instructions.
Its literal words are `0x02000080` at `0x08124590` and `0x0854CD54` at
`0x08124644`. The function consumes two unsigned-byte arguments and returns
void.

Selector `0xFF` scans 24 records of size `0x108`, selecting the first with
bit `0x400` in the halfword at offset `0x28`. Other high-bit selectors use
`func_08121CB4`; remaining selectors use `func_080C83CC`. The existing
scene object is looked up, or initialized from a position pair in the
40-byte definition table. The record coordinates are at offsets `0xF6`
and `0xF7`, facing at `0xF8`, and copied previous coordinates at `0xF9`
and `0xFA`. The final helper receives the object and two zero bytes.

The recovery preserves all original unchecked paths. It does not invent
record, reference-object, scene-object, or position-range guards.

## Verification and remaining difference

The retained canonical source was checked with the frozen reviewed toolkit
`kit-reviewed-c85d11d/tools/match.py` and compiler
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.

The complete compiled symbol is also 232 bytes, with no unresolved
relocations. The direct-call and source-plausibility gates pass, but only
197/232 bytes match, so the official command exits 1.

The canonical loop initializes the null result before searching, uses a
different entry/exit branch arrangement, and places its first literal pool
earlier than the ROM. The coordinate stores and subsequent argument loads
also assign the two field addresses to `r1` and `r3` in the opposite order.
The table stride, two-byte position offset, helper calls, later object-field
updates, and final update call have been recovered.

## Natural forms checked

- The retained bounded `for` loop uses a separate candidate pointer, null
  result, and ordinary success `break`.
- Searching directly through the result pointer and checking the final
  index emits 244 bytes, including extra loop exit work.
- A meaningful success jump to the shared record-resolution code emits
  232 bytes and matches 215/232 bytes. Its compiler hoists the `0x108`
  stride and assigns the mask to `r5` and stride to `r4`. The ROM keeps
  the mask in `r4` and constructs the stride in `r0` inside the loop.
  The coordinate-field address register difference remains.
- Moving pointer advancement into the loop body or initializing the null
  result before the success-jump form does not resolve the mismatch.
- A two-byte coordinate struct was discarded because this compiler pads
  that struct to four bytes. The retained byte-pointer representation
  correctly models the ROM's two-byte pairs.
- Table-record byte offsets use `sizeof(SceneDefinition)` and position
  offsets use `2 * position - 2`; both derive from the actual layouts.

No alternate optimization flags, register assignments, inline assembly,
volatile accesses, compiler pragmas, artificial code, or gate bypasses
were used. Only the canonical recovery is retained.

## Helper contracts checked

- `func_08121CB4` and `func_080C83CC` narrow the selector to one byte and
  return record pointers.
- `func_08096D7C` is a no-argument global context getter.
- `func_08099560` accepts context and record pointers and returns an
  object pointer; its iterator arguments are constructed locally.
- `func_0800A018` is a no-argument halfword getter.
- `func_08124238` obtains its own context and returns an enumerated object
  pointer, with no incoming argument dependency.
- `func_08124ACC` consumes four unsigned-byte coordinates and returns one
  of the facing values zero through three.
- `func_08092440` accepts context and record pointers and returns the
  existing or newly created object pointer.
- `func_080CE380` accepts a record and byte-valued enable flag, updating
  bit `0x80` of record byte `0xED`.
- The separately recovered `func_08124710` accepts an object pointer and
  two unsigned-byte arguments.

The unmatched active source and generated report were removed. No
task-owned scratch artifacts remain.
