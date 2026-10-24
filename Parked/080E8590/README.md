# 080E8590: preserved first-candidate nonmatch

**NONMATCH; zero match credit.** Exactly one natural candidate was frozen and
compiled once with literal `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`.
No source, type, order, register, flag or spelling retry followed the output.
No native campaign was run. This is a preservation payload, not source admission
or runtime equivalence.

## Actual result and ownership

The canonical diagnostic is:

```text
compiled symbol is shorter than the indexed span: 558 < 560
```

The canonical main raises SystemExit with that string; it does not return an
integer. The observer preserves the exact diagnostic and null main return,
and the real process exits1. Typed linking and structural checks completed
before this size gate. Canonical report generation and the canonical
plausibility stage were not reached. There is no canonical match report.
A subsequent read-only source plausibility check reports zero findings,
without waiver; that separate check does not establish a match.

| Owner | Bytes | Reached instructions | Code / literals / internal alignment |
| --- | ---: | ---: | --- |
| ROM [080E8590,080E87C0) | 560 | 231 | 496 / 56 / 8 |
| Complete original/linked function symbol | 558 | 233 | 500 / 52 / 6 |

Both original and linked `.text` sections are560 bytes, but their final
`c046` is **outside the 558-byte function symbol**. It cannot fill the missing
target bytes or acquire ownership. Within the actual target, the complete
linked function gives **164 positionally equal bytes, 394 different bytes,
and two missing bytes** at080E87BE/080E87BF (target `0847`). There are no excess
symbol bytes and no external ROM bytes in this comparison. Forty-five reached
instructions have identical bytes at the same target offsets; no aligned/LCS
metric or literal-as-code display is used as match evidence.

Observed differences include changed register allocation and address
construction, 24 rather than28 saved-register bytes, shifted pool/branch/call
positions and a different epilogue. Both local allocations are16 bytes. The
compiled body has more reached instructions despite its shorter total symbol.
These observations are not a proven single cause or a future-impossibility
claim. No extra assembly, padding or source rewrite was used to close the gap.

## Compatible recovery and preconditions

The local registration atE89AC passes callback080E8591 with payload52 decimal
bytes. The compatible ABI is full-word-zero `u32(task, descriptor, payload)`.
Offsets below are hexadecimal. Descriptor phase is u16+0, object pointer+4,
selector/flags halfwords+14/+16. Payload selector/flags are bytes+0/+1, signed
coordinates+2/+4, wrapper+8, underlying+C, resource+10, untyped storage+14,
coordinate child+1C, sequence child+20, two-slot array+24/+28, effect child+2C
and record child+30. Unknown bytes and the storage's downstream capacity are
not inferred from the surrounding fields.

Phase0 narrows selector/flags, calls DD748 with NULL optional z output, and
retains the projected-coordinate and forwarded -2/DE268 effects. It neither
initializes later child/resource slots nor advances phase. Phase100 retains
creation order, selector/flag reloads across effects, D4724's scalar **41
decimal**, DCFE4's separate delay-byte expressions and post-call phase reload.
RAM03000940 receives the observed halfword mask update.

Phase101 always polls resource, coordinate, sequence and the two-slot helper
in order, even after a nonnull earlier result. Mask clearing requires an
old-nonnull/new-null resource transition. The helper result is explicitly
tested only after low8 narrowing. Phase102 polls+2C; child+30 is unpolled.
Valid selectors, phase order, stored pointers and external initialization
remain preconditions; D6134 has no initial null guard. No invented guard,
zero store, cleanup, allocator freshness or asynchronous lifetime proof is
added. Typed direct-call summaries are not recursive callee equivalence.

## Retained evidence

Full immutable author bundle:
`/home/user/.codex-work/ffta-ulw/080E8590-author-next`.

- `ABI.md` records semantic/type decisions before compilation. `freeze.json`
  and `compile-start.json` establish freeze-before-compile chronology and bind
  the source, all nine unchanged headers, current maps, tools and support seals.
- `elf-capture.json` retains the complete genuine original2000-byte ELF and
  linked3092-byte ELF, linked symbol bytes, compiler assembly and commands from
  the sole canonical invocation. `compiler-output.txt` is the captured assembly,
  not an edited input. Seventeen genuine R_ARM_THM_CALL relocations resolve to
  sixteen indexed targets; no linked relocation, undefined symbol, helper or
  other nonempty allocated section remains.
- `canonical.log` and `process-exit.txt` preserve the failure and real status.
  `verification.json`, `BODY-DIFF.md` and `exact-diff.txt` retain complete owned
  partitions and every differing/missing position. The verification script
  only reparses retained bytes; it does not compile or link again.
- Frozen source SHA256:
  `e5a8fa456466bf09b9c3375656dbc20100356886a7e1b12ebd3209a599846b64`.
  Source plus nine-header fingerprint:
  `3e66e4667a091b53d1e0a38d9f18a2be9c9bd659aa7eb960c697140e531e1790`.
- Current functions map SHA256:
  `f596e6796b52306a76bc7913b8ab5faa0cf722514ddf7c5876820d1363c31d71`;
  actual `match.py` SHA256:
  `6d201276ae8195ca19879d8413da23f9bbea5451cd388ea8f30d9f64fe72aa36`.
  Approved ROM SHA1 is `4ac05441f4de70a4ec3dd932116346c61b8783d9`.

Only this unchanged C and README are proposed for Parked integration. No
metadata change or failed report is proposed; the current approved maps were
copied unchanged. No source-completion credit is claimed.
