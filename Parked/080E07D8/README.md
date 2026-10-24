# 080E07D8: nonmatching task-value predicate

**Parked preservation only.** One natural candidate forwards the object pointer
to `u32 func_08005BB0(const void *)` and returns whether its complete u32 result
is nonzero. The original nominal return typedef is unknown; the recovered u32
API is compatible with the machine result and existing callee declaration.

## Single-attempt result

Default agbcc with `-mthumb-interwork -O2` emits a complete 16-byte, seven-
instruction ELF function. The approved ROM target is 20 bytes and nine
instructions, [080E07D8,080E07EC). The canonical invocation exits **1** with:

```text
compiled symbol is shorter than the indexed span: 16 < 20
```

This is an early SystemExit diagnostic, not an integer return from main. The
observer retains that diagnostic and propagates process exit 1. No canonical
Markdown report is created because the short-symbol gate precedes report
generation. No MATCH, source equivalence or eligibility claim is made.

```text
ROM:      00b525f7e9f9002801d1002000e0012002bc0847
compiled: 00b525f7e9f9002800d0012002bc0847
```

The push, typed BL to 08005BB0, and full-word compare are identical. At E07E0
the ROM branches on nonzero to E07E6, explicitly writes zero otherwise, then
jumps to its return at E07E8. The candidate instead branches on zero directly
to its return at E07E4, retaining the already-zero r0, and writes one on the
nonzero path. Thus the candidate has two fewer instructions. Nine bytes match
at equal offsets (nine of the target's 20); seven overlapping bytes differ,
and four target tail bytes have no compiled counterpart. Three of nine ROM
instructions are identical at equal addresses. These are positional
diagnostics, not a semantic-match percentage.

Both original and linked .text sections are exactly 16 bytes, with a single
16-byte Thumb function symbol and no literals or external alignment to credit.
The original ELF has one R_ARM_THM_CALL at offset 2 for func_08005BB0; the linked
body has no unresolved symbols or remaining relocations. Static typed binding,
complete-symbol ownership and CFG checks pass, as does the source plausibility
check. Those checks do not override the extent mismatch.

## Evidence and limits

The one source, all nine unchanged headers, private mappings and tools were
hashed and the freeze serialized/read back before the explicit compile-start
record. The immutable source equals this payload. No output-driven source,
type, flag, branch-order or register alternatives were tried. No native or
emulator campaign ran after the nonmatch. This attempt does not prove that all
natural source forms fail or identify the original nominal return typedef.

The existing matched callee reads u16 at object+0x14 and returns whether it is
two. Readable aligned storage and ordinary ABI continuation are preconditions;
there is no invented null check or allocation/lifetime guarantee. The inventory's
8 KiB incoming-pattern scan had no hits, not a proof of global absence or use.
E07EC starts a separate cleanup body and is not target padding or target code.

Only this C file and this README are the proposed Parked payload. Retained
evidence is outside the integration payload, at these explicit paths:

- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/HANDOFF.md`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/freeze.json`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/compile-start.json`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/canonical.log`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/elf-capture.json`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/verification.json`
- `/home/user/.codex-work/ffta-ulw/080E07D8-author-next/DISASSEMBLY.md`

The retained ELF capture contains both complete raw files as hexadecimal text,
plus every section, symbol, relocation and linked function byte. The separate
metadata.patch proposes only the independently qualified E07D8 index addition;
it earns no C-match credit and is not silently included in this Parked payload.
