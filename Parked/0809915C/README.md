# 0809915C — Parked

Target: 0x0809915C..0x0809920A, 174 bytes / 81 reachable instructions.

The complete candidate selects an appearance table, applies one entry, swaps a saved ten-byte snapshot and five saved halfwords with the active unit, and calls the final refresh helper. Option 13 permits the alternate table when the unit belongs to one of the owner's two embedded unit records. The byte-sized ownership predicate matches the captured search and Boolean result.

The final default native matcher invocation exited 1. The complete compiled extent is 174 bytes, source plausibility passes, and 80/81 instructions / 172/174 bytes are identical. No exact-match credit is claimed.

The remaining gap is the initial saved-byte pointer increment. The candidate increments it before preparing the saved-halfword and unit-attribute bases; the target performs the same increment after those two base calculations. The rest of the retained operation sequence matches in the native comparison. Changing the pointer traversal or making both buffer bases explicit produced shorter candidates, so the best tested 80/81-instruction version is retained under fixed agbcc `-mthumb-interwork -O2`.

Bounded attempts also recovered the cached unit pointer, byte ownership-predicate result, contiguous saved-byte snapshot, and shared byte-swap temporary. No assembly, volatile access, or compiler steering is used.

The detailed native differing report and captured target remain outside the matching root in private address scratch. Unmatched active source and report have been cleared.
