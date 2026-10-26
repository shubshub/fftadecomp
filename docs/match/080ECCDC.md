# match report - 0x080ECCDC

* source: `src/080ECCDC.c`
* verification: `elf-symbol-thumb-frame-data-v1`
* source SHA-256: `410082c0c228226e02a9434576bcc9637420c73a7441e024d573fea98c02263a`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `c67d69b3eab91c7f647fa953c46c58c5c9f019257a289fcac4a9720b39a306a1`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `209e9538d07a7172b08790af3bcf97538ef4443f189250517f43ee628f4b720d`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b584b0161c0988012906d0012947dd8020400081422bd042e0301d0821e9f73bf93de0381c0821e9f74ef9051c2d042d0c0e486178a278e378ee24a400009407240194002402940394e8f7cbff2d04ad137d192860718849420904091424f78df970880130708017e00000c4cb4f08341d201c0821e9f7e7f87188271c2b290bd80a4b32888800c41820788242c9d0481c0004010c2b29f5d9308801303080002004b0f0bc02bc084700008c913908` (176 bytes)
* compiled : `f0b584b0161c0988012906d0012947dd8020400081422bd042e0301d0821e9f73bf93de0381c0821e9f74ef9051c2d042d0c0e486178a278e378ee24a400009407240194002402940394e8f7cbff2d04ad137d192860718849420904091424f78df970880130708017e00000c4cb4f08341d201c0821e9f7e7f87188271c2b290bd80a4b32888800c41820788242c9d0481c0004010c2b29f5d9308801303080002004b0f0bc02bc084700008c913908`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 176/176 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
sub sp, #0x10                           sub sp, #0x10
adds r6, r2, #0                         adds r6, r2, #0
ldrh r1, [r1]                           ldrh r1, [r1]
cmp r1, #1                              cmp r1, #1
beq #0x80eccf6                          beq #0x80eccf6
cmp r1, #1                              cmp r1, #1
ble #0x80ecd7c                          ble #0x80ecd7c
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #1                         lsls r0, r0, #1
cmp r1, r0                              cmp r1, r0
beq #0x80ecd4c                          beq #0x80ecd4c
b #0x80ecd7c                            b #0x80ecd7c
adds r0, r6, #4                         adds r0, r6, #4
movs r1, #8                             movs r1, #8
bl #0x80d5f74                           bl #0x80d5f74
b #0x80ecd7c                            b #0x80ecd7c
adds r0, r7, #0                         adds r0, r7, #0
movs r1, #8                             movs r1, #8
bl #0x80d5fa4                           bl #0x80d5fa4
adds r5, r0, #0                         adds r5, r0, #0
lsls r5, r5, #0x10                      lsls r5, r5, #0x10
lsrs r5, r5, #0x10                      lsrs r5, r5, #0x10
ldr r0, [pc, #0x38]                     ldr r0, [pc, #0x38]
ldrb r1, [r4, #1]                       ldrb r1, [r4, #1]
ldrb r2, [r4, #2]                       ldrb r2, [r4, #2]
ldrb r3, [r4, #3]                       ldrb r3, [r4, #3]
movs r4, #0xee                          movs r4, #0xee
lsls r4, r4, #2                         lsls r4, r4, #2
str r4, [sp]                            str r4, [sp]
movs r4, #7                             movs r4, #7
str r4, [sp, #4]                        str r4, [sp, #4]
movs r4, #0                             movs r4, #0
str r4, [sp, #8]                        str r4, [sp, #8]
str r4, [sp, #0xc]                      str r4, [sp, #0xc]
bl #0x80d5cc0                           bl #0x80d5cc0
lsls r5, r5, #0x10                      lsls r5, r5, #0x10
asrs r5, r5, #0xe                       asrs r5, r5, #0xe
adds r5, r7, r5                         adds r5, r7, r5
str r0, [r5]                            str r0, [r5]
ldrh r1, [r6, #2]                       ldrh r1, [r6, #2]
rsbs r1, r1, #0                         rsbs r1, r1, #0
lsls r1, r1, #0x10                      lsls r1, r1, #0x10
asrs r1, r1, #0x10                      asrs r1, r1, #0x10
bl #0x8011058                           bl #0x8011058
ldrh r0, [r6, #2]                       ldrh r0, [r6, #2]
adds r0, #1                             adds r0, #1
strh r0, [r6, #2]                       strh r0, [r6, #2]
b #0x80ecd76                            b #0x80ecd76
adds r4, r6, #4                         adds r4, r6, #4
adds r0, r4, #0                         adds r0, r4, #0
movs r1, #8                             movs r1, #8
bl #0x80d5f24                           bl #0x80d5f24
ldrh r1, [r6, #2]                       ldrh r1, [r6, #2]
adds r7, r4, #0                         adds r7, r4, #0
cmp r1, #0x2b                           cmp r1, #0x2b
bhi #0x80ecd76                          bhi #0x80ecd76
ldr r3, [pc, #0x28]                     ldr r3, [pc, #0x28]
ldrh r2, [r6]                           ldrh r2, [r6]
lsls r0, r1, #2                         lsls r0, r1, #2
adds r4, r0, r3                         adds r4, r0, r3
ldrb r0, [r4]                           ldrb r0, [r4]
cmp r2, r0                              cmp r2, r0
beq #0x80ecd00                          beq #0x80ecd00
adds r0, r1, #1                         adds r0, r1, #1
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r1, r0, #0x10                      lsrs r1, r0, #0x10
cmp r1, #0x2b                           cmp r1, #0x2b
bls #0x80ecd62                          bls #0x80ecd62
ldrh r0, [r6]                           ldrh r0, [r6]
adds r0, #1                             adds r0, #1
strh r0, [r6]                           strh r0, [r6]
movs r0, #0                             movs r0, #0
add sp, #0x10                           add sp, #0x10
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
