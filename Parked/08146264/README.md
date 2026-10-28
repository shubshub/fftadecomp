# 08146264

Complete target: [0x08146264, 0x08146282), 30 bytes, 15 reachable
instructions. Fixed agbcc -mthumb-interwork -O2.

Best tested complete candidate: native exit 1, 30-byte complete ELF symbol,
closed leaf CFG, source plausible, 20/30 bytes and 9/15 instructions identical.
It resets bytes +0x1A and +0x16, selects mask 0x0C when byte +0x18 is zero
or 0x03 otherwise, and merges the mask into byte +0. The candidate returns
the updated flags, matching the observed final R0 value; the target alone does
not establish whether callers consume that value or the historical C return type.

Remaining differences: target retains an initial movs r2,#0 before the store
zero in r0; this candidate eliminates that extra initialization. The candidate
hoists mask 3 into r2 before the comparison and conditionally replaces it with
12. The target selects both constants in r0 on separate branches and loads
existing flags into r2 afterward. The target returns directly through bx lr;
this compiler-generated candidate saves LR and returns via pop {r1}; bx r1.

Bounded tested forms:
- Separate byte resets, mask local, void result: 30 bytes, plausible,
  18/30 bytes and 7/15 instructions identical.
- Chained reset with direct conditional compound flag updates: 36 bytes,
  plausible, 16/36 bytes and 2/18 instructions identical across the compiled
  span, which included six bytes beyond the target. It reproduced the extra
  zero initialization but duplicated flag loads and retained saved-LR return.
- Preserved chained reset, shared byte mask, returned updated flags: 30 bytes,
  plausible, 20/30 bytes and 9/15 instructions identical as above.

No artificial zero local, register forcing, assembly, alternate flags or forced
inlining was introduced. Native report retained in address scratch as
last-native-report.md. Active unmatched source/report removed. No match credit.
