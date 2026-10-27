# 080D984C: bounded natural-C attempt

Target extent: `[0x080D984C, 0x080D987A)`, 46 bytes and 22 reachable instructions. The function obtains task data, selects the byte pair at offset 0x28 for selector zero or offset 0x2A otherwise, and writes its two byte arguments there.

The preserved complete candidate was tested using the native matcher with agbcc `-mthumb-interwork -O2`. It exited 1 at the complete-symbol extent gate: `compiled symbol is shorter than the indexed span: 40 < 46`. Byte comparison and the source-plausibility gate were not reached; no match or plausibility acceptance is claimed.

Direct if/else selection, a natural inline pair accessor, a natural inline task/pair accessor, and the preserved switch form all compiled to 40 bytes. The inspected direct-form assembly has 19 reachable instructions. It hoists the selected pointer to task-data offset 0x2A and conditionally subtracts two, then uses byte stores at offsets zero and one. The ROM keeps separate branches forming offsets 0x28 and 0x2A, then increments the selected pointer between zero-offset byte stores. The direct-form compiler also places the first and second byte values in R6 and R5 respectively, whereas the ROM uses R5 and R6. These control-flow, pointer-addressing and register-allocation differences remain unresolved under the fixed compiler. No compiler flags, artificial operations, volatile accesses, assembly or forced inlining were used.

Only this C/README pair is retained in Parked. The unmatched active source/report were removed.
