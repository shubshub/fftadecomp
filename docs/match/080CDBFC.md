# match report - 0x080CDBFC

* source: `src/080CDBFC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `1dce4fee676cc0694b3a491e137334d23394122dba7057640010d1405a205c73`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ec30102100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ec30102100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xec                          adds r0, #0xec
movs r1, #0x10                          movs r1, #0x10
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdc0e                          beq #0x80cdc0e
movs r0, #1                             movs r0, #1
b #0x80cdc10                            b #0x80cdc10
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
