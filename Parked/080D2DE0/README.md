# 080D2DE0

Complete recovered implementation for 0x080D2DE0..0x080D2E22: 66 bytes,
29 reachable target instructions, including a two-word literal pool. It
searches the global linked list at offset 0x28C8 for the requested ten-bit
identifier and returns the matching descriptor or null.

The preserved candidate is plausible under fixed native agbcc
`-mthumb-interwork -O2`, but is not byte identical. Its complete symbol is
66 bytes. Native aligned byte score: 39/66; actual same-offset equality:
26/66 bytes. The native alignment displays 12/28 decoded instructions;
that denominator is affected by differently placed pool words and does not
replace the captured target's 29 reachable instructions.

The principal differences are node/descriptor registers (candidate r3/r2,
target r2/r3), a forward branch over the found-result return instead of the
target's preceding return stub, and literal-pool placement after that return
instead of immediately after the initial empty-list branch. The candidate's
initial PC-relative loads use offset 0x24 instead of 0x0C, and the loop and
return branches have corresponding different encodings. The matching ID
arithmetic, byte loads, mask value, global base, list offset, and null result
are preserved.

Natural forms tried: a direct while traversal with early return (62-byte
symbol, shorter than the indexed target); an explicit head pointer and
nonempty-list do-while traversal (66 bytes, the preserved byte pattern);
returning the descriptor after breaking out of the loop (68 bytes, additional
node test); a descriptor local outside the do-while body with early return
(66 bytes, unchanged pattern); and the preserved inequality/else-return
form (66 bytes, unchanged pattern).

The native report and complete output are retained in the private address
scratch as best-native-report.md and last-native-output.txt. No compiler
flags, shared metadata, or verification rules changed. This is a bounded
unresolved source-generation gap, not an impossibility claim.
