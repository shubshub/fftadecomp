# match report - 0x080FDEBC

* source: `src/080FDEBC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `4881b7876fd4037cd2af7b4437f3cdbb80e0c5979ca67879232ee06d2db873e8`
* mapping SHA-256: `152998becf45afac16fa58b80404b77029c2252a4265ac04af3c927ccae97c02`
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
