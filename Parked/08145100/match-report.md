# match report - 0x08145100

* source: `src/08145100.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `bae19c946a0a7af89b737515cb0385a80ed57febd7d413a71cc51052e8139b72`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `021c536b0348834203d150680249084050607047536d7368ffffff7f021c0904` (32 bytes)
* compiled : `00b5021c516b0448814203d1506803490840506001bc0047536d7368ffffff7f`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 23/32 bytes

```
compiled                                rom
push {lr}                                                                         <- extra in compiled
adds r2, r0, #0                         adds r2, r0, #0
ldr r1, [r2, #0x34]                                                               <- extra in compiled
ldr r0, [pc, #0x10]                                                               <- extra in compiled
cmp r1, r0                                                                        <- extra in compiled
bne #0x8145114                                                                    <- extra in compiled
                                        ldr r3, [r2, #0x34]                       <- missing from compiled
                                        ldr r0, [pc, #0xc]                        <- missing from compiled
                                        cmp r3, r0                                <- missing from compiled
                                        bne #0x8145112                            <- missing from compiled
ldr r0, [r2, #4]                        ldr r0, [r2, #4]
ldr r1, [pc, #0xc]                                                                <- extra in compiled
                                        ldr r1, [pc, #8]                          <- missing from compiled
ands r0, r1                             ands r0, r1
str r0, [r2, #4]                        str r0, [r2, #4]
pop {r0}                                                                          <- extra in compiled
bx r0                                                                             <- extra in compiled
                                        bx lr                                     <- missing from compiled
                                        ldr r3, [r2, #0x54]                       <- missing from compiled
                                        ldr r3, [r6, #4]                          <- missing from compiled
```
