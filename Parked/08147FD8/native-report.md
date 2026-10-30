# match report - 0x08147FD8

* source: `src/08147FD8.c`
* verification: `elf-symbol-thumb-frame-calls-v1`
* source SHA-256: `e4554b7485eff075a66880045d9b81c0c31ffb8c39645116171459a6fdc75917`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b581b0069c0004000c061c0904090c1204150c1b041f0c2404220c7118013909040c0c0c48844200d9041c0223002a00d101232a04111401204042814201d104200343120c0097301c211cfef7c8ff01b0f0bc02bc0847ff01000070b582b0` (96 bytes)
* compiled : `f0b581b0069c0004000c061c0904090c1b041f0c2404250c7118013909040b0c1204110c0d48834200d9031c0224002d00d101240a04111401204042814201d104200443120c0097301c191c231cfef7c7ff01b0f0bc02bc08470000ff010000`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 77/96 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
sub sp, #4                              sub sp, #4
ldr r4, [sp, #0x18]                     ldr r4, [sp, #0x18]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r0, r0, #0x10                      lsrs r0, r0, #0x10
adds r6, r0, #0                         adds r6, r0, #0
lsls r1, r1, #0x10                      lsls r1, r1, #0x10
lsrs r1, r1, #0x10                      lsrs r1, r1, #0x10
                                        lsls r2, r2, #0x10                        <- missing from compiled
                                        lsrs r5, r2, #0x10                        <- missing from compiled
lsls r3, r3, #0x10                      lsls r3, r3, #0x10
lsrs r7, r3, #0x10                      lsrs r7, r3, #0x10
lsls r4, r4, #0x10                      lsls r4, r4, #0x10
lsrs r5, r4, #0x10                                                                <- extra in compiled
                                        lsrs r2, r4, #0x10                        <- missing from compiled
adds r1, r6, r1                         adds r1, r6, r1
subs r1, #1                             subs r1, #1
lsls r1, r1, #0x10                      lsls r1, r1, #0x10
lsrs r3, r1, #0x10                                                                <- extra in compiled
lsls r2, r2, #0x10                                                                <- extra in compiled
lsrs r1, r2, #0x10                                                                <- extra in compiled
ldr r0, [pc, #0x34]                                                               <- extra in compiled
cmp r3, r0                                                                        <- extra in compiled
                                        lsrs r4, r1, #0x10                        <- missing from compiled
                                        ldr r0, [pc, #0x30]                       <- missing from compiled
                                        cmp r4, r0                                <- missing from compiled
bls #0x8148004                          bls #0x8148004
adds r3, r0, #0                                                                   <- extra in compiled
movs r4, #2                                                                       <- extra in compiled
cmp r5, #0                                                                        <- extra in compiled
                                        adds r4, r0, #0                           <- missing from compiled
                                        movs r3, #2                               <- missing from compiled
                                        cmp r2, #0                                <- missing from compiled
bne #0x814800c                          bne #0x814800c
movs r4, #1                                                                       <- extra in compiled
lsls r2, r1, #0x10                                                                <- extra in compiled
                                        movs r3, #1                               <- missing from compiled
                                        lsls r2, r5, #0x10                        <- missing from compiled
asrs r1, r2, #0x10                      asrs r1, r2, #0x10
movs r0, #1                             movs r0, #1
rsbs r0, r0, #0                         rsbs r0, r0, #0
cmp r1, r0                              cmp r1, r0
bne #0x814801c                          bne #0x814801c
movs r0, #4                             movs r0, #4
orrs r4, r0                                                                       <- extra in compiled
                                        orrs r3, r0                               <- missing from compiled
lsrs r2, r2, #0x10                      lsrs r2, r2, #0x10
str r7, [sp]                            str r7, [sp]
adds r0, r6, #0                         adds r0, r6, #0
adds r1, r3, #0                                                                   <- extra in compiled
adds r3, r4, #0                                                                   <- extra in compiled
bl #0x8146fb8                                                                     <- extra in compiled
add sp, #4                                                                        <- extra in compiled
                                        adds r1, r4, #0                           <- missing from compiled
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
                                        lsls r7, r7, #7                           <- missing from compiled
```
