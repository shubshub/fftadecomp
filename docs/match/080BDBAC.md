# match report - 0x080BDBAC

* source: `src/080BDBAC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `931dcc9b2cef49623d933da4a7a67ef6df5ab27019ec872cdd35f08b935678a2`
* mapping SHA-256: `426649b8829c461179bb445a5ebbaf234a71aa3e4f2fc3df635566cbb2017de3`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `84f2215c67743e68c6bc6c71c9d9647271af1d72a1487082b07dd6b372528c6c`
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
