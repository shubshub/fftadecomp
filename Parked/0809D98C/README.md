# 0809D98C

Target: 0x0809D98C..0x0809D9D8, complete 76 bytes and 38 instructions.
The preserved candidate also compiles to 76 bytes and 38 instructions with
agbcc -mthumb-interwork -O2. The fresh default native matcher exits 1:
source plausible, closed leaf CFG, no relocations, bytes differ.

The function searches thirteen entries of stride 0xB4 starting at table+8.
For a matching key, it loads the record pointer at entry+4, stores the four
incoming halfwords at record+0x1E, +0x20, +0x22 and +0x24, then copies the
signed first value to record+0x1C.

The only remaining difference is allocation of the second and third
halfword arguments. The target retains the second in r3 and the third in r7;
the candidate retains them in r7 and r3 respectively. Four encodings differ:

- 0x0809D99A: target lsrs r3,r3,#16; candidate lsrs r7,r3,#16.
- 0x0809D99E: target lsrs r7,r1,#16; candidate lsrs r3,r1,#16.
- 0x0809D9CA: target strh r3,[r0,#0x20]; candidate strh r7,[r0,#0x20].
- 0x0809D9CC: target strh r7,[r0,#0x22]; candidate strh r3,[r0,#0x22].

The native diff reports 34/38 instructions and 72/76 bytes identical.
Lookup addresses, loop control, branch targets, stack arguments, signed first
value conversion, store order and returns otherwise agree.

Natural forms tested include the pointer-search while and do loops and a
separate inline record setter. These retain the same argument-register
exchange. A signed 16-bit temporary initially shortened the symbol to 74
bytes; the signed 32-bit conversion in this candidate reproduces the target's
explicit sign extension. No forced registers or artificial operations were
introduced. This candidate receives no match credit.
