# match report - 0x080CDCEC

* source: `src/080CDCEC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `7dca1bfc3e75ea40b02a83a3c8c31c67da4d19c89022a258bf3cff2558746fbf`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ed30402100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ed30402100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xed                          adds r0, #0xed
movs r1, #0x40                          movs r1, #0x40
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdcfe                          beq #0x80cdcfe
movs r0, #1                             movs r0, #1
b #0x80cdd00                            b #0x80cdd00
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
