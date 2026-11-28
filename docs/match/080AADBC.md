# match report - 0x080AADBC

* source: `src/080AADBC.c`
* verification: `elf-symbol-thumb-data-buffer-calls-v1`
* source SHA-256: `c46589d3a519ecc034979e4977b180319546b0d216c6b52fcb22b19a1b45c04d`
* stack frame: fixed Thumb frames and bounded stack aliases with return provenance
* buffer calls: ROM-checked bounded register and stack buffer arguments with returned alias provenance
* buffer proof SHA-256: `70726e4731c2f749ba8645d954b72b4071bab6420da2bdf9c057f18d1abf04f1`
* buffer signed remainder: `thumb-compiler-modsi3-numeric-leaf-summary-v1` __modsi3 0x08142950 (102 instructions, e29c5cee2bafd4fc) and __div0 as a native-proved leaf: R0 unknown scalar, R1-R3/R12/LR/flags clobbered, R4-R11/SP restored, no memory operand; no local pointer in R0/R1/LR; no remainder value or range
* buffer signed remainder: call 0x080AAED2 (0x080AADBC+0x116): divisor 17 (positive-signed32-constant-divisor); dead scratch discarded: r3=sp-63
* buffer signed remainder: call 0x080AAEEC (0x080AADBC+0x130): divisor 17 (positive-signed32-constant-divisor); dead scratch discarded: none
* buffer signed remainder: call 0x080AAF0A (0x080AADBC+0x14E): divisor 17 (positive-signed32-constant-divisor); dead scratch discarded: none
* buffer signed remainder: call 0x080AB1C8 (0x080AADBC+0x40C): divisor 7 (positive-signed32-constant-divisor); dead scratch discarded: none
* mapping SHA-256: `e2ae2e69c01541ba8a185c3d90e4ec51eb18d8e84aca6061adf052ba8bb0dd48`
* control flow: direct Thumb BL with ordinary ARM ABI call summaries
* data symbols SHA-256: `117686a176ad73ea978c65bc4fa7ea23bc024988023c19e1a1738a57e0dd78d2`
* data buffer calls: typed ABS32 object literals beside the ROM-checked version-2 buffer proof; every reached RAM/ROM address word typed; premise, not checked: named objects do not overlap any live stack
* data buffer manifest: `{"calls":[[66,"func_080A9B00"],[150,"func_080A92E4"],[158,"func_08141570"],[166,"func_080A7EC4"],[182,"func_0809836C"],[194,"func_0809A570"],[220,"func_080A8390"],[244,"func_0809A570"],[264,"func_0809A570"],[268,"func_08002804"],[278,"__modsi3"],[294,"func_08002804"],[304,"__modsi3"],[324,"func_08002804"],[334,"__modsi3"],[398,"func_080E2C00"],[642,"func_0809D66C"],[798,"func_0809836C"],[818,"_call_via_r3"],[932,"func_08099C34"],[942,"func_08141520"],[1022,"func_08002804"],[1036,"__modsi3"],[1194,"func_080A9E6C"],[1200,"func_08099C64"],[1222,"func_0809836C"]],"data":[[912,"data_0836D4BC",0],[916,"data_08394568",0]],"functions":[]}`
* data buffer proof SHA-256: `6eee0bff709bc87d5691ea45c65f0362d69871ed099d7d8e84dc445caccd9e04`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* verified extent: complete ELF function symbol, including literal pools
* relocations: none
* ROM bytes: `f0b557464e464546e0b48ab0061c894603934030017808200840002800d106e1002004904c2189198a46321cf4320592331c48330893d046371c443745462c68381cfef77ffeb86879684018b86099397960fa68824207db002905dcba602868844200d195e002e00120049091e0c421490070180078002814d1d04500d188e04a460823d15e0a24125f4d460c202b5e152000900020fef747fa02208d2196f089fb76e0f08efdf72ff849461f228a56484605210023edf77bfa4846002180221202eff777fb3068c07f000600164a461f2151566c46093402aa231cfdf77afa02a8007800060016002805d04846002180229200eff75efb00202056002805d0484600218022d200eff754fb57f79cfc00040014112197f03dfd4b46198909181039059c218057f78ffc00040014112197f030fd04304d466d894019311cf6310991088057f780fc00040014112197f021fd4a46918909181039331cf8331980301cfc3000240470341cfd3400252570059a0025515f099a0025525f944600229b5e00780090207801900398624637f059fe089b186800281ddd5046583080450cd0804502dcd04505d011e05046b030804506d00ce0311c743105e0311cca3102e093246400311908880130088002e0388e013838869a256d0070190021415642461068001248434b461b89c018f885154c3019002141561068001248434d46ad894019788608985830089058218844583750465830804500dc0fe7049a002a05d1321c40321178f320084010709e235b00f0180088012800d1ade0012805dc002807d0a0e1000035010000022800d154e199e1321c403211780220084310703268106b0221494208401063371c3e370020385699256d00741944497518211c2a1cf2f715fb32684b4618890004401500216156401a400110301081326898890004401500216956401a400110309081188900044015002161568900401a400110309b225200b1180880988900044015002169568900401a400110309c235b00f1180880002020564042207000202856404228704c460a25605f0002f0600a21605e30380002b06080210901716031680012488130680022ba56f38e0721edf747f91b4889225200b4181a490368201c082297f0aff88a235b00f51804370022301c7c30311c4431331c9c330c60428082800280583058319942f7dd3068c07f0006001680003f88c01901042871090e032001406a7907381040084368719e246400311901200880fee0000033010000bcd4360868453908b04645460435a846043d01cdeef768fd002868d17f2096f0d9f9321c403211780c200843107000274c2080198246311c483106911032079258203d1c4543721930680089111c723108803068408918300231088030688189101c76300180079b58190024046057f723fb06994c1900040014072197f0c2fb000400140330784303300002206099225200b018007800060016002808d053465a194c460825605f31680823c95e07e0544662194d460c21685e31680c23c95e401a002800da4042000210600137012fb6dd99246400301900789a256d00711908702049701800781f4ab1180870434658687168401858607068011c993971609a685868824202db002900dc5a603168b06800124881301c0421fef701fe3068eef7fafc002867d03068311c3e3100228a5603210023edf773f84c460a25605f30380002f0600a21605e0002b060002171603168001248819e225200b1180220088049e0330100003501000099235b00f21800201056002804d0316880000c89001908810e4d721900201056002804d0316880008a8980188881321d50687168401850607068011c9939716093685068834207db002905dc5360002203e000003301000001223168b06800124881002a12d13268106b012108431063321c40321078fd21014011700c200840002803d100201070002000e001200ab038bc9846a146aa46f0bc02bc0847` (1434 bytes)
* compiled : `f0b557464e464546e0b48ab0061c894603934030017808200840002800d106e1002004904c2189198a46321cf4320592331c48330893d046371c443745462c68381cfef77ffeb86879684018b86099397960fa68824207db002905dcba602868844200d195e002e00120049091e0c421490070180078002814d1d04500d188e04a460823d15e0a24125f4d460c202b5e152000900020fef747fa02208d2196f089fb76e0f08efdf72ff849461f228a56484605210023edf77bfa4846002180221202eff777fb3068c07f000600164a461f2151566c46093402aa231cfdf77afa02a8007800060016002805d04846002180229200eff75efb00202056002805d0484600218022d200eff754fb57f79cfc00040014112197f03dfd4b46198909181039059c218057f78ffc00040014112197f030fd04304d466d894019311cf6310991088057f780fc00040014112197f021fd4a46918909181039331cf8331980301cfc3000240470341cfd3400252570059a0025515f099a0025525f944600229b5e00780090207801900398624637f059fe089b186800281ddd5046583080450cd0804502dcd04505d011e05046b030804506d00ce0311c743105e0311cca3102e093246400311908880130088002e0388e013838869a256d0070190021415642461068001248434b461b89c018f885154c3019002141561068001248434d46ad894019788608985830089058218844583750465830804500dc0fe7049a002a05d1321c40321178f320084010709e235b00f0180088012800d1ade0012805dc002807d0a0e1000035010000022800d154e199e1321c403211780220084310703268106b0221494208401063371c3e370020385699256d00741944497518211c2a1cf2f715fb32684b4618890004401500216156401a400110301081326898890004401500216956401a400110309081188900044015002161568900401a400110309b225200b1180880988900044015002169568900401a400110309c235b00f1180880002020564042207000202856404228704c460a25605f0002f0600a21605e30380002b06080210901716031680012488130680022ba56f38e0721edf747f91b4889225200b4181a490368201c082297f0aff88a235b00f51804370022301c7c30311c4431331c9c330c60428082800280583058319942f7dd3068c07f0006001680003f88c01901042871090e032001406a7907381040084368719e246400311901200880fee0000033010000bcd4360868453908b04645460435a846043d01cdeef768fd002868d17f2096f0d9f9321c403211780c200843107000274c2080198246311c483106911032079258203d1c4543721930680089111c723108803068408918300231088030688189101c76300180079b58190024046057f723fb06994c1900040014072197f0c2fb000400140330784303300002206099225200b018007800060016002808d053465a194c460825605f31680823c95e07e0544662194d460c21685e31680c23c95e401a002800da4042000210600137012fb6dd99246400301900789a256d00711908702049701800781f4ab1180870434658687168401858607068011c993971609a685868824202db002900dc5a603168b06800124881301c0421fef701fe3068eef7fafc002867d03068311c3e3100228a5603210023edf773f84c460a25605f30380002f0600a21605e0002b060002171603168001248819e225200b1180220088049e0330100003501000099235b00f21800201056002804d0316880000c89001908810e4d721900201056002804d0316880008a8980188881321d50687168401850607068011c9939716093685068834207db002905dc5360002203e000003301000001223168b06800124881002a12d13268106b012108431063321c40321078fd21014011700c200840002803d100201070002000e001200ab038bc9846a146aa46f0bc02bc0847`
* source plausibility: plausible
* hand-asm allow list: not listed

**MATCH - byte identical** - 1434/1434 bytes

```
compiled                                rom
push {r4, r5, r6, r7, lr}               push {r4, r5, r6, r7, lr}
mov r7, sl                              mov r7, sl
mov r6, sb                              mov r6, sb
mov r5, r8                              mov r5, r8
push {r5, r6, r7}                       push {r5, r6, r7}
sub sp, #0x28                           sub sp, #0x28
adds r6, r0, #0                         adds r6, r0, #0
mov sb, r1                              mov sb, r1
str r3, [sp, #0xc]                      str r3, [sp, #0xc]
adds r0, #0x40                          adds r0, #0x40
ldrb r1, [r0]                           ldrb r1, [r0]
movs r0, #8                             movs r0, #8
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
bne #0x80aaddc                          bne #0x80aaddc
b #0x80aafea                            b #0x80aafea
movs r0, #0                             movs r0, #0
str r0, [sp, #0x10]                     str r0, [sp, #0x10]
movs r1, #0x4c                          movs r1, #0x4c
adds r1, r1, r6                         adds r1, r1, r6
mov sl, r1                              mov sl, r1
adds r2, r6, #0                         adds r2, r6, #0
adds r2, #0xf4                          adds r2, #0xf4
str r2, [sp, #0x14]                     str r2, [sp, #0x14]
adds r3, r6, #0                         adds r3, r6, #0
adds r3, #0x48                          adds r3, #0x48
str r3, [sp, #0x20]                     str r3, [sp, #0x20]
mov r8, sl                              mov r8, sl
adds r7, r6, #0                         adds r7, r6, #0
adds r7, #0x44                          adds r7, #0x44
mov r5, r8                              mov r5, r8
ldr r4, [r5]                            ldr r4, [r5]
adds r0, r7, #0                         adds r0, r7, #0
bl #0x80a9b00                           bl #0x80a9b00
ldr r0, [r7, #8]                        ldr r0, [r7, #8]
ldr r1, [r7, #4]                        ldr r1, [r7, #4]
adds r0, r0, r1                         adds r0, r0, r1
str r0, [r7, #8]                        str r0, [r7, #8]
subs r1, #0x99                          subs r1, #0x99
str r1, [r7, #4]                        str r1, [r7, #4]
ldr r2, [r7, #0xc]                      ldr r2, [r7, #0xc]
cmp r2, r0                              cmp r2, r0
blt #0x80aae24                          blt #0x80aae24
cmp r1, #0                              cmp r1, #0
bgt #0x80aae24                          bgt #0x80aae24
str r2, [r7, #8]                        str r2, [r7, #8]
ldr r0, [r5]                            ldr r0, [r5]
cmp r4, r0                              cmp r4, r0
bne #0x80aae22                          bne #0x80aae22
b #0x80aaf4e                            b #0x80aaf4e
b #0x80aae2a                            b #0x80aae2a
movs r0, #1                             movs r0, #1
str r0, [sp, #0x10]                     str r0, [sp, #0x10]
b #0x80aaf4e                            b #0x80aaf4e
movs r1, #0xc4                          movs r1, #0xc4
lsls r1, r1, #1                         lsls r1, r1, #1
adds r0, r6, r1                         adds r0, r6, r1
ldrb r0, [r0]                           ldrb r0, [r0]
cmp r0, #0                              cmp r0, #0
bne #0x80aae60                          bne #0x80aae60
cmp r8, sl                              cmp r8, sl
bne #0x80aae3c                          bne #0x80aae3c
b #0x80aaf4e                            b #0x80aaf4e
mov r2, sb                              mov r2, sb
movs r3, #8                             movs r3, #8
ldrsh r1, [r2, r3]                      ldrsh r1, [r2, r3]
movs r4, #0xa                           movs r4, #0xa
ldrsh r2, [r2, r4]                      ldrsh r2, [r2, r4]
mov r5, sb                              mov r5, sb
movs r0, #0xc                           movs r0, #0xc
ldrsh r3, [r5, r0]                      ldrsh r3, [r5, r0]
movs r0, #0x15                          movs r0, #0x15
str r0, [sp]                            str r0, [sp]
movs r0, #0                             movs r0, #0
bl #0x80a92e4                           bl #0x80a92e4
movs r0, #2                             movs r0, #2
movs r1, #0x8d                          movs r1, #0x8d
bl #0x8141570                           bl #0x8141570
b #0x80aaf4e                            b #0x80aaf4e
ldrh r0, [r6, #0x36]                    ldrh r0, [r6, #0x36]
bl #0x80a7ec4                           bl #0x80a7ec4
mov r1, sb                              mov r1, sb
movs r2, #0x1f                          movs r2, #0x1f
ldrsb r2, [r1, r2]                      ldrsb r2, [r1, r2]
mov r0, sb                              mov r0, sb
movs r1, #5                             movs r1, #5
movs r3, #0                             movs r3, #0
bl #0x809836c                           bl #0x809836c
mov r0, sb                              mov r0, sb
movs r1, #0                             movs r1, #0
movs r2, #0x80                          movs r2, #0x80
lsls r2, r2, #8                         lsls r2, r2, #8
bl #0x809a570                           bl #0x809a570
ldr r0, [r6]                            ldr r0, [r6]
ldrb r0, [r0, #0x1f]                    ldrb r0, [r0, #0x1f]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
mov r2, sb                              mov r2, sb
movs r1, #0x1f                          movs r1, #0x1f
ldrsb r1, [r2, r1]                      ldrsb r1, [r2, r1]
mov r4, sp                              mov r4, sp
adds r4, #9                             adds r4, #9
add r2, sp, #8                          add r2, sp, #8
adds r3, r4, #0                         adds r3, r4, #0
bl #0x80a8390                           bl #0x80a8390
add r0, sp, #8                          add r0, sp, #8
ldrb r0, [r0]                           ldrb r0, [r0]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80aaeb4                          beq #0x80aaeb4
mov r0, sb                              mov r0, sb
movs r1, #0                             movs r1, #0
movs r2, #0x80                          movs r2, #0x80
lsls r2, r2, #2                         lsls r2, r2, #2
bl #0x809a570                           bl #0x809a570
movs r0, #0                             movs r0, #0
ldrsb r0, [r4, r0]                      ldrsb r0, [r4, r0]
cmp r0, #0                              cmp r0, #0
beq #0x80aaec8                          beq #0x80aaec8
mov r0, sb                              mov r0, sb
movs r1, #0                             movs r1, #0
movs r2, #0x80                          movs r2, #0x80
lsls r2, r2, #3                         lsls r2, r2, #3
bl #0x809a570                           bl #0x809a570
bl #0x8002804                           bl #0x8002804
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
movs r1, #0x11                          movs r1, #0x11
bl #0x8142950                           bl #0x8142950
mov r3, sb                              mov r3, sb
ldrh r1, [r3, #8]                       ldrh r1, [r3, #8]
adds r1, r1, r0                         adds r1, r1, r0
subs r1, #0x10                          subs r1, #0x10
ldr r4, [sp, #0x14]                     ldr r4, [sp, #0x14]
strh r1, [r4]                           strh r1, [r4]
bl #0x8002804                           bl #0x8002804
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
movs r1, #0x11                          movs r1, #0x11
bl #0x8142950                           bl #0x8142950
adds r0, #4                             adds r0, #4
mov r5, sb                              mov r5, sb
ldrh r5, [r5, #0xa]                     ldrh r5, [r5, #0xa]
adds r0, r0, r5                         adds r0, r0, r5
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0xf6                          adds r1, #0xf6
str r1, [sp, #0x24]                     str r1, [sp, #0x24]
strh r0, [r1]                           strh r0, [r1]
bl #0x8002804                           bl #0x8002804
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
movs r1, #0x11                          movs r1, #0x11
bl #0x8142950                           bl #0x8142950
mov r2, sb                              mov r2, sb
ldrh r1, [r2, #0xc]                     ldrh r1, [r2, #0xc]
adds r1, r1, r0                         adds r1, r1, r0
subs r1, #0x10                          subs r1, #0x10
adds r3, r6, #0                         adds r3, r6, #0
adds r3, #0xf8                          adds r3, #0xf8
strh r1, [r3]                           strh r1, [r3]
adds r0, r6, #0                         adds r0, r6, #0
adds r0, #0xfc                          adds r0, #0xfc
movs r4, #0                             movs r4, #0
strb r4, [r0]                           strb r4, [r0]
adds r4, r6, #0                         adds r4, r6, #0
adds r4, #0xfd                          adds r4, #0xfd
movs r5, #0                             movs r5, #0
strb r5, [r4]                           strb r5, [r4]
ldr r2, [sp, #0x14]                     ldr r2, [sp, #0x14]
movs r5, #0                             movs r5, #0
ldrsh r1, [r2, r5]                      ldrsh r1, [r2, r5]
ldr r2, [sp, #0x24]                     ldr r2, [sp, #0x24]
movs r5, #0                             movs r5, #0
ldrsh r2, [r2, r5]                      ldrsh r2, [r2, r5]
mov ip, r2                              mov ip, r2
movs r2, #0                             movs r2, #0
ldrsh r3, [r3, r2]                      ldrsh r3, [r3, r2]
ldrb r0, [r0]                           ldrb r0, [r0]
str r0, [sp]                            str r0, [sp]
ldrb r0, [r4]                           ldrb r0, [r4]
str r0, [sp, #4]                        str r0, [sp, #4]
ldr r0, [sp, #0xc]                      ldr r0, [sp, #0xc]
mov r2, ip                              mov r2, ip
bl #0x80e2c00                           bl #0x80e2c00
ldr r3, [sp, #0x20]                     ldr r3, [sp, #0x20]
ldr r0, [r3]                            ldr r0, [r3]
cmp r0, #0                              cmp r0, #0
ble #0x80aaf92                          ble #0x80aaf92
mov r0, sl                              mov r0, sl
adds r0, #0x58                          adds r0, #0x58
cmp r8, r0                              cmp r8, r0
beq #0x80aaf78                          beq #0x80aaf78
cmp r8, r0                              cmp r8, r0
bgt #0x80aaf68                          bgt #0x80aaf68
cmp r8, sl                              cmp r8, sl
beq #0x80aaf72                          beq #0x80aaf72
b #0x80aaf8c                            b #0x80aaf8c
mov r0, sl                              mov r0, sl
adds r0, #0xb0                          adds r0, #0xb0
cmp r8, r0                              cmp r8, r0
beq #0x80aaf7e                          beq #0x80aaf7e
b #0x80aaf8c                            b #0x80aaf8c
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0x74                          adds r1, #0x74
b #0x80aaf84                            b #0x80aaf84
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0xca                          adds r1, #0xca
b #0x80aaf84                            b #0x80aaf84
movs r4, #0x93                          movs r4, #0x93
lsls r4, r4, #1                         lsls r4, r4, #1
adds r1, r6, r4                         adds r1, r6, r4
ldrh r0, [r1]                           ldrh r0, [r1]
adds r0, #1                             adds r0, #1
strh r0, [r1]                           strh r0, [r1]
b #0x80aaf92                            b #0x80aaf92
ldrh r0, [r7, #0x30]                    ldrh r0, [r7, #0x30]
subs r0, #1                             subs r0, #1
strh r0, [r7, #0x30]                    strh r0, [r7, #0x30]
movs r5, #0x9a                          movs r5, #0x9a
lsls r5, r5, #1                         lsls r5, r5, #1
adds r0, r6, r5                         adds r0, r6, r5
movs r1, #0                             movs r1, #0
ldrsb r1, [r0, r1]                      ldrsb r1, [r0, r1]
mov r2, r8                              mov r2, r8
ldr r0, [r2]                            ldr r0, [r2]
asrs r0, r0, #8                         asrs r0, r0, #8
muls r0, r1, r0                         muls r0, r1, r0
mov r3, sb                              mov r3, sb
ldrh r3, [r3, #8]                       ldrh r3, [r3, #8]
adds r0, r0, r3                         adds r0, r0, r3
strh r0, [r7, #0x2e]                    strh r0, [r7, #0x2e]
ldr r4, [pc, #0x54]                     ldr r4, [pc, #0x54]
adds r0, r6, r4                         adds r0, r6, r4
movs r1, #0                             movs r1, #0
ldrsb r1, [r0, r1]                      ldrsb r1, [r0, r1]
ldr r0, [r2]                            ldr r0, [r2]
asrs r0, r0, #8                         asrs r0, r0, #8
muls r0, r1, r0                         muls r0, r1, r0
mov r5, sb                              mov r5, sb
ldrh r5, [r5, #0xc]                     ldrh r5, [r5, #0xc]
adds r0, r0, r5                         adds r0, r0, r5
strh r0, [r7, #0x32]                    strh r0, [r7, #0x32]
ldr r0, [sp, #0x20]                     ldr r0, [sp, #0x20]
adds r0, #0x58                          adds r0, #0x58
str r0, [sp, #0x20]                     str r0, [sp, #0x20]
movs r1, #0x58                          movs r1, #0x58
add r8, r1                              add r8, r1
adds r7, #0x58                          adds r7, #0x58
mov r0, sl                              mov r0, sl
adds r0, #0x58                          adds r0, #0x58
cmp r8, r0                              cmp r8, r0
bgt #0x80aafd8                          bgt #0x80aafd8
b #0x80aadf8                            b #0x80aadf8
ldr r2, [sp, #0x10]                     ldr r2, [sp, #0x10]
cmp r2, #0                              cmp r2, #0
bne #0x80aafea                          bne #0x80aafea
adds r2, r6, #0                         adds r2, r6, #0
adds r2, #0x40                          adds r2, #0x40
ldrb r1, [r2]                           ldrb r1, [r2]
movs r0, #0xf3                          movs r0, #0xf3
ands r0, r1                             ands r0, r1
strb r0, [r2]                           strb r0, [r2]
movs r3, #0x9e                          movs r3, #0x9e
lsls r3, r3, #1                         lsls r3, r3, #1
adds r0, r6, r3                         adds r0, r6, r3
ldrh r0, [r0]                           ldrh r0, [r0]
cmp r0, #1                              cmp r0, #1
bne #0x80aaff8                          bne #0x80aaff8
b #0x80ab154                            b #0x80ab154
cmp r0, #1                              cmp r0, #1
bgt #0x80ab008                          bgt #0x80ab008
cmp r0, #0                              cmp r0, #0
beq #0x80ab010                          beq #0x80ab010
b #0x80ab344                            b #0x80ab344
cmp r0, #2                              cmp r0, #2
bne #0x80ab00e                          bne #0x80ab00e
b #0x80ab2b8                            b #0x80ab2b8
b #0x80ab344                            b #0x80ab344
adds r2, r6, #0                         adds r2, r6, #0
adds r2, #0x40                          adds r2, #0x40
ldrb r1, [r2]                           ldrb r1, [r2]
movs r0, #2                             movs r0, #2
orrs r0, r1                             orrs r0, r1
strb r0, [r2]                           strb r0, [r2]
ldr r2, [r6]                            ldr r2, [r6]
ldr r0, [r2, #0x30]                     ldr r0, [r2, #0x30]
movs r1, #2                             movs r1, #2
rsbs r1, r1, #0                         rsbs r1, r1, #0
ands r0, r1                             ands r0, r1
str r0, [r2, #0x30]                     str r0, [r2, #0x30]
adds r7, r6, #0                         adds r7, r6, #0
adds r7, #0x3e                          adds r7, #0x3e
movs r0, #0                             movs r0, #0
ldrsb r0, [r7, r0]                      ldrsb r0, [r7, r0]
movs r5, #0x99                          movs r5, #0x99
lsls r5, r5, #1                         lsls r5, r5, #1
adds r4, r6, r5                         adds r4, r6, r5
ldr r1, [pc, #0x110]                    ldr r1, [pc, #0x110]
adds r5, r6, r1                         adds r5, r6, r1
adds r1, r4, #0                         adds r1, r4, #0
adds r2, r5, #0                         adds r2, r5, #0
bl #0x809d66c                           bl #0x809d66c
ldr r2, [r6]                            ldr r2, [r6]
mov r3, sb                              mov r3, sb
ldrh r0, [r3, #8]                       ldrh r0, [r3, #8]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x15                      asrs r0, r0, #0x15
movs r1, #0                             movs r1, #0
ldrsb r1, [r4, r1]                      ldrsb r1, [r4, r1]
subs r0, r0, r1                         subs r0, r0, r1
lsls r0, r0, #5                         lsls r0, r0, #5
adds r0, #0x10                          adds r0, #0x10
strh r0, [r2, #8]                       strh r0, [r2, #8]
ldr r2, [r6]                            ldr r2, [r6]
ldrh r0, [r3, #0xc]                     ldrh r0, [r3, #0xc]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x15                      asrs r0, r0, #0x15
movs r1, #0                             movs r1, #0
ldrsb r1, [r5, r1]                      ldrsb r1, [r5, r1]
subs r0, r0, r1                         subs r0, r0, r1
lsls r0, r0, #5                         lsls r0, r0, #5
adds r0, #0x10                          adds r0, #0x10
strh r0, [r2, #0xc]                     strh r0, [r2, #0xc]
ldrh r0, [r3, #8]                       ldrh r0, [r3, #8]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x15                      asrs r0, r0, #0x15
movs r1, #0                             movs r1, #0
ldrsb r1, [r4, r1]                      ldrsb r1, [r4, r1]
lsls r1, r1, #2                         lsls r1, r1, #2
subs r0, r0, r1                         subs r0, r0, r1
lsls r0, r0, #5                         lsls r0, r0, #5
adds r0, #0x10                          adds r0, #0x10
movs r2, #0x9b                          movs r2, #0x9b
lsls r2, r2, #1                         lsls r2, r2, #1
adds r1, r6, r2                         adds r1, r6, r2
strh r0, [r1]                           strh r0, [r1]
ldrh r0, [r3, #0xc]                     ldrh r0, [r3, #0xc]
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x15                      asrs r0, r0, #0x15
movs r1, #0                             movs r1, #0
ldrsb r1, [r5, r1]                      ldrsb r1, [r5, r1]
lsls r1, r1, #2                         lsls r1, r1, #2
subs r0, r0, r1                         subs r0, r0, r1
lsls r0, r0, #5                         lsls r0, r0, #5
adds r0, #0x10                          adds r0, #0x10
movs r3, #0x9c                          movs r3, #0x9c
lsls r3, r3, #1                         lsls r3, r3, #1
adds r1, r6, r3                         adds r1, r6, r3
strh r0, [r1]                           strh r0, [r1]
movs r0, #0                             movs r0, #0
ldrsb r0, [r4, r0]                      ldrsb r0, [r4, r0]
rsbs r0, r0, #0                         rsbs r0, r0, #0
strb r0, [r4]                           strb r0, [r4]
movs r0, #0                             movs r0, #0
ldrsb r0, [r5, r0]                      ldrsb r0, [r5, r0]
rsbs r0, r0, #0                         rsbs r0, r0, #0
strb r0, [r5]                           strb r0, [r5]
mov r4, sb                              mov r4, sb
movs r5, #0xa                           movs r5, #0xa
ldrsh r0, [r4, r5]                      ldrsh r0, [r4, r5]
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r6, #0xc]                      str r0, [r6, #0xc]
movs r1, #0xa                           movs r1, #0xa
ldrsh r0, [r4, r1]                      ldrsh r0, [r4, r1]
subs r0, #0x30                          subs r0, #0x30
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r6, #8]                        str r0, [r6, #8]
movs r1, #0x80                          movs r1, #0x80
lsls r1, r1, #4                         lsls r1, r1, #4
str r1, [r6, #4]                        str r1, [r6, #4]
ldr r1, [r6]                            ldr r1, [r6]
asrs r0, r0, #8                         asrs r0, r0, #8
strh r0, [r1, #0xa]                     strh r0, [r1, #0xa]
ldr r0, [r6]                            ldr r0, [r6]
movs r2, #0                             movs r2, #0
ldrsb r2, [r7, r2]                      ldrsb r2, [r7, r2]
ldrh r3, [r6, #0x36]                    ldrh r3, [r6, #0x36]
movs r1, #7                             movs r1, #7
bl #0x809836c                           bl #0x809836c
ldr r0, [pc, #0x6c]                     ldr r0, [pc, #0x6c]
movs r2, #0x89                          movs r2, #0x89
lsls r2, r2, #1                         lsls r2, r2, #1
adds r4, r6, r2                         adds r4, r6, r2
ldr r1, [pc, #0x68]                     ldr r1, [pc, #0x68]
ldr r3, [r0]                            ldr r3, [r0]
adds r0, r4, #0                         adds r0, r4, #0
movs r2, #8                             movs r2, #8
bl #0x8142250                           bl #0x8142250
movs r3, #0x8a                          movs r3, #0x8a
lsls r3, r3, #1                         lsls r3, r3, #1
adds r5, r6, r3                         adds r5, r6, r3
adds r7, #4                             adds r7, #4
movs r2, #0                             movs r2, #0
adds r0, r6, #0                         adds r0, r6, #0
adds r0, #0x7c                          adds r0, #0x7c
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0x44                          adds r1, #0x44
adds r3, r6, #0                         adds r3, r6, #0
adds r3, #0x9c                          adds r3, #0x9c
str r4, [r1]                            str r4, [r1]
strh r2, [r0, #2]                       strh r2, [r0, #2]
strh r2, [r0, #4]                       strh r2, [r0, #4]
strh r2, [r0]                           strh r2, [r0]
adds r0, #0x58                          adds r0, #0x58
adds r1, #0x58                          adds r1, #0x58
cmp r1, r3                              cmp r1, r3
ble #0x80ab108                          ble #0x80ab108
ldr r0, [r6]                            ldr r0, [r6]
ldrb r0, [r0, #0x1f]                    ldrb r0, [r0, #0x1f]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
lsls r0, r0, #2                         lsls r0, r0, #2
ldrh r7, [r7]                           ldrh r7, [r7]
adds r0, r0, r7                         adds r0, r0, r7
lsls r1, r0, #0x10                      lsls r1, r0, #0x10
strb r0, [r5, #4]                       strb r0, [r5, #4]
lsrs r1, r1, #0x18                      lsrs r1, r1, #0x18
movs r0, #3                             movs r0, #3
ands r1, r0                             ands r1, r0
ldrb r2, [r5, #5]                       ldrb r2, [r5, #5]
subs r0, #7                             subs r0, #7
ands r0, r2                             ands r0, r2
orrs r0, r1                             orrs r0, r1
strb r0, [r5, #5]                       strb r0, [r5, #5]
movs r4, #0x9e                          movs r4, #0x9e
lsls r4, r4, #1                         lsls r4, r4, #1
adds r1, r6, r4                         adds r1, r6, r4
movs r0, #1                             movs r0, #1
strh r0, [r1]                           strh r0, [r1]
b #0x80ab344                            b #0x80ab344
mov r8, r6                              mov r8, r6
mov r5, r8                              mov r5, r8
adds r5, #4                             adds r5, #4
mov r8, r5                              mov r8, r5
subs r5, #4                             subs r5, #4
ldm r5!, {r0}                           ldm r5!, {r0}
bl #0x8099c34                           bl #0x8099c34
cmp r0, #0                              cmp r0, #0
bne #0x80ab23a                          bne #0x80ab23a
movs r0, #0x7f                          movs r0, #0x7f
bl #0x8141520                           bl #0x8141520
adds r2, r6, #0                         adds r2, r6, #0
adds r2, #0x40                          adds r2, #0x40
ldrb r1, [r2]                           ldrb r1, [r2]
movs r0, #0xc                           movs r0, #0xc
orrs r0, r1                             orrs r0, r1
strb r0, [r2]                           strb r0, [r2]
movs r7, #0                             movs r7, #0
movs r0, #0x4c                          movs r0, #0x4c
adds r0, r0, r6                         adds r0, r0, r6
mov sl, r0                              mov sl, r0
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0x48                          adds r1, #0x48
str r1, [sp, #0x18]                     str r1, [sp, #0x18]
adds r2, #0x10                          adds r2, #0x10
str r2, [sp, #0x1c]                     str r2, [sp, #0x1c]
movs r0, #0x58                          movs r0, #0x58
adds r5, r7, #0                         adds r5, r7, #0
muls r5, r0, r5                         muls r5, r0, r5
adds r2, r6, r5                         adds r2, r6, r5
ldr r0, [r6]                            ldr r0, [r6]
ldrh r0, [r0, #8]                       ldrh r0, [r0, #8]
adds r1, r2, #0                         adds r1, r2, #0
adds r1, #0x72                          adds r1, #0x72
strh r0, [r1]                           strh r0, [r1]
ldr r0, [r6]                            ldr r0, [r6]
ldrh r0, [r0, #0xa]                     ldrh r0, [r0, #0xa]
adds r0, #0x18                          adds r0, #0x18
adds r1, #2                             adds r1, #2
strh r0, [r1]                           strh r0, [r1]
ldr r0, [r6]                            ldr r0, [r6]
ldrh r1, [r0, #0xc]                     ldrh r1, [r0, #0xc]
adds r0, r2, #0                         adds r0, r2, #0
adds r0, #0x76                          adds r0, #0x76
strh r1, [r0]                           strh r1, [r0]
ldr r3, [sp, #0x1c]                     ldr r3, [sp, #0x1c]
adds r0, r3, r5                         adds r0, r3, r5
movs r4, #0                             movs r4, #0
str r4, [r0]                            str r4, [r0]
bl #0x8002804                           bl #0x8002804
ldr r1, [sp, #0x18]                     ldr r1, [sp, #0x18]
adds r4, r1, r5                         adds r4, r1, r5
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
movs r1, #7                             movs r1, #7
bl #0x8142950                           bl #0x8142950
lsls r0, r0, #0x10                      lsls r0, r0, #0x10
asrs r0, r0, #0x10                      asrs r0, r0, #0x10
adds r0, #3                             adds r0, #3
muls r0, r7, r0                         muls r0, r7, r0
adds r0, #3                             adds r0, #3
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r4]                            str r0, [r4]
movs r2, #0x99                          movs r2, #0x99
lsls r2, r2, #1                         lsls r2, r2, #1
adds r0, r6, r2                         adds r0, r6, r2
ldrb r0, [r0]                           ldrb r0, [r0]
lsls r0, r0, #0x18                      lsls r0, r0, #0x18
asrs r0, r0, #0x18                      asrs r0, r0, #0x18
cmp r0, #0                              cmp r0, #0
beq #0x80ab1fc                          beq #0x80ab1fc
mov r3, sl                              mov r3, sl
adds r2, r3, r5                         adds r2, r3, r5
mov r4, sb                              mov r4, sb
movs r5, #8                             movs r5, #8
ldrsh r0, [r4, r5]                      ldrsh r0, [r4, r5]
ldr r1, [r6]                            ldr r1, [r6]
movs r3, #8                             movs r3, #8
ldrsh r1, [r1, r3]                      ldrsh r1, [r1, r3]
b #0x80ab20c                            b #0x80ab20c
mov r4, sl                              mov r4, sl
adds r2, r4, r5                         adds r2, r4, r5
mov r5, sb                              mov r5, sb
movs r1, #0xc                           movs r1, #0xc
ldrsh r0, [r5, r1]                      ldrsh r0, [r5, r1]
ldr r1, [r6]                            ldr r1, [r6]
movs r3, #0xc                           movs r3, #0xc
ldrsh r1, [r1, r3]                      ldrsh r1, [r1, r3]
subs r0, r0, r1                         subs r0, r0, r1
cmp r0, #0                              cmp r0, #0
bge #0x80ab214                          bge #0x80ab214
rsbs r0, r0, #0                         rsbs r0, r0, #0
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r2]                            str r0, [r2]
adds r7, #1                             adds r7, #1
cmp r7, #1                              cmp r7, #1
ble #0x80ab18c                          ble #0x80ab18c
movs r4, #0x99                          movs r4, #0x99
lsls r4, r4, #1                         lsls r4, r4, #1
adds r0, r6, r4                         adds r0, r6, r4
ldrb r0, [r0]                           ldrb r0, [r0]
movs r5, #0x9a                          movs r5, #0x9a
lsls r5, r5, #1                         lsls r5, r5, #1
adds r1, r6, r5                         adds r1, r6, r5
strb r0, [r1]                           strb r0, [r1]
ldr r1, [pc, #0x80]                     ldr r1, [pc, #0x80]
adds r0, r6, r1                         adds r0, r6, r1
ldrb r0, [r0]                           ldrb r0, [r0]
ldr r2, [pc, #0x7c]                     ldr r2, [pc, #0x7c]
adds r1, r6, r2                         adds r1, r6, r2
strb r0, [r1]                           strb r0, [r1]
mov r3, r8                              mov r3, r8
ldr r0, [r3, #4]                        ldr r0, [r3, #4]
ldr r1, [r6, #4]                        ldr r1, [r6, #4]
adds r0, r0, r1                         adds r0, r0, r1
str r0, [r3, #4]                        str r0, [r3, #4]
ldr r0, [r6, #4]                        ldr r0, [r6, #4]
adds r1, r0, #0                         adds r1, r0, #0
subs r1, #0x99                          subs r1, #0x99
str r1, [r6, #4]                        str r1, [r6, #4]
ldr r2, [r3, #8]                        ldr r2, [r3, #8]
ldr r0, [r3, #4]                        ldr r0, [r3, #4]
cmp r2, r0                              cmp r2, r0
blt #0x80ab25a                          blt #0x80ab25a
cmp r1, #0                              cmp r1, #0
bgt #0x80ab25a                          bgt #0x80ab25a
str r2, [r3, #4]                        str r2, [r3, #4]
ldr r1, [r6]                            ldr r1, [r6]
ldr r0, [r6, #8]                        ldr r0, [r6, #8]
asrs r0, r0, #8                         asrs r0, r0, #8
strh r0, [r1, #0xa]                     strh r0, [r1, #0xa]
adds r0, r6, #0                         adds r0, r6, #0
movs r1, #4                             movs r1, #4
bl #0x80a9e6c                           bl #0x80a9e6c
ldr r0, [r6]                            ldr r0, [r6]
bl #0x8099c64                           bl #0x8099c64
cmp r0, #0                              cmp r0, #0
beq #0x80ab344                          beq #0x80ab344
ldr r0, [r6]                            ldr r0, [r6]
adds r1, r6, #0                         adds r1, r6, #0
adds r1, #0x3e                          adds r1, #0x3e
movs r2, #0                             movs r2, #0
ldrsb r2, [r1, r2]                      ldrsb r2, [r1, r2]
movs r1, #3                             movs r1, #3
movs r3, #0                             movs r3, #0
bl #0x809836c                           bl #0x809836c
mov r4, sb                              mov r4, sb
movs r5, #0xa                           movs r5, #0xa
ldrsh r0, [r4, r5]                      ldrsh r0, [r4, r5]
subs r0, #0x30                          subs r0, #0x30
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r6, #0xc]                      str r0, [r6, #0xc]
movs r1, #0xa                           movs r1, #0xa
ldrsh r0, [r4, r1]                      ldrsh r0, [r4, r1]
lsls r0, r0, #8                         lsls r0, r0, #8
str r0, [r6, #8]                        str r0, [r6, #8]
movs r1, #0                             movs r1, #0
str r1, [r6, #4]                        str r1, [r6, #4]
ldr r1, [r6]                            ldr r1, [r6]
asrs r0, r0, #8                         asrs r0, r0, #8
strh r0, [r1, #0xa]                     strh r0, [r1, #0xa]
movs r2, #0x9e                          movs r2, #0x9e
lsls r2, r2, #1                         lsls r2, r2, #1
adds r1, r6, r2                         adds r1, r6, r2
movs r0, #2                             movs r0, #2
strh r0, [r1]                           strh r0, [r1]
b #0x80ab344                            b #0x80ab344
movs r3, #0x99                          movs r3, #0x99
lsls r3, r3, #1                         lsls r3, r3, #1
adds r2, r6, r3                         adds r2, r6, r3
movs r0, #0                             movs r0, #0
ldrsb r0, [r2, r0]                      ldrsb r0, [r2, r0]
cmp r0, #0                              cmp r0, #0
beq #0x80ab2d0                          beq #0x80ab2d0
ldr r1, [r6]                            ldr r1, [r6]
lsls r0, r0, #2                         lsls r0, r0, #2
ldrh r4, [r1, #8]                       ldrh r4, [r1, #8]
adds r0, r0, r4                         adds r0, r0, r4
strh r0, [r1, #8]                       strh r0, [r1, #8]
ldr r5, [pc, #0x38]                     ldr r5, [pc, #0x38]
adds r2, r6, r5                         adds r2, r6, r5
movs r0, #0                             movs r0, #0
ldrsb r0, [r2, r0]                      ldrsb r0, [r2, r0]
cmp r0, #0                              cmp r0, #0
beq #0x80ab2e6                          beq #0x80ab2e6
ldr r1, [r6]                            ldr r1, [r6]
lsls r0, r0, #2                         lsls r0, r0, #2
ldrh r2, [r1, #0xc]                     ldrh r2, [r1, #0xc]
adds r0, r0, r2                         adds r0, r0, r2
strh r0, [r1, #0xc]                     strh r0, [r1, #0xc]
adds r2, r6, #4                         adds r2, r6, #4
ldr r0, [r2, #4]                        ldr r0, [r2, #4]
ldr r1, [r6, #4]                        ldr r1, [r6, #4]
adds r0, r0, r1                         adds r0, r0, r1
str r0, [r2, #4]                        str r0, [r2, #4]
ldr r0, [r6, #4]                        ldr r0, [r6, #4]
adds r1, r0, #0                         adds r1, r0, #0
subs r1, #0x99                          subs r1, #0x99
str r1, [r6, #4]                        str r1, [r6, #4]
ldr r3, [r2, #8]                        ldr r3, [r2, #8]
ldr r0, [r2, #4]                        ldr r0, [r2, #4]
cmp r3, r0                              cmp r3, r0
blt #0x80ab310                          blt #0x80ab310
cmp r1, #0                              cmp r1, #0
bgt #0x80ab310                          bgt #0x80ab310
str r3, [r2, #4]                        str r3, [r2, #4]
movs r2, #0                             movs r2, #0
b #0x80ab312                            b #0x80ab312
movs r2, #1                             movs r2, #1
ldr r1, [r6]                            ldr r1, [r6]
ldr r0, [r6, #8]                        ldr r0, [r6, #8]
asrs r0, r0, #8                         asrs r0, r0, #8
strh r0, [r1, #0xa]                     strh r0, [r1, #0xa]
cmp r2, #0                              cmp r2, #0
bne #0x80ab344                          bne #0x80ab344
ldr r2, [r6]                            ldr r2, [r6]
ldr r0, [r2, #0x30]                     ldr r0, [r2, #0x30]
movs r1, #1                             movs r1, #1
orrs r0, r1                             orrs r0, r1
str r0, [r2, #0x30]                     str r0, [r2, #0x30]
adds r2, r6, #0                         adds r2, r6, #0
adds r2, #0x40                          adds r2, #0x40
ldrb r0, [r2]                           ldrb r0, [r2]
movs r1, #0xfd                          movs r1, #0xfd
ands r1, r0                             ands r1, r0
strb r1, [r2]                           strb r1, [r2]
movs r0, #0xc                           movs r0, #0xc
ands r0, r1                             ands r0, r1
cmp r0, #0                              cmp r0, #0
bne #0x80ab344                          bne #0x80ab344
movs r0, #0                             movs r0, #0
strb r0, [r2]                           strb r0, [r2]
movs r0, #0                             movs r0, #0
b #0x80ab346                            b #0x80ab346
movs r0, #1                             movs r0, #1
add sp, #0x28                           add sp, #0x28
pop {r3, r4, r5}                        pop {r3, r4, r5}
mov r8, r3                              mov r8, r3
mov sb, r4                              mov sb, r4
mov sl, r5                              mov sl, r5
pop {r4, r5, r6, r7}                    pop {r4, r5, r6, r7}
pop {r1}                                pop {r1}
bx r1                                   bx r1
```
