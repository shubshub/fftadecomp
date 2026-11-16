# 0x0813D518 - byte-identical, refused by the volatile semantic check's decision bound (392 bytes)

Retry of Parked/0813D518 on 2026-11-16, kit fcdf2d45, default flags. The source here compiles byte-identical to the ROM
(392/392 bytes, 170/170 instructions), but match.py refuses it:

    bytes   identical
    source  IMPLAUSIBLE (not on the allow list)
    verdict HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x0813D518 is not on the hand-asm allow list
      allowlisted volatile semantic check: real compile of func_0813D518: more than 32 unknown branch conditions on one path
      (loops with unknown exit conditions are not modelled)

This is the `MAX_DECISIONS = 32` bound in tools/volatile_semantics.py: the 20-pass loop has several data-dependent branches
per pass, and the volatile reads of the shared control block (`bg0hofs`/`bg0vofs`/`bg1hofs`/`bg1vofs` in
include/control_flags.h) sit inside it. The pinned members (offsets #0xa-#0x10) are read inside
that loop, so it is not a loop that touches no pinned object. It needs further work on the semantic check, not a
selector; it is the same bound as the decision-cap cases recorded on kit issue #137.

Index row 0813D518 0813D6A0 392 170 is correct; data_0200F3B0 and data_083A9058 already exist.

What closed the older parked near miss (both one compile apart): the reference locals are `s16`, initialised to 0, with the
second call's coordinates written inline as `data_083A9058[index].x - reference_x` (agbcc keeps short locals
zero-extended: lsls/lsrs at the assignment, lsls/asrs at the use); and the sums are written definition operand first,
`data_083A9058[index].reference_x + g_control_flags_03000940.bg0hofs`. The parked file's private non-volatile struct for
0x03000940 is replaced by the shared include/control_flags.h. Struct layouts follow src/0813D4A0.c and src/0813E030.c.
Open points once it can be verified: `(u8)func_0813EDFC(...)` (the callee returns u32, the ROM tests only
the low byte); `(s16)data_0200F3B0->ids[index] == -1` on a u16 field (ldrsh for the compare, ldrh for the decrement).

kit issue: shubshub/fftadecomp-kit#137 (the volatile semantic check's path and decision bounds)
