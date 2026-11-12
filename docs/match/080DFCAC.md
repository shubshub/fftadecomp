# match report - 0x080DFCAC

* source: `src/080DFCAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `9488a7a81a9d3d0d36ab6b8f71f14a1bc4838662508e81876097b4fcb35264cf`
* mapping SHA-256: `fb0e746813c112a3b594465ae24ab7455a99fea21e1a226603117aae7f5092c2`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `e5b375382b98c5fa42d7de1cd919be6aa567f061c236103e2e91ee9f13267df9`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `70b50e1c151c3188012950d0012902dc002905d04be080204000814224d046e0b08a28710006002808d1281c08301621735e2021002200f091fc07e0281c08301622b35e0021202200f088fc2879002804d1014828602ae00000003f0148286025e000000000803f2c1c0834201c00f097fc09490822a85e8000401800682860201c00f0affc000600280dd02879002806d1024805e00000889b14080000803f0548286002203080286861f013fd002070bc02bc084700000000003f` (188 bytes)
* compiled : `70b50e1c151c3188012950d0012902dc002905d04be080204000814224d046e0b08a28710006002808d1281c08301621735e2021002200f091fc07e0281c08301622b35e0021202200f088fc2879002804d1014828602ae00000003f0148286025e000000000803f2c1c0834201c00f097fc09490822a85e8000401800682860201c00f0affc000600280dd02879002806d1024805e00000889b14080000803f0548286002203080286861f013fd002070bc02bc084700000000003f`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 188/188 bytes

```
compiled                                rom
push {r4, r5, r6, lr}                   push {r4, r5, r6, lr}
adds r6, r1, #0                         adds r6, r1, #0
adds r5, r2, #0                         adds r5, r2, #0
ldrh r1, [r6]                           ldrh r1, [r6]
cmp r1, #1                              cmp r1, #1
beq #0x80dfd5a                          beq #0x80dfd5a
cmp r1, #1                              cmp r1, #1
bgt #0x80dfcc2                          bgt #0x80dfcc2
cmp r1, #0                              cmp r1, #0
beq #0x80dfccc                          beq #0x80dfccc
b #0x80dfd5a                            b #0x80dfd5a
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #1                         lsls r0, r0, #1
cmp r1, r0                              cmp r1, r0
beq #0x80dfd14                          beq #0x80dfd14
b #0x80dfd5a                            b #0x80dfd5a
ldrh r0, [r6, #0x14]                    ldrh r0, [r6, #0x14]
strb r0, [r5, #4]                       strb r0, [r5, #4]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80dfce8                          bne #0x80dfce8
adds r0, r5, #0                         adds r0, r5, #0
adds r0, #8                             adds r0, #8
movs r1, #0x16                          movs r1, #0x16
ldrsh r3, [r6, r1]                      ldrsh r3, [r6, r1]
movs r1, #0x20                          movs r1, #0x20
movs r2, #0                             movs r2, #0
bl #0x80e0608                           bl #0x80e0608
b #0x80dfcf8                            b #0x80dfcf8
adds r0, r5, #0                         adds r0, r5, #0
adds r0, #8                             adds r0, #8
movs r2, #0x16                          movs r2, #0x16
ldrsh r3, [r6, r2]                      ldrsh r3, [r6, r2]
movs r1, #0                             movs r1, #0
movs r2, #0x20                          movs r2, #0x20
bl #0x80e0608                           bl #0x80e0608
ldrb r0, [r5, #4]                       ldrb r0, [r5, #4]
cmp r0, #0                              cmp r0, #0
bne #0x80dfd08                          bne #0x80dfd08
ldr r0, [pc, #4]                        ldr r0, [pc, #4]
str r0, [r5]                            str r0, [r5]
b #0x80dfd5a                            b #0x80dfd5a
ldr r0, [pc, #4]                        ldr r0, [pc, #4]
str r0, [r5]                            str r0, [r5]
b #0x80dfd5a                            b #0x80dfd5a
adds r4, r5, #0                         adds r4, r5, #0
adds r4, #8                             adds r4, #8
adds r0, r4, #0                         adds r0, r4, #0
bl #0x80e064c                           bl #0x80e064c
ldr r1, [pc, #0x24]                     ldr r1, [pc, #0x24]
movs r2, #8                             movs r2, #8
ldrsh r0, [r5, r2]                      ldrsh r0, [r5, r2]
lsls r0, r0, #2                         lsls r0, r0, #2
adds r0, r0, r1                         adds r0, r0, r1
ldr r0, [r0]                            ldr r0, [r0]
str r0, [r5]                            str r0, [r5]
adds r0, r4, #0                         adds r0, r4, #0
bl #0x80e0690                           bl #0x80e0690
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80dfd54                          beq #0x80dfd54
ldrb r0, [r5, #4]                       ldrb r0, [r5, #4]
cmp r0, #0                              cmp r0, #0
bne #0x80dfd4c                          bne #0x80dfd4c
ldr r0, [pc, #8]                        ldr r0, [pc, #8]
b #0x80dfd4e                            b #0x80dfd4e
ldr r0, [pc, #0x14]                     ldr r0, [pc, #0x14]
str r0, [r5]                            str r0, [r5]
movs r0, #2                             movs r0, #2
strh r0, [r6]                           strh r0, [r6]
ldr r0, [r5]                            ldr r0, [r5]
bl #0x8141780                           bl #0x8141780
movs r0, #0                             movs r0, #0
pop {r4, r5, r6}                        pop {r4, r5, r6}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
