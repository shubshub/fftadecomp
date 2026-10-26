# match report - 0x080CDBCC

* source: `src/080CDBCC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `2156b2935d10230c8e28cc685cb9caedb8de7271b6e7189812d59a1f7ab3addc`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ea30082100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ea30082100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xea                          adds r0, #0xea
movs r1, #8                             movs r1, #8
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdbde                          beq #0x80cdbde
movs r0, #1                             movs r0, #1
b #0x80cdbe0                            b #0x80cdbe0
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
