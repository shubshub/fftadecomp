# match report - 0x080DFAEC

* source: `src/080DFAEC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `a3f89ee42aca6845b83096bd57ccd0e1d5d3a19a7560311364e47bf62d0b9a41`
* mapping SHA-256: `543fd09054554bc82986d7e0d30f1480ffbdc612f5e3d75bfae0c081831c1595`
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
