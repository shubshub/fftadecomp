# match report - 0x080CDAAC

* source: `src/080CDAAC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `ffe7ac3e171ea005bb52fa414c371ea9205c736cb5fca3886c36bafbd0e033a4`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ea30202100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ea30202100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xea                          adds r0, #0xea
movs r1, #0x20                          movs r1, #0x20
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdabe                          beq #0x80cdabe
movs r0, #1                             movs r0, #1
b #0x80cdac0                            b #0x80cdac0
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
