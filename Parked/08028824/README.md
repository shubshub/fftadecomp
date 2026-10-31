# 08028824: unmatched natural form

Complete target: [0x08028824, 0x0802896E), 330 bytes, 116 reached instructions.

One natural source form was checked once with the default native matcher under
accepted lease 6536726156 (sol-8824). The native process exited 1 with:

```
compile failed:
switch caller differs from the ROM
```

The exact mapped-span guard passed before the byte comparison. No native match
or plausibility report was generated. This is an ordinary byte mismatch, not
an unsupported switch-profile finding.

One explicitly authorized compiler-only diagnostic rebuilt the unchanged source
with the same host cpp, agbcc -mthumb-interwork -O2, assembler and typed linker
bindings. The complete emitted ELF symbol is 330 bytes, as is the target, but
28 bytes differ. At 08028894..080288B0 the compiler schedules the selected
pointer-table load later and uses different low registers. At
0802891A..08028926 the encoded-record address and separate byte loads use
different low registers. All local switch-table words, data literal words,
the real 080CA7A4 call, and bytes outside those two regions agree. The source
was not changed to steer registers or scheduling.

The retained source uses the observed record offsets, signed16 index view,
separate byte2/byte3 little-endian assembly and actual defining helper signature
s32 func_080CA7A4(u16,u8). No external-table extent, physical readability or
universal helper arithmetic theorem is claimed.

No second C form, native replay, second diagnostic or successful proof occurred.
The exact first source is retained here; active src/08028824.c and its native
report are absent. Full commands, compiler ELF, complete body, disassembly,
diff, current runtime, 115 toolkit source pins, nine headers and both roots'
map pins are retained under state/matching-08028824-author/ in the handover.

Source SHA-256: b637995bdfee3c52c7e8e32affb6377e21f57f3b16f15dfbeb8a8c21185fc2bd
Original source/header fingerprint: 679a134879c00e394a235a9fd0242204fd2adb1c42d17276632be22b0646d5e2
Emitted complete body SHA-256: fc6df69d738deba33def19a6cb29b550d60f821566d34ef520b002c57225c8bc
Target body SHA-256: 5e6220864e9d4331592cd95d778e15e9fa936c5993417ab4abe547ff09117245
