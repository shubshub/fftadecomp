# match report - 0x080DEBAC

* source: `src/080DEBAC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `12282cbf7a327fad00378a2772f873c32092fe019c3b7d246a3a3dabf2a04894`
* mapping SHA-256: `ba5ed483ee967a46625d0d244d0d7d559746a28c70045ba8d1ed54931a6014e8`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `30b50d1c141c2988012961d0012902dc002905d05ce080204000814213d057e06a6810682060117961725179a1729179e172fdf753f8e0712072607aa071a88a0130a08044e0a088002804d00138a080000400283cd1a0790138a0710006020e002a35d1a07a002808d0217a08202056032801d122720ae0481c07e0217a08202056002801d1032000e0481e2072a089002806d02068a1890822a256fff770fa05e02068082161560022fff771fb607aa071e27a0b21615601204042814201d0501ee0720b202056002801d102202880002030bc02bc0847` (216 bytes)
* compiled : `30b50d1c141c2988012961d0012902dc002905d05ce080204000814213d057e06a6810682060117961725179a1729179e172fdf753f8e0712072607aa071a88a0130a08044e0a088002804d00138a080000400283cd1a0790138a0710006020e002a35d1a07a002808d0217a08202056032801d122720ae0481c07e0217a08202056002801d1032000e0481e2072a089002806d02068a1890822a256fff770fa05e02068082161560022fff771fb607aa071e27a0b21615601204042814201d0501ee0720b202056002801d102202880002030bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 216/216 bytes

```
compiled                                rom
push {r4, r5, lr}                       push {r4, r5, lr}
adds r5, r1, #0                         adds r5, r1, #0
adds r4, r2, #0                         adds r4, r2, #0
ldrh r1, [r5]                           ldrh r1, [r5]
cmp r1, #1                              cmp r1, #1
beq #0x80dec7c                          beq #0x80dec7c
cmp r1, #1                              cmp r1, #1
bgt #0x80debc2                          bgt #0x80debc2
cmp r1, #0                              cmp r1, #0
beq #0x80debcc                          beq #0x80debcc
b #0x80dec7c                            b #0x80dec7c
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #1                         lsls r0, r0, #1
cmp r1, r0                              cmp r1, r0
beq #0x80debf2                          beq #0x80debf2
b #0x80dec7c                            b #0x80dec7c
ldr r2, [r5, #4]                        ldr r2, [r5, #4]
ldr r0, [r2]                            ldr r0, [r2]
str r0, [r4]                            str r0, [r4]
ldrb r1, [r2, #4]                       ldrb r1, [r2, #4]
strb r1, [r4, #9]                       strb r1, [r4, #9]
ldrb r1, [r2, #5]                       ldrb r1, [r2, #5]
strb r1, [r4, #0xa]                     strb r1, [r4, #0xa]
ldrb r1, [r2, #6]                       ldrb r1, [r2, #6]
strb r1, [r4, #0xb]                     strb r1, [r4, #0xb]
bl #0x80dbc88                           bl #0x80dbc88
strb r0, [r4, #7]                       strb r0, [r4, #7]
strb r0, [r4, #8]                       strb r0, [r4, #8]
ldrb r0, [r4, #9]                       ldrb r0, [r4, #9]
strb r0, [r4, #6]                       strb r0, [r4, #6]
ldrh r0, [r5, #0x14]                    ldrh r0, [r5, #0x14]
adds r0, #1                             adds r0, #1
strh r0, [r4, #4]                       strh r0, [r4, #4]
b #0x80dec7c                            b #0x80dec7c
ldrh r0, [r4, #4]                       ldrh r0, [r4, #4]
cmp r0, #0                              cmp r0, #0
beq #0x80dec02                          beq #0x80dec02
subs r0, #1                             subs r0, #1
strh r0, [r4, #4]                       strh r0, [r4, #4]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
cmp r0, #0                              cmp r0, #0
bne #0x80dec7c                          bne #0x80dec7c
ldrb r0, [r4, #6]                       ldrb r0, [r4, #6]
subs r0, #1                             subs r0, #1
strb r0, [r4, #6]                       strb r0, [r4, #6]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, #0                              cmp r2, #0
bne #0x80dec7c                          bne #0x80dec7c
ldrb r0, [r4, #0xa]                     ldrb r0, [r4, #0xa]
cmp r0, #0                              cmp r0, #0
beq #0x80dec28                          beq #0x80dec28
ldrb r1, [r4, #8]                       ldrb r1, [r4, #8]
movs r0, #8                             movs r0, #8
ldrsb r0, [r4, r0]                      ldrsb r0, [r4, r0]
cmp r0, #3                              cmp r0, #3
bne #0x80dec24                          bne #0x80dec24
strb r2, [r4, #8]                       strb r2, [r4, #8]
b #0x80dec3a                            b #0x80dec3a
adds r0, r1, #1                         adds r0, r1, #1
b #0x80dec38                            b #0x80dec38
ldrb r1, [r4, #8]                       ldrb r1, [r4, #8]
movs r0, #8                             movs r0, #8
ldrsb r0, [r4, r0]                      ldrsb r0, [r4, r0]
cmp r0, #0                              cmp r0, #0
bne #0x80dec36                          bne #0x80dec36
movs r0, #3                             movs r0, #3
b #0x80dec38                            b #0x80dec38
subs r0, r1, #1                         subs r0, r1, #1
strb r0, [r4, #8]                       strb r0, [r4, #8]
ldrh r0, [r4, #0xc]                     ldrh r0, [r4, #0xc]
cmp r0, #0                              cmp r0, #0
beq #0x80dec4e                          beq #0x80dec4e
ldr r0, [r4]                            ldr r0, [r4]
ldrh r1, [r4, #0xc]                     ldrh r1, [r4, #0xc]
movs r2, #8                             movs r2, #8
ldrsb r2, [r4, r2]                      ldrsb r2, [r4, r2]
bl #0x80de12c                           bl #0x80de12c
b #0x80dec5a                            b #0x80dec5a
ldr r0, [r4]                            ldr r0, [r4]
movs r1, #8                             movs r1, #8
ldrsb r1, [r4, r1]                      ldrsb r1, [r4, r1]
movs r2, #0                             movs r2, #0
bl #0x80de33c                           bl #0x80de33c
ldrb r0, [r4, #9]                       ldrb r0, [r4, #9]
strb r0, [r4, #6]                       strb r0, [r4, #6]
ldrb r2, [r4, #0xb]                     ldrb r2, [r4, #0xb]
movs r1, #0xb                           movs r1, #0xb
ldrsb r1, [r4, r1]                      ldrsb r1, [r4, r1]
movs r0, #1                             movs r0, #1
rsbs r0, r0, #0                         rsbs r0, r0, #0
cmp r1, r0                              cmp r1, r0
beq #0x80dec70                          beq #0x80dec70
subs r0, r2, #1                         subs r0, r2, #1
strb r0, [r4, #0xb]                     strb r0, [r4, #0xb]
movs r0, #0xb                           movs r0, #0xb
ldrsb r0, [r4, r0]                      ldrsb r0, [r4, r0]
cmp r0, #0                              cmp r0, #0
bne #0x80dec7c                          bne #0x80dec7c
movs r0, #2                             movs r0, #2
strh r0, [r5]                           strh r0, [r5]
movs r0, #0                             movs r0, #0
pop {r4, r5}                            pop {r4, r5}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
