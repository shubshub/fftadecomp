# 080098F4 — first natural form, Parked only

## Verdict and ownership

**NOT MATCHING.** The first natural source is plausible, but its complete
44-byte symbol differs from the complete 44-byte ROM body. It remains frozen
at SHA256 `ea43f4b6719d4785f5a618f0298ed7c0ca485aa0d36b2b03ef44865d8ed6ece6`.
No source iteration, alternate return type, flag sweep, assembly, volatile,
pragma, forced register allocation or compiler-steering change was attempted.
This directory is an isolated author handoff for `Parked/080098F4`, not an
active source or a MATCH report. No production file was changed. Root owns
reservation release, independent review, metadata integration and publication.

Baseline: immutable `game-next-89c9cb3`, 504 active sources; toolkit:
`kit-software-double-candidate-v3`. The compiler and binutils, full toolkit,
all source-path headers, maps, ROM, existing registration declarations, parent
ROM dump and frozen interface proposal are pinned in `input-pins.json`.

## Reconstructed contract

The function accepts a callback word in r0 and an opaque full 32-bit context
in r1. It scans four 8-byte records at `03000890`, each with context at+0 and
callback at+4. It reads callback fields in ascending slot order. At the first
zero callback field it stores the supplied callback word at+4, then stores
the context at+0, and returns that slot index. A full table returns zero
without table writes. The zero result therefore does not distinguish a full
table from successful allocation of slot zero.

There is no incoming callback-null guard: a null callback is stored along
with its context and the selected slot remains available to later scans.
The registration function invokes no callbacks or helpers. Its own stack
usage is exactly 8 saved bytes; the leaf preserves r4-r11 and restores SP.

The private callback type is `u16 (*)(u32 context)`, following the separately
grounded `080098C4-review/TYPE-PROPOSAL.md`. The actual dispatcher loads the
stored context into r0 and tests the callback's returned low 16 bits. This is
a coherent reconstructed interface, not proof of the original nominal type.
The current scope does not re-execute that dispatcher or prove a future
callback's behavior merely by storing its address.

### Why the registration result remains u8

Both inspected existing registration declarations return u8:
`Parked/08008D50/08008D50.c:70` and
`Parked/08008954/08008954.c:46`. The frozen interface proposal deliberately
retains that scalar convention while correcting the incompatible callback
parameter type. This first source follows that convention, not a speculative
attempt to identify a unique historical return type.

The ROM produces full-register values 0, 1, 2 or 3 on its bounded paths; the
finite cases observe each of those values. These values fit u8, u16 and u32.
The ROM's direct register move does **not** uniquely establish which nominal
C return type was originally declared. The candidate's explicit compiler-
generated u8 result narrowing is a real byte discrepancy, not a semantic
reason to revise a compatible interface. No return-type change was made to
remove the narrowing or to seek a match.

Other owners must update the two known registration callers' callback
declarations and their callback definitions consistently with the proposal.
Those edits are outside this directory. Unrelated callback families passed
through 08013404 are not part of this contract.

## Complete extent and exact discrepancy

The indexed extent `[080098F4,08009920)` is correct. The target contains
19 reachable Thumb instructions /38 code bytes, a two-byte unreachable zero
alignment at `0800990A`, and one four-byte literal `03000890` at `0800990C`.
The target has no calls. The proposed metadata repair is count-only, 22 to19
in both indexes; `metadata-proposal.patch` does not change endpoints or any
other row and has not been applied to production or the fixture.

The candidate is one complete Thumb FUNC symbol of44 bytes and `.text`44,
alignment4, with20 instructions /40 code bytes and the same literal at+24.
It has no remaining alignment bytes, relocations, extra functions or nonempty
allocated sections. Original ELF, independent no-relocation link, linked ELF
and objcopy agree on the same complete candidate bytes. The diagnostic link
does not bypass or replace the official matcher's complete-symbol decision.

Differences are:

- The index initialization and literal load exchange order at+4/+6.
- At+18 the target returns the index with a register move. The candidate
  narrows it with `lsls #24; lsrs #24`; its branch occupies the target's
  internal alignment at+22. The literal remains at+24 in both bodies.
- Pointer and index increments exchange order at+28/+30.

There are13 differing byte positions, offsets4–7,19–23 and28–31, hence31/44
same-offset bytes agree. The official output's36/44 byte number is a
sequence-alignment metric, not same-offset equality; its16/20 instruction
figure is likewise not a complete CFG instruction count. `CLASSIFIED.txt`
and `build.json` retain full bodies, classifications and all discrepancy
positions. No prefix, padding truncation or pool exclusion is used.

Target body SHA256:
`4e34740247679c9b4155bc20fc3617459318249d8a4cbe735e80c2b52725de57`.
Candidate body SHA256:
`0aeb26d97c6753bf4404f7327f9c50d1facf7873281ddae5ab63a85df246c789`.

## Fresh validation and explicit limits

`check.py` reproduces official `--mode thumb --no-write` exit1, plausible
source and `NOT MATCHING - bytes differ`. The original first official output
is preserved separately. No MATCH report exists; strict MATCH-report replay
is therefore not applicable and is not claimed.

Eight target-compiler scalar/layout assertions and the matching typed
registration redeclaration/assignment pass. Three incompatible callback
declarations fail compilation: old u8(void), wrong parameter list alone, and
wrong return type alone. The target source remains unchanged throughout.

The bounded runtime matrix covers all16 occupied-slot masks, null and
non-null incoming callbacks, and contexts0/12345678/80000000/FFFFFFFF:
128 ROM/candidate pairs,256 executions. It compares the independently
specified exact ordered table/pool/stack access trace, every byte of EWRAM
and IWRAM including stack writes, return result, return instruction mode,
r4-r12/LR and restored SP. The matrix varies register/RAM seeds, ARM/Thumb
returns and SP alignment modulo8 and reaches all19 target and20 candidate
instructions. Six machine mutations are rejected: wrong stride, three-slot
bound, reversed occupancy branch, byte-only context store, callback stored
to the wrong field, and incorrect successful slot result. Mutations affect
only transient emulator bytes, not source or the stored candidate.

No helper or callback is modeled or executed here. Stored nonzero callback
words are data during registration; their eventual type compatibility,
live code identity, lifetime and semantics require the separately reviewed
scheduler-family work. Valid live aligned four-record RAM storage, a valid
ABI, readable ROM pool and a disjoint valid stack are preconditions. Absolute
target-RAM addressing is target-specific, not portable hosted C. Tests do not
establish arbitrary aliases, interrupts, concurrent registration, reentrancy,
atomic publication of the two stores, every possible RAM state or whole-game
equivalence. In particular, callback-first/context-second store ordering is
preserved rather than silently strengthened to an atomic registration.

## Reproduce and cleanup

Run in an owned sibling copy of this evidence directory, preserving the
named immutable inputs; do not overwrite this final freeze:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py > check.log 2>&1
```

All temporary game fixtures and object/assembly/linked binaries are removed
by the checker. Only small text evidence remains. The metadata patch is a
proposal for parent review, not authority to change shared indexes. The
finished outcome is **honest Parked author evidence**, not exact-match credit.
