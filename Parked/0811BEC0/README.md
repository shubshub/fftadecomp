# 0x0811BEC0 - near miss (344 bytes): 326 compiled; byte-identical only with volatile on a pointer-reached buffer

Retry of Parked/0811BEC0 (314 bytes) on 2026-11-16, kit fcdf2d45, default flags. The source here is the rule-abiding candidate (no volatile):
match.py says 'compiled symbol is shorter than the indexed span: 326 < 344'; plausible.py exits 0. The deficit is the reads of the destination:
five dead ldrb before strb (0811BF34, BF44, BF68, BF72, BF88) and three re-reads (BF40, BF6E, BF86).

Exact delta to byte identity: `volatile u16 right : 8; volatile u16 left : 8;` in the packed ScanlineBounds record -> 167/167, 344/344, profile
elf-symbol-thumb-frame-data-v1; then refused: bytes identical / 'source IMPLAUSIBLE (not on the allow list)' / 'HAND-ASM REQUIRED BUT NOT
ALLOWED' / ERROR: volatile on both members.

Not shipped: volatile is admitted only on evidence-backed declarations in include/ on the plausible.py allow list. The buffer is the pointer
func_080DABB4 returns (a per-scanline right/left window-edge table; consumer not traced), not a fixed-address symbol, so the kit's
tools/volatile_allow.json cannot express it. Kit issue: #168 (volatile on per-scanline HDMA and OAM RAM buffers reached through pointers).
Another writer of the same buffer, unmatched 0811435C, shows a dead ldrb before every strb; other func_080DABB4 callers likely the same
(080E61E4, 080EB740, 080EFD50, 08113220, 08119D74, 0811E1F8, 0811FD74 - rough scan only).

Corrected against Parked/0811BEC0: `row > 159` is a break (ROM falls out at 0811BFCC); phase locals and both phase pointers are s8; wrap test is
unsigned `>= sizeof(data_083A6BDC)` (20 s8 entries); record is `u16 x : 8` bit-fields in a packed struct.
Ruled out (with volatile in place): u8 locals with (s8) casts 332; signed > 19 348; u8 x : 8 members 336; unpacked struct stride 4. Not tried: an
unpacked u16 * table cast per row.
