# match report - 0x080CCBFC

* source: `src/080CCBFC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `7b424aca58496fe9d98aaf70be9d50d250f8836e254dfe813d43b8eaeab54c1b`
* mapping SHA-256: `b561a81685b6bd566c18ffa4214aca4ff9eb00ae9b127d94b313195fa0b1ba37`
* control flow: closed leaf CFG
* data symbols SHA-256: `b640b74f1d1022315974d7eef6f4beb3384834440bd2354aadb5bd19b924d8f6`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b50548054a81180878622801d80130087001bc0047000000000002681f0000` (32 bytes)
* compiled : `00b50548054a81180878622801d80130087001bc0047000000000002681f0000`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 32/32 bytes

```
compiled                                rom
push {lr}                               push {lr}
ldr r0, [pc, #0x14]                     ldr r0, [pc, #0x14]
ldr r2, [pc, #0x14]                     ldr r2, [pc, #0x14]
adds r1, r0, r2                         adds r1, r0, r2
ldrb r0, [r1]                           ldrb r0, [r1]
cmp r0, #0x62                           cmp r0, #0x62
bhi #0x80ccc0e                          bhi #0x80ccc0e
adds r0, #1                             adds r0, #1
strb r0, [r1]                           strb r0, [r1]
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
