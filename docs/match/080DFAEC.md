# match report - 0x080DFAEC

* source: `src/080DFAEC.c`
* verification: `elf-symbol-thumb-calls-v1`
* frame premise: `untracked-pointer-frame-v1`; unproved premise: no pointer the walk does not derive from SP (an incoming argument, a word read from memory, a result of code the walk does not inspect, or an absolute address) addresses stack that this function or a callee the walk inspects has allocated, except an escaped address used only as an escape premise of this report states; and no code the walk does not inspect (a callee, the BIOS, DMA or an interrupt handler) writes that stack other than the stack arguments it is passed, except as a summary or premise line of this report states
* source SHA-256: `932dd481fb8002f09e43a6947930676623c252a17168f6caddc0cb878f0a79fe`
* mapping SHA-256: `5bae15957462c5165e2a45f5a16aac7f91676ab61e9a1fce139cba867c15ea3c`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b526f785f8c28803491140034a1140c18001bc00470000ff7f0000fdff0000` (32 bytes)
* compiled : `00b526f785f8c28803491140034a1140c18001bc00470000ff7f0000fdff0000`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 32/32 bytes

```
compiled                                rom
push {lr}                               push {lr}
bl #0x8005bfc                           bl #0x8005bfc
ldrh r2, [r0, #6]                       ldrh r2, [r0, #6]
ldr r1, [pc, #0xc]                      ldr r1, [pc, #0xc]
ands r1, r2                             ands r1, r2
ldr r2, [pc, #0xc]                      ldr r2, [pc, #0xc]
ands r1, r2                             ands r1, r2
strh r1, [r0, #6]                       strh r1, [r0, #6]
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
