# 0x08133970: not matching

Complete target extent: [0x08133970, 0x08133988), 24 bytes.
The operation reads byte offset 4 from a 12-byte descriptor selected by a u8
index. The descriptor table is the existing mapped data_083A87B0. Neighboring
src/08133988.c and src/0813388C.c establish the constant table and entry size.

Three native checks used agbcc -mthumb-interwork -O2. All candidates were
plausible complete 24-byte bodies, but no complete exact match was obtained:

1. Typed descriptor access emitted ldrb [r1,#4] rather than adding 4 to the
   table base first. It matched 21/24 bytes and 7/9 compiled instructions.
2. A byte-column pointer view folded 4 into the literal, yielding 0x083A87B4
   instead of the target literal 0x083A87B0 and separate adds r2,#4. It matched
   21/24 bytes and 8/9 compiled instructions.
3. The retained byte-table indexing source matched 23/24 bytes and 9/10
   instructions. The sole difference is adds r1,#4 instead of adds r2,#4:
   the compiler adds the field offset to the scaled index, while the target
   adds it to the table base before combining the index and base.

Target bytes:
0006000e034a4100091889000432891808787047b0873a08

Final compiled bytes:
0006000e034a4100091889000431891808787047b0873a08

No successful check was replayed. The final source and unmodified failed
native report were moved here after verification. The report retains its
original src/ path and source/header fingerprint. Earlier candidates and
native logs remain in state/matching-08133970-author/ in the handover folder.
