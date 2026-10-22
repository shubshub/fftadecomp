# 0x08064EF8 — natural recovery, not byte-matching

## Complete target and retained result

Target `[0x08064EF8, 0x08064FA0)` is 168 bytes / 64 reachable decoded
instructions. It contains 142 code bytes, six literal words (24 bytes),
and two internal zero alignment bytes. Code ranges are
`[0x08064EF8,0x08064F44)`, `[0x08064F54,0x08064F82)`, and
`[0x08064F88,0x08064F9C)`. Pools occupy `0x08064F44..0x08064F54`,
`0x08064F84..0x08064F88`, and `0x08064F9C..0x08064FA0`; zero alignment
is `0x08064F82..0x08064F84`. The next entry is excluded.

Target SHA-256:
`895c49d076936d60be1ca00f0a5b4108cc2f24f41411400d772162596db5ebcd`.

The retained source emits exactly one 168-byte FUNC and a 168-byte `.text`,
with seven typed Thumb call relocations and no residual linked relocations.
The complete linked candidate passes local CFG and source plausibility but
is **NOT MATCHING**: 156/168 bytes and 52/64 same-address instructions agree.
There is no verifier/profile gap, missing literal, shortened comparison,
or extra function. Candidate SHA-256:
`5662e2c20745cb221dae45ad8d274a5c48bad0bc86110a65ea9a282a32a62871`.

The difference is register selection for the slot pointer and clear-size
constant: target uses r5/r6, candidate r6/r5. Exactly these byte addresses
differ: `0x08064F1D`, `0x08064F1E`, `0x08064F23`, `0x08064F28`,
`0x08064F2E`, `0x08064F32`, `0x08064F3C`, `0x08064F55`,
`0x08064F56`, `0x08064F64`, `0x08064F6C`, `0x08064F7C`.
All instruction addresses, call destinations, branch edges, literal values,
and literal locations otherwise agree. The active source and nonmatching
active report were removed after preserving this recovery.

## Grounded behavior and types

The compatible wrapper takes an unused first word and a mutable byte pointer
in the second ABI position. The first argument's original nominal type is
not recovered; `u32 unused` preserves its position without claiming it was
historically an integer rather than an unused pointer. Only incoming r1 is
consumed. Saved LR returns through r0, so the function is void. It saves
20 bytes, has no fixed local frame and no incoming stack argument. Entry
evidence here is the structural prologue/closed CFG/adjacent-body separation,
not a discovered incoming callback reference.

- Phase 0 allocates `0x3800` bytes through 22840, publishes the pointer at
  `0x0200F454`, and clears the first `0x1704` bytes through the actual clear
  slot `0x0836D4B8`. It reloads the published pointer, stores the original
  allocation at offset 4, initializes an arena at original allocation+1704
  with full size `0x20FC`, reloads the slot again, stores the returned manager
  at offset 0, then writes phase 1. There is no null-allocation guard.
- Phase 1 reloads the slot and reads byte 8; if nonzero it writes phase FF.
  There is no null-slot guard in this phase.
- Phase FF tests the live slot. When nonnull, cache its allocation word 4,
  call 5A24 on its manager word 0, then reload slot and manager separately
  before 5B18 and again before 5C34. Release the cached allocation through
  22854, overwrite the slot with zero, and write phase 2. A null slot leaves
  phase FF unchanged. Helper changes do not replace the cached release base.
- Other byte phases do nothing beyond reading the phase.

`TaskContext` models the actual cleared `0x1704`-byte prefix, with observed
pointer words at 0/4 and byte at 8; the remaining bytes are explicitly
unknown. Target-compiler layout is size1704/alignment4 and offsets0/4/8/9.
The immediately following `0x20FC` bytes form the supplied arena, exactly
filling the observed `0x3800` allocation request. These observations do not
establish original type names or allocation success. The ordinary C domain
requires valid aligned context/arena storage, a valid mutable phase byte,
and valid pointers for whichever phase executes. No arbitrary pointer,
alias, lifetime, live-allocation, or cyclic-task safety claim is made.

Immediate compatible interfaces are void 5A24(manager), void 5B18(manager),
pointer-returning 5C14(storage,u32 size), and void 5C34(manager). The complete
helper audit establishes local input widths and preserves unknown callback
effects. 5A24/58A4 can invoke task callbacks with task/local-halfword/data
pointers; callbacks can mutate globals, retain pointers, or fail to return.
No purity, general no-hidden-argument callback proof, or universal task
termination is assumed. The separate existing allocator/free contracts and
copied-clear startup provenance are reused, not recursively reproved.

## Natural attempts

All attempts use ordinary C with the same agbcc `-mthumb-interwork -O2` flags.

1. A minimal three-field context plus byte-addressed allocation cursor:
   168 bytes / 64 instructions, 150/168 bytes and 46/64 instructions agree.
2. The complete grounded cleared-context view and `context + 1` arena
   address: 168/64, 151/168 bytes and 47/64 instructions agree.
3. Retained form: the same typed view with separate initialization-context
   and teardown-allocation locals in their natural branch scopes: 168/64,
   156/168 bytes and 52/64 instructions agree.

No register declaration, artificial work/CFG, forced storage/alignment,
optimization pragma, volatile, assembly, or alternate flags were used.
Further register-selection manipulation was not pursued.

## Fresh verification and explicit boundaries

Reproducer retained outside the repository:
`/home/user/.codex-work/ffta-ulw/08064EF8-author/check.py`.
Run with `PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp` and the existing
`/home/user/armtc/root/usr/bin` on PATH. It copies only this source into its
own isolated root with current shared headers/maps, invokes frozen
`kit-reviewed-4847c93` officially with `--no-write`, and requires plausible
NOT MATCHING. It separately verifies complete typed ELF/CFG/layout evidence,
then deletes generated build files. No successful saved-match replay exists
or is claimed for a nonmatching candidate.

28 target/candidate pairs (56 executions) pass an independently specified
caller RAM-access/call-order oracle, final EWRAM comparison, exact paired
nonstack access traces including ROM literal reads, and saved r4-r11/SP/PC.
All RAM is synthetic. Six pairs execute the real selected allocation/free
wrappers, task helpers, initializer, copied clear and thunks, with 7138 and
7170 explicitly modeled rather than real allocator internals. Eighteen
pairs exercise polling/default/null-cleanup paths without helper calls.
Four further pairs model direct helper effects explicitly, changing the
global slot and cached allocation field and clobbering caller-saved registers
to test each reload and preservation requirement. These are valid model
boundaries, not evidence that arbitrary task callbacks were executed.

The actual scheduler fixtures use an empty task list. First-word inputs are
0, `0x12345678`, and `0xFFFFFFFF`; polling includes zero and high-bit finished
bytes. All 63 feasible caller instructions execute in both bodies. The sole
unexecuted instruction, `0x08064F0A`, would require the initially loaded
unsigned byte to be less than 1 but not zero, so that edge is infeasible.
There is no fault-injection, unrestricted alias, nonempty scheduler-tree,
successful real allocation, or engine-termination claim in these fixtures.

Full prerequisite evidence remains under
`/home/user/.codex-work/ffta-ulw/64ef8-helper-audit/` and caller inventory under
`script-after64ccc-inventory/`. This recovery is ready for independent
semantic/nonmatch review, not promotion into active matching sources.
