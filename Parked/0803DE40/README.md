# 0803DE40: recovered, not byte exact

The accepted target is the complete function at `0803DE40..0803E078`:
568 bytes and 214 reachable Thumb instructions. This attempt has zero C-match
credit.

The preserved C reconstructs the four observed states (0, 1, 2 and 253),
the two transfer-busy checks, resource selection, both resource-copy paths,
command submission, completion polling and final sentinel writes. The global
pointer is reloaded after calls where the ROM reloads it; the final state also
retains the earlier record pointer for its first completion write. External
objects use the private fixture's existing evidence-backed data bindings.

Two natural candidates were tested with the unchanged native matcher and
fixed `agbcc -mthumb-interwork -O2` configuration. The preserved first candidate
emits one 568-byte ELF function. Native matching reached the byte comparison
and source plausibility gate, reported `source plausible`, then exited 1 with
`NOT MATCHING - bytes differ`. Its compiled CFG has 196 instructions versus
the target's 214. The native diff reports 124/196 instructions identical and
454/568 bytes identical; these metrics do not establish a match.

Concrete residual differences include:

- The compiled switch tests state 1 first; the target tests state 2 first.
- The initial global-pointer load and record-offset multiplication have a
  different evaluation/register schedule.
- The resource-pointer field becomes the relocated literal `085669FC`,
  whereas the target loads the mapped `085668B0` base and adds `0x14C`.
- The transfer enable store uses a `0x135` address constant; the target
  forms record 4's `0x130` base and stores its byte field at offset 5.
- Several resource-index calculations, post-call reloads and the final
  sentinel stores have different instruction/register sequences.

A second candidate used an explicit initial state local, a typed entries
member at offset `0x6C`, a const-correct secondary pointer and a `-1` final
sentinel. The native extent gate rejected it before plausibility or full
matching: `compiled symbol is shorter than the indexed span: 564 < 568`.
The first tested candidate was restored and its original compiler ELF was
captured again; its sole function remains exactly 568 bytes. No extra cases,
artificial reads, assembly, volatile qualifiers, compiler flags or metadata
changes were used to force the remaining shape.

Immutable address-owned evidence is outside the disposable matching root at
`/home/user/.codex-work/ffta-ulw/audio-following-v692-matching/0803DE40/`:
`attempt-1.log`, `attempt-2.log`, `attempted-report.md`, `compiled.s`,
`original.o` and `result.json`. The active unmatched source and match report
were removed. Parent integration owns reservation release.
