# 0x08125FA8 - byte-identical (368 bytes), refused by the allowlisted-volatile rule

Retry of Parked/08125FA8 on 2026-11-16, kit fcdf2d45. Bytes identical 368/368 (153/153) with default flags; match.py exits 1: source IMPLAUSIBLE
(not on the allow list) / 'HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x08125FA8 is not on the hand-asm allow list', findings on
`control = &g_control_flags_03000940;` (08125FA8.c:62):
- volatile-allowlist: allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry
  the qualifier to other memory
- volatile-allowlist: no `&` may precede g_control_flags_03000940 ...
--owner-runtime-profile named-data-buffer-v1 and named-data-buffer-compiler-copy80-binding-v1: source IMPLAUSIBLE / NOT VERIFIED - the selector was
not run (allowlisted volatile semantic check: the whole object (its size, alignment, address or a copy) depends on the pinned layout).

Not shipped: include/control_flags.h is the allow-listed declaration, but its rules forbid taking the block's address, and this function passes
the address to the copy callee; the volatile it needs is only admitted as member accesses.

Shape: the function snapshots the whole control block with func_081443FC(&state->saved_control, <block address>, 0x50) AND does volatile member
stores to bldcnt_lo (0x0300098A): `g_control_flags_03000940.bldcnt_lo &= ~0x1C` and `.bldcnt_lo = state->saved_control.bldcnt_lo` give the two
dead loads (08126026, 081260FA). A local pointer holding the block's address assigned before the snapshot call gives the ROM's ldr r4 placement
(passing &g_control_flags_03000940 in the call swaps r4/r5, 125/153). The kit README lists passing the block's address on as a known limit of
include/control_flags.h.

The source here uses `const void *control` as a stand-in; the natural form is a typed pointer (`__typeof__(g_control_flags_03000940) *control`,
also byte-identical, adds a typeof refusal). Do not ship the const void * form as is.
Without the header (non-volatile block or extern u8 [] as copy-only siblings 08070414 / 080312A8 / 080651FC): 364 bytes, the two dead loads are lost.
Parked sibling 08125DE8 has the same save/restore shape and the same two dead loads; very likely blocked the same way (not compiled).

Kit issue: shubshub/fftadecomp-kit#224 - the allow-listed block's address cannot be taken, so a function that copies the whole block and also does volatile
member stores cannot use the declaration (a documented limit in the kit README, not tracked by an issue).
