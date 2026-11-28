# match report - 0x080DEDFC

* source: `src/080DEDFC.c`
* verification: `elf-symbol-thumb-switches-v1`
* frame premise: `untracked-pointer-frame-v1`; unproved premise: no pointer the walk does not derive from SP (an incoming argument, a word read from memory, a result of code the walk does not inspect, or an absolute address) addresses stack that this function or a callee the walk inspects has allocated, except an escaped address used only as an escape premise of this report states; and no code the walk does not inspect (a callee, the BIOS, DMA or an interrupt handler) writes that stack other than the stack arguments it is passed, except as a summary or premise line of this report states
* source SHA-256: `d03264ba7c027a811b8a944e6310658e67a275f97923f5afb75f8862b6ef8aa7`
* mapping SHA-256: `5bae15957462c5165e2a45f5a16aac7f91676ab61e9a1fce139cba867c15ea3c`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* switches: one unsigned-guarded local Thumb word table with verified predecessor edges
* switch manifest: `{"calls":[[96,"func_080DBC88"],[216,"func_080E0608"],[236,"func_080E064C"],[242,"func_080E0690"],[274,"func_080E0608"],[316,"func_08007A4C"]],"switch":{"bound":5,"comparison":106,"default":204,"dispatch":110,"guard":108,"literal":120,"relocations":[[120,124],[124,148],[128,164],[132,180],[136,186],[140,190],[144,198]],"table":124}}`
* switch proof SHA-256: `e153d7bb341b9e27209d864abc6b1fc63d3c6f1553ed3891a96b427c3882bc17`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b50f1c141c398801291ad0012902dc002908d0bae080204000814216d0013081425fd0b2e07968086820600879a0724879e072c888a0810889e081b88a2082a4e021680020c88108829fe0208a002805d0013820820004002800d096e02068fcf714ff0006020ea07a05282ed88000014940180068874678ee0d0890ee0d08a0ee0d08b0ee0d08b6ee0d08baee0d08c2ee0d0810060016002801d0022809d1e07a12e010060016002803d0022801d0e07a0ae0e07ae08008e0e07a05e0e07ae080404201e0e07ae0802081201c14300e21635e0021802201f098fb38880130388053e02668251c1435281c01f0b0fb281c01f0cffb000600281ed000212079002800d1012121710e22a35e281c0021802201f07bfba2890c20215e0120404281420ad0501ea08100040014002804d1f08130820220388028e0207d28f788fd000400140622a15e48430002030ca07a042803d118044042020c00e01a1c2079002805d018044042030c10044042020c0e20315e18040014814205d11020315e10040014814201d0f38132820020f0bc02bc0847` (404 bytes)
* compiled : `f0b50f1c141c398801291ad0012902dc002908d0bae080204000814216d0013081425fd0b2e07968086820600879a0724879e072c888a0810889e081b88a2082a4e021680020c88108829fe0208a002805d0013820820004002800d096e02068fcf714ff0006020ea07a05282ed88000014940180068874678ee0d0890ee0d08a0ee0d08b0ee0d08b6ee0d08baee0d08c2ee0d0810060016002801d0022809d1e07a12e010060016002803d0022801d0e07a0ae0e07ae08008e0e07a05e0e07ae080404201e0e07ae0802081201c14300e21635e0021802201f098fb38880130388053e02668251c1435281c01f0b0fb281c01f0cffb000600281ed000212079002800d1012121710e22a35e281c0021802201f07bfba2890c20215e0120404281420ad0501ea08100040014002804d1f08130820220388028e0207d28f788fd000400140622a15e48430002030ca07a042803d118044042020c00e01a1c2079002805d018044042030c10044042020c0e20315e18040014814205d11020315e10040014814201d0f38132820020f0bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 404/404 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
adds r7, r1, #0                         adds r7, r1, #0
adds r4, r2, #0                         adds r4, r2, #0
ldrh r1, [r7]                           ldrh r1, [r7]
cmp r1, #1                              cmp r1, #1
beq #0x80dee3e                          beq #0x80dee3e
cmp r1, #1                              cmp r1, #1
bgt #0x80dee12                          bgt #0x80dee12
cmp r1, #0                              cmp r1, #0
beq #0x80dee22                          beq #0x80dee22
b #0x80def88                            b #0x80def88
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #1                         lsls r0, r0, #1
cmp r1, r0                              cmp r1, r0
beq #0x80dee48                          beq #0x80dee48
adds r0, #1                             adds r0, #1
cmp r1, r0                              cmp r1, r0
beq #0x80deee0                          beq #0x80deee0
b #0x80def88                            b #0x80def88
ldr r1, [r7, #4]                        ldr r1, [r7, #4]
ldr r0, [r1]                            ldr r0, [r1]
str r0, [r4]                            str r0, [r4]
ldrb r0, [r1, #4]                       ldrb r0, [r1, #4]
strb r0, [r4, #0xa]                     strb r0, [r4, #0xa]
ldrb r0, [r1, #5]                       ldrb r0, [r1, #5]
strb r0, [r4, #0xb]                     strb r0, [r4, #0xb]
ldrh r0, [r1, #6]                       ldrh r0, [r1, #6]
strh r0, [r4, #0xc]                     strh r0, [r4, #0xc]
ldrh r0, [r1, #8]                       ldrh r0, [r1, #8]
strh r0, [r4, #0xe]                     strh r0, [r4, #0xe]
ldrh r0, [r7, #0x14]                    ldrh r0, [r7, #0x14]
strh r0, [r4, #0x10]                    strh r0, [r4, #0x10]
b #0x80def88                            b #0x80def88
ldr r1, [r4]                            ldr r1, [r4]
movs r0, #0                             movs r0, #0
strh r0, [r1, #0xe]                     strh r0, [r1, #0xe]
strh r0, [r1, #0x10]                    strh r0, [r1, #0x10]
b #0x80def88                            b #0x80def88
ldrh r0, [r4, #0x10]                    ldrh r0, [r4, #0x10]
cmp r0, #0                              cmp r0, #0
beq #0x80dee5a                          beq #0x80dee5a
subs r0, #1                             subs r0, #1
strh r0, [r4, #0x10]                    strh r0, [r4, #0x10]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
cmp r0, #0                              cmp r0, #0
beq #0x80dee5a                          beq #0x80dee5a
b #0x80def88                            b #0x80def88
ldr r0, [r4]                            ldr r0, [r4]
bl #0x80dbc88                           bl #0x80dbc88
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
ldrb r0, [r4, #0xa]                     ldrb r0, [r4, #0xa]
cmp r0, #5                              cmp r0, #5
bhi #0x80deec8                          bhi #0x80deec8
lsls r0, r0, #2                         lsls r0, r0, #2
ldr r1, [pc, #4]                        ldr r1, [pc, #4]
adds r0, r0, r1                         adds r0, r0, r1
ldr r0, [r0]                            ldr r0, [r0]
mov pc, r0                              mov pc, r0
lsls r0, r2, #0x18                      lsls r0, r2, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80dee9c                          beq #0x80dee9c
cmp r0, #2                              cmp r0, #2
bne #0x80deeb0                          bne #0x80deeb0
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
b #0x80deec6                            b #0x80deec6
lsls r0, r2, #0x18                      lsls r0, r2, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80deeb0                          beq #0x80deeb0
cmp r0, #2                              cmp r0, #2
beq #0x80deeb0                          beq #0x80deeb0
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
b #0x80deec6                            b #0x80deec6
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
strh r0, [r4, #6]                       strh r0, [r4, #6]
b #0x80deec8                            b #0x80deec8
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
b #0x80deec6                            b #0x80deec6
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
strh r0, [r4, #6]                       strh r0, [r4, #6]
rsbs r0, r0, #0                         rsbs r0, r0, #0
b #0x80deec6                            b #0x80deec6
ldrb r0, [r4, #0xb]                     ldrb r0, [r4, #0xb]
strh r0, [r4, #6]                       strh r0, [r4, #6]
strh r0, [r4, #8]                       strh r0, [r4, #8]
adds r0, r4, #0                         adds r0, r4, #0
adds r0, #0x14                          adds r0, #0x14
movs r1, #0xe                           movs r1, #0xe
ldrsh r3, [r4, r1]                      ldrsh r3, [r4, r1]
movs r1, #0                             movs r1, #0
movs r2, #0x80                          movs r2, #0x80
bl #0x80e0608                           bl #0x80e0608
ldrh r0, [r7]                           ldrh r0, [r7]
adds r0, #1                             adds r0, #1
strh r0, [r7]                           strh r0, [r7]
b #0x80def88                            b #0x80def88
ldr r6, [r4]                            ldr r6, [r4]
adds r5, r4, #0                         adds r5, r4, #0
adds r5, #0x14                          adds r5, #0x14
adds r0, r5, #0                         adds r0, r5, #0
bl #0x80e064c                           bl #0x80e064c
adds r0, r5, #0                         adds r0, r5, #0
bl #0x80e0690                           bl #0x80e0690
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80def36                          beq #0x80def36
movs r1, #0                             movs r1, #0
ldrb r0, [r4, #4]                       ldrb r0, [r4, #4]
cmp r0, #0                              cmp r0, #0
bne #0x80def02                          bne #0x80def02
movs r1, #1                             movs r1, #1
strb r1, [r4, #4]                       strb r1, [r4, #4]
movs r2, #0xe                           movs r2, #0xe
ldrsh r3, [r4, r2]                      ldrsh r3, [r4, r2]
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0                             movs r1, #0
movs r2, #0x80                          movs r2, #0x80
bl #0x80e0608                           bl #0x80e0608
ldrh r2, [r4, #0xc]                     ldrh r2, [r4, #0xc]
movs r0, #0xc                           movs r0, #0xc
ldrsh r1, [r4, r0]                      ldrsh r1, [r4, r0]
movs r0, #1                             movs r0, #1
rsbs r0, r0, #0                         rsbs r0, r0, #0
cmp r1, r0                              cmp r1, r0
beq #0x80def36                          beq #0x80def36
subs r0, r2, #1                         subs r0, r2, #1
strh r0, [r4, #0xc]                     strh r0, [r4, #0xc]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
cmp r0, #0                              cmp r0, #0
bne #0x80def36                          bne #0x80def36
strh r0, [r6, #0xe]                     strh r0, [r6, #0xe]
strh r0, [r6, #0x10]                    strh r0, [r6, #0x10]
movs r0, #2                             movs r0, #2
strh r0, [r7]                           strh r0, [r7]
b #0x80def88                            b #0x80def88
ldrb r0, [r4, #0x14]                    ldrb r0, [r4, #0x14]
bl #0x8007a4c                           bl #0x8007a4c
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
movs r2, #6                             movs r2, #6
ldrsh r1, [r4, r2]                      ldrsh r1, [r4, r2]
muls r0, r1, r0                         muls r0, r1, r0
lsls r0, r0, #8                         lsls r0, r0, #8
lsrs r3, r0, #0x10                      lsrs r3, r0, #0x10
ldrb r0, [r4, #0xa]                     ldrb r0, [r4, #0xa]
cmp r0, #4                              cmp r0, #4
bne #0x80def58                          bne #0x80def58
lsls r0, r3, #0x10                      lsls r0, r3, #0x10
rsbs r0, r0, #0                         rsbs r0, r0, #0
lsrs r2, r0, #0x10                      lsrs r2, r0, #0x10
b #0x80def5a                            b #0x80def5a
adds r2, r3, #0                         adds r2, r3, #0
ldrb r0, [r4, #4]                       ldrb r0, [r4, #4]
cmp r0, #0                              cmp r0, #0
beq #0x80def6c                          beq #0x80def6c
lsls r0, r3, #0x10                      lsls r0, r3, #0x10
rsbs r0, r0, #0                         rsbs r0, r0, #0
lsrs r3, r0, #0x10                      lsrs r3, r0, #0x10
lsls r0, r2, #0x10                      lsls r0, r2, #0x10
rsbs r0, r0, #0                         rsbs r0, r0, #0
lsrs r2, r0, #0x10                      lsrs r2, r0, #0x10
movs r0, #0xe                           movs r0, #0xe
ldrsh r1, [r6, r0]                      ldrsh r1, [r6, r0]
lsls r0, r3, #0x10                      lsls r0, r3, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
cmp r1, r0                              cmp r1, r0
bne #0x80def84                          bne #0x80def84
movs r0, #0x10                          movs r0, #0x10
ldrsh r1, [r6, r0]                      ldrsh r1, [r6, r0]
lsls r0, r2, #0x10                      lsls r0, r2, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
cmp r1, r0                              cmp r1, r0
beq #0x80def88                          beq #0x80def88
strh r3, [r6, #0xe]                     strh r3, [r6, #0xe]
strh r2, [r6, #0x10]                    strh r2, [r6, #0x10]
movs r0, #0                             movs r0, #0
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
