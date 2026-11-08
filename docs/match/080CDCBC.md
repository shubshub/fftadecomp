# match report - 0x080CDCBC

* source: `src/080CDCBC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `f8d442ee67c74cb3df6adb16a32f721eb78e6cdf9d79121cbf9e607ed4eb1748`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ed30102100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ed30102100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xed                          adds r0, #0xed
movs r1, #0x10                          movs r1, #0x10
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdcce                          beq #0x80cdcce
movs r0, #1                             movs r0, #1
b #0x80cdcd0                            b #0x80cdcd0
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
