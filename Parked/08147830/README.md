# 0x08147830 — RGB5 blend register/frame mismatch

Target: complete `[0x08147830, 0x081478DC)`, 172 bytes and 86 reachable
instructions, with no literal pool or external references.

The recovered C extracts the three five-bit channels from each input color,
scales each contribution independently by its weight divided by 16, adds the
two contributions per channel, clamps each sum to 31, and packs the channels.
The two colors are u16 inputs and the two weights are u8 inputs. The target
extracts and scales the second color before the first color.

The actual native matcher command was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x08147830
```

The final native result for the retained 32-bit channel formulation was exit 1:

```text
function  0x08147830   172 bytes (Thumb)
source    src/08147830.c
compiler  $HOME/agbcc/gcc/agbcc -mthumb-interwork -O2
compiled symbol is shorter than the indexed span: 166 < 172
```

Fixed-toolchain diagnostic assembly shows the blend/extraction/clamp stages,
but a different register allocation. The target saves r8/r9 and reserves four
stack bytes; the original 32-bit in-place channel formulation saves r8/r9/r10
and needs no explicit stack allocation. The corresponding 16-bit channel
formulation saves three high registers and reserves twelve stack bytes. Its
complete symbol is 170 bytes. It does not establish a two-byte-only mismatch,
since the register choices and frame also differ throughout the body.

Bounded natural formulations tried: in-place 32-bit channels (166 bytes),
separate scaled-second contributions (164 bytes), 16-bit channels with and
without separate scaled-second contributions (170 bytes), separate output
channels (156 bytes), and unsigned division by 16 in place of the equivalent
right shift (166 bytes). No flags, artificial frame, forced register, inert
code, assembly, or shared-file changes were used.

All native attempts stopped at the complete-symbol size guard, before byte
comparison and the native plausibility verdict. This is an ordinary C/codegen
mismatch, not an established verification-profile limitation. Byte identity
remains unverified.
