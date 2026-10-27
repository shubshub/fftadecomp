# 0812C2B8 — unresolved control-byte read

Target: `[0x0812C2B8, 0x0812C4E4)`, 556 bytes, 229 reachable instructions.
The retained complete natural C candidate also emits a 556-byte ELF symbol
under fixed agbcc `-mthumb-interwork -O2`.

Fresh final native result: exit 1, complete-symbol ordinary ARM ABI call
proof, no relocations, source plausible, bytes different. The native aligned
diff reports `227/228 instructions identical (553/556 bytes)`. This alignment
score is not same-offset equality: direct comparison of the target and
compiled hex strings in the final log gives 550/556 equal bytes at identical
offsets. No exact-match credit is claimed.

The remaining mismatch is the target's unused `ldrb r1, [r4]` at
0x0812C372, immediately before the control byte at offset 0x4A of 0x03000940
is stored. The candidate computes and stores the same masked byte but omits
that second read. A branch/literal-pool layout difference accompanies it;
the aligned diff otherwise matches all recovered instructions.

The source recovers the complete state machine: allocation and display-state
snapshot; display flag and target-mask setup; scene-dependent initialization;
selection polling and index narrowing; two processing phases with bounded
retry counters; message display and wait; a 60-frame countdown; resource
cleanup and owner-completion notification. States 0, 1 and 0x100 through 0x107
are covered, and the incoming context is unused. The function returns zero.

Delaying the named display-pointer initialization until after owner/counter
setup recovered the target's command-pointer and switch-constant register
allocation. Natural byte-, halfword-, and word-based eight-bit field models
were tested. An explicit masked byte local was also tested. None retained the
second read. The best compound-assignment form was restored and freshly
checked before parking. The field declaration is a candidate model, not a
confirmed reconstruction of the original type.

No volatile qualifier, artificial discarded read, assembly, forced inline,
extra emitted function, compiler-option change, or dead code was introduced.
Further recovery needs evidence for a legitimate access/type form that
explains the extra read. This residual is not proof of unmatchability.

The complete target and fresh final matcher output remain in the sibling
address scratch directory as `target-disassembly.md` and `match-current.log`.
The unmatched active source and report were removed. No shared metadata,
headers, toolkit, main-game files, or other addresses were changed.
