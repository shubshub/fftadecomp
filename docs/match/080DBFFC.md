# match report - 0x080DBFFC

* source: `src/080DBFFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `d4bd5d7fe57b6121eab155de578dca58d141f66edb9102c7174caceb64ce42d4`
* mapping SHA-256: `a26935092348963b4b7958754d65b86ee3638c439a3dfad87b8d2d75a55c55bc`
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
