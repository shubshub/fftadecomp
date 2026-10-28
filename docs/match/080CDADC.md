# match report - 0x080CDADC

* source: `src/080CDADC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `766f36cb042d05fb7c5b9d31e72d01b2b14398043422deb066812d4b4c5cd53a`
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
