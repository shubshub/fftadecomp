# match report - 0x08060E0C

* source: `src/08060E0C.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `38c52f99f7f55efa5b722b47cc72af89fd051faaad5bcc85504ba6a30e9dae12`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: closed leaf CFG
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00060449800d94225200801809680918887870474cf40002` (24 bytes)
* compiled : `0006800d942149004018024909680918887870474cf40002`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 19/24 bytes

```
compiled                                rom
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
                                        ldr r1, [pc, #0x10]                       <- missing from compiled
lsrs r0, r0, #0x16                      lsrs r0, r0, #0x16
movs r1, #0x94                                                                    <- extra in compiled
lsls r1, r1, #1                                                                   <- extra in compiled
adds r0, r0, r1                                                                   <- extra in compiled
ldr r1, [pc, #8]                                                                  <- extra in compiled
                                        movs r2, #0x94                            <- missing from compiled
                                        lsls r2, r2, #1                           <- missing from compiled
                                        adds r0, r0, r2                           <- missing from compiled
ldr r1, [r1]                            ldr r1, [r1]
adds r1, r1, r0                         adds r1, r1, r0
ldrb r0, [r1, #2]                       ldrb r0, [r1, #2]
bx lr                                   bx lr
```
