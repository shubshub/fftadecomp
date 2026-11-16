# 0x080BFDB0 - fallback position search: bytes identical, refused (named data + loop-replayed buffer callee) (1054 bytes)

Attempt 2026-11-16, kit fcdf2d45. With the 12 bl targets and the data word bound to their ROM addresses, all 1054 bytes
equal ROM [0x080BFDB0, 0x080C01CE). plausible.py --strict: 0 findings. Index correct.

Needs `"data_08394658": "0x08394658"` (after data_08394650): a const s8[4] of direction offsets {0, -1, 1, -2}, ldrb
+ sign extend at 0x080BFE2C-0x080BFE36.

Refusals, with the symbol added:
- default: `buffer-call evidence does not support data relocations`
- `--owner-runtime-profile named-data-buffer-v1` / `-known-query-callee-v1` / `-dead-argument-aliases-v1` /
  `-stack-index-v1`: `buffer callee 0x0812F0D8: buffer callee 0x0812E55C: buffer callee 0x0812E4F4: inconsistent
  possible pointer offsets at control-flow join`
- `--owner-runtime-profile canonical-integer-scalar-data-source-v1`: `owner requires sole complete Thumb ELF function`

Kit gap: bounded loop replay (kit #153) is opt-in per proof class. The plain buffer path replays loops (sibling
0x080BE5F4 matches as elf-symbol-thumb-frame-buffer-calls-v2 with bounded-loop-replay-v2) but then refuses any data
relocation (tools/match.py:5960-5961); the named-data-buffer proofs accept data but do not opt into replay. In a copy
of the kit with either the data-relocation refusal removed or NamedDataBufferProof opted into loop replay, match.py
reports MATCH - byte identical.

Choices the bytes do not fully pin:
- the `u8 better` flag (ROM movs #1 at 0x080C0066, movs #0 at 0x080C0072, cmp/beq at 0x080C0074; the plain condition
  jumps directly);
- the nested func_080B7EA0(path, func_080B4A1C(...), ...) call (ROM moves the result straight to r1 at 0x080C002C);
- tile_is_open / tile_is_candidate, verbatim from merged src/080BF5A4.c (inlined at 0x080BFF5E-0x080BFF9C and
  0x080C00CA-0x080C0106);
- `if (search->status == 0) { ...; return 0; } return 1;` as in 080BF5A4 (return 1 at 0x080C01BC);
- the declaration order `u16 entries[2];` before `RangeRequest request;` (sp+4 / sp+8) is load-bearing;
- u32 i (bhi at 0x080C01A2); the layout follows 080BF5A4's PositionSearch and 080B4A1C's RangeRequest.
