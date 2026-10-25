# match report - 0x080DFECC

* source: `src/080DFECC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `3504674884f7ce3d935879b793eb8774e9479149b196f9162c9bd794be72707f`
* mapping SHA-256: `cdc2d3bf3411f5ba6be0b801023d4d37012569c684a8258f73f8c420f6ff8ad6`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b525f743fe01bc0047` (10 bytes)
* compiled : `00b525f743fe01bc0047`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 10/10 bytes

```
compiled                                rom
push {lr}                               push {lr}
bl #0x8005b58                           bl #0x8005b58
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
