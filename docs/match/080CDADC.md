# match report - 0x080CDADC

* source: `src/080CDADC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `95205f36212cccafa6d73fb526483f7119b49b3a60c3a4676de28b1ff0a39eae`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ea30802100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ea30802100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xea                          adds r0, #0xea
movs r1, #0x80                          movs r1, #0x80
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdaee                          beq #0x80cdaee
movs r0, #1                             movs r0, #1
b #0x80cdaf0                            b #0x80cdaf0
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
