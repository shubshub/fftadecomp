# 0x080651C8: exact bytes, unsupported descriptor callback proof

Parked only. The first natural candidate reproduces the complete ROM symbol,
but the official matcher rejects the outgoing descriptor's dynamic callback
boundary. There is no active source or valid match report and no claim of a
verified MATCH or inherent unmatchability.

## Complete extent and diagnostic result

Target `[0x080651C8,0x080651FA)` is 50 bytes / 20 instructions:

- Code `[0x080651C8,0x080651DE)` and `[0x080651E4,0x080651FA)`: 44 bytes.
- Internal zero halfword `[0x080651DE,0x080651E0)`.
- Literal at 0x080651E0: 0x00000103.
- Following ROM zero halfword `[0x080651FA,0x080651FC)` is external.

The unchanged frozen 4847c93 compiler/linker machinery, with standard
`-mthumb-interwork -O2`, independently emits exactly one 50-byte FUNC.
Typed BL relocations bind 0x080651CC to 0x08005BFC and 0x080651F0 to
0x08005C04; the linked ELF has no unresolved relocations. All 50 symbol
bytes, including the literal and internal zero halfword, equal ROM.
The emitted `.text` is 52 bytes because an external C046 NOP follows the
function; that padding is not included in the comparison.

Target and complete candidate SHA256 are both
`853181285b734f7bd65eb38dde99797fe8b18a9a230d935661861918b6cd1a87`.
These are separate typed-link diagnostics, not an official verifier verdict.
There is no remaining compiler byte difference in this candidate.

The official command rejects with:

```text
buffer callee 0x08005C04: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification
```

The buffer proof follows the descriptor through 0x08005C04 to its real BX-r3
thunk and cannot close the dynamic callback boundary. No helper substitution,
purity assumption, verifier patch, metadata bypass or source trick was used.
No valid report or successful replay is claimed.

## Natural source and contracts

The compatible caller is `void func_080651C8(void *task)`. The existing
`void *func_08005BFC(void *)` helper returns task+0x18. The caller reads
payload byte+0x08, sets only descriptor halfword zero to 0x103 when kind
equals seven and otherwise 0x106, then reads payload word+0x10 as the task
forwarded to `u32 func_08005C04(void *, void *)`. Its result is discarded.
There are no added guards, initialized remainder bytes or extra inputs.

The local 28-byte descriptor is grounded by the observed frame and the
existing task engine's 28-byte descriptor-copy convention. Its first
halfword is the event; the remaining 26 bytes remain uninitialized.
The target compiler verifies descriptor size 28/alignment 4/offsets 0 and 2,
and the payload view size 20/alignment 4/kind offset 8/task offset 0x10.
Opaque members describe observed storage, not forced frame padding.

Actual 0x08005C04 is 16 bytes / seven instructions. It overwrites incoming
r2 with forwarded task+0x18 and incoming r3 with the task's first word, then
dispatches through real 0x08142250 with `(task, descriptor, task+0x18)`.
It does not itself read, copy, mutate or retain descriptor bytes; it forwards
the callback's full result unchanged. Original r2/r3 and incoming stack words
are not additional inputs to this helper. Its dynamic callback can still
read, mutate or retain the pointer and need not terminate.

Ordinary C requires valid aligned payload/task backing and a callback that
obeys the relevant ABI and descriptor lifetime/initialization contract.
The partially initialized remainder is not known to be zero or safe for
arbitrary typed reads. A retained pointer would outlive local storage after
return; no global no-retention, allocation, arbitrary-alias or termination
property has been proved. The source's naturalness check reports zero findings.

Only this one ordinary representation was attempted. Since its full bytes
already agree, alternate branch spellings, flags, storage layouts and helper
disguises would not resolve the actual proof limitation and were not tried.

## Bounded behavior and reproduction

The retained scoped reproducer is
`/home/user/.codex-work/ffta-ulw/080651C8-author/check.py`.
Run from the game with:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080651C8-author/check.py
```

It creates an isolated temporary source tree under its disk-backed scope,
reproduces the official rejection, performs fresh typed-link diagnostics and
layout checks, and removes all generated files. It does not edit game sources,
reports, mappings or toolkit code.

Eight paired fixtures / 16 executions run actual 5BFC, 5C04 and the BX-r3
thunk, with an explicitly modeled mutable callback. They cover both event
branches and all 20 caller, two getter, seven dispatcher and one thunk
instructions. An independent expected-access/call oracle checks exact order,
including the kind-seven literal load and stack accesses; paired traces,
complete synthetic RAM, saved registers, SP and return agree. Maximum stack
depth is 36 bytes: caller save+descriptor 32, dispatcher save four.

Six callback models use only the initialized event halfword and may mutate it
and the original payload kind. Two additional machine-only models inspect
and mutate the raw remainder bytes. The test driver observes all 28 raw frame
bytes to confirm that only the first two were initialized; this observation
does not make the remaining bytes initialized C values. Callback result and
caller-clobbered registers are varied, and two fixtures forward the original
task itself. All RAM/stack contents are synthetic fixtures; no real dynamic
callback behavior, retention policy or lifetime safety is claimed.

Only small reproducible scripts/logs remain in author scratch. No generated
object, ELF, binary, active source or active report remains for this address.
