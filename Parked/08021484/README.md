# 08021484 — Parked

Complete captured target: `[0x08021484, 0x0802158C)`, 264 bytes and 119 reachable instructions.

The complete natural C candidate reconstructs the animation update, transfer-capacity checks, deferred-animation assignment, flag updates, transfer-record setup and queue-count increment. It uses the fixed agbcc `-mthumb-interwork -O2` configuration and the default native matcher.

Latest native result: exit 1, `compiled symbol is shorter than the indexed span: 260 < 264`. This extent guard stops before byte comparison and source plausibility; neither an exact-match score nor a plausibility verdict is claimed for this candidate. An earlier 272-byte candidate reached the comparison and was plausible but differed.

Bounded natural attempts covered separate versus combined capacity guards, success versus failure branches, assignment versus block-local initialization of the pending value, pointer versus opaque 32-bit representation, and a combined entry condition. The closest generated sequence observed retained the target's transfer body and capacity branches but loaded the pending value directly into its saved register. The target instead loads it through a temporary register and copies it; the shorter sequence also changes alignment and literal-pool placement. No redundant operation or compiler steering was added to manufacture the missing bytes.

The best tested complete candidate is `08021484.c`. Raw target capture, compiler diagnostic output and the earlier differing native report are private address scratch outside the matching root. Unmatched source and native report have been removed from their active paths. No matching credit is claimed.
