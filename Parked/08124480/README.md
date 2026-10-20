# 0x08124480

Status: natural recovery preserved, not byte-identical. This remains a
matching task; it is not classified as inherently unmatchable.

## Complete target and behavior

The complete ROM symbol is `[0x08124480, 0x08124560)`, 224 bytes and
104 instructions in 14 basic blocks. Its only literal word is
`0x02000080` at `0x081244C8`.

The function consumes five unsigned-byte arguments: selector, two
coordinates, facing, and an enable flag. The fifth argument is loaded
from entry-SP offset zero after 28 bytes of register saves. It returns
void.

Selector `0xFF` scans 24 records of size `0x108`, selecting the first
whose halfword at offset `0x28` has bit `0x400`. Other high-bit selectors
use `func_08121CB4`; remaining selectors use `func_080C83CC`. The selected
record receives coordinates at `0xF6` and `0xF7` and facing at `0xF8`.

The object lookup uses the global scene context and the selected record.
Its coordinate helper receives signed-byte coordinates. Current
coordinates are then copied to record offsets `0xF9` and `0xFA`, and
the update helper receives the object, one, and facing. A nonzero fifth
argument clears bit zero of the object's word at offset `0x30`; zero
sets that bit. The recovery preserves the original unchecked record
and object paths.

## Verification and remaining difference

Checks used the frozen reviewed toolkit
`kit-reviewed-79334c6/tools/match.py` with compiler
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.

The retained canonical pointer-scan and success-break recovery compiles
to a complete 224-byte symbol. Source plausibility and the direct-call,
external-data, and incoming-stack-argument profile checks pass, with no
unresolved relocations. However, only 194/224 bytes match. Its null-result
initialization, loop branch arrangement, literal placement, and selected
record register differ from the ROM.

Three ordinary source forms were checked:

- The retained pointer scan initializes the result to null and uses a
  success `break`. It emits 224 bytes.
- A pointer scan with a meaningful success jump to the shared
  record-resolution code emits 224 bytes and matches 214/224 bytes,
  with 97/104 instructions identical. Every differing byte is within
  `0x081244AA` through `0x081244C2`. The compiler hoists the `0x108`
  stride into `r5` and places the mask in `r4`; the ROM places the
  mask in `r5` and constructs the stride in `r0` inside the loop.
  The literal and all subsequent object updates, helper calls, flag
  handling, and epilogue bytes match.
- An indexed-array scan with the same shared success path emits
  236 bytes, increases register-save requirements, and does not match.

A single requested optimization-level diagnostic used the retained
canonical source with `-mthumb-interwork -O1` and `--no-write`. The frozen
matcher exited 1 before byte comparison with
`compile failed: unexpected nonempty allocated section`. Consequently,
there is no verified `-O1` symbol size or byte-difference result, and this
diagnostic does not establish whether optimization level explains the
loop difference. The standard `-O2` baseline remains unchanged.

No other optimization flags, forced registers, inline assembly, volatile
accesses, compiler pragmas, artificial code, or gate bypasses were used.
Only the canonical recovery is retained.

## Helper contracts checked

- `func_08121CB4` and `func_080C83CC` consume unsigned-byte selectors
  and return record pointers.
- `func_08096D7C` obtains the global context without incoming arguments.
- `func_08099560` consumes context and record pointers and returns an
  object pointer.
- `func_08099E68` consumes an object and two signed-byte coordinates,
  converts each to a pixel coordinate using `32 * value + 16`, updates
  the object, and writes the coordinate bytes back to its record.
  Its complete symbol is `[0x08099E68, 0x08099EA0)`, 56 bytes and
  27 instructions, with no pools.
- `func_08124710` consumes an object and two unsigned bytes; this caller
  passes update value one and its original facing argument.

The unmatched active source and generated report were removed. No
task-owned scratch artifacts remain.
