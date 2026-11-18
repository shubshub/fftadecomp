# 0804BBC0

Kit 4e89006 links the default Thumb agbcc -O2 build to all 396 bytes from 0804BBC0 to 0804BD4C. The linked symbol's SHA-256 is 6c53fa0b12f34f92d94533c7020dd3a7103c68fe863a306bbbb8ea66dd62c455. Its 189 reachable instructions contain no calls. The literal pool binds the map records at 08391E40, the unlock flags at 02002E58, and the coordinate-sequence table at 083931B0.

The caller at 0804BB5C supplies its own 32-byte distance array and forwards the caller's predecessor/output array. At 0804BB8E it follows predecessors backwards and then reverses that path for its caller. The graph has 30 connected nodes, with 90 active directed edges representing 45 reciprocal routes. The first two bits at 02002E58 control entry to nodes 8 and 27. The routine relaxes hop counts on a circular pass over 32 slots. It compares the coordinate-sequence length when two routes have the same hop count.

For each of the 30 starting nodes and all four combinations of the two flag bits, the original ROM routine ran to its return in Unicorn. All 120 distance arrays agreed with independent breadth-first search. Every reachable non-source node had an adjacent predecessor at distance one less. Every unreachable node and every source retained the predecessor sentinel 0xFF.

The ordinary verifier and named-data-buffer-v1 reject the stack-alias use. The named-data-buffer-stack-index-v2 profile rejects pointer-bearing local words. In particular, the ROM spills a pointer to the local cost array at 0804BBDA. At 0804BC18 it indexes that 32-halfword array by the input start node. The instruction sequence narrows the input to eight bits, and the array access needs a tighter bound. The finite ROM checks cover the 30 map nodes. The saved C retains the original unsanitized start and adds no assumed index mask.

The independently recovered 100-byte wrapper at 0804BB5C also links exactly.
Its five direct call sites and the unresolved start/destination value sources
are documented in ../0804BB5C/README.md. Rebuilding the worker on toolkit
f1b81350 reproduced its 396 bytes and the variable-index refusal for
pointer-bearing local stack words.

For unlock flags 0, 1, 2 and 3, independent BFS of all ordered node pairs
finds 842, 871, 871 and 900 reachable pairs. Each graph's diameter is eight
hops. Executing the original wrapper and worker together on one longest
path per flag configuration, plus three unreachable cases and one equal
endpoint case, reproduced each result. Returned paths followed actual map
edges and eight-byte guards on both sides of a 32-byte output remained
intact. These checks start from the 30 valid nodes. They provide no bound
on the mutable fields supplying arguments at the five caller sites.
