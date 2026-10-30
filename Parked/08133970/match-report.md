# match report - 0x08133970

* source: `src/08133970.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `e753bf1eed206c4cf4369b22da5d478324bf5ee2a437a2f0b369c3411c9e4742`
* mapping SHA-256: `de8f8fa9de4981e67ef457d3c3675a96d19985b488387594f3a153b237ae1f42`
* control flow: closed leaf CFG
* data symbols SHA-256: `c6dfeaa3c18128a41d3cf5aaf93b6b81675b51508efdc53fc8a1f1a9a2a41aa8`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `0006000e034a4100091889000432891808787047b0873a08` (24 bytes)
* compiled : `0006000e034a4100091889000431891808787047b0873a08`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 23/24 bytes

```
compiled                                rom
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r0, r0, #0x18                      lsrs r0, r0, #0x18
ldr r2, [pc, #0xc]                      ldr r2, [pc, #0xc]
lsls r1, r0, #1                         lsls r1, r0, #1
adds r1, r1, r0                         adds r1, r1, r0
lsls r1, r1, #2                         lsls r1, r1, #2
adds r1, #4                                                                       <- extra in compiled
                                        adds r2, #4                               <- missing from compiled
adds r1, r1, r2                         adds r1, r1, r2
ldrb r0, [r1]                           ldrb r0, [r1]
bx lr                                   bx lr
```
