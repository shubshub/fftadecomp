# 080E7130: preserved first-candidate nonmatch

**NONMATCH, zero match credit.** One frozen natural C candidate was compiled
once with literal `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. The canonical
main return, SystemExit code and actual process exit are all 1. The source
plausibility gate reports `plausible`, with no finding or waiver; that does
not establish byte identity or runtime equivalence. No retry, post-output
source/type/ordering/flag change or native campaign occurred.

## Exact difference and ownership

| Body | Complete bytes | Reached instructions | Code / literals / alignment |
| --- | ---: | ---: | --- |
| ROM [080E7130,080E72B4) | 388 | 170 | 366 / 20 / 2 |
| Sole compiled ELF symbol | 400 | 175 | 376 / 20 / 4 |

Within the actual 388-byte ROM owner, **28 bytes are positionally equal and
360 differ**; none are absent. The compiler symbol has 12 additional bytes.
Its `.text` is also exactly 400 bytes, so there is no outside-symbol filler
to remove or count. Both bodies have all five referenced literal words inside
their own complete symbol envelopes, distinct from reached instructions.

The canonical report displays a 400-byte ROM diagnostic window. Its final
12 bytes `f0b5474680b48bb0061c0f1c` belong to the next entry 080E72B4, not to
this target. The report's **294/400 aligned bytes** and 83/161 displayed
instructions are not raw same-position counts or ownership credit. CFG
instruction counts above exclude literal/alignment misdecodes in that display.

Concrete differences include an additional saved high register (r10), changed
register allocation and conditional argument construction, moved literal pools,
branch/call displacement changes and a different epilogue. These are observed
differences, not a proven single root cause or proof that future evidence-led
recovery cannot match. Nothing was rewritten to chase them.

## Recovered contract and limits

E72B4 registers 080E7131 through 05B6C at E754A with payload size0x24.
The compatible public ABI is `u32(void *, void *, void *)`; every local path
returns zero. The descriptor phase is u16+0, object pointer+4 and flags u16+14.
Payload fields are flags byte+0, signed coordinates +2/+4/+6, wrapper+8,
underlying+C, resources[2] at+10/+14, auxiliary child+18, effect child+1C
and record child+20. Offsets are hexadecimal; unknown bytes remain unknown.

DD748's fourth argument here is an actual nonnull third `s16 *` output,
selecting DD760 -> DBD5C's unprojected triple. A null fourth argument would
instead select projected coordinates. DD748 also passes -2 to DD760, causing
the later DE268 call; it is not a pure getter or an invented numeric mode API.
The two D5E80 calls retain signed coordinate reloads, then 11058 receives -1
and +1. DD684's low-byte truth test and DD4D4's signed-halfword comparison
select the effect record. D5F24 receives the two-resource array and count2;
its caller tests the low byte. Phase and flags are reloaded across effects.

Auxiliary child+18 is assigned only on the DD684-true path, yet later polled
unconditionally in phase0x102. Its external initialization is unproved; no
zero store or protective guard was invented. Polling short-circuits before
effect child+1C; record child+20 remains unpolled. Record stride20 is observed,
not proof of an original table type, allocation extent or asynchronous lifetime.
Opaque direct-call summaries assume ABI preservation/return, not recursive
allocator or callee equivalence. DD4D4 remains a Parked dependency.

## Reproducible evidence

Immutable author bundle:
`/home/user/.codex-work/ffta-ulw/080E7130-author-next`.

- Preserved source SHA256:
  `21f14ac2bb49cfcfc5114b4e0c9ee616dbd6f7c491ae28d6b5e4f8a00340dcb4`.
- Source plus nine-header fingerprint:
  `66461a6cdb2f0bc3307e532e68fe4547db8e6ae31b47b44bc16442b0ee1589d1`.
- `ABI.md`, `preparation.json`, `freeze.json` and `compile-start.json` bind
  decisions, current maps/tools and successful freeze before the sole compile.
- `elf-capture.json` retains every byte of the genuine 1596-byte original ELF
  and 1600-byte linked ELF, sections/symbols and all 13 R_ARM_THM_CALL records
  to ten indexed targets. The linked image has no residual relocation, helper,
  undefined symbol or other nonempty allocated section.
- `canonical.log`, `process-exit.txt` and `isolatedroot/docs/match/080E7130.md`
  retain the unmodified canonical nonmatch and actual status. `verification.json`
  and `DISASSEMBLY.md` retain complete owned partitions and every positional
  difference. Read-only verification does not invoke the compiler again.

The current toolkit is acef82d; match.py SHA256 is
`6d201276ae8195ca19879d8413da23f9bbea5451cd388ea8f30d9f64fe72aa36`.
Private functions mapping SHA256 is
`4ede03ef974b0477f07e96ad2a0a2942e29c628d9d469456bc1f5573314ac104`.
The coordinator's approved three-entry metadata was copied unchanged, not
reapplied or expanded. All nine headers remain unchanged. Approved ROM SHA1:
`4ac05441f4de70a4ec3dd932116346c61b8783d9`.

Only this exact C/README pair is a proposed Parked payload. The diagnostic
report is evidence of nonmatch, not eligibility for `src/` or completion credit.
