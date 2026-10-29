# 0813BA5C — bounded natural C nonmatch

Target: complete [0x0813BA5C, 0x0813BB04), 168 bytes and 67 reachable instructions.
Best semantically correct candidate: 176 bytes and 69 reachable instructions.
Fixed compiler: agbcc -mthumb-interwork -O2. Fresh native matcher exit 1;
source plausibility passed, complete-byte comparison failed. Zero C match credit.

The function takes a context pointer and u8 mode. Its u16 override is at
context +0x3C28; the u8 selection is at +0x3C2A, and its source marker is at
+0x2F. Mode 0 uses a nonzero override, otherwise a table value; mode 1 always
uses the override; other modes always use the table value. Table selection
reads byte +6 of a 12-byte entry at 0x08563A70, then byte +0 of a packed
27-byte record at 0x08564670. Existing sources 080CEB34 and 08045424 confirm
the table layouts. The record must be packed: the compiler rounds an ordinary
27-byte structure to 28 bytes, and that incorrect-stride form was excluded.

The actual caller at 0x0813BB84 calls this function, then STRH R0 at context
+0x36, shifts R0 right by 16, and STRH at +0x38. The caller observes the full
32-bit result; a byte return signature is not a justified narrowing.

Remaining difference: in each duplicated table fallback, the candidate keeps
the record pointer in R2 and the context in R3. It forms the marker address
with a separate copy into R1, sets R0 to 1, stores through R1 and loads the
result through R2. ROM keeps the record pointer in R0 and context in R2,
advances R2 itself to +0x2F, sets R1 to 1, stores through R2 and loads through
R0. That saves one instruction in each fallback. Register choices also differ
in the override paths. The two extra instructions plus changed literal-pool
alignment produce the eight-byte excess. The common 168-byte span differs at
103 byte positions; the candidate then has eight additional bytes. A target
truncation or comparison with neighboring function bytes would not be valid.

Natural forms tried: typed record pointers and 27-byte byte-array rows;
16-bit versus 32-bit return spelling; a byte context view; direct table return
after marker assignment; computing the value before updating the marker;
explicit record-byte offset arithmetic; and switch versus if/else control.
The direct-expression form changes register pressure without matching.
Computing the value first merges the fallback branches into a 120-byte body.
The final preserved typed-pointer form is plausible and correct in the
recovered data layout, but remains a complete 176-byte nonmatch. No compiler
flags, artificial volatility, assembly, padding or register steering were used.

The original compiler ET_REL is preserved unmodified as original.o in the
sibling 0813BA5C delivery directory, outside the disposable matching-root.
The native mismatch report and log are preserved there. Failed active source
and report have been removed; parent owns reservation outcome and release.
