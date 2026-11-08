# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `1bb991c3d11dde22a8ade5aa28385aa04fde76e7877af238178461a1db0b77ba`
* mapping SHA-256: `54cb537c5d9acfc78cfd7b5355633d6a1d943b21790dbf3a1aa3d8cd75d4ea37`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `d905de3c5c9cb55c83d03f28f8e28244d5316ab10a33735f3e3a3c9b9b8c8f72`
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
