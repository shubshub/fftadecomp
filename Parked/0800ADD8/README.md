# 0800ADD8 — Parked

Target: complete 0x0800ADD8..0x0800AE9E, 198 bytes and 99 reachable instructions.

The retained C masks the index to 14 bits, reads a relative offset from either
a halfword or word table according to flag 0x4000, and optionally returns that
offset and four metadata values. The compact layout supplies four bytes; the
other layout supplies four little-endian halfwords. Output pointers are optional.

With fixed agbcc `-mthumb-interwork -O2`, the retained direct parser's native
run exited 1 at the extent gate: `compiled symbol is shorter than the indexed
span: 162 < 198`. Byte comparison and source plausibility were not reached for
this candidate. There is no exact-match or plausibility claim for the retained C.

The target contains a flag-bit-0 dispatch before the two offset formats, retains
an additional high register, and has separate tail paths. The direct parser
omits that dispatch because both bit-0 branches perform the same observable
extraction, and shares the final output store. Its symbol is 36 bytes short.

Two additional reconstructions retained the observed bit-0 dispatch: duplicated
format bodies, and shared ordinary static inline format decoders. Both compiled
to 258-byte complete leaf symbols. Their native runs reached plausibility and
reported plausible source, but failed byte comparison. The native instruction
comparison for those longer symbols extends beyond this target's 198-byte span
and does not establish partial credit for the indexed target.

The simpler direct parser is retained. No assembly, volatile accesses, compiler
flags, forced inlining, or artificial memory reads were added. Raw native output
and the differing generated report remain in private address scratch outside
repository artifacts. Unmatched active source and report were removed.
