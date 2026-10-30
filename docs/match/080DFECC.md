# match report - 0x080DFECC

* source: `src/080DFECC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `3504674884f7ce3d935879b793eb8774e9479149b196f9162c9bd794be72707f`
* mapping SHA-256: `1eafd1a48ecc13243b51cd2bffe5f077344a1a20e05bdc773c381e50d81d2233`
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
