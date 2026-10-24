# 081453B0: one frozen nonmatching candidate

**NONMATCH. Only this C file and README are proposed for Parked preservation;
no matching-source integration, report promotion or match credit is claimed.**

One natural candidate was frozen before one canonical compilation with agbcc
`-mthumb-interwork -O2`. There were no source revisions, flag changes, spelling
searches or retry compilations. The candidate SHA-256 is
`65f9362a606f42a4b164ad958ca7ab489b3a8e430d5e0394177e5542c9e713f5`.

## Local source contract

The input is a state pointer with an unsigned byte count at +8 and a track
pointer at +0x2C under the 32-bit target ABI. Each track occupies 0x50 bytes.
The byte count is promoted to signed `int`, captured once, and decremented
until zero. A zero count causes no track accesses or calls, although the state
and its track-pointer field are still read. A valid state and a valid array of
at least the counted tracks are preconditions; no allocation bounds are proved.

For each track, both flag masks 0x80 and 0x40 must be set. That path calls
08145528 with the track pointer, then writes bytes 0x80, 2, 0x40, 0x16 and 1 at
offsets 0, 0x0F, 0x13, 0x19 and 0x24 respectively, in that order. All other
track bytes are directly untouched by this caller. The unknown regions and
field names are intentionally uninterpreted; original public types and musical
meanings are not recovered.

The declared `void func_08145528(void *)` is a local interface hypothesis:
the observed wrapper forwards r0, loads a callback into r1 from global
02008EEC, and calls the register-dispatch stub at 08142248. It discards the
callback result when restoring its return word. Other bounded inventory code
also passes a state pointer to this wrapper, so its argument is opaque rather
than assumed exclusively a track. The actual callback, its side effects and
its returning/preservation contract are not proved. Ordinary returning ARM ABI
behavior and valid memory remain assumptions for this caller interpretation.

## Exact failure

The complete ROM target is `[081453B0,081453F8)`: **72 bytes, 35 instructions,
no literal pool or owned trailing alignment**. The actual emitted ELF function
is **64 bytes, 31 instructions**, ending at 081453F0. Its `.text` is exactly
64 bytes; no hidden helper, pool, padding or extra allocated payload explains
the shortfall. The canonical matcher exits 1 with:

```text
compiled symbol is shorter than the indexed span: 64 < 72
```

The compiler combines the two source flag tests into `(flags & 0xC0) == 0xC0`.
The ROM instead tests masks 0x80 and 0x40 separately, saves r4-r7, and retains
those constants in r7/r6 across the call. The candidate saves only r4/r5 and
materializes those constants after the call. Branch targets, call displacement,
store registers and epilogue location consequently differ. The flag predicates
are algebraically equivalent for an unsigned byte; no executed C/ROM/compiled
equivalence test or claim is made.

At identical offsets, **10 bytes agree, 54 common positions differ, and eight
ROM tail bytes have no corresponding emitted symbol byte**. These are
positional counts, not an instruction-aligned score. The canonical extent
failure occurs after typed linking and local CFG/literal guards, but before
plausibility checking and report generation. No canonical match report or
aligned-score result exists.
A separate source-only plausibility check reports zero findings, without an
allow-list exemption; this does not override the failed extent gate.

## Retained evidence and limits

Full author bundle:
`/home/user/.codex-work/ffta-ulw/081453B0-author-next/`.

- `freeze.json` binds the original candidate, all nine unchanged headers and
  the actual mapping/index input snapshots before compilation.
- `canonical.log` records the single attempt. `run-canonical.py` invokes the
  unchanged matcher main and observes original `Runner.read_binary` outputs
  to capture that same invocation's ELF files; returned bytes and gates are
  unchanged. `capture.json` describes this observation.
- `original-elf.txt`, `linked-elf.txt`, `disassembly.txt`, `results.json` and
  `exact-diff.txt` retain ELF ownership, the complete target/emitted hex,
  bounded callee observations and every positional difference.
- `inspect-result.py` checks those actual generated ELF files, target comment,
  relocation and all frozen inputs. It passed before binary cleanup. Rerunning
  it requires regenerating the two captured build objects; those binaries are
  deliberately not retained. Text evidence and complete byte strings remain.
- `plausibility.json`, `CHRONOLOGY.md`, `HANDOFF.md` and `SHA256SUMS` retain the
  remaining result and provenance. No native or emulator execution was run.

The original object has one `R_ARM_THM_CALL` at +0x16 to 08145528; the linked
ELF resolves it to the unique aligned indexed Thumb target, with no remaining
relocations. This demonstrates typed link production, not completion of the
canonical verifier after its extent rejection or transitive callback proof.

Legacy metadata lists 36 instructions and an addressed symbol size of ten
bytes. The bounded ROM evidence instead gives 35 actual instructions and 72
bytes. Those potential corrections remain coordinator-owned and are not part
of this two-file payload. This single failed candidate does not establish that
all honest source reconstructions are impossible.
