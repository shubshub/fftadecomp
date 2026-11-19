# match report - 0x080CEECC

* source: `src/080CEECC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `19561a05cbba83f7b88288e298cdff7f9dab4e304c2838c44fd0e73324e8e2b1`
* mapping SHA-256: `15c424424228494c803616496002f734da727ae6345f480c853a95d9a49a825a`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `8f355aa0946a8c8e2a525103bfcd20c8b91227abbf9a8e98c06b6c8cca07a24e`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `30b50004050c281c2a21fff701fb0004010c002911d000220148024c031907e000000002082b0000043301323f2a02dc18788842f8d1402a2dd0281c2c21fff7e7fa0004010c002911d000220148024c031907e000000002082b0000043301323f2a02dc18788842f8d1402a13d0281c2e21fff7cdfa0004010c002912d007484900074a801809180c78281c2f21fff7bffa844206d2002005e0000000000002b4210000012030bc02bc0847` (172 bytes)
* compiled : `30b50004050c281c2a21fff701fb0004010c002911d000220148024c031907e000000002082b0000043301323f2a02dc18788842f8d1402a2dd0281c2c21fff7e7fa0004010c002911d000220148024c031907e000000002082b0000043301323f2a02dc18788842f8d1402a13d0281c2e21fff7cdfa0004010c002912d007484900074a801809180c78281c2f21fff7bffa844206d2002005e0000000000002b4210000012030bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 172/172 bytes

```
compiled                                rom
push {r4, r5, lr}                       push {r4, r5, lr}
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r5, r0, #0x10                      lsrs r5, r0, #0x10
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0x2a                          movs r1, #0x2a
bl #0x80ce4dc                           bl #0x80ce4dc
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r1, r0, #0x10                      lsrs r1, r0, #0x10
cmp r1, #0                              cmp r1, #0
beq #0x80cef06                          beq #0x80cef06
movs r2, #0                             movs r2, #0
ldr r0, [pc, #4]                        ldr r0, [pc, #4]
ldr r4, [pc, #8]                        ldr r4, [pc, #8]
adds r3, r0, r4                         adds r3, r0, r4
b #0x80ceefc                            b #0x80ceefc
adds r3, #4                             adds r3, #4
adds r2, #1                             adds r2, #1
cmp r2, #0x3f                           cmp r2, #0x3f
bgt #0x80cef02                          bgt #0x80cef02
ldrb r0, [r3]                           ldrb r0, [r3]
cmp r0, r1                              cmp r0, r1
bne #0x80ceef4                          bne #0x80ceef4
cmp r2, #0x40                           cmp r2, #0x40
beq #0x80cef62                          beq #0x80cef62
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0x2c                          movs r1, #0x2c
bl #0x80ce4dc                           bl #0x80ce4dc
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r1, r0, #0x10                      lsrs r1, r0, #0x10
cmp r1, #0                              cmp r1, #0
beq #0x80cef3a                          beq #0x80cef3a
movs r2, #0                             movs r2, #0
ldr r0, [pc, #4]                        ldr r0, [pc, #4]
ldr r4, [pc, #8]                        ldr r4, [pc, #8]
adds r3, r0, r4                         adds r3, r0, r4
b #0x80cef30                            b #0x80cef30
adds r3, #4                             adds r3, #4
adds r2, #1                             adds r2, #1
cmp r2, #0x3f                           cmp r2, #0x3f
bgt #0x80cef36                          bgt #0x80cef36
ldrb r0, [r3]                           ldrb r0, [r3]
cmp r0, r1                              cmp r0, r1
bne #0x80cef28                          bne #0x80cef28
cmp r2, #0x40                           cmp r2, #0x40
beq #0x80cef62                          beq #0x80cef62
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0x2e                          movs r1, #0x2e
bl #0x80ce4dc                           bl #0x80ce4dc
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r1, r0, #0x10                      lsrs r1, r0, #0x10
cmp r1, #0                              cmp r1, #0
beq #0x80cef70                          beq #0x80cef70
ldr r0, [pc, #0x1c]                     ldr r0, [pc, #0x1c]
lsls r1, r1, #1                         lsls r1, r1, #1
ldr r2, [pc, #0x1c]                     ldr r2, [pc, #0x1c]
adds r0, r0, r2                         adds r0, r0, r2
adds r1, r1, r0                         adds r1, r1, r0
ldrb r4, [r1]                           ldrb r4, [r1]
adds r0, r5, #0                         adds r0, r5, #0
movs r1, #0x2f                          movs r1, #0x2f
bl #0x80ce4dc                           bl #0x80ce4dc
cmp r4, r0                              cmp r4, r0
bhs #0x80cef70                          bhs #0x80cef70
movs r0, #0                             movs r0, #0
b #0x80cef72                            b #0x80cef72
movs r0, #1                             movs r0, #1
pop {r4, r5}                            pop {r4, r5}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
