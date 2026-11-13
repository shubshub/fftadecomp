# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `412b060fc4dfd8cd2502622d798055604fa4213606f328e45c1cf0a9836ca8c6`
* mapping SHA-256: `53b679d232357713d7ddb69eb15319865d699feebf345d8ecc5bd12f6ce9ccc2`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `df82c46cf620f8333d921a6eceec643e91c4bde8127dc4a525ed565d379c3b74`
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
