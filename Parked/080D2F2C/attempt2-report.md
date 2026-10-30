# match report - 0x080D2F2C

* source: `src/080D2F2C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `f55c4f4f38170bf1d32ada5fee49b44b0eb3a8a22e9ee6ce3924794a68db86b6`
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b500230a48021c84328424640017211078002800d00133121901390029f7da052b09dd03480021f6f70efb08e0000000000002a705000003480121f6f704fb10bc01bc00470000a7050000` (76 bytes)
* compiled : `10b500230a4a172184246400101c84300078002800d00133121901390029f5da052b09dd03480021f6f70efb08e0000000000002a705000003480121f6f704fb10bc01bc00470000a7050000`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 68/76 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
movs r3, #0                             movs r3, #0
ldr r2, [pc, #0x28]                                                               <- extra in compiled
movs r1, #0x17                                                                    <- extra in compiled
                                        ldr r0, [pc, #0x28]                       <- missing from compiled
                                        adds r2, r0, #0                           <- missing from compiled
                                        adds r2, #0x84                            <- missing from compiled
movs r4, #0x84                          movs r4, #0x84
lsls r4, r4, #1                         lsls r4, r4, #1
adds r0, r2, #0                                                                   <- extra in compiled
adds r0, #0x84                                                                    <- extra in compiled
ldrb r0, [r0]                                                                     <- extra in compiled
                                        movs r1, #0x17                            <- missing from compiled
                                        ldrb r0, [r2]                             <- missing from compiled
cmp r0, #0                              cmp r0, #0
beq #0x80d2f44                          beq #0x80d2f44
adds r3, #1                             adds r3, #1
adds r2, r2, r4                         adds r2, r2, r4
subs r1, #1                             subs r1, #1
cmp r1, #0                              cmp r1, #0
bge #0x80d2f38                                                                    <- extra in compiled
                                        bge #0x80d2f3c                            <- missing from compiled
cmp r3, #5                              cmp r3, #5
ble #0x80d2f64                          ble #0x80d2f64
ldr r0, [pc, #0xc]                      ldr r0, [pc, #0xc]
movs r1, #0                             movs r1, #0
bl #0x80c9574                           bl #0x80c9574
b #0x80d2f6c                            b #0x80d2f6c
ldr r0, [pc, #0xc]                      ldr r0, [pc, #0xc]
movs r1, #1                             movs r1, #1
bl #0x80c9574                           bl #0x80c9574
pop {r4}                                pop {r4}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
