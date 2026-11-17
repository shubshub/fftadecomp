# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `d8881bae917da5482577e954373f8ed719dff332487a903549265477d79c7f33`
* mapping SHA-256: `2584d01a0c36ee78c415b0207fbe9bb462a292b0d660c8882f4437b90a9e59b6`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `0c8e8df9e28902ad7a149dbafe11ae8f4e6dceb004f9f0f5ded81a8cf08580f4`
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
