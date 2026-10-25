# 080DFEB8: preserved single-candidate non-match

The unchanged natural candidate forwards its object pointer to the matched
`u32 func_08005BB0(const void *)` and returns whether the complete 32-bit result
is nonzero. The original public return typedef is not uniquely recovered;
`u32` is an ABI-compatible scalar choice for the observed zero-or-one result.
The callee requires a readable aligned unsigned halfword at object+0x14 and
tests it against two. No null guard or allocation-size guarantee is invented.

Exactly one candidate was frozen before exactly one canonical invocation of
`match.py --root <isolatedroot> 0x080DFEB8`, using the default
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2` toolchain. No source, type, flag,
register, declaration-order or spelling retry followed the compiler output.

The complete owned ROM target is `[0x080DFEB8,0x080DFECC)`: **20 bytes and nine
instructions**, without pools or alignment. The complete emitted ELF function
and text section are **16 bytes and seven instructions**. The compiler keeps
the callee's zero result and branches past `movs r0,#1`; the ROM instead uses
explicit zero and one arms plus an unconditional merge branch. Both use a
full-width comparison, the same typed direct call and balanced Thumb return.
This source-level interpretation does not constitute a machine-equivalence
proof or byte match.

Raw positional comparison has **9 equal bytes, 7 different bytes and 4 missing
target bytes**. A separate byte-LCS metric is 15, which is alignment evidence
only and gives no match credit. The original ELF contains one
`R_ARM_THM_CALL` relocation at +2 to `func_08005BB0`; the linked ELF resolves it
to 0x08005BB0 and has no remaining relocations. No adjacent bytes are included.

The canonical process exits 1 at its short-symbol gate before producing a
report or running source plausibility. The observer retained decoded summaries
of the original and linked ELF images, readelf text, and complete text-section
hex. Raw full ELF images were decoded during the sole run and then deleted;
they are not retained for independent raw-ELF re-parsing. Its `SystemExit`
handler did not retain or print the string diagnostic. The gate reason is
inferred from the pinned
tool's size check and the captured 16-versus-20 sizes; it is not presented as
a captured error message. No native or emulator campaign was run for this
non-match. This bounded attempt does not establish that the function cannot
be matched by a future independently justified reconstruction.

Only this C file and README are proposed for Parked integration. Complete
retained evidence is outside that minimal payload:

- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/HANDOFF.md`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/freeze.json`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/elf-capture.json`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/EXACT-DIFF.md`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/comparison.json`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/canonical.log`
- `/home/user/.codex-work/ffta-ulw/080DFEB8-author-next/SHA256SUMS`

Nine unchanged input headers and private mapping bindings are frozen there.
The separate metadata proposal adds only this 20-byte entry to three indexes;
metadata qualification gives no compiled-source credit. A prior 36 KiB
incoming-reference scan found none within its coverage, not across the ROM.
Root owns independent review, metadata integration and reservation release.
