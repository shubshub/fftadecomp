# 080A7A80 — bounded natural C attempt

Target: `0x080A7A80..0x080A7C9C` (exclusive end), complete 540 bytes and 252 reachable instructions, including the indexed literal pools. No match credit.

The preserved source is the best tested natural reconstruction. The fresh default native matcher returned exit 1: source plausible, complete compiled ELF symbol 540 bytes, ordinary typed calls, bounded fixed frame and return provenance accepted, no remaining relocations. Compiler flags remain `-mthumb-interwork -O2`.

The unresolved gap is register and local lifetime allocation. Target reserves 20 bytes of locals, keeps the group in r8 and child in r7, uses r6 as the outer index and r5 as the output-count pointer, and retains a second group address in `[sp,#0xC]` with the next outer index in `[sp,#0x10]`. This candidate reserves 16 bytes, coalesces that group address, uses r7 for group and r8 for child, swaps the outer-index/output-count roles, and spills the next index at `[sp,#0xC]`. The changed lifetimes affect instructions and branch/literal placement; target middle literal is at 0x080A7AF0, compiled at 0x080A7AEC.

Bounded source forms tested: the direct `Group *` child accessor with a conventional outer for loop (preserved, 540 bytes); a source/group-index child accessor (556 bytes, restores group/child registers but recalculates the group inside the inner loop); and an explicit outer while loop that consumes the group index before its children (540 bytes, still the 16-byte frame and register-lifetime gap). The preserved for-loop form was restored and freshly matched after these attempts.

Native diff alignment score: 415/540 bytes and 143/242 decoded instructions. These are the native alignment score, not same-offset equality or the complete target instruction count. Its ordinary diff treats the relocated middle literal pool as instructions; the independently captured target has 252 reachable instructions.

Preserved source SHA-256: `a8b17ab35e7e73ad7ee84a3fada8739ff7a52bf3741ecfa801e11258a7f8d042`.
Nonmatching generated report SHA-256 before removing the active report: `afb16dc9cbfbcd16bef956bd4edc397222e62aa50a92f360b857eebc1916849a`.
Fresh native output remains in `audio-following-v203-matching/080A7A80/native-output.txt`; complete captured target remains in that address's `target-disassembly.md`.
