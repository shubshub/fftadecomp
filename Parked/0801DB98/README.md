# 0801DB98 — bounded natural C attempt

Target: `[0x0801DB98, 0x0801DC04)`, 108 bytes, 47 reachable Thumb instructions. The recovered function takes a 16-bit index, substitutes the current global index for signed -1, and returns 255 for signed index 255. Otherwise it selects the normal byte at offset 0x54 in a 0x58-byte resource record, or the alternate byte at offset 0x55 when the runtime condition is active and the alternate is not 255. Signed indexing and byte return semantics follow the ROM.

Final native matcher exit: 1, `NOT MATCHING - bytes differ`. The preserved typed-record candidate has a complete 112-byte ELF symbol. Native ordinary-call/extent validation passed and source plausibility was reported `plausible`; this does not establish an exact match and receives no match credit.

The residual is in record-field address calculation and the resulting middle-pool/branch layout. For example, at the alternate-field test the ROM adds 0x55 to the table base in r1 before combining it with the index-times-0x58 value in r0. The compiler combines the unadjusted base and product in r0, then adds 0x55 to r0. The final normal/alternate branches also choose different address registers and share their final addition/load differently. Their literal-pool placement consequently differs. The native comparison displayed an aligned 91/112 bytes and 33/48 instructions identical; those are alignment scores, not same-offset equality or the complete target instruction count, and the compiled extent exceeds the 108-byte indexed target.

Natural forms tested: direct typed record members; delaying the default result initialization until after the index substitution; a naturally inline packed-field accessor; and direct byte-field views. The typed form remains 112 bytes. The packed accessor with a signed 16-bit index also produced 112 bytes with additional narrowing differences; its 32-bit-index form and direct byte-field views produced 104-byte symbols, refused by the extent gate before plausibility. The complete typed candidate was restored and freshly tested for this record. No assembly, artificial volatile access, compiler flag changes, forced inlining, or inert code was used.

Compiler: agbcc `-mthumb-interwork -O2`.
Native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x0801DB98
```

Final native output: `/home/user/.codex-work/ffta-ulw/audio-following-v459-matching/0801DB98/match-current.log`.
Full target: `/home/user/.codex-work/ffta-ulw/audio-following-v459-matching/0801DB98/target-disassembly.md`.
