# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `412b060fc4dfd8cd2502622d798055604fa4213606f328e45c1cf0a9836ca8c6`
* mapping SHA-256: `dde0c6302dc8e49f8f1499e2cc2f14465eab8cd466e2cc33273b9e009bb9cf8c`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `f8fad83079df6e53492ff6a2196764d38de879cf81ee2427cb3fcfe8e9b055cf`
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
