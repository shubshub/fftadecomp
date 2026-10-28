# 080194E4 — Parked

Target: complete [0x080194E4, 0x08019574), 144 bytes / 58 reachable instructions.

The complete natural reconstruction selects the current packed resource's first or second identifier, checks property 0x3d or 0x3e, obtains either fixed text or identifier text, writes it to the destination, and returns zero.

The preserved candidate is the tested direct-call form. The unchanged native matcher returned exit 1: complete compiled symbol 148 bytes, source plausible, bytes differ. Its normal identifier lookup matches the target's register choices, but the compiler duplicates the final formatter call in the fixed-text branch. At target 0x08019520 there is one branch to the common formatter setup at 0x08019560; the candidate instead emits destination setup and a formatter call at 0x08019520/0x08019522 followed by a branch to its epilogue. This adds four bytes overall and shifts the following body. The target's separate fixed-text and identifier-table pointer loads remain the unresolved join difference.

Three bounded natural forms were tested under fixed agbcc -mthumb-interwork -O2: common text local and one formatter call (140-byte short-symbol refusal); separate branch formatter calls (preserved 148-byte plausible mismatch); and a genuine inline identifier-to-text lookup helper with a common formatter call (140-byte short-symbol refusal). The common-call forms merge the pointer loads, unlike the target. Short-symbol attempts were refused before plausibility/comparison gates and receive no match credit. No compiler steering or gate changes were used.

Native evidence is retained in the private address scratch directory. The active source and report were removed; this pair earns no match credit.
