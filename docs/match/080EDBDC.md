# match report - 0x080EDBDC

* source: `src/080EDBDC.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `579fe3aa53a58788c2136b2130ef0b4c4ddaa1aa53a95ec2301a90e29ea01421`
* mapping SHA-256: `7fa82f9e82f31c1bd120ee182b5509dc33f7cd5482f51c4446bf5b7410af7d49`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5041c002c0dd017f7e4ff002801d0012000e00020002804d0201c17f7aeff002000e0201c10bc02bc0847` (44 bytes)
* compiled : `10b5041c002c0dd017f7e4ff002801d0012000e00020002804d0201c17f7aeff002000e0201c10bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 44/44 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
adds r4, r0, #0                         adds r4, r0, #0
cmp r4, #0                              cmp r4, #0
beq #0x80edc00                          beq #0x80edc00
bl #0x8005bb0                           bl #0x8005bb0
cmp r0, #0                              cmp r0, #0
beq #0x80edbf0                          beq #0x80edbf0
movs r0, #1                             movs r0, #1
b #0x80edbf2                            b #0x80edbf2
movs r0, #0                             movs r0, #0
cmp r0, #0                              cmp r0, #0
beq #0x80edc00                          beq #0x80edc00
adds r0, r4, #0                         adds r0, r4, #0
bl #0x8005b58                           bl #0x8005b58
movs r0, #0                             movs r0, #0
b #0x80edc02                            b #0x80edc02
adds r0, r4, #0                         adds r0, r4, #0
pop {r4}                                pop {r4}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
