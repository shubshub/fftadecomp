# 0800ED58 — bounded natural C nonmatch

Target: `0800ED58..0800F068`, complete 784-byte symbol, 370 reachable instructions. Accepted claim: `6455813572`.

The complete recovered candidate draws ellipse scanline bounds, delegates equal radii to `func_0800E878`, uses the indexed quotient function `func_08141870`, and reads the mapped right-edge adjustment byte `data_02009160`. It retains both radius-order branches, direction selection, clipping conditions, narrow coordinate arithmetic, and the midpoint recurrence. It uses ordinary typed C without assembly, artificial qualifiers, padding, runtime aliases, or compiler steering.

## Final tested result

The default native command with the approved ROM and unchanged `-mthumb-interwork -O2` flags exits **1**:

```
compiled symbol is shorter than the indexed span: 776 < 784
```

The preserved source compiles to **776 bytes / 369 reachable instructions**, versus **784 bytes / 370 instructions** in the complete target. Native matching stops at the compiled extent guard before its plausibility stage. The separate standalone plausibility check exits 0; the separate original-ELF compile, typed linking, native CFG, and data-literal diagnostic also exits 0. These diagnostic results do not discharge the native match guard or establish match credit.

Only **127/784 target bytes** are equal at the same offsets. This is raw same-offset equality, not an aligned diff score. The eight-byte size deficit does not mean that only eight bytes differ. The generated frame allocates 64 local bytes while the target allocates 56; remaining differences include register allocation, sign extensions, row-store merging, and recurrence instruction selection. No native capability gap was identified.

## Bounded natural forms tested

- Duplicated drawing branches with unsigned 16-bit counters: 758 bytes.
- Shared row stores with direction skips and signed views: 744 bytes with unsigned counters.
- Signed 16-bit centers and counters: 800 bytes; native comparison and plausibility reached.
- Unsigned coordinate parameters with signed counters: 796 bytes; native comparison and plausibility reached.
- Wide row intermediates with signed counters and unsigned error storage: 776 bytes.
- Wide center locals: 748 bytes; direct parameter casts: 724 bytes.
- Unsigned row storage with signed views: 792 bytes; native comparison and plausibility reached.
- Final wide-row form with the equivalent old-major error recurrence: the preserved 776-byte candidate.

The final source is retained for future recovery. No partial match credit or successful report replay is claimed. Unmatched active source and the obsolete generated report were removed.

## Evidence

Address-private scratch `/home/user/.codex-work/ffta-ulw/audio-following-v659-matching/0800ED58` retains `diagnostic.json`, `match.log`, `plausible.log`, `candidate.o`, `candidate.elf`, `candidate.bin`, and `candidate.s`. The object is the original complete compiler ELF; the linked ELF and binary are diagnostic outputs. `diagnostic.json` records the exact source and ELF hashes, native exit, counts, and raw comparison. The stale report from a prior 792-byte candidate is not evidence for this source.
