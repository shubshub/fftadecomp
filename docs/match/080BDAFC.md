# match report - 0x080BDAFC

* source: `src/080BDAFC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `95d58d9b91df70310798cf4d0e3da7a87b206f36b726356cd3c2a0d34340bdee`
* mapping SHA-256: `c71fe2caa157aaa5181323bb96c2e9eff121749bf08ea1349ce3ba5ecdd751aa`
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
