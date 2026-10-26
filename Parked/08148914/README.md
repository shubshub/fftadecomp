# 08148914 — priority-tree budget accumulation and dispatch

Target and retained candidate both cover the complete indexed `[0x08148914, 0x08148A06)` span: 242 bytes and 115 reachable Thumb instructions. No subspan was attempted.

The first pass repeatedly walks the priority tree, subtracts each signed priority from the current budget, adds that priority to a signed 16-bit per-node accumulator, and stops on budget exhaustion. Priorities above 254 set the accumulator to 0xffff and end accumulation. The second pass dispatches nonzero accumulators to `func_08148B60`, narrowing the accumulator to a signed byte. The node layout agrees with the neighboring matched insertion function 08148860.

Eight native matcher invocations used fixed `agbcc -mthumb-interwork -O2`. The initial single-scope traversal compiled to 230 bytes; separating traversal scopes and left/right pointer expressions reached 242 bytes. An explicit cached root pointer produced 238 bytes. Other complete attempts stayed at 242 bytes. All exited 1. The retained shared statement-macro implementation received native `source plausible` and `NOT MATCHING - bytes differ`, with native diff scores of 78/115 instructions and 201/242 bytes. These are the matcher's aligned diff scores, not a claim of same-offset byte equality. One preceding explicit-label implementation scored 202/242 bytes.

The entire second traversal `[0x081489A6, 0x08148A06)` is byte identical, including the relocated direct Thumb call. Remaining differences are confined to the first pass:

- The candidate uses r1 for the current node and r2 for its right child; the target uses r2 and r3. The signed-priority/addition temporaries consequently differ too.
- Initial root-address construction and preserving the global base in IP occur in a different order, with different registers.
- The retained macro assigns the budget before loading the traversal root; the target loads the root first.
- At the outer restart, the candidate compares the copied budget in r0, while the target compares the remaining budget in r4. Both then restart at the same offset.

Natural iterations included independent traversal scopes, direct left-child expressions, local counter scopes, explicit traversal labels, root-pointer caching, global-base initialization placement, and one shared tree-iterator statement macro. The macro preserves the established parent/left/right traversal and avoids helper functions. No flags were changed; no assembly, volatile, pragmas, inert computations or steering constructs were introduced.

The unmatched active source and generated report were removed. Full target disassembly and the retained private candidate remain in the assigned disk-backed directory. Root owns reservation release.
