# match report - 0x080DFECC

* source: `src/080DFECC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `238ad5702a51dac6ffda98398caa0acb303fb1c9c4aff920b9d3d60d16e74aac`
* mapping SHA-256: `4fcdf0ec83e44f41cefddf07b3e17375c65a6204e581dee608592ba945358fb4`
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
