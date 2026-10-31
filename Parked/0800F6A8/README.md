# 0800F6A8: complete compiled extent mismatch

Target: [0x0800F6A8, 0x0800F770), 200 bytes and 96 reached instructions.
The single retained natural form uses a genuine 44-byte automatic state,
the actual five-argument 080075CC interface and one-argument 080076A0
interface, and the existing mapped byte data_02009160. It preserves the
observed low-halfword coordinate behavior, signed row narrowing, conditional
record stores and helper order. The first two historical formal widths are
not recovered; the retained declaration is a compatible low-halfword ABI view.

One original native attempt used the existing named-data-buffer-v1 selector
and the fixed -mthumb-interwork -O2 toolchain. It exited 1 at the complete
indexed-span guard (inert_spin_profile.py:86), before emitting a report.
This is not evidence of an unsupported buffer operation: the guard was
reached before the buffer-effect checks.

One authorized compiler-only diagnostic of the unchanged source emitted a
complete 184-byte ELF function symbol, 16 bytes shorter than the target.
The complete linked bytes, original ELF, assembly, disassembly, byte diff,
commands and tool pins are retained in state/matching-0800F6A8-author/.
The compiled form saves R8/R9, while the target saves R8/R9/R10. Both allocate
52 local/outgoing bytes. The compiled form also omits the target's separate
coordinate sign-extension operations before the two halfword-store arms.
No definite semantic source bug was identified from this diagnostic, and no
second form or native retry was performed. No profile refusal is inferred
from this ordinary compiled-extent mismatch; no MATCH is claimed.

Original source SHA-256:
985174f071fa8e730820516311e00b3aaf003718f6c3e9a3215772c7904261d2

Complete compiled symbol SHA-256:
54ed1ca0ae2df38c83a55762c0519a9534703ae5df82409d0ddd395a0882e15c

Complete target SHA-256:
fc223de5fa4d5443b77615f3d5b92cba8d0331bfb5e3e9f8c20b3dfacf76f7fb

No compiler flags, ABI/prototype changes, assembly, volatile, pragmas, filler,
extra bounds, source reshaping or successful proof replay were used.
