# 080034B8: control-register shadow update

Complete indexed target: [0x080034B8, 0x08003508), 80 bytes and 30 reachable instructions.

The recovered function takes a 16-bit control value and an 8-bit layer. It updates the halfword at offset 2, 4, or 6 of g_control_flags_03000940 for layers 0, 1, or 2 respectively; all other layers update offset 8. It returns no value.

The retained natural C uses 16-bit control bitfields. Fixed agbcc -mthumb-interwork -O2 emits 72 bytes and 26 instructions. The final native matcher exits 1 at the extent gate: compiled symbol is shorter than the indexed span, 72 < 80. Plausibility is not reached for this retained candidate; no match credit is claimed.

The target reads the old halfword into r1 immediately before each full halfword store. The compiler omits these four unused reads. The retained assembly otherwise reproduces the conditional selection, pointer literals, halfword stores, and epilogue. Explaining the reads requires further original-type or access-qualification evidence. No dead expressions or artificial volatile accesses were introduced.

Unpacked 32-bit-backed 16-bit fields also emitted 72 bytes. A packed representation emitted 92 bytes with byte stores and passed source plausibility, but changed the access pattern and did not match. The retained candidate preserves the target's halfword access width.

Native command (from this private matching root):

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x080034B8
```

The final native output and retained assembly are in ../080034B8/match-current.log and ../080034B8/candidate.s. Active unmatched source and report were removed.
