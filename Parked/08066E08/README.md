# 08066E08 — unmatched natural C

Target: complete 150-byte function, 68 reachable instructions, ending at
0x08066E9E. Fixed compiler: agbcc -mthumb-interwork -O2.

The preserved candidate initializes two tilemap regions when mode is 4 and the
initialization byte is zero, then sets that byte. Each region contains eight
rows, with 28 halfwords cleared per row and a 32-halfword row stride. Other
calls return the byte result of func_08017180 for the control state at +0x24.
The tilemap pointers are the +0x14 members of the existing 0x03000990 and
0x030008B0 symbols; both origins use func_080161A0(1, 11, 32).

The final native invocation exits 1, reports source plausible, and proves a
complete 154-byte compiled ELF symbol. It is four bytes longer than the indexed
150-byte target, ending at 0x08066EA2 when placed at the target entry. This is
not a match and receives no match credit.

Remaining differences:

- The target's first outer loop advances its row pointer after the inner clear
  loop and uses a signed BLE comparison. The candidate uses an unsigned BLS
  pointer comparison and preserves the next-row pointer before the inner loop.
- The target keeps the context in r6; the candidate uses r5. In the second
  outer loop, the target uses r4 for the row index, r5 for zero, and r1 for the
  base, whereas the candidate uses r0, r1, and r4 respectively.
- Literal-pool positions and later branch/call displacements consequently differ.

Natural pointer-for and signed tile-index loops produced 158-byte symbols. A
zero-based linear tile-index loop and the preserved pointer do/while form
produced 154-byte symbols. None reproduced the target's control flow and
register allocation. No flags, compiler configuration, bindings, or shared
files were changed; no signed raw-address casts or other steering was added.
The native diff extends to the longer compiled extent, so its aggregate byte
score is not a same-offset equality count for the indexed 150-byte function.
