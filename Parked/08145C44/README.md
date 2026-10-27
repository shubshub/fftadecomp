# 08145C44

Target: complete 104-byte Thumb function, 52 reachable instructions,
0x08145C44..0x08145CAC. Fixed agbcc -mthumb-interwork -O2.

Preserved complete candidate: 92-byte ELF symbol (46 emitted instructions).
The final native matcher exited 1 at the short-extent gate: 92 < 104.
It did not reach CFG, plausibility, or byte comparison for this candidate.

The candidate implements channel-mask selection, the shared single-channel
intensity clamp, scaling, and the allowed-mask intersection. Its control-flow
shape agrees with the target. Remaining differences begin at the byte inputs:
the target retains two lsls #24 / lsrs #24 pairs after its byte loads and uses
the shifted values for division; this candidate uses the byte loads directly.
The target also restores saved r4 and copies the strength before multiplication;
the candidate uses fewer registers and omits those instructions. These six
additional target instructions account for the 12-byte extent gap, with related
register assignments differing throughout. No artificial narrowing or register
forcing was introduced to manufacture those operations.

Bounded tested forms:
- A byte-argument mask-return helper followed by the intensity branch: 96 bytes,
  rejected at the short-extent gate.
- Explicit channel branches with shared semantic inline helpers and unsigned
  volume bitfields: 106 bytes, native exit 1, source plausible, 44/106 bytes and
  8/53 instructions identical across that compiled extent. It duplicated clamp
  blocks and did not reproduce the initial extensions. The comparison included
  two bytes beyond the 104-byte target. That layout hypothesis was discarded.
- Preserved direct byte-field version with shared single-channel and scaling
  blocks: 92 bytes, short extent as above. Unsigned sums reproduce logical shifts.

No match credit. Active unmatched source/report removed.
