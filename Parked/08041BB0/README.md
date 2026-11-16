# 0x08041BB0 - record panel draw switch: bytes identical, refused (interposed-pool switch + CpuFastSet local fill) (1028 bytes)

Attempt 2026-11-16, kit fcdf2d45. agbcc -O2 .text equals the ROM's 1028 bytes outside relocation sites; all literal and jump-table
relocations resolve to the ROM words (13 case targets) and the 31 bl targets are the same callees in order.
plausible.py exit 0. Index correct; no new data symbols (g_state_03002810, data_030009E0, data_02003CB0,
g_table_085567F0). Siblings: src/08042D4C.c (same prologue, records at 0x954 stride 0xCC, CpuFastSet fill) and
src/080814B4.c (number drawing).
Refusals: default and the owner selectors bios-word-switch-local-buffers-v1, bounded-buffer-bios-mixed-fast-fill-
source-v1 (08042D4C's), bounded-buffer-guarded-switch-v1, bounded-buffer-root-guarded-switch-v1: `switch requires one
exact adjacent unsigned guard and five-op dispatch` (five literal words between the dispatch and the table pointer);
u16-scalars-v2 / -frame-v1 accept the switch but have no buffer proof (tools/match.py:4749): `stack aliases cannot cross
calls in caller-clobbered registers` (the fill word at sp+4 passed to func_08141868). match.py: "switch evidence
cannot combine frame or buffer proof profiles".
Choices the bytes do not fully pin: `u8 *buffer = data_02003CB0;` (pool reloads at 0x08041D10, 0x08041D2A; text of merged
080814B4/08041848); `string` assigned before the call in case 0 (text pointer at 0x08041CB8 before g_state at
0x08041CBA); `u8 number` in six branches (ldrb r1,[r0,#16] at 0x08041D08; as 080814B4); cases 1 and 2 as two identical
bodies (separate table entries 0x08041CE0 and 0x08041D3C, commented); func_08041848 declared with five parameters
(every call stores map to [sp] first) where its definition has four.
