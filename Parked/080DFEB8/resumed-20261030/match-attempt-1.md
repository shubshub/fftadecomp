# match report - 0x080DFEB8

* source: `src/080DFEB8.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `151c224d0760283849a8b7f669183e9477266e503ab7ca44cddbc5f2324d10f1`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b525f779fe002801d1002000e0012002bc0847` (20 bytes)
* compiled : `00b525f779fe002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 17/20 bytes

```
compiled                                rom
push {lr}                               push {lr}
bl #0x8005bb0                           bl #0x8005bb0
cmp r0, #0                              cmp r0, #0
beq #0x80dfec6                                                                    <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
b #0x80dfec8                                                                      <- extra in compiled
                                        bne #0x80dfec6                            <- missing from compiled
movs r0, #0                             movs r0, #0
                                        b #0x80dfec8                              <- missing from compiled
                                        movs r0, #1                               <- missing from compiled
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
