# match report - 0x080DCBBC

* source: `src/080DCBBC.c`
* verification: `elf-symbol-thumb-frame-calls-v1`
* source SHA-256: `201e2f9c8c7f9df62119d7728ecd0c77f0ddced2038b68b5d56b3f8ef3a0c877`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `d7ab5f0200abc138d79c7eb0d912440cce93aa819752b455faded4d09f8a8824`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b557464e464546e0b482b00090c0202df742fd814660204844804660202df73bfd051cbaf7ccf8291cbdf779f80006040e0022a2420ad290004b46c118401900680860501c0006020ea242f4d3281c2df72cfd019460202df71efd051cbaf7aff8291cbdf772f80006040e0022a2420ad290004346c118401900680860501c0006020ea242f4d3281c2df70ffda246a0004446061960202df7fefc051cbaf78ff8291cbdf768f80006040e0022a24209d290008119401900680860501c0006020ea242f5d3281c2df7f0fc201c0027002501998f422cd253461e1800236c1ca446b34213daa8004946421811684446206881420bd0341c581c0006030ea34205da98004044116800688142f4d1b34209d1b90000980918a800484400680860781c0006070e61460806050e019b9d42d4d348462df7bafc381c02b038bc9846a146aa46f0bc02bc0847` (330 bytes)
* compiled : `f0b557464e464546e0b482b00090c0202df742fd814660204844804660202df73bfd051cbaf7ccf8291cbdf779f80006040e0022a2420ad290004b46c118401900680860501c0006020ea242f4d3281c2df72cfd019460202df71efd051cbaf7aff8291cbdf772f80006040e0022a2420ad290004346c118401900680860501c0006020ea242f4d3281c2df70ffda246a0004446061960202df7fefc051cbaf78ff8291cbdf768f80006040e0022a24209d290008119401900680860501c0006020ea242f5d3281c2df7f0fc201c0027002501998f422cd253461e1800236c1ca446b34213daa8004946421811684446206881420bd0341c581c0006030ea34205da98004044116800688142f4d1b34209d1b90000980918a800484400680860781c0006070e61460806050e019b9d42d4d348462df7bafc381c02b038bc9846a146aa46f0bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 330/330 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, sl                              mov r7, sl
mov r6, sb                              mov r6, sb
mov r5, r8                              mov r5, r8
push {r5, r6, r7}                       push {r5, r6, r7}
sub sp, #8                              sub sp, #8
str r0, [sp]                            str r0, [sp]
movs r0, #0xc0                          movs r0, #0xc0
bl #0x800a654                           bl #0x800a654
mov sb, r0                              mov sb, r0
movs r0, #0x60                          movs r0, #0x60
add r0, sb                              add r0, sb
mov r8, r0                              mov r8, r0
movs r0, #0x60                          movs r0, #0x60
bl #0x800a654                           bl #0x800a654
adds r5, r0, #0                         adds r5, r0, #0
bl #0x8096d7c                           bl #0x8096d7c
adds r1, r5, #0                         adds r1, r5, #0
bl #0x8099cdc                           bl #0x8099cdc
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r4, r0, #0x18                      lsrs r4, r0, #0x18
movs r2, #0                             movs r2, #0
cmp r2, r4                              cmp r2, r4
bhs #0x80dcc0a                          bhs #0x80dcc0a
lsls r0, r2, #2                         lsls r0, r2, #2
mov r3, sb                              mov r3, sb
adds r1, r0, r3                         adds r1, r0, r3
adds r0, r0, r5                         adds r0, r0, r5
ldr r0, [r0]                            ldr r0, [r0]
str r0, [r1]                            str r0, [r1]
adds r0, r2, #1                         adds r0, r2, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, r4                              cmp r2, r4
blo #0x80dcbf4                          blo #0x80dcbf4
adds r0, r5, #0                         adds r0, r5, #0
bl #0x800a668                           bl #0x800a668
str r4, [sp, #4]                        str r4, [sp, #4]
movs r0, #0x60                          movs r0, #0x60
bl #0x800a654                           bl #0x800a654
adds r5, r0, #0                         adds r5, r0, #0
bl #0x8096d7c                           bl #0x8096d7c
adds r1, r5, #0                         adds r1, r5, #0
bl #0x8099d08                           bl #0x8099d08
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r4, r0, #0x18                      lsrs r4, r0, #0x18
movs r2, #0                             movs r2, #0
cmp r2, r4                              cmp r2, r4
bhs #0x80dcc44                          bhs #0x80dcc44
lsls r0, r2, #2                         lsls r0, r2, #2
mov r3, r8                              mov r3, r8
adds r1, r0, r3                         adds r1, r0, r3
adds r0, r0, r5                         adds r0, r0, r5
ldr r0, [r0]                            ldr r0, [r0]
str r0, [r1]                            str r0, [r1]
adds r0, r2, #1                         adds r0, r2, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, r4                              cmp r2, r4
blo #0x80dcc2e                          blo #0x80dcc2e
adds r0, r5, #0                         adds r0, r5, #0
bl #0x800a668                           bl #0x800a668
mov sl, r4                              mov sl, r4
lsls r0, r4, #2                         lsls r0, r4, #2
mov r4, r8                              mov r4, r8
adds r6, r0, r4                         adds r6, r0, r4
movs r0, #0x60                          movs r0, #0x60
bl #0x800a654                           bl #0x800a654
adds r5, r0, #0                         adds r5, r0, #0
bl #0x8096d7c                           bl #0x8096d7c
adds r1, r5, #0                         adds r1, r5, #0
bl #0x8099d34                           bl #0x8099d34
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r4, r0, #0x18                      lsrs r4, r0, #0x18
movs r2, #0                             movs r2, #0
cmp r2, r4                              cmp r2, r4
bhs #0x80dcc82                          bhs #0x80dcc82
lsls r0, r2, #2                         lsls r0, r2, #2
adds r1, r0, r6                         adds r1, r0, r6
adds r0, r0, r5                         adds r0, r0, r5
ldr r0, [r0]                            ldr r0, [r0]
str r0, [r1]                            str r0, [r1]
adds r0, r2, #1                         adds r0, r2, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, r4                              cmp r2, r4
blo #0x80dcc6e                          blo #0x80dcc6e
adds r0, r5, #0                         adds r0, r5, #0
bl #0x800a668                           bl #0x800a668
adds r0, r4, #0                         adds r0, r4, #0
movs r7, #0                             movs r7, #0
movs r5, #0                             movs r5, #0
ldr r1, [sp, #4]                        ldr r1, [sp, #4]
cmp r7, r1                              cmp r7, r1
bhs #0x80dccee                          bhs #0x80dccee
mov r3, sl                              mov r3, sl
adds r6, r3, r0                         adds r6, r3, r0
movs r3, #0                             movs r3, #0
adds r4, r5, #1                         adds r4, r5, #1
mov ip, r4                              mov ip, r4
cmp r3, r6                              cmp r3, r6
bge #0x80dccca                          bge #0x80dccca
lsls r0, r5, #2                         lsls r0, r5, #2
mov r1, sb                              mov r1, sb
adds r2, r0, r1                         adds r2, r0, r1
ldr r1, [r2]                            ldr r1, [r2]
mov r4, r8                              mov r4, r8
ldr r0, [r4]                            ldr r0, [r4]
cmp r1, r0                              cmp r1, r0
beq #0x80dccca                          beq #0x80dccca
adds r4, r6, #0                         adds r4, r6, #0
adds r0, r3, #1                         adds r0, r3, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r3, r0, #0x18                      lsrs r3, r0, #0x18
cmp r3, r4                              cmp r3, r4
bge #0x80dccca                          bge #0x80dccca
lsls r0, r3, #2                         lsls r0, r3, #2
add r0, r8                              add r0, r8
ldr r1, [r2]                            ldr r1, [r2]
ldr r0, [r0]                            ldr r0, [r0]
cmp r1, r0                              cmp r1, r0
bne #0x80dccb4                          bne #0x80dccb4
cmp r3, r6                              cmp r3, r6
bne #0x80dcce2                          bne #0x80dcce2
lsls r1, r7, #2                         lsls r1, r7, #2
ldr r0, [sp]                            ldr r0, [sp]
adds r1, r1, r0                         adds r1, r1, r0
lsls r0, r5, #2                         lsls r0, r5, #2
add r0, sb                              add r0, sb
ldr r0, [r0]                            ldr r0, [r0]
str r0, [r1]                            str r0, [r1]
adds r0, r7, #1                         adds r0, r7, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r7, r0, #0x18                      lsrs r7, r0, #0x18
mov r1, ip                              mov r1, ip
lsls r0, r1, #0x18                      lsls r0, r1, #0x18
lsrs r5, r0, #0x18                      lsrs r5, r0, #0x18
ldr r3, [sp, #4]                        ldr r3, [sp, #4]
cmp r5, r3                              cmp r5, r3
blo #0x80dcc98                          blo #0x80dcc98
mov r0, sb                              mov r0, sb
bl #0x800a668                           bl #0x800a668
adds r0, r7, #0                         adds r0, r7, #0
add sp, #8                              add sp, #8
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
