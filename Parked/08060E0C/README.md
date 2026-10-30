# 0x08060E0C: not matching

Complete target extent: [0x08060E0C, 0x08060E24), 24 bytes.
The observed operation narrows the input to u8, selects a four-byte entry
at object offset 0x128, and reads the byte at entry offset 2. The object
pointer is the existing mapped data_0200F44C.

Four native candidate checks ran with agbcc -mthumb-interwork -O2:

1. A struct with a C99 unspecified-length trailing array was rejected:
   field `entries` has incomplete type.
2. A typed entry-base view compiled to a plausible complete 24-byte body,
   but loaded the global object pointer before the scaled index and added
   0x128 to the base first. It matched 17/24 bytes and 5/10 instructions.
3. A GNU zero-length trailing-array struct compiled to a plausible complete
   24-byte body, but folded the field offset into 0x12A and emitted a byte
   load at offset zero. It matched 17/24 bytes and 5/10 instructions.
4. The retained source computes the entry byte offset explicitly. It is
   plausible and matches 19/24 bytes and 6/10 instructions. It loads the
   global literal after computing the offset and uses r1 for the 0x128
   constant. The target loads the literal early into r1 and computes the
   offset with r2, before dereferencing the global object pointer.

Target bytes:
00060449800d94225200801809680918887870474cf40002

Final compiled bytes:
0006800d942149004018024909680918887870474cf40002

No complete exact match was obtained. No successful check was replayed.
The final source and unmodified native failed report were moved here after
verification. Earlier source candidates and logs remain in
state/matching-08060E0C-author/ in the handover workspace. The final report
retains its original src/ path and source/header fingerprint.
