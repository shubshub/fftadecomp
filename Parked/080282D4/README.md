# 080282D4 — bounded natural-source mismatch

Target: `080282D4..08028350`, 124 bytes / 55 reachable instructions.
The preserved candidate produces a complete 124-byte ELF symbol with
54 reachable instructions under unchanged `agbcc -mthumb-interwork -O2`.
The native extent/CFG/typed-linking checks and source plausibility passed;
byte comparison returned `NOT MATCHING`, exit 1. No match credit is claimed.

The native aligned diff score is 50/54 instructions and 116/124 bytes.
These are native diff scores, not same-offset byte equality.

The remaining code difference is the control-flags update. The target loads
old flags into r2, constructs 0xC00 in r6, copies that mask to r0, and ORs
r2 into r0. The compiler constructs the mask in r2 first, loads old flags
into r0, and ORs r2 into r0 directly. Its one fewer instruction is offset
by additional alignment before the middle literal pool; branch displacements
around that pool consequently differ. The window arguments, repeated color
load, conditional flag update, and both calls otherwise align.

Direct compound OR and read/OR/store forms produced 120-byte symbols and
stopped at the extent gate. Explicit mask and promoted-flags locals produced
the preserved 124-byte form; both u16 and u32 masks retained the same gap.
A two-bit control-field assignment produced 116 bytes and also stopped at
the extent gate. No plausibility claim is made for those refused extents.
No assembly, volatile RAM, forced inlining, flag changes, or compiler
steering was used. Unmatched active source and report were removed.
