# 08021FB4: tree traversal, loop-layout mismatch

The target is the complete `[0x08021FB4, 0x0802200A)` function:
86 bytes and 42 Thumb instructions, with no literal pool or local stack
allocation. It saves `r4` through `r7` and calls the indirect-call runtime
thunk at `0x08142260`.

## Recovered behavior and contracts

The context root is at offset `0x0C`. Node links are right at `0x3C`,
left at `0x40`, and parent at `0x44`. The initial previous-node value is
`(TreeNode *)-1`, used only in pointer comparisons, never dereferenced.

The traversal descends to an unvisited left child, invokes the callback
with the current node and payload, visits a right child, and ascends through
parents until it returns to the starting node or reaches a null cursor.
The right-child field is reloaded after the callback, preserving mutations
made by the callback. Parent links are also read when ascent occurs.
There is no added guard, cycle detector, or assertion of termination for
malformed or arbitrarily callback-mutated trees.

The callback recovery uses `void (TreeNode *, void *)`. The ROM explicitly
provides those two arguments and discards the result. This is a compatible
ordinary-ABI contract, not proof of every possible callback's behavior or
of a unique original return type. Node and context pointers must refer to
valid objects, and callbacks must satisfy the assumed ABI when invoked.

## Verification and attempts

All candidates used agbcc `-mthumb-interwork -O2` and reviewed toolkit
`3f840c6`:

```
PYTHONDONTWRITEBYTECODE=1 PATH=/home/user/armtc/root/usr/bin:$PATH TMPDIR=/home/user/tmp python3 /home/user/.codex-work/ffta-ulw/kit-reviewed-3f840c6/tools/match.py --root . 0x08021FB4
```

The runtime thunk is already supported and checked against its ROM bytes.
The verifier accepted the candidates' call/CFG profile and source
plausibility; byte equality failed. This is not a toolkit support blocker.

Three natural structures were tried:

1. Nested `do/while` with right-descent `continue`: 86-byte compiled symbol,
   but different cursor initialization and loop rotation.
2. Flattened `while` with descent `continue`: 88-byte compiled symbol;
   this simpler recovery is retained.
3. Structured `do/while` without `continue`, spelling ascent in the two
   applicable cases: 88-byte compiled symbol, still with rotated ascent.

The retained candidate was reverified before parking. It produced
28/42 identical aligned instructions and 72/88 identical aligned bytes
in the verifier's diagnostic comparison. Those figures are not a match:
the actual target symbol is only 86 bytes.

The ROM keeps the root check and parent ascent at the loop tail, followed
by the shared cursor-null test. The compiler instead places ascent before
the main loop body and adds a preheader branch. This changes branch targets
and the runtime-call displacement as well as the symbol length. No forced
labels, inert conditions, register bindings, or arbitrary extra operations
were introduced to control block layout.

No nonmatching active source or match report remains. No manual scratch
artifacts were created. This is a local code-generation mismatch, not a
claim that the function is inherently unmatchable.
