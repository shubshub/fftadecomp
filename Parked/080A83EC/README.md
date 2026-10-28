# 080A83EC — Parked

Target: 68 bytes / 30 reachable instructions.

The default native matcher exits 1 for the retained complete 68-byte candidate. Source plausibility passes; 28/30 instructions and 65/68 bytes are identical. No exact-match credit is claimed.

The function forms signed coordinate deltas, obtains an angle, rounds its high byte to one of sixteen sectors, and indexes the genuine bound data table. The only remaining difference is arithmetic scheduling: compiled code subtracts each coordinate pair earlier, while the target normalizes all four inputs before the first subtraction and narrows each difference immediately after subtracting. The helper call, sector arithmetic, table load, and return match.

Bounded attempts covered signed-halfword and integer delta locals, direct call expressions, and a conventional inline point-angle helper. Integer deltas with an unsigned sector mask give the best native comparison. No reordered helper interface or artificial promotion temporaries were introduced to force instruction order.

Detailed native output and the differing report remain in private address scratch, outside the matching root.
