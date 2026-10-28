# 080CC2B4: bounded matching attempt

Complete indexed target: `[0x080CC2B4, 0x080CC300)`, 76 bytes and 36 reachable instructions. The retained complete natural C compacts the 20-element halfword table at `0x02001F3C`: each zero slot receives the next nonzero value, and that value's old slot is cleared. Both loop indices are bytes, as in the target.

The final fixed native match returned exit 1, `NOT MATCHING - bytes differ`. The native gate accepted source plausibility and the complete compiled symbol as a closed leaf CFG without relocations. The compiled symbol is 80 bytes with 38 instructions, four bytes longer than the target.

The principal remaining difference is table-base register allocation. The candidate retains the outer table base through `ip`, adding `mov ip, r7` and `mov r2, ip`; the target uses `r7` directly for the outer load. The candidate also computes the inner destination from the outer base, while the target uses the newly loaded inner base. This changes saved-register assignments, literal displacement, and branch destinations. The first 76 bytes have only 8 equal bytes at identical offsets because the extra instructions shift the body. The matcher's aligned score compares its 80-byte compiled window, including bytes beyond the indexed target; it is not complete-target equality and earns no match credit.

A local absolute table pointer compiled to 90 bytes. A local alias inside the empty-slot branch compiled to 106 bytes. Factoring the fill operation into a fully inlined semantic helper retained the same 80-byte gap. The minimal direct nested-loop candidate is preserved here. This is a bounded code-generation gap, not a claim of unmatchability.

Final native log: `/home/user/.codex-work/ffta-ulw/audio-following-v262-matching/080CC2B4/match-current.log`.

Command, from the v262 private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x080CC2B4
```

The tested source is retained as `080CC2B4.c` beside this file. Unmatched active source/report files were removed after this result. No shared files were changed.
