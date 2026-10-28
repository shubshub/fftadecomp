# 080A0D04 — Parked

Target: 230 bytes / 114 reachable instructions.

The default native matcher exits 1 for the retained complete 240-byte candidate. Source plausibility passes. Native comparison reports 50/119 instructions and 162/240 bytes identical across the compiled span; the span extends ten bytes beyond the target boundary. No exact-match credit is claimed.

The routine evaluates the indexed curve using a signed 64-bit fixed-point argument, computes signed X/Z offsets, adds the origin, and reports remaining travel. The remaining gap is evaluation order and register allocation: compiled code converts the fixed-point argument before preparing curve pointers, retains progress in a high register, and saves an additional high register. The target prepares the curve address between the product and conversion and keeps progress in a low register.

Bounded attempts covered a direct expression, explicit curve-pointer preparation, natural maximum and fixed-point conversion helpers, and an inline curve-evaluation wrapper. The retained form has the best native comparison at the closest compiled extent. The 64-bit direct call passes the existing native ABI gate without an extra profile flag.

Detailed native output and the differing report remain in private address scratch, outside the matching root.
