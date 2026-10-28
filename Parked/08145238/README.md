# 08145238: bounded native mismatch

Target: complete [0x08145238, 0x0814528C), 84 bytes / 34 reachable instructions.
Fixed compiler: agbcc -mthumb-interwork -O2.
Latest native match.py exited 1 after complete ELF extent and plausibility passed.
Candidate extent is 84 bytes; 29/34 instructions and 79/84 same-offset bytes match.

The reconstruction selects the song and its music player from the two mapped tables,
starts a different or inactive song, and resumes a paused active song.
All playback branches, calls, status reads, literal values and epilogue match.
The only remaining difference is the independent table-base/index register allocation:

- 0x0814523C: target loads the player table into r2; candidate uses r3.
- 0x08145244: target loads the player index into r3; candidate uses r2.
- 0x08145246: target shifts r3; candidate shifts r2.
- 0x08145248: target adds r3; candidate adds r2.
- 0x0814524C: target adds the table base in r2; candidate adds r3.

Bounded natural attempts covered direct table lookup, named table bases, a named song
header, in-place song-entry traversal and an ordinary separate player declaration.
Named table bases give the preserved best complete candidate. A named song header
also swapped two independent header loads; in-place traversal produced an 82-byte
symbol rejected by the extent gate. No artificial reads, volatile, assembly, compiler
changes or steering were introduced. Native output remains in address scratch at
../08145238/native-output.txt relative to this matching root.

The active unmatched source and generated report were removed. No exact match credit.
