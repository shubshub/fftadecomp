# match report - 0x0813ADF0

* source: `src/0813ADF0.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `d2c19ca5615a570e083a94f50ea2b6776faad832f06f484586703ec65c78cf46`
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: closed leaf CFG
* data symbols SHA-256: `2700674a140d34970193b5f305b60368eb357884472a99b78c981513153bdac4`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `70b5041cd24300238b4210d20a4e0b4de018007850400006120a3240800d401900684240581c0004030c8b42f0d3d243101c70bc02bc0847ffffff0018333908f0b557464e464546` (72 bytes)
* compiled : `f0b5051c0c1cd2430023a34212d20c488446ff270b4ee81800785040384080006044110a314002684a40581c0004030ca342f0d3d243101cf0bc02bc0847000018333908ffffff00`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 42/72 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}                                                         <- extra in compiled
adds r5, r0, #0                                                                   <- extra in compiled
adds r4, r1, #0                                                                   <- extra in compiled
                                        push {r4, r5, r6, lr}                     <- missing from compiled
                                        adds r4, r0, #0                           <- missing from compiled
mvns r2, r2                             mvns r2, r2
movs r3, #0                             movs r3, #0
cmp r3, r4                                                                        <- extra in compiled
bhs #0x813ae24                                                                    <- extra in compiled
ldr r0, [pc, #0x30]                                                               <- extra in compiled
mov ip, r0                                                                        <- extra in compiled
movs r7, #0xff                                                                    <- extra in compiled
ldr r6, [pc, #0x2c]                                                               <- extra in compiled
adds r0, r5, r3                                                                   <- extra in compiled
                                        cmp r3, r1                                <- missing from compiled
                                        bhs #0x813ae1e                            <- missing from compiled
                                        ldr r6, [pc, #0x28]                       <- missing from compiled
                                        ldr r5, [pc, #0x2c]                       <- missing from compiled
                                        adds r0, r4, r3                           <- missing from compiled
ldrb r0, [r0]                           ldrb r0, [r0]
eors r0, r2                             eors r0, r2
ands r0, r7                                                                       <- extra in compiled
lsls r0, r0, #2                                                                   <- extra in compiled
add r0, ip                                                                        <- extra in compiled
lsrs r1, r2, #8                                                                   <- extra in compiled
ands r1, r6                                                                       <- extra in compiled
ldr r2, [r0]                                                                      <- extra in compiled
eors r2, r1                                                                       <- extra in compiled
                                        lsls r0, r0, #0x18                        <- missing from compiled
                                        lsrs r2, r2, #8                           <- missing from compiled
                                        ands r2, r6                               <- missing from compiled
                                        lsrs r0, r0, #0x16                        <- missing from compiled
                                        adds r0, r0, r5                           <- missing from compiled
                                        ldr r0, [r0]                              <- missing from compiled
                                        eors r2, r0                               <- missing from compiled
adds r0, r3, #1                         adds r0, r3, #1
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r3, r0, #0x10                      lsrs r3, r0, #0x10
cmp r3, r4                                                                        <- extra in compiled
blo #0x813ae06                                                                    <- extra in compiled
                                        cmp r3, r1                                <- missing from compiled
                                        blo #0x813ae00                            <- missing from compiled
mvns r2, r2                             mvns r2, r2
adds r0, r2, #0                         adds r0, r2, #0
pop {r4, r5, r6, r7}                                                              <- extra in compiled
                                        pop {r4, r5, r6}                          <- missing from compiled
pop {r1}                                pop {r1}
bx r1                                   bx r1
                                        lsls r7, r7, #3                           <- missing from compiled
                                        adds r3, #0x18                            <- missing from compiled
```
