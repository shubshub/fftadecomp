# match report - 0x080CCBFC

* source: `src/080CCBFC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `915211e1f6bc6e05af30289ae8c7f109f349d3ecbb83d56e772042b97cc37dd0`
* mapping SHA-256: `538ae90566a51200f5c57f8ec30a9f7f3be5e6c2368aa9534b2a566b29e402e8`
* control flow: closed leaf CFG
* data symbols SHA-256: `0b81e0e040aa40401e24b066cc69b87a527567739bafdb52bca77a6042faccb1`
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
