# match report - 0x080BDAFC

* source: `src/080BDAFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `cf37dbc891cdad07a81fea9a5fe4869be2c14108ebecb7032685298e2f134d89`
* mapping SHA-256: `53b679d232357713d7ddb69eb15319865d699feebf345d8ecc5bd12f6ce9ccc2`
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
