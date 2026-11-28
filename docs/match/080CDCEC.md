# match report - 0x080CDCEC

* source: `src/080CDCEC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* frame premise: `untracked-pointer-frame-v1`; unproved premise: no pointer the walk does not derive from SP (an incoming argument, a word read from memory, a result of code the walk does not inspect, or an absolute address) addresses stack that this function or a callee the walk inspects has allocated, except an escaped address used only as an escape premise of this report states; and no code the walk does not inspect (a callee, the BIOS, DMA or an interrupt handler) writes that stack other than the stack arguments it is passed, except as a summary or premise line of this report states
* source SHA-256: `0acf44b7425e9b6f92be67f5d3d003453e9908451d818c9c514e22a701532c4f`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5ed30402100780840002801d0012000e0002002bc0847` (24 bytes)
* compiled : `00b5ed30402100780840002801d0012000e0002002bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
adds r0, #0xed                          adds r0, #0xed
movs r1, #0x40                          movs r1, #0x40
ldrb r0, [r0]                           ldrb r0, [r0]
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
beq #0x80cdcfe                          beq #0x80cdcfe
movs r0, #1                             movs r0, #1
b #0x80cdd00                            b #0x80cdd00
movs r0, #0                             movs r0, #0
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
