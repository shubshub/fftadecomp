# match report - 0x080CBABC

* source: `src/080CBABC.c`
* verification: `elf-symbol-thumb-data-v1`
* source SHA-256: `4c4ac8cad76810176ea43afc5151a1733ae3cdd37aba9890ba067a221d9b0e73`
* mapping SHA-256: `9b5039711c75cf5c89ddf9949e6e12a0228f51123fd5c7c1e18da4b367f591ec`
* control flow: closed leaf CFG
* data symbols SHA-256: `1688a45a8eb25bf439f083748d23d0738c7463e2da424fe9b1f12c6267a69732`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `00b50006010e0748074a801800788007800f012814d0022822d10f2908d84801024929e000000002c22f000060ac4108081c1038400101491ee0000060ae41080f2905d84801014916e0000040b74108081c1038400101490ee0000040b941080f2907d9081c10384001014904e0000060a3410848010249401802bc0847000060a14108` (132 bytes)
* compiled : `00b50006010e0748074a801800788007800f012814d0022822d10f2908d84801024929e000000002c22f000060ac4108081c1038400101491ee0000060ae41080f2905d84801014916e0000040b74108081c1038400101490ee0000040b941080f2907d9081c10384001014904e0000060a3410848010249401802bc0847000060a14108`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 132/132 bytes

```
compiled                                rom
push {lr}                               push {lr}
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
lsrs r1, r0, #0x18                      lsrs r1, r0, #0x18
ldr r0, [pc, #0x1c]                     ldr r0, [pc, #0x1c]
ldr r2, [pc, #0x1c]                     ldr r2, [pc, #0x1c]
adds r0, r0, r2                         adds r0, r0, r2
ldrb r0, [r0]                           ldrb r0, [r0]
lsls r0, r0, #0x1e                      lsls r0, r0, #0x1e
lsrs r0, r0, #0x1e                      lsrs r0, r0, #0x1e
cmp r0, #1                              cmp r0, #1
beq #0x80cbafc                          beq #0x80cbafc
cmp r0, #2                              cmp r0, #2
bne #0x80cbb1c                          bne #0x80cbb1c
cmp r1, #0xf                            cmp r1, #0xf
bhi #0x80cbaec                          bhi #0x80cbaec
lsls r0, r1, #5                         lsls r0, r1, #5
ldr r1, [pc, #8]                        ldr r1, [pc, #8]
b #0x80cbb34                            b #0x80cbb34
adds r0, r1, #0                         adds r0, r1, #0
subs r0, #0x10                          subs r0, #0x10
lsls r0, r0, #5                         lsls r0, r0, #5
ldr r1, [pc, #4]                        ldr r1, [pc, #4]
b #0x80cbb34                            b #0x80cbb34
cmp r1, #0xf                            cmp r1, #0xf
bhi #0x80cbb0c                          bhi #0x80cbb0c
lsls r0, r1, #5                         lsls r0, r1, #5
ldr r1, [pc, #4]                        ldr r1, [pc, #4]
b #0x80cbb34                            b #0x80cbb34
adds r0, r1, #0                         adds r0, r1, #0
subs r0, #0x10                          subs r0, #0x10
lsls r0, r0, #5                         lsls r0, r0, #5
ldr r1, [pc, #4]                        ldr r1, [pc, #4]
b #0x80cbb34                            b #0x80cbb34
cmp r1, #0xf                            cmp r1, #0xf
bls #0x80cbb30                          bls #0x80cbb30
adds r0, r1, #0                         adds r0, r1, #0
subs r0, #0x10                          subs r0, #0x10
lsls r0, r0, #5                         lsls r0, r0, #5
ldr r1, [pc, #4]                        ldr r1, [pc, #4]
b #0x80cbb34                            b #0x80cbb34
lsls r0, r1, #5                         lsls r0, r1, #5
ldr r1, [pc, #8]                        ldr r1, [pc, #8]
adds r0, r0, r1                         adds r0, r0, r1
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
