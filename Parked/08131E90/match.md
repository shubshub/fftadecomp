# parked match report - 0x08131E90

* source: `src/08131E90.c`
* verification: `elf-symbol-thumb-calls-v1`
* source SHA-256: `6d7879d14fdaaac828f4463e7c406e7fb728950889c3db16d1a78eba8fe8a78a`
* mapping SHA-256: `533ba6b9d5ca8efc1dc0fd30e750869327f18250319b1d08687ed24fad9fff36`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `10b5041c2068262196f704f8211c28310a785200083989180022895e42180a2a00dd0a222068d630028010bc01bc0047` (48 bytes)
* compiled : `10b5041c2068262196f704f8011c201c28300078400000192022805e09180a2900dd0a212068d630018010bc01bc0047`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 35/48 bytes

```
compiled                                rom
push {r4, lr}                           push {r4, lr}
adds r4, r0, #0                         adds r4, r0, #0
ldr r0, [r4]                            ldr r0, [r4]
movs r1, #0x26                          movs r1, #0x26
bl #0x80c7ea4                           bl #0x80c7ea4
adds r1, r0, #0                                                                   <- extra in compiled
adds r0, r4, #0                                                                   <- extra in compiled
adds r0, #0x28                                                                    <- extra in compiled
ldrb r0, [r0]                                                                     <- extra in compiled
lsls r0, r0, #1                                                                   <- extra in compiled
adds r0, r0, r4                                                                   <- extra in compiled
movs r2, #0x20                                                                    <- extra in compiled
ldrsh r0, [r0, r2]                                                                <- extra in compiled
adds r1, r1, r0                                                                   <- extra in compiled
cmp r1, #0xa                                                                      <- extra in compiled
                                        adds r1, r4, #0                           <- missing from compiled
                                        adds r1, #0x28                            <- missing from compiled
                                        ldrb r2, [r1]                             <- missing from compiled
                                        lsls r2, r2, #1                           <- missing from compiled
                                        subs r1, #8                               <- missing from compiled
                                        adds r1, r1, r2                           <- missing from compiled
                                        movs r2, #0                               <- missing from compiled
                                        ldrsh r1, [r1, r2]                        <- missing from compiled
                                        adds r2, r0, r1                           <- missing from compiled
                                        cmp r2, #0xa                              <- missing from compiled
ble #0x8131eb4                          ble #0x8131eb4
movs r1, #0xa                                                                     <- extra in compiled
                                        movs r2, #0xa                             <- missing from compiled
ldr r0, [r4]                            ldr r0, [r4]
adds r0, #0xd6                          adds r0, #0xd6
strh r1, [r0]                                                                     <- extra in compiled
                                        strh r2, [r0]                             <- missing from compiled
pop {r4}                                pop {r4}
pop {r0}                                pop {r0}
bx r0                                   bx r0
```
