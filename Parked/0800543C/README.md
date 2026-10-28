# 0800543C — compressed byte-stream decoder

Target: complete indexed `[0x0800543C, 0x0800588C)`, 1104 bytes and 552 reachable Thumb instructions. The retained candidate is the complete 1098-byte ELF function symbol, `[0x0800543C, 0x08005886)`, with 549 reachable instructions. No shorter target subspan was used.

The decoder reads a big-endian output length and returns it after processing a command stream. High command bits select short back-references, literal runs, short zero runs, or longer back-references. Commands 0, 1 and 2 encode extended back-references, 0xff runs and zero runs. Back-reference copies preserve forward expansion, using byte copies for differing source/destination alignment and aligned byte/halfword/word transfers otherwise. Fill operations use corresponding destination-alignment handling. Unknown low commands consume no output.

Nine fixed native matcher invocations used `agbcc -mthumb-interwork -O2`. Complete generated extents were 1122, 1122, 1042, 1074, 1124, 1090, 1092, 1098 and 1098 bytes. Every native invocation exited 1. The final verdict was `compiled symbol is shorter than the indexed span: 1098 < 1104`; this gate runs before byte comparison and plausibility, so the retained candidate has no native match/plausibility verdict. Earlier 1122/1124-byte forms were native-plausible closed leaf CFGs with no relocations, but their bytes differed. The best complete-form native aligned diff score was 217/561 instructions and 741/1122 bytes; that is not same-offset byte equality and does not describe the final short candidate.

Remaining observed code-generation differences:

- The target uses an eight-byte stack frame, keeps the produced-output offset in r9, and retains only alignment constant 2 in r10. The candidate uses a twelve-byte frame, spills the output offset at SP+8, and caches -1 in r10, 1 in r9 and 2 in r8. Header construction otherwise follows the same byte-load/shift/OR operations and stores the output base at SP+4.
- Source/destination/count temporaries consequently use different registers. The target's initial short back-reference retains its destination in r6 and pre-decrement match pointer in r8 before entering the copy block; the candidate allocates those values differently.
- The compiler shares aligned-copy tails across command branches differently, including long jumps from the first back-reference copy into a later common tail. The target retains its early halfword/byte tail locally and shares a later pair of tails.
- An unsigned-byte command promoted to int reproduces the target's logical shift and signed switch branching; this fixes a real type difference but leaves the register allocation and common-tail differences.

Natural iterations covered a retained output-base local, structured versus explicit command loops, signed versus unsigned word counters, guarded destination/fill temporaries, caller output-pointer locals, and command working types. The target-style unsigned word countdown and structured outer loop are retained. Signed word counters and explicit outer labels changed the loop lowering away from the target and were discarded. The implementation uses one copy macro and one fill macro, with no helper functions, assembly, volatile, pragmas, padding, dead computations or changed compiler flags.

Only this address's unmatched active source/report were removed. Full target disassembly and the retained private candidate remain in the assigned disk-backed directory. Root owns reservation release.
