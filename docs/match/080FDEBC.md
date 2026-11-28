# match report - 0x080FDEBC

* source: `src/080FDEBC.c`
* verification: `elf-symbol-thumb-calls-v1`
* frame premise: `untracked-pointer-frame-v1`; unproved premise: no pointer the walk does not derive from SP (an incoming argument, a word read from memory, a result of code the walk does not inspect, or an absolute address) addresses stack that this function or a callee the walk inspects has allocated, except an escaped address used only as an escape premise of this report states; and no code the walk does not inspect (a callee, the BIOS, DMA or an interrupt handler) writes that stack other than the stack arguments it is passed, except as a summary or premise line of this report states
* source SHA-256: `7b01c02a4ff3e0904551403bea765f02ccdcbafd63b3ee6276ffedff4be46dbb`
* mapping SHA-256: `5bae15957462c5165e2a45f5a16aac7f91676ab61e9a1fce139cba867c15ea3c`
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
