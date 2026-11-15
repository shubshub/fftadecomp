# match report - 0x080DBFFC

* source: `src/080DBFFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `d0f90cf31f25f617716d2f16fb91539c8018c3853dbeb189a8ee9da4851ccd00`
* mapping SHA-256: `3ac7d004b278b96d4b01241ca0911632260217cae20bafdf99ef97b3935e1083`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b50906090e01f057fafff717fc0006000e02bc0847` (22 bytes)
* compiled : `00b50906090e01f057fafff717fc0006000e02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 22/22 bytes

```
compiled                                rom
push {lr}                               push {lr}
lsls r1, r1, #0x18                      lsls r1, r1, #0x18
lsrs r1, r1, #0x18                      lsrs r1, r1, #0x18
bl #0x80dd4b4                           bl #0x80dd4b4
bl #0x80db838                           bl #0x80db838
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r0, r0, #0x18                      lsrs r0, r0, #0x18
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
