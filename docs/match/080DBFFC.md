# match report - 0x080DBFFC

* source: `src/080DBFFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `a74e271ba7d62cf2bc989d8bad44925ea0c26ff6800cec9a362ac5606a3b4e41`
* mapping SHA-256: `c71fe2caa157aaa5181323bb96c2e9eff121749bf08ea1349ce3ba5ecdd751aa`
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
