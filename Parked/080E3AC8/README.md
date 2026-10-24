# 080E3AC8 — first natural candidate, NONMATCH

The sole candidate was compiled once with the canonical default
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. It is preserved unchanged here.
There were no source/type/order/flag retries, assembly edits, native tests or
runtime-equivalence claims. This is Parked evidence, not compiled match credit.

## Exact failure and ownership

Canonical process exit: **1**. The actual SystemExit string was:

```text
compiled symbol is shorter than the indexed span: 314 < 322
```

The passive observer's `main` return event was `None` on this exceptional exit;
it is not a successful return. No canonical match report was written.

| Body | Owned bytes | Reached instructions | Code / literals / alignment |
| --- | ---: | ---: | --- |
| ROM [080E3AC8,080E3C0A) | 322 | 141 | 296 / 24 / 2 |
| Complete compiled function symbol | 314 | 139 | 292 / 20 / 2 |

The compiler's 316-byte `.text` includes external `c046` after its 314-byte
function symbol; that filler is excluded. ROM's `0000` at E3C0A..E3C0C is also
external and excluded. A positional comparison restricted to the owned target
finds 46 equal positions, 268 differing present positions and eight target-tail
positions absent from the compiler symbol. These counts do not equate displaced
instructions or fill in missing bytes. Both complete raw ELF images are retained
in the full author bundle, not merely a candidate-sized ROM display.

The first difference is offset 0xA, E3AD2: ROM `8046` (`mov r8, r0`) versus
compiled `071c` (`adds r7, r0, #0`). Register assignments and pool placement differ.
The compiler hoists the 08396820 duration-table base before phase dispatch, and
derives 083967CC by subtracting 15 from 083967DB instead of emitting the separate
pointer-table literal. This accounts for one fewer literal word, but is not a
complete semantic proof or a proposed source rewrite. The two duration byte
loads remain separate. Both bodies retain the seven dependency calls, phase
reloads and 16-byte outgoing frame with 28 saved bytes. No attempt was made to
steer those observed allocation or literal-placement choices.

## Recovery and assumptions

The callback has the compatible scheduler ABI `u32(void *, void *, void *)`.
Phase zero copies/narrows selector and flags, forwards two signed-halfword output
addresses and stores the underlying object. Phase 0x100 creates the coordinate,
effect and sound children in order and then reloads/increments phase. Phases
0x101 and 0x102 poll only the first two children; other phases return zero.
There is no invented initialization, selector bounds check, extra third-child
wait or null guard.

Numeric ROM table views preserve observed byte/pointer access widths and
20-/8-byte row strides without fabricated named-data entries or table bounds.
DD5A8 is observed through signed low8, then normalized; its actual ROM returns
0/1, while its published C remains Parked. Narrow callee declarations are
compatible ABI choices, not uniquely recovered original typedefs. Selector
validity, object/storage lifetime, initialization, scheduler copying and direct
callee return/preservation remain ordinary assumptions, not recursive proofs.

Fresh static reparse verifies complete ARM Thumb original/linked ELF ownership,
all seven original `R_ARM_THM_CALL` relocations, unique indexed callees and no
linked residuals/undefined symbols/helpers/other nonempty allocated sections.
The unchanged ordinary framed verifier accepts the actual 314-byte candidate
CFG. This does not make its bytes match the 322-byte target.

A separate, source-only `plausible.py` check exited 1 with five `SUSPECT:
rom-address` findings, one per numeric table-pointer initializer. Its heuristic
requires an inline justification that the frozen source does not contain.
The five addresses/access widths are independently witnessed and documented
before compilation in ABI.md, but that is not an automatic gate waiver. No
inline comment, numeric spelling, named mapping or source change was added in
response. The exact check output is retained as plausibility.log. This candidate
has neither byte-match approval nor automatic plausibility approval.

## Immutable evidence and integration

Only this README and `080E3AC8.c` are the proposed Parked integration payload.
Full retained evidence lives at
`/home/user/.codex-work/ffta-ulw/080E3AC8-author-next/`:
`ABI.md`, `freeze.json`, `compile-start.json`, `canonical.log`, `process-exit.txt`,
`elf-capture.json`, `verification.json`, `DISASSEMBLY.md`, and `HANDOFF.md`.
Source SHA256 (including the precompile target-byte comment):
`7445f1f393f97992e95023579af465f6ac68832216d13a42807b8c8ec095ebe3`.
Source plus all nine headers fingerprint:
`b45c20704410c01903463da04d114312f57439b2bb9853f0fa12196bc390655c`.
Full capture SHA256:
`15164e1daee5b2d3bdd5ae2c36000af34e0e5838bbb2fec45bad97a05a9b558b`.

The separately approved three-entry metadata patch changes only instruction
counts and legacy symbol sizes for E28C4/E2FA4/E3AC8. It changes neither this
target's endpoint nor data mappings. Root already applied that patch; this
Parked payload is not a request to reapply it or credit another function.
