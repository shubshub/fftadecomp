# 080069B0 — snapshotted transition constructor, not byte-matched

This is an honest **Parked recovery only**. Frozen `4847c93` official
verification exits one with `function-address caller differs from the ROM`.
There is no active source or match report, and no MATCH or cached-replay claim.

## Complete body and exact remaining difference

The complete target is `[0x080069B0,0x080069F4)`: **68 bytes / 29 instructions**.
Code occupies the first60 bytes; the trailing words at `0x080069EC` and
`0x080069F0` contain `0x03000940` and callback address `0x0800664D`.
No alignment gap, table or following-function bytes belong to this span.
The coordinating session applied the independently reviewed instruction
count correction from34 to29; the existing endpoints are unchanged.

The retained candidate has one complete **68-byte ELF FUNC and .text**,
29 instructions and both full trailing pool words. Diagnostic typed linking
resolves the ordinary call at `0x080069E0` to `08005B6C` and the function-address
literal to `0800664C`; no unresolved relocation remains. Full positional
comparison finds **52/68 equal bytes and 19/29 equal instructions**.

All ten differing instructions are at `0x080069BA` through `0x080069CC`:
the candidate loads the output base into r4 before materializing the descriptor
address, reads the first output into r5 and the second into r4, then computes
the packed pair. The target materializes the descriptor address first, loads
the output base into r5, reads and shifts the first byte in r4, then reads the
second byte into r5. The first descriptor store consequently uses r5 versus
r4. The candidate still reads `0x0300098C` before `0x0300098D`, once each.
Every instruction after the initial-pair store, the prologue, both literals,
call displacement, epilogue and complete extent agree.

Three grounded forms were tried at fixed `-mthumb-interwork -O2`:

- Direct struct-member packing produced80 bytes with an extra r8 save/restore.
- A byte-array view of the same observed offsets produced the same80 bytes.
- Explicit ordered byte snapshots produced the retained68-byte candidate.

The80-byte forms were rejected with
`function-address caller requires an exact mapped Thumb span`; their linked
SHA256 was `1cde5ca44b73b19d12e76a5ccefad35153773e7842f706ede232e2d294e89e2b`.
No flag sweep, inline assembly, volatile access, pragma, dummy branch, register
constraint or synthetic storage was used. Other natural forms are not claimed
exhausted.

## Positional interface, layout and effects

The compatible wrapper interface is
`void *(u8 target_first, u8 target_second, u16 duration, void *parent)`.
All four positions are genuine; original r3 is the full parent pointer.
No incoming stack position is consumed. The first two positions contribute
low8 and the third low16; the duration's original signed nominal type is not
uniquely determined. The full returned task pointer is forwarded unchanged.

Eight target-agbcc assertions establish a28-byte, four-aligned descriptor,
initial/target/duration halfwords at `+0x14/+0x16/+0x18`, two-byte u16 and
four-byte object/function pointers. The five unknown words are an observed
prefix view, not an assertion that those fields were originally word arrays.
The source's byte pointer exposes only the two evidenced output accesses;
the base literal is not proof of a complete global allocation.

The wrapper snapshots the two global bytes, packs the first as the high byte,
then stores initial pair, target pair and duration in that order. It calls
`08005B6C(callback0664C, 0x38, &descriptor, parent)` once. The44-byte local
stack depth is16 bytes of register saves plus28 descriptor bytes. There is
no post-call output reload, null check or duration guard.

## Partial descriptor and callback boundaries

Only six of28 descriptor bytes are initialized; the remaining22 bytes,
including `+0x1A/+0x1B`, are indeterminate and are not zero-filled. The reused
`task-5b6c-contract/CONTRACT.md` and engine audit establish that5954 reads all
seven descriptor words in ascending order before replacing local state with
zero. This machine copying does not prove arbitrary typed reads of the
indeterminate bytes valid in C.

The wrapper's generic callback declaration agrees with the active helper's
`u32 (*)(void *, void *, void *)` interface. The separately Parked0664C
definition instead has specific event/payload pointer parameters. These
declarations establish the same three-position machine ABI, **not compatible
C function types across those recoveries**. Coordinated callback declarations
are required before integration; no function-pointer cast or shared original
typedef is asserted to repair this boundary.

The engine retains the callback and nonnull parent and invokes the callback
with its own local descriptor. Event0 consumes the packed halfwords and signed
duration. Neither this wrapper nor the bounded tests establish arbitrary
callback read validity, retention/lifetime safety, allocator success, list
validity or transitive termination. The existing helper contract also retains
its manager reload, returned-task mutation and absence of a failure guard.

Raw frozen CFG checks on both complete bodies reject the outgoing descriptor
alias with `stack aliases cannot cross calls in caller-clobbered registers`.
This diagnostic is separate from the actual official byte rejection. An exact
future candidate would still require the supported outgoing-buffer proof path
with its function-address binding; this attempt does not establish acceptance
or rejection after that future byte check.

## Fresh bounded evidence

The self-cleaning reproducer makes an isolated root with current maps/headers
and a ROM symlink, reruns the official failure, checks the complete linked
ELF, asserts layouts and executes **six pairs / twelve executions** against
an independently expressed operation oracle. All29 caller instructions execute
on both sides. The fixtures cover zero/max and differing endpoints, duration
zero/one/0x7FFF/0x8000/0xFFFF, null/nonzero parent and distinctive full returns.
One additional fixture within those six supplies noncanonical upper bits and
arbitrary pointer patterns as a machine truncation/forwarding diagnostic;
it is not claimed to be a valid typed call to the real engine.

Each execution checks exactly two ordered global byte reads, three ordered
descriptor halfword writes, the four forwarded arguments, all28 descriptor
bytes including22 unchanged prefilled bytes, caller-saved clobber tolerance,
r4-r11/SP/return control,44-byte peak local stack depth and all synthetic
IWRAM. The explicit modeled5B6C boundary returns a chosen pointer and mutates
the global bytes; no later read is observed. The paired compared traces exclude
instruction fetches, literal reads and register-save/restore traffic. This is
finite local behavioral evidence, not blanket trace or source equivalence.

The real helper, engine, allocator and callback do **not** execute in these
fixtures; their properties come from the reused contracts. Prefilled emulator
stack bytes do not make the source's uninitialized descriptor bytes initialized.
Individual-source plausibility passes with zero findings.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  /home/user/.codex-work/ffta-ulw/scratch080069B0-author/check.py
```

Only the small reproducer and text evidence remain in owned scratch; compiler
objects, binaries, isolated roots and layout products self-clean. Parent owns
the mapping correction, reservation release and final checkpoint reporting.

- Source SHA256: `ea8011fbe70dabdca1593c6c29d962658bbe1e11dfd85af55b732ee8f3e3c1de`
- Target SHA256: `7a23867cc9a12f6f318f282c82e24838df5bf48c1c6dc56f4df3d324a4bc4704`
- Candidate SHA256: `5df4f6f33d9c21baaf5633eb00bb014128466da9a7bc404de7884f56931e60e9`
