# match report - 0x08FE1FCC

* source: `src/08FE1FCC.c`
* verification: `elf-symbol-cfg-leaf-v2`
* source SHA-256: `b419fb895fa46b35c455b8112c71c23b8ef77496ff51213f7336ca3e5b401a04`
* library unit: `{"end":"0x08FE1FF8","evidence":"Development-cartridge debug monitor in late ROM; nothing outside 0x08FE0000-0x08FE3FFF calls it. That area holds separately linked programs: program A, 0x08FE0000-0x08FE1FF7 with ARM vectors at 0x08FE0000, is linked to run at its ROM address plus 0x01002000, and the program from 0x08FE2000 is linked at its ROM address plus 0x01001000, with its own ARM code, Thumb functions and linker ARM-to-Thumb veneers. This row is program A's compiled Thumb code: from 0x08FE1638, right after the literal pool of the ARM code before it, to 0x08FE1FF8, the end of program A, which eight bytes of padding separate from the next program. 08FE1FCC is a leaf with a conditional branch that returns by a bare bx lr. Stock agbcc -O2 saves lr in such a leaf: far_jump_used_p (thumb.c) caches current_function_has_far_jump when INITIAL_ELIMINATION_OFFSET (thumb.h) asks during reload, before branch lengths are known, so the bne counts as a far jump and the function gets push {lr} and pop {r0}; bx r0. -fprologue-bugfix skips that cache. Under agbcc -mthumb-interwork -O2 -fprologue-bugfix 08FE1FCC is byte-identical; old_agbcc also returns by bx lr but allocates differently, and it does not reproduce the merged 08FE18F0 either. Every other function in the run saves low registers or calls, so lr is saved either way, and the merged 08FE1638 and 08FE18F0 compile to the identical function with and without the flag.","identity":[{"address":"0x08FE1638","sha256":"e56bca86b48328f780d39810065d86c4a9d79db21bab2be98baef706053b0fcb","size":2496}],"name":"debug monitor -fprologue-bugfix","proof":"0x08FE1FCC","start":"0x08FE1638","toolchain":"agbcc-O2-prologue-bugfix-v1"}`
* unit toolchain: `agbcc-O2-prologue-bugfix-v1`
* unit compiler SHA-256: `63deeb6946e16e5add66cc173fcaa925f58ae56983d4d5a4649389bf8a23776f`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2 -fprologue-bugfix`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `074a118801200840002804d1054811880088014311800449002008807047000008020004f420fe09f020fe09` (44 bytes)
* compiled : `074a118801200840002804d1054811880088014311800449002008807047000008020004f420fe09f020fe09`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 44/44 bytes

```
compiled                                rom
ldr r2, [pc, #0x1c]                     ldr r2, [pc, #0x1c]
ldrh r1, [r2]                           ldrh r1, [r2]
movs r0, #1                             movs r0, #1
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
bne #0x8fe1fe2                          bne #0x8fe1fe2
ldr r0, [pc, #0x14]                     ldr r0, [pc, #0x14]
ldrh r1, [r2]                           ldrh r1, [r2]
ldrh r0, [r0]                           ldrh r0, [r0]
orrs r1, r0                             orrs r1, r0
strh r1, [r2]                           strh r1, [r2]
ldr r1, [pc, #0x10]                     ldr r1, [pc, #0x10]
movs r0, #0                             movs r0, #0
strh r0, [r1]                           strh r0, [r1]
bx lr                                   bx lr
```
