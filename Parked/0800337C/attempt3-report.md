# match report - 0x0800337C

* source: `src/0800337C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `e8f9f4fd5ae7d8bfb5c96e7878c853c88284ac7d5e5d77b5d15702ba407fbc72`
* mapping SHA-256: `66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158`
* control flow: closed leaf CFG
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `a021c904002008800348a021490001808020c0040180704740090003` (28 bytes)
* compiled : `a021c90400200880a0214900024801808020c0040180704740090003`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 26/28 bytes

```
compiled                                rom
movs r1, #0xa0                          movs r1, #0xa0
lsls r1, r1, #0x13                      lsls r1, r1, #0x13
movs r0, #0                             movs r0, #0
strh r0, [r1]                           strh r0, [r1]
                                        ldr r0, [pc, #0xc]                        <- missing from compiled
movs r1, #0xa0                          movs r1, #0xa0
lsls r1, r1, #1                         lsls r1, r1, #1
ldr r0, [pc, #8]                                                                  <- extra in compiled
strh r1, [r0]                           strh r1, [r0]
movs r0, #0x80                          movs r0, #0x80
lsls r0, r0, #0x13                      lsls r0, r0, #0x13
strh r1, [r0]                           strh r1, [r0]
bx lr                                   bx lr
```
