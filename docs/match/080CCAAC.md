# match report - 0x080CCAAC

* source: `src/080CCAAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `606cbe4eb8e9f73679abbeee7b63f069a0402da39a5b926c36b9e0b51a31936d`
* mapping SHA-256: `63ffb8e206e7e3ab05190689a1f633c21bb20baf749f08af13579d4c4472f9e4`
* control flow: closed leaf CFG
* data symbols SHA-256: `14f0aec7b541e11f4cab39834ca44a8daa7ee0648f7fa38cded2e815bab01cc1`
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
