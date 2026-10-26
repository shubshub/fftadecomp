# 080BDC58 — Parked

The complete target spans 080BDC58..080BDC98: 64 bytes and 32 reachable instructions. The recovered function removes a node from a 16-column grid cell's chain. It skips null and minus-one sentinel heads, clears the cell when the head is the requested node, and otherwise searches for the predecessor before replacing its next pointer with the removed node's next pointer. The observed next member is at offset 4.

The final default native matcher exited 1 with plausible source and a complete 74-byte ELF symbol. The comparison reports 23/37 compiled instructions identical and 57/74 bytes identical. These counts cover the compiled span, which extends ten bytes past the indexed target. This is not an exact match.

Two differences remain. The target combines x*4 and y*64 before adding the grid base; the retained typed grid accessor adds the row offset to the base before adding the column offset. The compiler also duplicates the first next-pointer loop test, adding ten bytes, whereas the target enters a shared test block directly. Sentinel handling, head clearing, list traversal operations, predecessor update and return are recovered.

Tried direct two-dimensional array parameters, a flattened cell index, a grid struct with a typed inline cell accessor, compound while conditions, an explicit terminating search loop, and a for search with early returns. Flattening combines the coordinate index before scaling and adds another instruction. The typed accessor and ordinary for search retain the best tested 74-byte form. Fixed compiler flags were unchanged; no shared metadata or steering constructs were used.

The differing native report is retained privately outside the matching root at ../080BDC58/native-not-matching.md. Unmatched active source and report were removed.
