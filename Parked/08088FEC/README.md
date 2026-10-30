# 08088FEC: bounded natural-source byte mismatch

Target: complete [0x08088FEC, 0x080891BC), 464 bytes. The original bounded owner
graph has 200 reached instructions, 408 code bytes, 52 referenced literal bytes
and 4 canonical zero alignment bytes. No boundary or mapping change was made.

The retained source is the third natural form, with scoped pointers to the option
byte being updated and a typed descriptor pointer for the no-direction refresh.
The native report binds this exact source and its headers. It admits the complete
464-byte symbol and reports plausible source, but NOT MATCHING: 441/464 aligned
bytes and 171/197 instructions in the native comparison. The 197 denominator is
from the compiled comparison; it is not the original owner's 200-instruction count.
The exact complete ROM and compiled bodies are retained in the native report and
source-bound author receipt. Aligned match counts are not same-offset byte counts.

The remaining differences are ordinary compiler control-flow/address formation:
- The compiler shares the 0x40 guard's compare/branch tail with the later guard,
  whereas the ROM keeps that compare/branch locally. Subsequent branches, calls
  and literal-pool placement change with the shortened control flow.
- In the no-direction refresh, a typed descriptor pointer computes the record's
  +4 base and accesses bytes+1/+2. The ROM keeps the selector in r5, uses the
  object-relative record base, and accesses bytes+5/+6. Registers and alignment
  differ accordingly.

The source preserves the actual pending bit clear, input order80/40/10/20,
visible/enabled high-bit guards, writer/sound ABI, opaque-call reloads, old-option
save, mask only on the stored option, full original u8 destination for lookup,
and coordinate/extra-field update order. It uses the existing defining record
writer, same-object constructor layout and ordinary sound declaration evidence.
No independent semantic equivalence or callee contract proof is claimed.

All native checks used:
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x08088FEC
from the isolated batch3 game-worktree, with -mthumb-interwork -O2.

Bounded forms:
1. One function-wide destination byte. Native exit1: compiled symbol324 <464;
   no native report or source-plausibility result was generated.
2. A destination byte scoped to each branch. Native exit1: compiled symbol324
   <464, again without a report. One compile-only diagnostic showed merged
   update/guard tails and option reloads. It used the native compiler API with
   root explicitly pinned to the isolated worktree; no admission proof ran.
3. Scoped pointer to the edited option byte in each branch, plus a typed pointer
   for the no-direction descriptor refresh. Native exit1: complete464-byte
   source-plausible mismatch described above. This exact source/report is parked.

Accounting: three natural forms and three native match commands, two shorter-symbol
refusals, one complete plausible byte mismatch, one additional compile-only
diagnostic, zero native matches, zero successful replays. No assembly, volatile,
pragmas, dead operations, synthetic constants, invented ABI arguments, shared
input edits, boundary changes or native gate workarounds were used.

The machine/runtime, compiler and tool hashes, source/header fingerprint, all
three actual map hashes, exact commands, failed logs, source snapshots, complete
body comparison and diagnostic accounting are in:
state/matching-08088FEC-author/receipt.json
