# match report - 0x0801E204

* source: `src/0801E204.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `4df9c4f39311a625799f92ec095ed01056be2cd75834728e90e3d54c9b832d0f`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `70b556464d46444670b40120214d0021894628704846687002200321a870e9700120fff737ff1c498a465046e5f720fc041cc026f604301ce5f720fc0443022004432404240c201c0121e5f733f913488046e5f70dfc041c301ce5f70ffc0443032004432404240c201c0021e5f722f92e61514669614046a86108204946297768774846e88338bc9846a146aa4670bc01bc0047407f00020070000600600006f0b557464e464546` (168 bytes)
* compiled : `70b556464d46444670b4244d0020814601202870484668700220a8700320e8700120fff737ff1e488246e5f721fc041c2404240cc026f604301ce5f71ffc04432404240c02200443201c0121e5f732f914488046e5f70cfc041c2404240c301ce5f70cfc04432404c02080022043000c0021e5f71ff92e61504668614046a86148462877082068774846e88338bc9846a146aa4670bc01bc00470000407f00020070000600600006`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 123/168 bytes

```
compiled                                rom
push {r4, r5, r6, lr}                   push {r4, r5, r6, lr}
mov r6, sl                              mov r6, sl
mov r5, sb                              mov r5, sb
mov r4, r8                              mov r4, r8
push {r4, r5, r6}                       push {r4, r5, r6}
ldr r5, [pc, #0x90]                                                               <- extra in compiled
movs r0, #0                                                                       <- extra in compiled
mov sb, r0                                                                        <- extra in compiled
movs r0, #1                             movs r0, #1
                                        ldr r5, [pc, #0x84]                       <- missing from compiled
                                        movs r1, #0                               <- missing from compiled
                                        mov sb, r1                                <- missing from compiled
strb r0, [r5]                           strb r0, [r5]
mov r0, sb                              mov r0, sb
strb r0, [r5, #1]                       strb r0, [r5, #1]
movs r0, #2                             movs r0, #2
                                        movs r1, #3                               <- missing from compiled
strb r0, [r5, #2]                       strb r0, [r5, #2]
movs r0, #3                                                                       <- extra in compiled
strb r0, [r5, #3]                                                                 <- extra in compiled
                                        strb r1, [r5, #3]                         <- missing from compiled
movs r0, #1                             movs r0, #1
bl #0x801e098                           bl #0x801e098
ldr r0, [pc, #0x78]                                                               <- extra in compiled
mov sl, r0                                                                        <- extra in compiled
bl #0x8003a74                                                                     <- extra in compiled
                                        ldr r1, [pc, #0x70]                       <- missing from compiled
                                        mov sl, r1                                <- missing from compiled
                                        mov r0, sl                                <- missing from compiled
adds r4, r0, #0                         adds r4, r0, #0
lsls r4, r4, #0x10                                                                <- extra in compiled
lsrs r4, r4, #0x10                                                                <- extra in compiled
movs r6, #0xc0                          movs r6, #0xc0
lsls r6, r6, #0x13                      lsls r6, r6, #0x13
adds r0, r6, #0                         adds r0, r6, #0
bl #0x8003a80                                                                     <- extra in compiled
                                        stc2 p3, c4, [r0], #-0x10                 <- missing from compiled
                                        movs r0, #2                               <- missing from compiled
orrs r4, r0                             orrs r4, r0
lsls r4, r4, #0x10                      lsls r4, r4, #0x10
lsrs r4, r4, #0x10                      lsrs r4, r4, #0x10
movs r0, #2                                                                       <- extra in compiled
orrs r4, r0                                                                       <- extra in compiled
adds r0, r4, #0                         adds r0, r4, #0
movs r1, #1                             movs r1, #1
bl #0x80034b8                                                                     <- extra in compiled
ldr r0, [pc, #0x50]                                                               <- extra in compiled
mov r8, r0                              mov r8, r0
bl #0x8003a74                                                                     <- extra in compiled
adds r4, r0, #0                                                                   <- extra in compiled
lsls r4, r4, #0x10                                                                <- extra in compiled
lsrs r4, r4, #0x10                                                                <- extra in compiled
adds r0, r6, #0                         adds r0, r6, #0
bl #0x8003a80                                                                     <- extra in compiled
orrs r4, r0                             orrs r4, r0
                                        movs r0, #3                               <- missing from compiled
                                        orrs r4, r0                               <- missing from compiled
lsls r4, r4, #0x10                      lsls r4, r4, #0x10
movs r0, #0xc0                                                                    <- extra in compiled
lsls r0, r0, #0xa                                                                 <- extra in compiled
orrs r0, r4                                                                       <- extra in compiled
lsrs r0, r0, #0x10                                                                <- extra in compiled
                                        lsrs r4, r4, #0x10                        <- missing from compiled
                                        adds r0, r4, #0                           <- missing from compiled
movs r1, #0                             movs r1, #0
bl #0x80034b8                                                                     <- extra in compiled
str r6, [r5, #0x10]                     str r6, [r5, #0x10]
mov r0, sl                                                                        <- extra in compiled
str r0, [r5, #0x14]                                                               <- extra in compiled
                                        mov r1, sl                                <- missing from compiled
                                        str r1, [r5, #0x14]                       <- missing from compiled
mov r0, r8                              mov r0, r8
str r0, [r5, #0x18]                     str r0, [r5, #0x18]
mov r0, sb                                                                        <- extra in compiled
strb r0, [r5, #0x1c]                                                              <- extra in compiled
movs r0, #8                             movs r0, #8
                                        mov r1, sb                                <- missing from compiled
                                        strb r1, [r5, #0x1c]                      <- missing from compiled
strb r0, [r5, #0x1d]                    strb r0, [r5, #0x1d]
mov r0, sb                              mov r0, sb
strh r0, [r5, #0x1e]                    strh r0, [r5, #0x1e]
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6}                        pop {r4, r5, r6}
pop {r0}                                pop {r0}
bx r0                                   bx r0
                                        ldrb r0, [r0, #0x1d]                      <- missing from compiled
                                        lsls r0, r0, #8                           <- missing from compiled
                                        strb r0, [r0]                             <- missing from compiled
```
