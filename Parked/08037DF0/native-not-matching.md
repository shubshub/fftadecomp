# match report - 0x08037DF0

* source: `src/08037DF0.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `a072f91381cf08fb1bf9817cef8964a792f0618702fc7007bff497133d843651`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `30b50a4dcc22041c544328682018084a801809060916dff7affe29680919054a8918087030bc01bc0047000010280003cc0900008a090000` (56 bytes)
* compiled : `30b50a4dcc22041c544328680019084a801809060916dff7affe29680919054a8918087030bc01bc0047000010280003cc0900008a090000`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 54/56 bytes

```
compiled                                rom
push {r4, r5, lr}                       push {r4, r5, lr}
ldr r5, [pc, #0x28]                     ldr r5, [pc, #0x28]
movs r2, #0xcc                          movs r2, #0xcc
adds r4, r0, #0                         adds r4, r0, #0
muls r4, r2, r4                         muls r4, r2, r4
ldr r0, [r5]                            ldr r0, [r5]
adds r0, r0, r4                                                                   <- extra in compiled
                                        adds r0, r4, r0                           <- missing from compiled
ldr r2, [pc, #0x20]                     ldr r2, [pc, #0x20]
adds r0, r0, r2                         adds r0, r0, r2
lsls r1, r1, #0x18                      lsls r1, r1, #0x18
asrs r1, r1, #0x18                      asrs r1, r1, #0x18
bl #0x8017b68                           bl #0x8017b68
ldr r1, [r5]                            ldr r1, [r5]
adds r1, r1, r4                         adds r1, r1, r4
ldr r2, [pc, #0x14]                     ldr r2, [pc, #0x14]
adds r1, r1, r2                         adds r1, r1, r2
strb r0, [r1]                           strb r0, [r1]
pop {r4, r5}                            pop {r4, r5}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
