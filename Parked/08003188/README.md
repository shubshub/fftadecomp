# 08003188 — bounded natural-source extent gap

Target: `08003188..080031E8`, 96 bytes / 48 reachable Thumb instructions.
The preserved natural hexadecimal formatter was tested with unchanged
`agbcc -mthumb-interwork -O2`; its complete symbol is 92 bytes /
46 instructions. The native matcher returned exit 1 with
`compiled symbol is shorter than the indexed span: 92 < 96`.
The extent gate stopped first: no native byte-equality or source-plausibility
acceptance is claimed.

Both bodies reverse-write uppercase hexadecimal cells, OR each character
with the u16 attributes, left-pad the six-cell field with spaces, and write
a zero terminator. The signed-word input is shifted through its unsigned
16-bit representation so all bit patterns terminate.

The target shifts the working representation right by 20, then normalizes
it through `lsl #16; lsr #16` and compares the shifted intermediate to zero.
The compiler keeps the already bounded right-shift result directly, omitting
the two normalization instructions and comparing that result. Other remaining
instruction-order differences are earlier initialization of the six-cell
counter and reversed decimal/letter branch placement. Pointer, attribute,
working-value, and loop-counter register assignments otherwise agree with
the target in this preserved form.

The initial unsigned inline expression produced 84 bytes. Signed input with
logical nibble shifts and an unsigned padding count produced this 92-byte
form. A named signed digit with unsigned working value produced 86 bytes;
a natural inline hexadecimal-digit helper produced 80 bytes. Every tested
form stopped at the extent gate. No assembly, volatile RAM, forced inline,
compiler flags, or artificial operations were added to reproduce the missing
normalization. Unmatched active source and report were removed.
