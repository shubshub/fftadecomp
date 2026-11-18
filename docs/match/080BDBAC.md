# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `c66d3c5a93ae32f02687782b8fd76e3f7a34f198f6995b37cf05ece40ebf86c6`
* mapping SHA-256: `7c0936f5b8b3262a612a7e69f5385286cf26e36c158e36f5be292e57345e3cef`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `2658147de64cb2742ee034f3da4abc5e9a8eb01a957c1ae20bb54432235965db`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b5034a0349126884f04afb01bc0047b8d4360804450000` (24 bytes)
* compiled : `00b5034a0349126884f04afb01bc0047b8d4360804450000`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 24/24 bytes

```
compiled                                rom
push {lr}                               push {lr}
ldr r2, [pc, #0xc]                      ldr r2, [pc, #0xc]
ldr r1, [pc, #0xc]                      ldr r1, [pc, #0xc]
ldr r2, [r2]                            ldr r2, [r2]
bl #0x814224c                           bl #0x814224c
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
