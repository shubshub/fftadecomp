# match report - 0x080CCAAC

* source: `src/080CCAAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `43f21d4fc06e0bd29d3b8369703d901c06adc0ebe8e1a890a379216eff0a56c1`
* mapping SHA-256: `5bae15957462c5165e2a45f5a16aac7f91676ab61e9a1fce139cba867c15ea3c`
* control flow: closed leaf CFG
* data symbols SHA-256: `4d26adbb4b95e3f8478b5ce751d09b04d48b19962e5be43774ce1431905f8a96`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b50004030c0022034c500001190888002803d10b8006e03c1f0002501c0006020e132af1d910bc01bc0047` (44 bytes)
* compiled : `10b50004030c0022034c500001190888002803d10b8006e03c1f0002501c0006020e132af1d910bc01bc0047`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 44/44 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
lsrs r3, r0, #0x10                      lsrs r3, r0, #0x10
movs r2, #0                             movs r2, #0
ldr r4, [pc, #0xc]                      ldr r4, [pc, #0xc]
lsls r0, r2, #1                         lsls r0, r2, #1
adds r1, r0, r4                         adds r1, r0, r4
ldrh r0, [r1]                           ldrh r0, [r1]
cmp r0, #0                              cmp r0, #0
bne #0x80ccac8                          bne #0x80ccac8
strh r3, [r1]                           strh r3, [r1]
b #0x80ccad2                            b #0x80ccad2
adds r0, r2, #1                         adds r0, r2, #1
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r2, r0, #0x18                      lsrs r2, r0, #0x18
cmp r2, #0x13                           cmp r2, #0x13
bls #0x80ccab6                          bls #0x80ccab6
pop {r4}                                pop {r4}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
