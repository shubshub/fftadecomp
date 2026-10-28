# 080BB370 — bounded natural C attempt

Target: `0x080BB370..0x080BB424` (exclusive end), complete 180 bytes / 90 reachable instructions. No match credit.

The preserved candidate is the closest tested structured reconstruction: two inlined transition-step updates, the active flag clear, and signed-byte four-call timer with two counters capped at 100. The restored candidate was freshly run through the default matcher with fixed `-mthumb-interwork -O2`; exit 1 reports a complete compiled symbol of 176 bytes versus the indexed 180. Verification stops at the extent check, so no native match or current native plausibility acceptance is claimed.

The target copies the selected maximum delta from r1 to r0 before each signed division by 16, applies the negative bias to r0, and shifts r0 into r1. The candidate applies that bias and shift in r1 directly, eliminating one two-byte move in each update. It also retains the State pointer in r3 and the x delta in r2, while the target uses r2 and r3 respectively. The explicit clamp form recovers the target's greater-than branch at the 256 minimum, but does not recover the division temporary or register allocation. Field offsets, division by 16, the two minimum-256 clamps, timer increment/reset, and counter caps remain represented in natural C.

Forms ruled out: built-in abs with a conditional clamp (176 bytes); inline maximum helper (176); a maximum macro (180 but different maximum-selection moves, in-place division and clamp branches); manual absolute-value branches plus explicit <=256 clamp (preserved, 176); and a pure value-returning calculation helper assigned by the caller (182, with additional address moves and different retained step values). No artificial register constraints or unused operations were added. The final native result belongs to the restored 176-byte source, not the rejected 180/182-byte forms.

Raw C SHA256: `14d18349bc8152d17ab67e0691e5e6327f269d73db9ca7477a32fb0897ad66ee`.
The full captured target and final native extent refusal remain in `audio-following-v227-matching/080BB370/`. No active source/report is retained.
