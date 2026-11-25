# match report - 0x080BDAFC

* source: `src/080BDAFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `c01ff74b2f087ad139c69d9080c51dc44796c11d958c511c3e207d036652832b`
* mapping SHA-256: `e2ae2e69c01541ba8a185c3d90e4ec51eb18d8e84aca6061adf052ba8bb0dd48`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5054864f79efe041c00f051f8201c10bc02bc0847000004450000` (28 bytes)
* compiled : `10b5054864f79efe041c00f051f8201c10bc02bc0847000004450000`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 28/28 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
ldr r0, [pc, #0x14]                     ldr r0, [pc, #0x14]
bl #0x8022840                           bl #0x8022840
adds r4, r0, #0                         adds r4, r0, #0
bl #0x80bdbac                           bl #0x80bdbac
adds r0, r4, #0                         adds r0, r4, #0
pop {r4}                                pop {r4}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
