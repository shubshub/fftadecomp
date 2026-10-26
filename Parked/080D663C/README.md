# 080D663C — Parked

The full reconstruction reads a halfword from a plain or encoded stream.
Plain reads use the existing cursor and increment the u16 index. Encoded blocks
have a packed u16 control word: bits 0..13 give the element count, bit 15 selects
an increasing run from the first value, and bit 14 selects a repeated value.
Bit 15 takes precedence. Without either mode bit, the block contains an array.
After consuming the block count, the cursor advances by four bytes for either
run mode or by two header bytes plus twice the count for an array; the index
resets to zero. Arithmetic and the index wrap at u16 width.

The final canonical native invocation used unchanged agbcc
-mthumb-interwork -O2 and exited 1 because the complete compiled target function
is 168 bytes, shorter than the indexed 178-byte target. This early rejection
does not run the source-plausibility gate or full byte comparison. No exact
match, aligned similarity score, or plausibility pass is claimed.

The target has 87 reachable instructions. The preserved candidate emits 81
instructions plus its four-byte 0x3FFF literal and two alignment bytes. Its naturally inlined
read_packed helper emits no separate function body or helper call in the
retained compiler assembly.

The remaining gap is register allocation, masking, and the outer result join:

- The target holds the cursor in r7, count in r6, and assembled control word
  in r3; the candidate uses r6, r7, and r2, respectively.
- The target loads the packed header pointer into r2 and copies it to r4
  during the first mode test. The candidate loads directly into r4.
- For the count mask the target emits ldr r1; mov r0,r1; mov r6,r3; and r6,r0.
  The candidate emits ldr r7; and r7,r2.
- For bit 15 the target copies the mask to r1 and the control to r0 before
  AND. The candidate directly ANDs r0 with r2. The bit-14 test also lacks
  the target's separate mask-register copy.
- The array cursor-advance arithmetic groups the base/offset additions in
  a different order. The candidate moves the compressed result into r0
  before jumping to the shared return; the target joins both paths with
  the result in r3 and performs one final move.

Four natural reconstructions were tested: the direct packed-header function
(166 bytes), a semantic packed-block reader helper with u16 bookkeeping
(168 bytes, preserved here), promoted u32 bookkeeping (166 bytes), and an
explicit little-endian halfword reader helper (162 bytes). The best 168-byte
candidate was restored and freshly rerun. No flags, assembly, volatile access,
forced inlining, or scheduling-only parameters were introduced.

The final native output and compiler assembly remain in the private address
scratch directory. Unmatched active source/report were removed. This Parked
directory contains only the complete C candidate and this diagnosis.
