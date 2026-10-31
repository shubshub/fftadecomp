# 0x080BE074: bounded coordinate candidate update

Complete indexed target: [0x080BE074,0x080BE1F4), 384 bytes and 185 reached
instructions, including two numeric literal words and two alignment bytes.

One natural source form was tested once with the fixed default native command:

```sh
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x080BE074
```

The original native run exited 1: source plausible, complete emitted symbol
388 bytes, NOT MATCHING. Its report records 109/188 aligned instructions and
308/388 bytes identical. The report compares its full 388-byte emitted extent,
so its ROM line extends four bytes past the actual indexed target. That is
preserved as original output, not an extension of this function's ownership.

The candidate saves R8/R9/R10 with a 32-byte saved frame; the target saves
R8/R9 with a 28-byte saved frame. The fifth incoming scalar therefore appears
at SP+0x20 versus target SP+0x1C. Coordinate byte conversions and register use
differ. The final stores have different address lowering; the candidate has
one trailing 0x1B3 word, while the target references 0x1B3 and 0x1B5.

The source retains unsigned stored/helper coordinate bytes and signed-byte
predicate/comparison views. The actual existing wide helper interface is
retained, with explicit low-byte views after both lookup calls. Original
historical qualifier/formal signedness is not uniquely inferred, and no table
allocation extent, memory mutability or helper termination theorem is claimed.
No concrete source semantic error was identified from the saved body.

No second source form, retry, compiler-only diagnostic or successful proof
replay was run. The original native report already contains the entire emitted
body, so no extra compilation was needed. This is a bounded unsuccessful
attempt, not a claim that natural C cannot match the target.

Exact original source SHA-256:
`b3317bd47fa6bad0e787821a590ee7b4067ac7d25b384ef6b961483d16cc19c1`.
Native source/header composite SHA-256:
`d8c0bb3952017c388b24d9c18c37a53a486408f5636aea152cb48a1f6b3ec7d6`.

Original stdout/stderr, report, complete emitted/target bodies, positional diff,
current-machine inputs and final receipt are retained under
`state/matching-080BE074-author/` at the handover root. Parent owns native
lease release and integration. The failed active source/report were moved into
preservation; no other source, map, header or tool was changed.
