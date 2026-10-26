# 0809D79C — Parked

Target: 72 bytes / 34 instructions.

The default native matcher exits 1. The retained complete 72-byte candidate passes source plausibility and matches 33/34 instructions and 71/72 bytes.

The sole remaining difference is the initial normalization of Y: compiled code uses a logical right shift where the target uses an arithmetic right shift. The later signed conversion, bounds checks, helper calls, return handling, and remaining instructions match.

Bounded attempts covered direct combined and separate guards, inline bounds helpers with integer and byte results, and signed-byte or full-width predicate parameters. The retained direct combined guard with unsigned-byte helper coordinates gives the best native result. No exact-match credit is claimed.

Detailed native output and the differing report remain in private address scratch, outside the matching root.
