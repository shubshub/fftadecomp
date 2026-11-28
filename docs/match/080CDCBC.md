# match report - 0x080CDCBC

* source: `src/080CDCBC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* frame premise: `untracked-pointer-frame-v1`; unproved premise: no pointer the walk does not derive from SP (an incoming argument, a word read from memory, a result of code the walk does not inspect, or an absolute address) addresses stack that this function or a callee the walk inspects has allocated, except an escaped address used only as an escape premise of this report states; and no code the walk does not inspect (a callee, the BIOS, DMA or an interrupt handler) writes that stack other than the stack arguments it is passed, except as a summary or premise line of this report states
* source SHA-256: `1cb795167753e599a56b50a5c76a964fb773fe08737723caaa0e2c33f14d331e`
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
