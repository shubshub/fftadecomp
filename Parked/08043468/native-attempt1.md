# match report - 0x08043468

* source: `src/08043468.c`
* verification: `elf-symbol-thumb-frame-data-v1`
* source SHA-256: `0913aa50709b84efe60814215727e87df1ed316b9f19432c0407e5b442ea9254`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* mapping SHA-256: `696d16c2d97d3fc16edab7c872b3c4420105b2c438f505eb124811293640d36f`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `88454a7a7e1f4c53e9f9bcf432dd6ce92847eb056af8f50a3fdf3195fed6477a`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b557464e464546e0b48fb00e900c4881460168cc200e9a161c46438819094bc2181778032f00d1f4e1032f0cdc012f00d1f9e0012f00dd0ce2002f11d03fe21028000387090000fe2f00d12fe2fe2f03dcfd2f00d10ce232e2ff2f00d117e22ee2644a88180e9bc0180770494608684268117821204042084010704a4610684268117841204042084010700b23984649460868584a801880190068092100f075fc06252d1a6d004b461868011c94310a6890300368514800690090b421490040180190029703974046049003210591092006900f24641b2406240e0794414608910320099009210a910b940c910d9404200c2146f084fe414a9246b22040005044434603703f485044032101709f22520052440021cb201080663050440170bc2040005044012202703748504402700720bd214900514408700c20401b3349514408704b4618682b494018801901680097019783200290012203920e9804220023f4f75bfba620400050440068ac21490051440978264a524412780091052301930c250295c023d2f7a8fea420400050440068092300930121019102950921221cc023d2f7a8ff1a4d042001210122012348f063f9041c17483e210322d4f77dff021c281c211c0123f2f721f8134850440322027004200b2146f0dfff1048012303704946086880190e4a8018fd2165e10000be0400001c0a000040270003e009000365010000790100007b010000590100003ec00000b03c000235010000e4f401028709000009490e98fcf778feff2813d14b4618688019064940180621017018688019044a8018ff2137e10000ffff000086090000870900004b46186881190d4d481902881740002f00d1a3e00a4a88180488002c12d16420fdf02cff0020f2f7abf84b461868811949190c8080301621017077e09209000094090000012c0fd16420fdf017ff0020f2f796f848460268901940190021018080321520107061e0022c15d16420fdf005ff0020f2f784f84946086880194019002101804020012185f012ff4a46106880301421017049e0032c2bd10020f2f76ff84b4618681049401800231e2101704a46106841688e310878402210430870494608688019401903800420012146f037ff0649fe2008704a4610688019044bc018fd21bde000003e0f0000e4f4010287090000042c19d16420fdf0bffe0848084940180324047004200c2146f018ff4a4610688019044bc0180470a2e00000e009000335010000870900000420012146f006ff0649ff20087006480068cc210e9a51434018044bc018fd2189e00000e4f4010210280003870900000220104000281dd06920fdf089fe0948094a81180320087004200c2146f0e2fe0649ff2008704b461868801904494018fd2168e0e009000335010000e4f4010287090000044a8818007803285cd10420022146f0c7fe57e0860900000c4898235b00c0180478002c4ed101200221f2f7a9f8494608688019064a8018022101704b46186880190449401804803ce00000e00900038709000092090000034bc8180078fe2804d110702ee00000530a0000ff2829d10120107026e00548982149004018007800281fd10248007810701be0e0090003e4f401024a6810782021084310704a461068426810784021084310700120f1f7cdff084800689723db00c0180e994018002101700fb038bc9846a146aa46f0bc01bc004710280003f0b557464e464546e0b48eb080460b4881460168cc20424642439246` (1264 bytes)
* compiled : `f0b557464e464546e0b48fb00e900c480168cc200e9b1a1c424391468818094bc2181778032f00d100e2032f0cdc012f00d1f3e0012f00dd1ae2002f11d04de21028000387090000fe2f00d13de2fe2f03dcfd2f00d11ae240e2ff2f00d125e23ce2614a88180e9bc01807705f4908684268117821204042084010705b4a1068426811784120404208401070574b18685749401848440068092100f077fc0626361a76000f25ad1b2d062d0e4f4a1068011c94310a68903003684e4800690090b421490040180190029703970b24049403200590092106910795089409900a910b950c910d9504200c2146f089fe424a9246b22040005044047040485044032303709f22520052440021cb201080663050440170bc20400050440121884642460270374850440270bd2149005144072008700c20801b334c544420702b4b18682b494018484401680097019783200290424603920e9804220023f4f75ffba620400050440068ac2149005144097822780091052301930c240294c023d2f7aefea4204000504400680923009341460191029409212a1cc023d2f7aeff1a4d042001210122012348f069f9041c17483e210322d4f783ff021c281c211c0123f2f727f8134850440322027004200b2146f0e5ff1048434603700449086848440e4a8018fd2179e10000be040000102800031c0a000040270003e009000365010000790100007b0100003ec00000b03c000235010000e4f401028709000009490e98fcf77efeff2815d1074b18684844074940180621017018684844054a8018ff214be10000ffff00001028000386090000870900000f4b18684a4681180e4d481902881740002f00d1b0e00c4bc8180488002c15d16420fdf02fff0020f2f7aef8044908684a46811849190c8080301621017083e0102800039209000094090000012c13d16420fdf017ff0020f2f796f8054b1a68494650184019002101808032152010706ae0000010280003022c17d16420fdf001ff0020f2f780f8074a106848444019002101804020012185f00eff024b18688030142101704fe010280003032c2dd10020f2f769f811490868114a801800231e2101700d49086841688e310a78402010430870094a10684844401903800420012146f031ff0749fe200870034b1868484405494018fd21c5e00000102800033e0f0000e4f4010287090000042c1bd16420fdf0b7fe0848084a80180324047004200c2146f010ff054b18684844054940180470a8e00000e00900033501000010280003870900000420012146f0fcfe0649ff20087006480068cc210e9a51434018044bc018fd218de00000e4f4010210280003870900000220104000281fd06920fdf07ffe0948094a81180320087004200c2146f0d8fe0649ff200870064b1868484405494018fd216ce0e009000335010000e4f401021028000387090000044a8818007803285ed10420022146f0bbfe59e0860900000c4898235b00c0180478002c50d101200221f2f79df8084908684844074a801802210170044b186848440549401804803ee00000e0090003102800038709000092090000034bc8180078fe2804d110702ee00000530a0000ff2829d10120107026e00548982149004018007800281fd10248007810701be0e0090003e4f401024a6810782021084310700d4a1068426810784021084310700120f1f7bfff084800689723db00c0180e994018002101700fb038bc9846a146aa46f0bc01bc004710280003`
* source plausibility: plausible
* hand-asm allow list: not listed

**NOT MATCHING - bytes differ** - 1009/1264 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, sl                              mov r7, sl
mov r6, sb                              mov r6, sb
mov r5, r8                              mov r5, r8
push {r5, r6, r7}                       push {r5, r6, r7}
sub sp, #0x3c                           sub sp, #0x3c
str r0, [sp, #0x38]                     str r0, [sp, #0x38]
ldr r0, [pc, #0x30]                     ldr r0, [pc, #0x30]
                                        mov sb, r0                                <- missing from compiled
ldr r1, [r0]                            ldr r1, [r0]
movs r0, #0xcc                          movs r0, #0xcc
ldr r3, [sp, #0x38]                                                               <- extra in compiled
adds r2, r3, #0                                                                   <- extra in compiled
muls r2, r0, r2                                                                   <- extra in compiled
mov sb, r2                                                                        <- extra in compiled
adds r0, r1, r2                                                                   <- extra in compiled
                                        ldr r2, [sp, #0x38]                       <- missing from compiled
                                        adds r6, r2, #0                           <- missing from compiled
                                        muls r6, r0, r6                           <- missing from compiled
                                        adds r0, r1, r6                           <- missing from compiled
ldr r3, [pc, #0x24]                     ldr r3, [pc, #0x24]
adds r2, r0, r3                         adds r2, r0, r3
ldrb r7, [r2]                           ldrb r7, [r2]
cmp r7, #3                              cmp r7, #3
bne #0x8043492                          bne #0x8043492
b #0x8043894                                                                      <- extra in compiled
                                        b #0x804387c                              <- missing from compiled
cmp r7, #3                              cmp r7, #3
bgt #0x80434b0                          bgt #0x80434b0
cmp r7, #1                              cmp r7, #1
bne #0x804349c                          bne #0x804349c
b #0x8043684                                                                      <- extra in compiled
                                        b #0x8043690                              <- missing from compiled
cmp r7, #1                              cmp r7, #1
ble #0x80434a2                          ble #0x80434a2
b #0x80438d8                                                                      <- extra in compiled
                                        b #0x80438bc                              <- missing from compiled
cmp r7, #0                              cmp r7, #0
beq #0x80434ca                          beq #0x80434ca
b #0x8043944                                                                      <- extra in compiled
                                        b #0x8043928                              <- missing from compiled
cmp r7, #0xfe                           cmp r7, #0xfe
bne #0x80434b6                          bne #0x80434b6
b #0x8043932                                                                      <- extra in compiled
                                        b #0x8043916                              <- missing from compiled
cmp r7, #0xfe                           cmp r7, #0xfe
bgt #0x80434c2                          bgt #0x80434c2
cmp r7, #0xfd                           cmp r7, #0xfd
bne #0x80434c0                          bne #0x80434c0
b #0x80438f6                                                                      <- extra in compiled
b #0x8043944                                                                      <- extra in compiled
                                        b #0x80438da                              <- missing from compiled
                                        b #0x8043928                              <- missing from compiled
cmp r7, #0xff                           cmp r7, #0xff
bne #0x80434c8                          bne #0x80434c8
b #0x8043914                                                                      <- extra in compiled
b #0x8043944                                                                      <- extra in compiled
ldr r2, [pc, #0x184]                                                              <- extra in compiled
                                        b #0x80438f8                              <- missing from compiled
                                        b #0x8043928                              <- missing from compiled
                                        ldr r2, [pc, #0x190]                      <- missing from compiled
adds r0, r1, r2                         adds r0, r1, r2
ldr r3, [sp, #0x38]                     ldr r3, [sp, #0x38]
adds r0, r0, r3                         adds r0, r0, r3
strb r7, [r0]                           strb r7, [r0]
ldr r1, [pc, #0x17c]                                                              <- extra in compiled
                                        mov r1, sb                                <- missing from compiled
ldr r0, [r1]                            ldr r0, [r1]
ldr r2, [r0, #4]                        ldr r2, [r0, #4]
ldrb r1, [r2]                           ldrb r1, [r2]
movs r0, #0x21                          movs r0, #0x21
rsbs r0, r0, #0                         rsbs r0, r0, #0
ands r0, r1                             ands r0, r1
strb r0, [r2]                           strb r0, [r2]
ldr r2, [pc, #0x16c]                                                              <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
ldr r0, [r2]                            ldr r0, [r2]
ldr r2, [r0, #4]                        ldr r2, [r0, #4]
ldrb r1, [r2]                           ldrb r1, [r2]
movs r0, #0x41                          movs r0, #0x41
rsbs r0, r0, #0                         rsbs r0, r0, #0
ands r0, r1                             ands r0, r1
strb r0, [r2]                           strb r0, [r2]
ldr r3, [pc, #0x15c]                                                              <- extra in compiled
ldr r0, [r3]                                                                      <- extra in compiled
ldr r1, [pc, #0x15c]                                                              <- extra in compiled
adds r0, r0, r1                                                                   <- extra in compiled
add r0, sb                                                                        <- extra in compiled
                                        movs r3, #0xb                             <- missing from compiled
                                        mov r8, r3                                <- missing from compiled
                                        mov r1, sb                                <- missing from compiled
                                        ldr r0, [r1]                              <- missing from compiled
                                        ldr r2, [pc, #0x160]                      <- missing from compiled
                                        adds r0, r0, r2                           <- missing from compiled
                                        adds r0, r0, r6                           <- missing from compiled
ldr r0, [r0]                            ldr r0, [r0]
movs r1, #9                             movs r1, #9
bl #0x8043df4                                                                     <- extra in compiled
movs r6, #6                                                                       <- extra in compiled
subs r6, r6, r0                                                                   <- extra in compiled
lsls r6, r6, #1                                                                   <- extra in compiled
movs r5, #0xf                                                                     <- extra in compiled
subs r5, r5, r6                                                                   <- extra in compiled
lsls r5, r5, #0x18                                                                <- extra in compiled
lsrs r5, r5, #0x18                                                                <- extra in compiled
ldr r2, [pc, #0x13c]                                                              <- extra in compiled
ldr r0, [r2]                                                                      <- extra in compiled
                                        movs r5, #6                               <- missing from compiled
                                        subs r5, r5, r0                           <- missing from compiled
                                        lsls r5, r5, #1                           <- missing from compiled
                                        mov r3, sb                                <- missing from compiled
                                        ldr r0, [r3]                              <- missing from compiled
adds r1, r0, #0                         adds r1, r0, #0
adds r1, #0x94                          adds r1, #0x94
ldr r2, [r1]                            ldr r2, [r1]
adds r0, #0x90                          adds r0, #0x90
ldr r3, [r0]                            ldr r3, [r0]
ldr r0, [pc, #0x138]                                                              <- extra in compiled
                                        ldr r0, [pc, #0x144]                      <- missing from compiled
ldr r0, [r0, #0x10]                     ldr r0, [r0, #0x10]
str r0, [sp]                            str r0, [sp]
movs r1, #0xb4                          movs r1, #0xb4
lsls r1, r1, #1                         lsls r1, r1, #1
adds r0, r0, r1                         adds r0, r0, r1
str r0, [sp, #4]                        str r0, [sp, #4]
str r7, [sp, #8]                        str r7, [sp, #8]
str r7, [sp, #0xc]                      str r7, [sp, #0xc]
movs r4, #0xb                                                                     <- extra in compiled
str r4, [sp, #0x10]                                                               <- extra in compiled
                                        mov r0, r8                                <- missing from compiled
                                        str r0, [sp, #0x10]                       <- missing from compiled
                                        movs r1, #3                               <- missing from compiled
                                        str r1, [sp, #0x14]                       <- missing from compiled
                                        movs r0, #9                               <- missing from compiled
                                        str r0, [sp, #0x18]                       <- missing from compiled
                                        movs r4, #0xf                             <- missing from compiled
                                        subs r4, r4, r5                           <- missing from compiled
                                        lsls r4, r4, #0x18                        <- missing from compiled
                                        lsrs r4, r4, #0x18                        <- missing from compiled
                                        str r4, [sp, #0x1c]                       <- missing from compiled
                                        mov r1, r8                                <- missing from compiled
                                        str r1, [sp, #0x20]                       <- missing from compiled
movs r0, #3                             movs r0, #3
str r0, [sp, #0x14]                                                               <- extra in compiled
movs r1, #9                                                                       <- extra in compiled
str r1, [sp, #0x18]                                                               <- extra in compiled
str r5, [sp, #0x1c]                                                               <- extra in compiled
str r4, [sp, #0x20]                                                               <- extra in compiled
str r0, [sp, #0x24]                     str r0, [sp, #0x24]
                                        movs r1, #9                               <- missing from compiled
str r1, [sp, #0x28]                     str r1, [sp, #0x28]
str r5, [sp, #0x2c]                                                               <- extra in compiled
                                        str r4, [sp, #0x2c]                       <- missing from compiled
str r1, [sp, #0x30]                     str r1, [sp, #0x30]
str r5, [sp, #0x34]                                                               <- extra in compiled
                                        str r4, [sp, #0x34]                       <- missing from compiled
movs r0, #4                             movs r0, #4
movs r1, #0xc                           movs r1, #0xc
bl #0x808a268                                                                     <- extra in compiled
ldr r2, [pc, #0x108]                                                              <- extra in compiled
                                        ldr r2, [pc, #0x104]                      <- missing from compiled
mov sl, r2                              mov sl, r2
movs r0, #0xb2                          movs r0, #0xb2
lsls r0, r0, #1                         lsls r0, r0, #1
add r0, sl                              add r0, sl
strb r4, [r0]                                                                     <- extra in compiled
ldr r0, [pc, #0x100]                                                              <- extra in compiled
add r0, sl                                                                        <- extra in compiled
movs r3, #3                                                                       <- extra in compiled
                                        mov r3, r8                                <- missing from compiled
strb r3, [r0]                           strb r3, [r0]
                                        ldr r0, [pc, #0xfc]                       <- missing from compiled
                                        add r0, sl                                <- missing from compiled
                                        movs r1, #3                               <- missing from compiled
                                        strb r1, [r0]                             <- missing from compiled
movs r2, #0x9f                          movs r2, #0x9f
lsls r2, r2, #1                         lsls r2, r2, #1
add r2, sl                              add r2, sl
movs r1, #0                             movs r1, #0
movs r0, #0xcb                          movs r0, #0xcb
strh r0, [r2]                           strh r0, [r2]
adds r0, #0x66                          adds r0, #0x66
add r0, sl                              add r0, sl
strb r1, [r0]                           strb r1, [r0]
movs r0, #0xbc                          movs r0, #0xbc
lsls r0, r0, #1                         lsls r0, r0, #1
add r0, sl                              add r0, sl
movs r1, #1                                                                       <- extra in compiled
mov r8, r1                                                                        <- extra in compiled
mov r2, r8                                                                        <- extra in compiled
                                        movs r2, #1                               <- missing from compiled
strb r2, [r0]                           strb r2, [r0]
ldr r0, [pc, #0xdc]                     ldr r0, [pc, #0xdc]
add r0, sl                              add r0, sl
strb r2, [r0]                           strb r2, [r0]
                                        movs r0, #7                               <- missing from compiled
movs r1, #0xbd                          movs r1, #0xbd
lsls r1, r1, #1                         lsls r1, r1, #1
add r1, sl                              add r1, sl
movs r0, #7                                                                       <- extra in compiled
strb r0, [r1]                           strb r0, [r1]
movs r0, #0xc                           movs r0, #0xc
subs r0, r0, r6                                                                   <- extra in compiled
ldr r4, [pc, #0xcc]                                                               <- extra in compiled
add r4, sl                                                                        <- extra in compiled
strb r0, [r4]                                                                     <- extra in compiled
ldr r3, [pc, #0xac]                                                               <- extra in compiled
                                        subs r0, r0, r5                           <- missing from compiled
                                        ldr r1, [pc, #0xcc]                       <- missing from compiled
                                        add r1, sl                                <- missing from compiled
                                        strb r0, [r1]                             <- missing from compiled
                                        mov r3, sb                                <- missing from compiled
ldr r0, [r3]                            ldr r0, [r3]
ldr r1, [pc, #0xac]                     ldr r1, [pc, #0xac]
adds r0, r0, r1                         adds r0, r0, r1
add r0, sb                                                                        <- extra in compiled
                                        adds r0, r0, r6                           <- missing from compiled
ldr r1, [r0]                            ldr r1, [r0]
str r7, [sp]                            str r7, [sp]
str r7, [sp, #4]                        str r7, [sp, #4]
movs r0, #0x83                          movs r0, #0x83
str r0, [sp, #8]                        str r0, [sp, #8]
mov r2, r8                                                                        <- extra in compiled
                                        movs r2, #1                               <- missing from compiled
str r2, [sp, #0xc]                      str r2, [sp, #0xc]
ldr r0, [sp, #0x38]                     ldr r0, [sp, #0x38]
movs r2, #4                             movs r2, #4
movs r3, #0                             movs r3, #0
bl #0x8037c84                                                                     <- extra in compiled
movs r0, #0xa6                          movs r0, #0xa6
lsls r0, r0, #1                         lsls r0, r0, #1
add r0, sl                              add r0, sl
ldr r0, [r0]                            ldr r0, [r0]
movs r1, #0xac                          movs r1, #0xac
lsls r1, r1, #1                         lsls r1, r1, #1
add r1, sl                              add r1, sl
ldrb r1, [r1]                           ldrb r1, [r1]
ldrb r2, [r4]                                                                     <- extra in compiled
                                        ldr r2, [pc, #0x98]                       <- missing from compiled
                                        add r2, sl                                <- missing from compiled
                                        ldrb r2, [r2]                             <- missing from compiled
str r1, [sp]                            str r1, [sp]
movs r3, #5                             movs r3, #5
str r3, [sp, #4]                        str r3, [sp, #4]
movs r4, #0xc                                                                     <- extra in compiled
str r4, [sp, #8]                                                                  <- extra in compiled
                                        movs r5, #0xc                             <- missing from compiled
                                        str r5, [sp, #8]                          <- missing from compiled
movs r3, #0xc0                          movs r3, #0xc0
bl #0x8016344                                                                     <- extra in compiled
movs r0, #0xa4                          movs r0, #0xa4
lsls r0, r0, #1                         lsls r0, r0, #1
add r0, sl                              add r0, sl
ldr r0, [r0]                            ldr r0, [r0]
movs r3, #9                             movs r3, #9
str r3, [sp]                            str r3, [sp]
mov r1, r8                                                                        <- extra in compiled
                                        movs r1, #1                               <- missing from compiled
str r1, [sp, #4]                        str r1, [sp, #4]
str r4, [sp, #8]                                                                  <- extra in compiled
                                        str r5, [sp, #8]                          <- missing from compiled
movs r1, #9                             movs r1, #9
adds r2, r5, #0                                                                   <- extra in compiled
                                        adds r2, r4, #0                           <- missing from compiled
movs r3, #0xc0                          movs r3, #0xc0
bl #0x8016560                                                                     <- extra in compiled
ldr r5, [pc, #0x68]                                                               <- extra in compiled
                                        vcvt.u16.f16 d4, d10, #0x18               <- missing from compiled
movs r0, #4                             movs r0, #4
movs r1, #1                             movs r1, #1
movs r2, #1                             movs r2, #1
movs r3, #1                             movs r3, #1
bl #0x808b8e4                           bl #0x808b8e4
adds r4, r0, #0                         adds r4, r0, #0
ldr r0, [pc, #0x5c]                     ldr r0, [pc, #0x5c]
movs r1, #0x3e                          movs r1, #0x3e
movs r2, #3                             movs r2, #3
bl #0x8018524                           bl #0x8018524
adds r2, r0, #0                         adds r2, r0, #0
adds r0, r5, #0                         adds r0, r5, #0
adds r1, r4, #0                         adds r1, r4, #0
movs r3, #1                             movs r3, #1
bl #0x8035678                                                                     <- extra in compiled
ldr r0, [pc, #0x4c]                     ldr r0, [pc, #0x4c]
add r0, sl                              add r0, sl
movs r2, #3                             movs r2, #3
strb r2, [r0]                           strb r2, [r0]
movs r0, #4                             movs r0, #4
movs r1, #0xb                           movs r1, #0xb
bl #0x808a604                                                                     <- extra in compiled
ldr r0, [pc, #0x40]                     ldr r0, [pc, #0x40]
mov r3, r8                                                                        <- extra in compiled
                                        movs r3, #1                               <- missing from compiled
strb r3, [r0]                           strb r3, [r0]
ldr r1, [pc, #0x10]                                                               <- extra in compiled
ldr r0, [r1]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
ldr r2, [pc, #0x38]                                                               <- extra in compiled
adds r0, r0, r2                                                                   <- extra in compiled
movs r1, #0xfd                                                                    <- extra in compiled
b #0x8043942                                                                      <- extra in compiled
                                        mov r1, sb                                <- missing from compiled
                                        lsls r5, r6, #4                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
ldr r1, [pc, #0x24]                     ldr r1, [pc, #0x24]
ldr r0, [sp, #0x38]                     ldr r0, [sp, #0x38]
bl #0x8040388                                                                     <- extra in compiled
cmp r0, #0xff                           cmp r0, #0xff
bne #0x80436bc                                                                    <- extra in compiled
ldr r3, [pc, #0x1c]                                                               <- extra in compiled
                                        bne #0x80436c4                            <- missing from compiled
                                        mov r3, sb                                <- missing from compiled
ldr r0, [r3]                            ldr r0, [r3]
add r0, sb                                                                        <- extra in compiled
ldr r1, [pc, #0x1c]                                                               <- extra in compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r1, [pc, #0x18]                       <- missing from compiled
adds r0, r0, r1                         adds r0, r0, r1
movs r1, #6                             movs r1, #6
strb r1, [r0]                           strb r1, [r0]
ldr r0, [r3]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
ldr r2, [pc, #0x14]                                                               <- extra in compiled
adds r0, r0, r2                                                                   <- extra in compiled
movs r1, #0xff                                                                    <- extra in compiled
b #0x8043942                                                                      <- extra in compiled
ldr r3, [pc, #0x3c]                                                               <- extra in compiled
                                        lsrs r6, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        mov r3, sb                                <- missing from compiled
ldr r0, [r3]                            ldr r0, [r3]
mov r2, sb                                                                        <- extra in compiled
adds r1, r0, r2                                                                   <- extra in compiled
ldr r5, [pc, #0x38]                                                               <- extra in compiled
                                        adds r1, r0, r6                           <- missing from compiled
                                        ldr r5, [pc, #0x34]                       <- missing from compiled
adds r0, r1, r5                         adds r0, r1, r5
ldrh r2, [r0]                           ldrh r2, [r0]
ands r7, r2                             ands r7, r2
cmp r7, #0                              cmp r7, #0
bne #0x80436d2                                                                    <- extra in compiled
b #0x8043834                                                                      <- extra in compiled
ldr r3, [pc, #0x30]                                                               <- extra in compiled
adds r0, r1, r3                                                                   <- extra in compiled
                                        bne #0x80436d8                            <- missing from compiled
                                        b #0x8043820                              <- missing from compiled
                                        ldr r2, [pc, #0x28]                       <- missing from compiled
                                        adds r0, r1, r2                           <- missing from compiled
ldrh r4, [r0]                           ldrh r4, [r0]
cmp r4, #0                              cmp r4, #0
bne #0x8043708                          bne #0x8043708
movs r0, #0x64                          movs r0, #0x64
bl #0x8141540                           bl #0x8141540
movs r0, #0                             movs r0, #0
bl #0x8035844                                                                     <- extra in compiled
ldr r1, [pc, #0x10]                                                               <- extra in compiled
ldr r0, [r1]                                                                      <- extra in compiled
mov r2, sb                                                                        <- extra in compiled
adds r1, r0, r2                                                                   <- extra in compiled
                                        mov r3, sb                                <- missing from compiled
                                        ldr r0, [r3]                              <- missing from compiled
                                        adds r1, r0, r6                           <- missing from compiled
adds r1, r1, r5                         adds r1, r1, r5
strh r4, [r1]                           strh r4, [r1]
adds r0, #0x80                          adds r0, #0x80
movs r1, #0x16                          movs r1, #0x16
strb r1, [r0]                                                                     <- extra in compiled
b #0x8043804                                                                      <- extra in compiled
cmp r4, #1                              cmp r4, #1
bne #0x8043734                                                                    <- extra in compiled
                                        bne #0x804372c                            <- missing from compiled
movs r0, #0x64                          movs r0, #0x64
bl #0x8141540                           bl #0x8141540
movs r0, #0                             movs r0, #0
bl #0x8035844                           bl #0x8035844
ldr r3, [pc, #0x14]                                                               <- extra in compiled
ldr r2, [r3]                                                                      <- extra in compiled
mov r1, sb                                                                        <- extra in compiled
adds r0, r2, r1                                                                   <- extra in compiled
                                        mov r0, sb                                <- missing from compiled
                                        ldr r2, [r0]                              <- missing from compiled
                                        adds r0, r2, r6                           <- missing from compiled
adds r0, r0, r5                         adds r0, r0, r5
movs r1, #0                             movs r1, #0
strh r1, [r0]                           strh r1, [r0]
adds r2, #0x80                          adds r2, #0x80
movs r0, #0x15                          movs r0, #0x15
strb r0, [r2]                           strb r0, [r2]
b #0x8043804                                                                      <- extra in compiled
                                        b #0x80437f0                              <- missing from compiled
cmp r4, #2                              cmp r4, #2
bne #0x8043768                                                                    <- extra in compiled
movs r0, #0x64                                                                    <- extra in compiled
bl #0x8141540                                                                     <- extra in compiled
movs r0, #0                             movs r0, #0
bl #0x8035844                                                                     <- extra in compiled
ldr r2, [pc, #0x1c]                                                               <- extra in compiled
ldr r0, [r2]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
                                        strb.w r4, [r4, #0x649]                   <- missing from compiled
                                        ldr r0, [r1]                              <- missing from compiled
                                        adds r0, r0, r6                           <- missing from compiled
adds r0, r0, r5                         adds r0, r0, r5
movs r1, #0                             movs r1, #0
strh r1, [r0]                           strh r1, [r0]
movs r0, #0x40                          movs r0, #0x40
movs r1, #1                             movs r1, #1
bl #0x80c9574                                                                     <- extra in compiled
ldr r3, [pc, #8]                                                                  <- extra in compiled
ldr r0, [r3]                                                                      <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
adds r0, #0x80                          adds r0, #0x80
movs r1, #0x14                          movs r1, #0x14
strb r1, [r0]                           strb r1, [r0]
b #0x8043804                                                                      <- extra in compiled
                                        b #0x80437f0                              <- missing from compiled
cmp r4, #3                              cmp r4, #3
bne #0x80437c8                                                                    <- extra in compiled
                                        bne #0x80437b8                            <- missing from compiled
movs r0, #0                             movs r0, #0
bl #0x8035844                                                                     <- extra in compiled
ldr r1, [pc, #0x44]                                                               <- extra in compiled
ldr r0, [r1]                                                                      <- extra in compiled
ldr r2, [pc, #0x44]                                                               <- extra in compiled
adds r0, r0, r2                                                                   <- extra in compiled
                                        ldr r0, [r3]                              <- missing from compiled
                                        ldr r1, [pc, #0x40]                       <- missing from compiled
                                        adds r0, r0, r1                           <- missing from compiled
movs r3, #0                             movs r3, #0
movs r1, #0x1e                          movs r1, #0x1e
strb r1, [r0]                           strb r1, [r0]
ldr r1, [pc, #0x34]                                                               <- extra in compiled
ldr r0, [r1]                                                                      <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
ldr r1, [r0, #4]                        ldr r1, [r0, #4]
adds r1, #0x8e                          adds r1, #0x8e
ldrb r2, [r1]                                                                     <- extra in compiled
movs r0, #0x40                                                                    <- extra in compiled
                                        ldrb r0, [r1]                             <- missing from compiled
                                        movs r2, #0x40                            <- missing from compiled
orrs r0, r2                             orrs r0, r2
strb r0, [r1]                           strb r0, [r1]
ldr r2, [pc, #0x24]                                                               <- extra in compiled
ldr r0, [r2]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
                                        mov r1, sb                                <- missing from compiled
                                        ldr r0, [r1]                              <- missing from compiled
                                        adds r0, r0, r6                           <- missing from compiled
adds r0, r0, r5                         adds r0, r0, r5
strh r3, [r0]                           strh r3, [r0]
movs r0, #4                             movs r0, #4
movs r1, #1                             movs r1, #1
bl #0x808a604                                                                     <- extra in compiled
ldr r1, [pc, #0x1c]                                                               <- extra in compiled
                                        ldr r1, [pc, #0x18]                       <- missing from compiled
movs r0, #0xfe                          movs r0, #0xfe
strb r0, [r1]                           strb r0, [r1]
ldr r3, [pc, #0xc]                                                                <- extra in compiled
ldr r0, [r3]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
ldr r1, [pc, #0x14]                                                               <- extra in compiled
adds r0, r0, r1                                                                   <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r3, [pc, #0x10]                       <- missing from compiled
                                        adds r0, r0, r3                           <- missing from compiled
movs r1, #0xfd                          movs r1, #0xfd
b #0x8043942                                                                      <- extra in compiled
cmp r4, #4                                                                        <- extra in compiled
bne #0x8043804                                                                    <- extra in compiled
movs r0, #0x64                                                                    <- extra in compiled
bl #0x8141540                                                                     <- extra in compiled
ldr r0, [pc, #0x20]                                                               <- extra in compiled
ldr r2, [pc, #0x20]                                                               <- extra in compiled
adds r0, r0, r2                                                                   <- extra in compiled
                                        b #0x8043926                              <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r6, r7, #0x1c                        <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsls r1, r0, #8                           <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
movs r4, #3                             movs r4, #3
strb r4, [r0]                           strb r4, [r0]
movs r0, #4                             movs r0, #4
movs r1, #0xc                           movs r1, #0xc
bl #0x808a604                                                                     <- extra in compiled
ldr r3, [pc, #0x14]                                                               <- extra in compiled
ldr r0, [r3]                                                                      <- extra in compiled
add r0, sb                                                                        <- extra in compiled
ldr r1, [pc, #0x14]                                                               <- extra in compiled
adds r0, r0, r1                                                                   <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
                                        ldr r0, [r2]                              <- missing from compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r3, [pc, #0x10]                       <- missing from compiled
                                        adds r0, r0, r3                           <- missing from compiled
strb r4, [r0]                           strb r4, [r0]
b #0x8043944                                                                      <- extra in compiled
                                        b #0x8043928                              <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r0, r4, #7                           <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        lsls r5, r6, #4                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
movs r0, #4                             movs r0, #4
movs r1, #1                                                                       <- extra in compiled
bl #0x808a604                                                                     <- extra in compiled
ldr r1, [pc, #0x18]                                                               <- extra in compiled
movs r0, #0xff                                                                    <- extra in compiled
strb r0, [r1]                                                                     <- extra in compiled
ldr r0, [pc, #0x18]                                                               <- extra in compiled
ldr r0, [r0]                                                                      <- extra in compiled
movs r1, #0xcc                                                                    <- extra in compiled
ldr r2, [sp, #0x38]                     ldr r2, [sp, #0x38]
muls r1, r2, r1                         muls r1, r2, r1
adds r0, r0, r1                         adds r0, r0, r1
ldr r3, [pc, #0x10]                     ldr r3, [pc, #0x10]
adds r0, r0, r3                         adds r0, r0, r3
movs r1, #0xfd                          movs r1, #0xfd
b #0x8043942                                                                      <- extra in compiled
                                        b #0x8043926                              <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsls r1, r0, #8                           <- missing from compiled
                                        cmp r0, #0x10                             <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
movs r0, #2                             movs r0, #2
ands r0, r2                             ands r0, r2
cmp r0, #0                              cmp r0, #0
beq #0x804387c                                                                    <- extra in compiled
movs r0, #0x69                                                                    <- extra in compiled
bl #0x8141540                                                                     <- extra in compiled
ldr r0, [pc, #0x24]                                                               <- extra in compiled
ldr r2, [pc, #0x24]                                                               <- extra in compiled
adds r1, r0, r2                                                                   <- extra in compiled
movs r0, #3                             movs r0, #3
strb r0, [r1]                           strb r0, [r1]
movs r0, #4                             movs r0, #4
movs r1, #0xc                           movs r1, #0xc
bl #0x808a604                                                                     <- extra in compiled
ldr r1, [pc, #0x18]                                                               <- extra in compiled
                                        cdp2 p9, #0xe, c4, c2, c6, #0             <- missing from compiled
movs r0, #0xff                          movs r0, #0xff
strb r0, [r1]                           strb r0, [r1]
ldr r3, [pc, #0x18]                                                               <- extra in compiled
                                        mov r3, sb                                <- missing from compiled
ldr r0, [r3]                            ldr r0, [r3]
add r0, sb                                                                        <- extra in compiled
ldr r1, [pc, #0x14]                                                               <- extra in compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r1, [pc, #0x10]                       <- missing from compiled
adds r0, r0, r1                         adds r0, r0, r1
movs r1, #0xfd                          movs r1, #0xfd
b #0x8043942                                                                      <- extra in compiled
                                        b #0x8043926                              <- missing from compiled
                                        lsrs r0, r4, #7                           <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        lsls r5, r6, #4                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsls r1, r0, #8                           <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
ldr r2, [pc, #0x10]                     ldr r2, [pc, #0x10]
adds r0, r1, r2                         adds r0, r1, r2
ldrb r0, [r0]                                                                     <- extra in compiled
cmp r0, #3                                                                        <- extra in compiled
bne #0x8043944                                                                    <- extra in compiled
movs r0, #4                                                                       <- extra in compiled
movs r1, #2                                                                       <- extra in compiled
bl #0x808a604                                                                     <- extra in compiled
b #0x8043944                                                                      <- extra in compiled
ldr r0, [pc, #0x30]                     ldr r0, [pc, #0x30]
movs r3, #0x98                          movs r3, #0x98
lsls r3, r3, #1                         lsls r3, r3, #1
adds r0, r0, r3                         adds r0, r0, r3
ldrb r4, [r0]                           ldrb r4, [r0]
cmp r4, #0                              cmp r4, #0
bne #0x8043944                                                                    <- extra in compiled
                                        bne #0x8043928                            <- missing from compiled
movs r0, #1                             movs r0, #1
movs r1, #2                             movs r1, #2
bl #0x80359e4                                                                     <- extra in compiled
ldr r1, [pc, #0x20]                                                               <- extra in compiled
ldr r0, [r1]                            ldr r0, [r1]
add r0, sb                                                                        <- extra in compiled
ldr r2, [pc, #0x1c]                                                               <- extra in compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r2, [pc, #0x18]                       <- missing from compiled
adds r0, r0, r2                         adds r0, r0, r2
movs r1, #2                             movs r1, #2
strb r1, [r0]                           strb r1, [r0]
ldr r3, [pc, #0x10]                                                               <- extra in compiled
                                        mov r3, sb                                <- missing from compiled
ldr r0, [r3]                            ldr r0, [r3]
add r0, sb                                                                        <- extra in compiled
ldr r1, [pc, #0x14]                                                               <- extra in compiled
                                        adds r0, r0, r6                           <- missing from compiled
                                        ldr r1, [pc, #0x10]                       <- missing from compiled
adds r0, r0, r1                         adds r0, r0, r1
strh r4, [r0]                           strh r4, [r0]
b #0x8043944                                                                      <- extra in compiled
                                        b #0x8043928                              <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r0, r4, #7                           <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        lsrs r7, r0, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
                                        lsrs r2, r2, #6                           <- missing from compiled
                                        movs r0, r0                               <- missing from compiled
ldr r3, [pc, #0xc]                      ldr r3, [pc, #0xc]
adds r0, r1, r3                         adds r0, r1, r3
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r0, #0xfe                           cmp r0, #0xfe
bne #0x80438ec                                                                    <- extra in compiled
strb r0, [r2]                                                                     <- extra in compiled
b #0x8043944                                                                      <- extra in compiled
cmp r0, #0xff                                                                     <- extra in compiled
bne #0x8043944                                                                    <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
strb r0, [r2]                                                                     <- extra in compiled
b #0x8043944                                                                      <- extra in compiled
                                        bne #0x80438d0                            <- missing from compiled
                                        b #0x8043928                              <- missing from compiled
ldr r0, [pc, #0x14]                     ldr r0, [pc, #0x14]
movs r1, #0x98                          movs r1, #0x98
lsls r1, r1, #1                         lsls r1, r1, #1
adds r0, r0, r1                         adds r0, r0, r1
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r0, #0                              cmp r0, #0
bne #0x8043944                                                                    <- extra in compiled
ldr r0, [pc, #8]                                                                  <- extra in compiled
ldrb r0, [r0]                                                                     <- extra in compiled
strb r0, [r2]                           strb r0, [r2]
b #0x8043944                                                                      <- extra in compiled
                                        b #0x8043928                              <- missing from compiled
                                        lsrs r0, r4, #7                           <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        lsls r1, r0, #8                           <- missing from compiled
ldr r2, [r1, #4]                        ldr r2, [r1, #4]
ldrb r0, [r2]                           ldrb r0, [r2]
movs r1, #0x20                          movs r1, #0x20
orrs r0, r1                             orrs r0, r1
strb r0, [r2]                           strb r0, [r2]
ldr r2, [pc, #0x34]                                                               <- extra in compiled
                                        mov r2, sb                                <- missing from compiled
ldr r0, [r2]                            ldr r0, [r2]
ldr r2, [r0, #4]                        ldr r2, [r0, #4]
ldrb r0, [r2]                           ldrb r0, [r2]
movs r1, #0x40                          movs r1, #0x40
orrs r0, r1                                                                       <- extra in compiled
strb r0, [r2]                                                                     <- extra in compiled
movs r0, #1                                                                       <- extra in compiled
bl #0x80358b0                                                                     <- extra in compiled
ldr r0, [pc, #0x20]                     ldr r0, [pc, #0x20]
ldr r0, [r0]                            ldr r0, [r0]
movs r3, #0x97                          movs r3, #0x97
lsls r3, r3, #3                         lsls r3, r3, #3
adds r0, r0, r3                         adds r0, r0, r3
ldr r1, [sp, #0x38]                     ldr r1, [sp, #0x38]
adds r0, r0, r1                         adds r0, r0, r1
movs r1, #0                             movs r1, #0
strb r1, [r0]                           strb r1, [r0]
add sp, #0x3c                           add sp, #0x3c
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r0}                                pop {r0}
bx r0                                   bx r0
                                        cmp r0, #0x10                             <- missing from compiled
                                        lsls r0, r0, #0xc                         <- missing from compiled
                                        push {r4, r5, r6, r7, lr}                 <- missing from compiled
                                        mov r7, sl                                <- missing from compiled
                                        mov r6, sb                                <- missing from compiled
                                        mov r5, r8                                <- missing from compiled
                                        push {r5, r6, r7}                         <- missing from compiled
                                        sub sp, #0x38                             <- missing from compiled
                                        mov r8, r0                                <- missing from compiled
                                        ldr r0, [pc, #0x2c]                       <- missing from compiled
                                        mov sb, r0                                <- missing from compiled
                                        ldr r1, [r0]                              <- missing from compiled
                                        movs r0, #0xcc                            <- missing from compiled
                                        mov r2, r8                                <- missing from compiled
```
