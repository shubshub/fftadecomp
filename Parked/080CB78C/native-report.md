# match report - 0x080CB78C

* source: `src/080CB78C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `47bb291e31e5a16e1aaeaa66091026ecc511dff09aae3eeefefe67a2081711bd`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5041cfcf7f4fc0006002806d1201c0921fdf7a7fd0006000e06e02179c800401a400002494018c07a10bc02bc0847d8735208` (52 bytes)
* compiled : `10b5041cfcf7f4fc0006002806d1201c0921fdf7a7fd0006000e06e02079c100091a490002480918c87a10bc02bc0847d8735208`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 45/52 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
adds r4, r0, #0                         adds r4, r0, #0
bl #0x80c817c                           bl #0x80c817c
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80cb7a8                          bne #0x80cb7a8
adds r0, r4, #0                         adds r0, r4, #0
movs r1, #9                             movs r1, #9
bl #0x80c92f0                           bl #0x80c92f0
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r0, r0, #0x18                      lsrs r0, r0, #0x18
b #0x80cb7b6                            b #0x80cb7b6
ldrb r0, [r4, #4]                                                                 <- extra in compiled
lsls r1, r0, #3                                                                   <- extra in compiled
subs r1, r1, r0                                                                   <- extra in compiled
lsls r1, r1, #1                                                                   <- extra in compiled
ldr r0, [pc, #8]                                                                  <- extra in compiled
adds r1, r1, r0                                                                   <- extra in compiled
ldrb r0, [r1, #0xb]                                                               <- extra in compiled
                                        ldrb r1, [r4, #4]                         <- missing from compiled
                                        lsls r0, r1, #3                           <- missing from compiled
                                        subs r0, r0, r1                           <- missing from compiled
                                        lsls r0, r0, #1                           <- missing from compiled
                                        ldr r1, [pc, #8]                          <- missing from compiled
                                        adds r0, r0, r1                           <- missing from compiled
                                        ldrb r0, [r0, #0xb]                       <- missing from compiled
pop {r4}                                pop {r4}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
