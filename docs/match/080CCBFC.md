# match report - 0x080CCBFC

* source: `src/080CCBFC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `7b424aca58496fe9d98aaf70be9d50d250f8836e254dfe813d43b8eaeab54c1b`
* mapping SHA-256: `dffaf9b11fde4a7c88e7273d560af830b95069e30f24a33c99c4c7472a097841`
* control flow: closed leaf CFG
* data symbols SHA-256: `585d876831ed343e811b1e1115be677da0ac9735e440dcc2855f516180d0332a`
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
