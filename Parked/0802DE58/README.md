# 0802DE58 — not matching

Target: 0x0802DE58..0x0802DF10, 184 bytes and 84 reachable instructions.
Compiler: fixed agbcc -mthumb-interwork -O2.

The retained C searches two context-selected units when mode 13 is enabled,
then 24 records at g_state_02000080 using flag mask 0x81, then 12 records at
g_state_02002FC4 using flag mask 1. It returns the first record whose byte at
0x104 is not 0xFF and matches the search key's low four bits. Each fixed-array
record has stride 0x108, with halfword flags at 0x28.

Fresh default native matching exits 1 before byte comparison or source
plausibility: "compiled symbol is shorter than the indexed span: 176 < 184".
No byte-identical or native-plausibility result is claimed.

Fixed-flag assembly diagnostics show the compiler retains the identifier
loaded for the 0xFF test and reuses it for the key comparison in each of the
three loops. The target instead reloads that identifier after loading and
shifting the key byte. Those three missing reloads account for six bytes;
the shorter body also changes literal-pool alignment and register allocation.
The retained C represents the key as a packed four-bit byte field, consistent
with the target's byte load and the related group-record access pattern.

An unpacked key bitfield and a full-width eight-bit bitfield for the unit
identifier were also tried under the same fixed compiler options. All three
forms produced a 176-byte body. The unpacked key form additionally generated
a word load instead of the target's byte load. The simpler packed-key and
ordinary unit-byte-field source was restored and freshly tested again.
No extra loads, volatile accesses or compiler options were introduced.

No unmatched active source or native report remains. The native refusal is
retained only in private address scratch.
