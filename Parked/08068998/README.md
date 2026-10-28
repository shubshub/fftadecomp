# 08068998 — Parked

Complete target: 0x08068998..0x08068ADE, 326 bytes and 150 reachable instructions.

`08068998.c` retains the complete tested animation updater: the blocking flag, initial resource preparation and menu drawing, invalid-frame handling, 64-tick counter, and frame-index wrapping. Its animation payload has byte and aligned halfword record views, matching the observed mixed-width accesses. No assembly, volatile access, compiler-flag changes, or shared metadata edits were used.

The latest default native matcher invocation with agbcc `-mthumb-interwork -O2` returned exit 1: `compiled symbol is shorter than the indexed span: 322 < 326`. This early extent guard prevents byte-comparison and plausibility results for the retained candidate; neither an exact match nor fresh plausibility acceptance is claimed.

Diagnostic output from the same fixed compiler shows the unresolved drawing-loop differences: the row-offset product becomes a carried induction value, scratch-buffer addresses are reloaded instead of held in the target's saved register, and the frame-address expression combines its fixed offset differently. The initialization fields and frame-counter update paths are implemented, with no omitted branches.

Bounded natural attempts covered typed animation records, byte/halfword payload views, byte versus integer loop locals, and ordinary narrow position calculations. Earlier complete candidates reached the indexed extent and were accepted as plausible, but still differed in loop arithmetic, pointer addressing, and register allocation. The retained candidate favors the recovered field layout and complete behavior without adding instruction-forcing constructs.

The latest native extent refusal is retained as `native-result.txt` in the private address scratch directory outside the matching root. Unmatched active source and generated report have been removed. No exact-match credit is claimed.
