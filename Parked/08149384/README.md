# 0x08149384 — Parked

Complete target: `[0x08149384, 0x081493AA)`, 38 bytes / 19 instructions.

The fixed native matcher exits 1: plausible C; complete 38-byte ELF symbol; 36/38 bytes and 18/19 instructions identical. The candidate checks bit 7 of byte 2 in a seven-byte tile record indexed by `y * 16 + x`.

The sole remaining difference is the placement of the x-coordinate zero-extension right shift. Target begins `lsls r1,#24; lsls r2,#24; lsrs r2,#20; lsrs r1,#24`; the best natural byte-pointer candidate emits `lsls r1,#24; lsrs r1,#24; lsls r2,#24; lsrs r2,#20`. All following instructions match.

Eight native runs covered a byte-record struct, byte-pointer arithmetic with natural parameter-width variants, and a seven-byte array view, then restored the best byte-pointer candidate for the retained native report. The struct exposed agbcc padding (seven byte fields have an eight-byte stride); the array view also changed the address register. No assembly, volatile, compiler pragmas, or artificial steering was used.

Native evidence is retained privately at `/home/user/.codex-work/ffta-ulw/audio-following-v66-matching/08149384/last-native-report.md`. The nonmatching active source and report were removed. No completion claim is made.
