# 080372FC — tile-number narrowing gap

The complete target is 0x080372FC..0x08037398: 156 bytes and 61 reachable
instructions. The preserved candidate emits one function, 152 bytes and 59
instructions, with agbcc `-mthumb-interwork -O2`.

The latest native matcher exits 1 at the complete-symbol extent gate:
`compiled symbol is shorter than the indexed span: 152 < 156`. That attempt
does not receive a native plausibility verdict or match credit.

Both branches draw through func_0804C598 with ten arguments. A nonzero icon
selects the first byte of a four-byte record, adds 25 with byte wrapping, and
uses style 0x52. A zero icon uses tile 1 and style 0x30. The remaining call
arguments, frame allocation, register saves, and return structure agree.

Immediately after the common `ldrb r2, [r0]`, the candidate emits:

```text
adds r2, #25
lsls r2, r2, #24
lsrs r2, r2, #24
```

The target instead emits:

```text
lsls r2, r2, #24
movs r0, #0xC8
lsls r0, r0, #21
adds r2, r2, r0
lsrs r2, r2, #24
```

The target adds 0x19000000 after shifting the byte. These five instructions
produce the same wrapped result as the candidate's three instructions. The
missing four bytes also change subsequent literal-pool and branch locations.

Natural attempts covered a direct unsigned-byte calculation, a word-sized
table field, separate byte loading and addition, signed-byte intermediates,
and the preserved naturally inlined icon lookup helper. The signed-byte
load/add form reached 156 bytes but introduced `movs r2, #0; ldrsb r2, [r0,
r2]`, moved the arithmetic around the map load, and still differed. Its
native aligned diff score was 52/59 instructions and 141/156 bytes; those
figures are not same-offset byte equality. No compiler flags or emitted
helpers were added. The preserved unsigned-byte helper form retains the
direct data model and leaves only the documented narrowing-expression gap.
