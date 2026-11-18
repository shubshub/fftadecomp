# match report - 0x080DFECC

* source: `src/080DFECC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `502fc38ec0cbfebc462b8cc14d9c702f6af40bb00858827d295b49709b892fea`
* mapping SHA-256: `c71fe2caa157aaa5181323bb96c2e9eff121749bf08ea1349ce3ba5ecdd751aa`
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
