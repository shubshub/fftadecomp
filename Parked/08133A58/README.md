# 0x08133A58: saved flag validation

Target: complete [0x08133A58, 0x08133ADC), **132 bytes / 63 instructions**.
The preserved natural candidate has a **136-byte complete ELF symbol** under
fixed `agbcc -mthumb-interwork -O2`; native matcher exits 1, source plausible.

The function saves the words at +0xe8/+0xec, conditionally updates the object,
checks its 44 flag bits against the selector, then restores both saved words.
The inline bit test reproduces the target's explicit Boolean conversion.

Remaining difference: saved-value/address register allocation. The target
keeps saved values in r5/r6, field addresses in r7/r8, selector in r9, and an
r10 copy of the first address for restoration. This candidate keeps saved
values in r10/r9, field addresses in r5/r6, selector in r7, and an r8 address
copy; the resulting extra moves add four bytes and shift branches/calls.

Tested natural forms: direct loop with a common restore block (124 bytes,
then 128 with explicit byte/bit offsets); word/byte union view (128); inline
whole-bitset predicate (136, preserved here); explicit saved-word pointers
(128); inline predicate parameter order (unchanged 136). No absent unused-load
sites were identified. No asm, volatile, pragmas, or compiler flag changes.

Stopped on root instruction; no further variants or matcher runs. Root owns
release of claim 6406336336, label codex-sol61-v58-08133a58.
