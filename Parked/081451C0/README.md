# 081451C0: preserved nonmatching candidate

One natural-C candidate was frozen before one canonical compilation with
`agbcc -mthumb-interwork -O2`. No body revisions or further attempts were made.
**NONMATCH: no source integration or match credit is claimed.**

The canonical tool verified a complete 44-byte ELF function with typed Thumb
linking and no remaining relocations, but its bytes differ. At identical byte
positions, 16 of 44 bytes differ (28/44 identical); the tool's instruction-aligned
score is separately 12/17 instructions and 35/44 bytes. Table-address load
scheduling, selector register allocation and the two pool-word positions differ.
Exact offsets, ROM byte -> compiled byte:

```text
04:07->40 05:4A->0B 06:08->07 09:0B->18
0A:40->82 0B:18->88 0C:83->51 0D:88->00
0E:59->89 0F:00->18 10:C9->89 11:18->00
12:89->05 13:00->4A 24:24->48 28:48->24
```

The plausibility gate also reports two `SUSPECT: rom-address` findings for the
fixed table casts at 0814BB24 and 0814BB48 (original source lines 22 and 23).
They were not bypassed with an allow-list entry, named data or source steering.
No assertion is made that every natural source form is impossible.

This preservation copy adds only the required target-byte comment. Removing
that leading comment and blank line yields the exact frozen original file,
SHA-256 `4b9025cde7028d13b9957236961fe29154da6712d534325c3f83a63e72ef155b`.
The executable source body is unchanged. This comment-only copy was not
compiled; the original report remains bound to the original source fingerprint
and must not be represented as fresh verification of this copy.

Evidence bundle: `/home/user/.codex-work/ffta-ulw/081451C0-author-next/`.
Original candidate: `isolated/src/081451C0.c`; canonical report:
`isolated/docs/match/081451C0.md`; supporting files: `canonical.log`,
`chronology.jsonl`, `input-pins.json`, `HANDOFF.md`, `SHA256SUMS`.
Those frozen artifacts remain unchanged. `HANDOFF.md` records the observed
caller, table layout and direct callee-use facts. No separate raw callee/table
byte dump was retained; the earlier disassembly/table reads were terminal
output in the conversation, not an additional evidence file.
