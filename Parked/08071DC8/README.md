# 0x08071DC8 - unit list sort by mode: bytes identical, refused (word switch + indexed stack list passed to a callee) (872 bytes)

Attempt 2026-11-16, kit fcdf2d45. Linked at 0x08071DC8 (g_state_02000000, stub func_08087D98) the agbcc -O2 object equals the ROM's
872 bytes. plausible.py --strict: no findings. Index correct; no new data symbols (layout of src/0802DBA0.c, field
names from src/0802C270.c).
Refusals: default and bounded-buffer-root-guarded-switch-v1 `unsupported stack-alias use or escape` (0x08072052
`adds r1, r7, r0`: list[n], sp + n*8); named-data-buffer(-stack-index-v1/v2) and bounded-buffer-guarded-switch-v1
`named-data buffer caller excludes local BL and word switches`; conditional-finite-local-word-loops-v1 `finite loops
exclude local BL and word switches`; u16-scalars-v2 / -frame-v1 `unsupported stack-alias use or escape`. Closest fit:
root-guarded switch with stack-index premises (n < 24 at each list[n] site holds because n <= i <= 23, a relation
interval analysis cannot prove).
Choice the bytes do not fully pin (possibly a spare temporary): each sort case counts into a case-local `u8 n` and copies
it with `count = n;` into a function-scope `u8 count`. The ROM has the six copies (adds r4, rN, #0 at 0x08071E5E,
0x08071EC6, 0x08071F2E, 0x08071FA2, 0x0807200A, 0x0807206E); the sibling 0x08072130 (same callee, same loops) stores
the counter to data_03002818->count (strb at 0x0807221A, 0x080722A6) before its sort. One variable, or an inline sort
helper, compiles to 852 bytes.
