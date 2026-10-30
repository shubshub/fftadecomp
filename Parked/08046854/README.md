# 08046854: bounded native matching attempt

The recovered C remains unmatched. The complete indexed Thumb target is
08046854..08046910: 188 bytes and 84 reached instructions, including its
referenced literal pools. No index, header, tool or data mapping was changed
by this author.

Two natural source forms and two native invocations were retained:

1. The first form represented the observed object prefix with a flexible
   byte-array member. Native exit 1 was the agbcc declaration error
   `field `bytes' has incomplete type`. This form did not emit a complete
   body; its original source and stderr remain in author attempt-1.
2. The final form represents the actual incoming byte object as `u8 *` and
   reads the same observed byte at object+0x2A+index. Native exit 1 was
   `unsigned remainder caller requires exact complete mapped ROM bytes`.
   That error combines extent, ownership and byte checks. It does not prove
   an unsupported profile. The exact final source is this directory's C file.

Exactly one parent-authorized compiler-only diagnostic compiled unchanged
form 2 with the selected native cpp/agbcc/as/link pipeline and genuine typed
bindings for __umodsi3 (08142B28) and g_state_02000000 (02000000). The complete
linked ELF symbol is 192 bytes and 85 reached instructions, against the target's
188 bytes and 84 instructions. Complete linked bytes, assembly, ELF, relocation
metadata, instruction comparison, raw diff, commands and fixed input/runtime
pins are retained under:

`state/matching-08046854-author/attempt-2/compiler-only-diagnostic/`

The raw comparison has 106 differing offsets when comparing complete bodies
and counting the four trailing emitted bytes. The diagnostic shows differences
in address grouping, non-volatile read ordering and register allocation,
including an additional move around the two byte loads. There is no identified
independent arithmetic, control-flow or stored-value correction that justifies
a third form. No type, declaration, register, constant, padding or order change
was attempted to steer emitted bytes.

Both forms retain the observed five incoming slots, byte truncations, unsigned
remainder by 100, halfword flag updates, clamp and final store order. No object
capacity, nonalias property, semantic game meaning or unique original C spelling
is asserted. Existing unsigned-remainder support remains available; this bounded
failure is not an impossibility or unsupported-profile claim.

No diagnostic proof API or native admission replay ran. There is no MATCH,
plausibility verdict, report or match credit. The active src/report paths are
absent. Original native outputs, source/header snapshots and the final
source-bound receipt remain under `state/matching-08046854-author/`.
