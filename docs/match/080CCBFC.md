# match report - 0x080CCBFC

* source: `src/080CCBFC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `7b424aca58496fe9d98aaf70be9d50d250f8836e254dfe813d43b8eaeab54c1b`
* mapping SHA-256: `bcf208dd735699bfd936138d6d2179e9dba347aa1d2f0a469198ee9ea81ed20f`
* control flow: closed leaf CFG
* data symbols SHA-256: `993de1de5810b350fc9fe9175f2adfb24ea29164efd643f51c719c332b934b7e`
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
