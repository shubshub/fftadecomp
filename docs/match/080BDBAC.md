# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `ca09156ce2ff6735d4588f074d05def2d2272ffe2f2e751b312755035259179d`
* mapping SHA-256: `5bae15957462c5165e2a45f5a16aac7f91676ab61e9a1fce139cba867c15ea3c`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `4d26adbb4b95e3f8478b5ce751d09b04d48b19962e5be43774ce1431905f8a96`
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
