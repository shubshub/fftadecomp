# 0x080FD6E8 — unmatched ordinary C attempt

The fixed `agbcc -mthumb-interwork -O2` build produces a **956-byte, 420-instruction** function. The indexed target is **968 bytes, 426 instructions**, ending at `0x080FDAB0`. The existing matcher exits 1 with `compiled symbol is shorter than the indexed span: 956 < 968`; no exact match or qualification is claimed.

The target reads each previous byte before overwriting both lanes in all three pair-writing loops. The candidate omits six static byte-load instructions at target sites `0x080FD83C`, `0x080FD844`, `0x080FD868`, `0x080FD86E`, `0x080FD89E` and `0x080FD8A6`. The missing six instructions account for twelve code bytes. Register allocation, address-constant reuse and shared phase-store placement also differ, so adding twelve bytes would not establish a match. The matcher stops at the size mismatch before complete linked-byte comparison or plausibility qualification.

Natural representations tried:

- An ordinary unpacked byte-bitfield pair is rounded to four bytes by this compiler and gives the wrong stride and later payload offsets; that candidate was rejected.
- Packed two-byte pairs with unsigned 8-, 16- and 32-bit full-byte bitfields all omit the old-byte reads. The preserved candidate uses 8-bit fields.
- Signed packed bitfields, nested packed byte fields and per-field packing also omit those reads in bounded compiler probes.
- An unpacked bitfield view over halfword storage omits the reads and changes code shape further; it was rejected.

No discarded read, inert mask expression, assembly, volatile qualifier, pragma, alternate compiler flags or verifier workaround was added. This records a bounded unmatched attempt, not impossibility.

The candidate preserves the three finite write sequences and byte-sized induction variables: 64 pairs `(12,16)`, eleven descending groups of three pairs from `(11,16)` through `(1,16)`, then 63 pairs `(0,16)`. It separates counter zero at entry from decrementing one to zero, sequences the display helper before the signed position read, retains the 21-bit numeric supervisor mask, preserves ordered readiness and handle polls, and reads the halfword global after the mask helper returns. The omitted old-byte reads remain an explicit fidelity gap.

Structs and arrays are reconstructed access views, not recovered original declarations or extents. Named data declarations are unsized address bindings. Valid storage, separate later phases/status/handles, returning opaque helpers and supervisor behavior remain premises. No scheduler, allocation initialization, universal ABI or supervisor copying semantics are established.

Reproduce after placing this candidate at `src/080FD6E8.c` in an authorized lane:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x080FD6E8
```
