# match report - 0x08121E9C

* source: `src/08121E9C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `adfd2fdfeae8b0f8875257527ff20f785b04f8280a31a39ec7ec99e73daef99c`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `30b50f4c0f4d28680f49e5f647f920600e4a0d49126820f0cbf9286880214901e5f63cf92168486080214901e3f6a4fe216808600648007b086130bc01bc0047cc590102c459010258090000b8d4360890f3000270b50e4c` (88 bytes)
* compiled : `70b5104d104e3068104c211ce5f646f928600f490a68211c20f0caf9306880246401211ce5f63af929684860211ce3f6a3fe296808600748007b086170bc01bc00470000cc590102c459010258090000b8d4360890f30002`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 58/88 bytes

```
compiled                                rom
push {r4, r5, r6, lr}                                                             <- extra in compiled
ldr r5, [pc, #0x40]                                                               <- extra in compiled
ldr r6, [pc, #0x40]                                                               <- extra in compiled
ldr r0, [r6]                                                                      <- extra in compiled
ldr r4, [pc, #0x40]                                                               <- extra in compiled
adds r1, r4, #0                                                                   <- extra in compiled
bl #0x8007138                                                                     <- extra in compiled
str r0, [r5]                                                                      <- extra in compiled
                                        push {r4, r5, lr}                         <- missing from compiled
                                        ldr r4, [pc, #0x3c]                       <- missing from compiled
                                        ldr r5, [pc, #0x3c]                       <- missing from compiled
                                        ldr r0, [r5]                              <- missing from compiled
ldr r1, [pc, #0x3c]                     ldr r1, [pc, #0x3c]
ldr r2, [r1]                                                                      <- extra in compiled
adds r1, r4, #0                                                                   <- extra in compiled
bl #0x814224c                                                                     <- extra in compiled
ldr r0, [r6]                                                                      <- extra in compiled
movs r4, #0x80                                                                    <- extra in compiled
lsls r4, r4, #5                                                                   <- extra in compiled
adds r1, r4, #0                                                                   <- extra in compiled
bl #0x8007138                                                                     <- extra in compiled
ldr r1, [r5]                                                                      <- extra in compiled
                                        vst4.8 {d22, d23, d24, d25}, [r7:0x80], r0  <- missing from compiled
                                        ldr r2, [pc, #0x38]                       <- missing from compiled
                                        ldr r1, [pc, #0x34]                       <- missing from compiled
                                        ldr r2, [r2]                              <- missing from compiled
                                        movs r1, #0x80                            <- missing from compiled
                                        lsls r1, r1, #5                           <- missing from compiled
                                        ldr r1, [r4]                              <- missing from compiled
str r0, [r1, #4]                        str r0, [r1, #4]
adds r1, r4, #0                                                                   <- extra in compiled
bl #0x8005c14                                                                     <- extra in compiled
ldr r1, [r5]                                                                      <- extra in compiled
                                        movs r1, #0x80                            <- missing from compiled
                                        lsls r1, r1, #5                           <- missing from compiled
                                        cdp2 p8, #0xa, c6, c4, c1, #1             <- missing from compiled
str r0, [r1]                            str r0, [r1]
ldr r0, [pc, #0x1c]                                                               <- extra in compiled
                                        ldr r0, [pc, #0x18]                       <- missing from compiled
ldrb r0, [r0, #0xc]                     ldrb r0, [r0, #0xc]
str r0, [r1, #0x10]                     str r0, [r1, #0x10]
pop {r4, r5, r6}                                                                  <- extra in compiled
                                        pop {r4, r5}                              <- missing from compiled
pop {r0}                                pop {r0}
bx r0                                   bx r0
                                        ldr r4, [r1, r7]                          <- missing from compiled
```
