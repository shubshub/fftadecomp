# 08141D9C — parked

Complete indexed target [0x08141D9C, 0x08141E30): 148 bytes / 53 instructions. Fixed agbcc -mthumb-interwork -O2 and approved ROM used. No exact native success.

The first typed-table candidate compiled to 132 bytes: the compiler combined the byte/halfword ID reads and cached the selected table pointer across output stores. An opaque pointer table with separate maker/device access reproduces the table reloads, hardware update, search, all six bindings, literal pools, frame and complete 148-byte extent. Source is plausible.

The remaining difference is the packed identifier comparison at target 0x08141DD6..0x08141DDC:

- Target: ldrh r0, [r1, #0x28]; cmp r3, r0; bne backedge.
- Current: ldrh r1, [r1, #0x28]; cmp r3, r1; bne backedge.

The current native report is exit 1, plausible, 51/53 instructions and 146/148 bytes identical. The earlier union-view candidate with record ID on the left produced ldrh r0, [r1, #0x28]; cmp r0, r3: 52/53 instructions and 147/148 bytes identical. Natural comparison operand order, a local ID, a wider fetched ID, and packed maker/device access did not produce the target pair. No asm, volatile, pragmas, fixed registers, compiler changes or artificial control flow were introduced. This is not the unused-load-before-store family.

The native report is retained privately at /home/user/.codex-work/ffta-ulw/audio-following-v63-matching/08141D9C/last-native-report.md. Nonmatching src/08141D9C.c and docs/match/08141D9C.md were removed. Root owns the accepted lease and its release.
