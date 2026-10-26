# 08042CB4 — unmatched

Complete indexed target: `[0x08042CB4, 0x08042D4A)`, 150 bytes / 75 instructions.

The natural C fills thirteen columns of each row pair with sequential 16-bit tile values. The palette occupies the upper tile bits; the row width and pair count come from the input record.

The final default native matcher run exited 1 with source plausibility `plausible`, profile `elf-symbol-cfg-leaf-v2`, and a complete 150-byte ELF symbol. Its aligned comparison reports 73/75 instructions and 146/150 bytes identical. Direct comparison differs at 8 bytes across four instruction positions, all in setup `[0x08042CD6, 0x08042CDE)`. The target calculates the pair stride before calculating the bottom-row address and uses r1 for the latter; the candidate calculates the bottom-row address first and uses r2. The loop body and all remaining bytes match.

Pointer traversal, indexed columns, explicit pair stride, and byte-pitch forms were tried with the fixed `-mthumb-interwork -O2` flags. The retained indexed-column form has the closest complete result. No assembly, volatile, pragmas, dead code, or register-steering constructs were used.

Native report retained in address scratch as `native-match.md`; unmatched private src/report paths are clear. No match credit.
