# 0x0801ED24 — Parked

The complete indexed target is 650 bytes with 315 reachable instructions, ending at 0x0801EFAE. The recovered C includes indexed and raw decoding, narrow and wide table entries and indices, tile-pair construction, optional two-screen clipping, source advancement, termination, and a resumable byte budget.

The final default native matcher with fixed agbcc `-mthumb-interwork -O2` returned exit 1. It accepted the source as plausible and verified a complete 668-byte ELF function using the ordinary direct Thumb-call profile with no relocations. The generated function is 18 bytes longer than the target. Its diagnostic totals were 153/321 instructions and 451/668 bytes identical; those totals cover the compiled span, including bytes beyond the assigned target, and are not complete-target match credit.

Eight bounded natural candidates varied destination pointer types, count lifetimes, signed coordinate conversions, flag normalization, tile-index decoding, and branch-local budget handling. Generated extents ranged from 622 to 694 bytes. The retained candidate still differs in register allocation, stack spills, coordinate conversion sequences, pointer advancement, and branch layout. The native tool supports the function; no verifier limitation was encountered.

The differing native report remains private at `/home/user/.codex-work/ffta-ulw/audio-following-v76-matching/0801ED24/native-not-matching.md`. No ROM-derived instruction diff is included in this directory.
