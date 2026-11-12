# match report - 0x080FDEBC

* source: `src/080FDEBC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `77e18321ae1ff590274cb52e262a638b645a85693fde6def56f98e84d9de0c15`
* mapping SHA-256: `dde0c6302dc8e49f8f1499e2cc2f14465eab8cd466e2cc33273b9e009bb9cf8c`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5041c002c0dd007f774fe002801d0012000e00020002804d0201c07f73efe002000e0201c10bc02bc0847` (44 bytes)
* compiled : `10b5041c002c0dd007f774fe002801d0012000e00020002804d0201c07f73efe002000e0201c10bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 44/44 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
adds r4, r0, #0                         adds r4, r0, #0
cmp r4, #0                              cmp r4, #0
beq #0x80fdee0                          beq #0x80fdee0
bl #0x8005bb0                           bl #0x8005bb0
cmp r0, #0                              cmp r0, #0
beq #0x80fded0                          beq #0x80fded0
movs r0, #1                             movs r0, #1
b #0x80fded2                            b #0x80fded2
movs r0, #0                             movs r0, #0
cmp r0, #0                              cmp r0, #0
beq #0x80fdee0                          beq #0x80fdee0
adds r0, r4, #0                         adds r0, r4, #0
bl #0x8005b58                           bl #0x8005b58
movs r0, #0                             movs r0, #0
b #0x80fdee2                            b #0x80fdee2
adds r0, r4, #0                         adds r0, r4, #0
pop {r4}                                pop {r4}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
