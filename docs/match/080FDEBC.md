# match report - 0x080FDEBC

* source: `src/080FDEBC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `810d69ffaa7d7f478d120f30aa6b0c8f21c62063536403a6b5cd136018a45ad5`
* mapping SHA-256: `e2d9f89492ea232c1c99f40897a5edc041f936f1f5e830f3897a2fcc5481fd2d`
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
