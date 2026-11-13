# match report - 0x080DBFFC

* source: `src/080DBFFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `10432031cb82a74cf253954e6f291db547f203375c70019f14a8ba06351c04d3`
* mapping SHA-256: `b1a7635f6de7e988a6652a4e3bf68f2037565e3d9ed2d8dacc864aa880bd432d`
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
