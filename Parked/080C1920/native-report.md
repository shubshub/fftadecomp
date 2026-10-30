# match report - 0x080C1920

* source: `src/080C1920.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `f970cc2c5f15eca7def9200a531e6dcc2609dd0dec151b0fe3a4138b915b896c`
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5041c0d2007f03ffe0006002821d0201cd9f76df8000600281bd1206872f041f90006002801d0012014e0201c803000682168d5f7c8fb002805d0d9f758f80006002806d1efe704480178082008400028e9d1002010bc02bc0847a0280003` (96 bytes)
* compiled : `10b5041c0d2007f03ffe0006002820d0201cd9f76df8000600281ad1206872f041f9000600280cd1201c803000682168d5f7cafb002806d0d9f75af80006002807d1012006e005480178082008400028f7d1002010bc02bc08470000a0280003`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 80/96 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
adds r4, r0, #0                         adds r4, r0, #0
movs r0, #0xd                           movs r0, #0xd
bl #0x80c95a8                           bl #0x80c95a8
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80c1972                                                                    <- extra in compiled
                                        beq #0x80c1974                            <- missing from compiled
adds r0, r4, #0                         adds r0, r4, #0
bl #0x809aa10                           bl #0x809aa10
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c1972                                                                    <- extra in compiled
                                        bne #0x80c1974                            <- missing from compiled
ldr r0, [r4]                            ldr r0, [r4]
bl #0x8133bc4                           bl #0x8133bc4
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c1962                                                                    <- extra in compiled
                                        beq #0x80c194c                            <- missing from compiled
                                        movs r0, #1                               <- missing from compiled
                                        b #0x80c1976                              <- missing from compiled
adds r0, r4, #0                         adds r0, r4, #0
adds r0, #0x80                          adds r0, #0x80
ldr r0, [r0]                            ldr r0, [r0]
ldr r1, [r4]                            ldr r1, [r4]
bl #0x80970e8                                                                     <- extra in compiled
cmp r0, #0                              cmp r0, #0
beq #0x80c1966                                                                    <- extra in compiled
bl #0x809aa10                                                                     <- extra in compiled
                                        beq #0x80c1968                            <- missing from compiled
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
bne #0x80c1972                                                                    <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
b #0x80c1974                                                                      <- extra in compiled
ldr r0, [pc, #0x14]                                                               <- extra in compiled
                                        bne #0x80c1974                            <- missing from compiled
                                        b #0x80c1948                              <- missing from compiled
                                        ldr r0, [pc, #0x10]                       <- missing from compiled
ldrb r1, [r0]                           ldrb r1, [r0]
movs r0, #8                             movs r0, #8
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
bne #0x80c1962                                                                    <- extra in compiled
                                        bne #0x80c1948                            <- missing from compiled
movs r0, #0                             movs r0, #0
pop {r4}                                pop {r4}
pop {r1}                                pop {r1}
bx r1                                                                             <- extra in compiled
```
