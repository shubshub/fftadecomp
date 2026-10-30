# 081464F8: bounded native mismatch

Accepted claim 6526507267, lane sol-64F8. Exact indexed target is
[081464F8,08146540), 72 bytes and 27 instructions. The actual dispatcher
establishes void(void *owner, CommandContext *context); the first argument is
unused by this handler. No C or toolkit inputs outside the owned address changed.

Three natural, fully initialized forms were checked with the default native
profile: (1) a union word and four unsigned 8-bit bitfields with a local cursor;
(2) a union word and four-byte array with a local cursor; (3) the same byte-array
union using the context cursor directly. Every byte field is assigned before
the word is read. No explicit steering masks, asm, pragmas, volatile, dead
operations, uninitialized union-word reads, or padding instructions were used.

All three native commands exited 1 with ordinary NOT MATCHING verdicts. All
three sources were plausible and compiled to the same 72-byte complete symbol
under elf-symbol-cfg-leaf-v2. Native aligned comparison reported 51/72 identical
bytes and 8/27 identical instructions. Exact offset comparison finds 25 differing
byte positions and 47 identical positions. These are distinct metrics. All four
integer literal words and both alignment bytes match. This is an ordinary byte
mismatch, not an unsupported-profile or span refusal.

The target keeps the cursor in r2 and loads the first mask before loading byte0.
All candidates keep it in r3 and load byte0 into r2 before the first mask. Later
byte shifts and masks also use different r0/r2/r3 registers, and the final cursor
add/store use r3 instead of r2. Both sides store the assembled word through r4,
use identical masks, then advance the cursor by four. The exact offset-by-offset
comparison is retained in the receipt; semantic equivalence is not substituted
for byte identity.

The third source and its exact native report were moved from their owned active
paths into this directory. Earlier exact sources/reports, all three native
commands/logs/runtime receipts, all nine pre-native header hashes, three mapping
hashes, and the full ROM and compiled bodies are retained under
state/matching-081464F8-author/. No native success, success replay, extra
diagnostic compilation, broad status, Git or broker operation occurred.
