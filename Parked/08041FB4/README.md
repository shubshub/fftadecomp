# 08041FB4: bounded native mismatch

Target: `[0x08041FB4,0x08042024)`, 112 bytes, 51 reached instructions.

The recovered routine copies rows through the actual three-argument CpuSet
wrapper. It maintains a u16 selection, calls the existing named
`s32 func_08142950(s32, s32)` routine with the selection and twice byte field17,
then uses the truncated result to select a source row. Width is snapshotted
from byte15; the destination advances by twice byte1E after each copy.
The defining helper08017B50 returns u16 from one record pointer.

The addressed remainder contract is the existing default typed direct-call
route. No C percent operator, percent-zero semantics, added guard, fabricated
alias, or new numeric theorem is used. Ordinary helper ABI assumptions remain
conditional; this candidate does not prove BIOS behavior or general callee
contracts.

All three default native checks exited1 with:

```
signed remainder caller requires exact complete mapped ROM bytes
```

The parent classified this combined owner/extent/byte guard as an ordinary
compiler mismatch because the complete target/index ownership pins pass.
No unsupported-model conclusion is claimed.

Attempts, retained under handover-root `state/matching-08041FB4-author/`:

1. `attempt-1`: halfword source/destination pointers, cached width, countdown
   row counter and separate u16 selection. One explicitly authorized
   compiler-only diagnostic of this unchanged source emitted108 bytes versus
   target112. It saves r8/r9 while the target also saves r10, and it reuses one
   cached width register for the source-offset calculation and CpuSet count.
   The target retains an additional width copy. Initial count/byte-load
   scheduling also differs. Full linked bytes, ELF, assembly, disassembly,
   diff, exact commands and input pins are in `compiler-only-diagnostic-1/`.
2. `attempt-2`: explicit byte-offset source/destination arithmetic, with the
   same actual field widths, snapshots and helper contracts. The native guard
   rejected it before exposing full compiled bytes. Its extent is not claimed.
3. `attempt-3`: forward row traversal from zero to the same truncated count,
   separate u16 selection and original halfword-pointer arithmetic. This is
   the exact source parked here. The same native guard rejected it before
   exposing full compiled bytes. Its extent is not claimed.

Native command for each distinct form:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08041FB4
```

Current function maps were696d16c2/938bd175, data map1f9c8183,
matcher933a72d9, actual host cpp13c48f8b1b and agbcc63deeb69.
All nine headers and all actual native binaries were freshly captured before
C and before every attempt. The old qualification capsule was preserved;
only the unrelated parent-approved52790 index repair changed those two maps.

No complete MATCH, source-plausibility pass, native generated report or M
credit was obtained. There were three natural forms and one authorized
compiler-only diagnostic. No second diagnostic, fourth form, success replay,
shared input edit or production toolkit change was made. This bounded result
is not a claim that the target is impossible to match.
