# 0804D86C bounded matching attempt

This candidate remains unmatched. Two distinct natural source forms and one
explicitly authorized compiler-only diagnostic were executed. No MATCH credit
or impossibility claim is made.

The complete indexed ROM span is [0x0804D86C, 0x0804D91C), 176 bytes. Both normal
native attempts reached the exact mapped switch span and layout checks, then
failed with `switch caller differs from the ROM`. The newly published one-object
word placement after the local switch table was accepted before byte inequality.
No unsupported-profile conclusion follows.

Form 1 used the actual observed case order and `flags |= 0x1C00`. The unchanged
source compiler-only diagnostic produced 176 linked bytes with exactly two
byte differences: at 0x0804D8AE ROM `11` versus compiled `10` (ldrh destination
r1 versus r0); at 0x0804D8B4 ROM `18` versus compiled `19` (copy the mask into
r0 versus r1). The other 174 bytes were identical. Full assembly, linked ELF,
linked bytes, commands and source/input pins remain in the author diagnostic.

Form 2, retained here, used the explicit mask-first assignment
`flags = 0x1C00 | flags` with the same operations, case order and helper ABI.
It again reached the exact 176-byte span check and failed byte equality.
No second compiler diagnostic was run, so its differing byte offsets are not
claimed. No third form was invented.

The second argument is a genuine byte-state pointer. The ignored first slot
remains opaque. Helper interfaces and observed low-byte result tests follow the
bounded complete ROM evidence in the immutable switch prerequisite case.
Ordinary helper ABI summaries do not prove nested SVC/division implementations.

Exact evidence: `receipt.json` and `native-failure.json` here. The author directory
is `state/matching-0804D86C-author` at the handover root; it retains both source
snapshots, normal native outputs, fresh runtime/tool/compiler/header/map pins,
whole target bytes and the sole compiler diagnostic. No report was generated.
The parent owns reservation release and any later matching decision.
