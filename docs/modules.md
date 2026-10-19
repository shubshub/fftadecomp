# Proposed file structure, derived from the ROM

    functions considered   4,311
    informative globals   100 (2..32 referrers), covering 519 functions
    ubiquitous globals    11 (too common to be evidence, e.g. the EWRAM base)
    demoted globals       10 (informative alone, but merging them would over-fill a cluster)
    mutual-recursion SCCs  0 (0 functions)
    identical-code groups  163 (386 functions)

    clusters of >= 2 functions: 75
    singletons with no shared evidence: 3,792

Names are address-based on purpose. There are no strings in this ROM to name things
after, and a wrong confident name is worse than func_080C15DC.

## Largest clusters

| functions | bytes | matched | shared globals | cyc | proposed file |
|---|---|---|---|---|---|
| 28 | 1,420 | 1 | 0x02000080, 0x03000990 | - | `module_009750.c` |
| 23 | 1,246 | 2 | 0x02007F10, 0x020080C4 | - | `module_019FC0.c` |
| 22 | 636 | 0 | 0x0200F448 | - | `module_05D100.c` |
| 21 | 336 | 0 | 0x0200F390 | - | `module_022C20.c` |
| 20 | 510 | 1 | 0x0200918C | - | `module_011740.c` |
| 20 | 972 | 0 | 0x030027D8, 0x03003860 | - | `module_030E50.c` |
| 19 | 536 | 1 | 0x02004270, 0x0200F444 | - | `module_02DFC0.c` |
| 17 | 686 | 0 | 0x0200F3B0, 0x03000E60 | - | `module_022870.c` |
| 15 | 510 | 0 | 0x02009188 | - | `module_008810.c` |
| 15 | 232 | 0 | 0x020159C4, 0x020159CC | - | `module_121A40.c` |
| 14 | 494 | 0 | 0x03002BC0, 0x03002BCC | - | `module_0007C0.c` |
| 14 | 402 | 1 | 0x0200F440 | - | `module_02B6A0.c` |
| 13 | 408 | 0 | 0x02008FF8, 0x02009000 | - | `module_00A670.c` |
| 13 | 374 | 0 | 0x0200F44C | - | `module_05F410.c` |
| 13 | 234 | 0 | 0x020084D8 | - | `module_1414B0.c` |
| 12 | 844 | 0 | 0x03000020, 0x03000030 | - | `module_001050.c` |
| 11 | 868 | 8 | 0x020101F8 | - | `module_0C1460.c` |
| 11 | 300 | 0 | 0x0200F430, 0x020159C0 | - | `module_0D37C0.c` |
| 10 | 364 | 0 | 0x03000870, 0x03000EA0 | - | `module_0006D0.c` |
| 9 | 248 | 0 | 0x03000ED0 | - | `module_002160.c` |
| 9 | 156 | 0 | 0x02015738 | - | `module_0C7240.c` |
| 8 | 152 | 0 | 0x0200F3F0 | - | `module_12F2A0.c` |
| 8 | 232 | 0 | 0x03007FF0 | - | `module_144E00.c` |
| 7 | 204 | 0 | 0x02009168, 0x02009170 | - | `module_010930.c` |
| 7 | 148 | 0 | 0x02009190 | - | `module_0185C0.c` |
| 7 | 362 | 0 | 0x02008168 | - | `module_01CE60.c` |
| 7 | 448 | 0 | 0x03000E30 | - | `module_035840.c` |
| 6 | 188 | 0 | 0x0200F370 | - | `module_141B10.c` |
| 5 | 100 | 0 | 0x02008FF0 | - | `module_005A20.c` |
| 5 | 142 | 0 | 0x02009148 | - | `module_00C340.c` |
| 5 | 222 | 0 | 0x0200F1D4 | - | `module_020A60.c` |
| 5 | 102 | 0 | 0x02002FC4 | - | `module_02D7A0.c` |
| 5 | 112 | 0 | 0x02001F3C | - | `module_051040.c` |
| 5 | 72 | 0 | 0x0200F3B8, 0x0200FFC8 | - | `module_09DE00.c` |
| 5 | 120 | 0 | 0x0200F9E8 | - | `module_0A9290.c` |
| 4 | 50 | 0 | 0x03000880 | - | `module_000430.c` |
| 4 | 60 | 0 | 0x03000890 | - | `module_0098C0.c` |
| 4 | 86 | 0 | 0x02007F20 | - | `module_01D980.c` |
| 4 | 128 | 0 | 0x02003C3C | - | `module_02DD50.c` |
| 4 | 70 | 0 | 0x0201F544 | - | `module_04CBB0.c` |

## Identical code

Same function at two addresses - proof of a shared module, and a free match for whoever
reaches the second one.

- 0x08102FEC, 0x08105F64, 0x081065B4, 0x08106778, 0x0810693C, 0x08106C04, 0x08106DA0
- 0x0814362C, 0x0814365C, 0x081436AC, 0x081436FC, 0x0814374C, 0x0814379C, 0x081437EC
- 0x0803FAA4, 0x08040628, 0x08041224, 0x080425F8, 0x080853A0, 0x080855C8
- 0x0800DC7C, 0x0800DCA0, 0x0800DD30, 0x0800DD5C, 0x0800DD88
- 0x080401F4, 0x08040DA4, 0x08041FB4, 0x08042E48, 0x08085558
- 0x080EDE64, 0x080EE2F4, 0x080EE948, 0x0810205C, 0x0810457C
- 0x080F2E78, 0x080F93E0, 0x080FE7BC, 0x080FF180, 0x081007F0
- 0x080F5F7C, 0x080F695C, 0x080F7A34, 0x080F8608, 0x080FC058
- 0x0810471C, 0x0810482C, 0x0810522C, 0x081064A4, 0x08106AF4
- 0x0803FB50, 0x080406D4, 0x080412D0, 0x080426A4
- 0x080535E8, 0x08057388, 0x0805C3D4, 0x0806E60C
- 0x080E5438, 0x080EFCC0, 0x080F6490, 0x0810835C
- 0x080EA2D8, 0x080EF120, 0x080EF37C, 0x080F0594
- 0x080034B8, 0x08003508, 0x08003558
- 0x080035A8, 0x080035D0, 0x080035F8
- 0x0800B2A4, 0x0800B394, 0x0800B47C
- 0x0800E4DC, 0x08010160, 0x080102EC
- 0x0802807C, 0x0802BAF8, 0x0802EAE0
- 0x0805CF00, 0x081369B0, 0x0813F19C
- 0x0809975C, 0x08099790, 0x080997E8

## Mutual recursion

A cycle is hard to express across objects, so these belong together.


## Shared globals, largest first

A global touched by several functions is a struct, and a struct is the reason
two functions end up in the same file.

| global | functions | sample |
|---|---|---|
| `0x0200F448` | 22 | 0x0805D108, 0x0805D13C, 0x0805D174, 0x0805D1C0 |
| `0x02007F10` | 21 | 0x08019FC8, 0x0801A320, 0x0801CB20, 0x0801CC38 |
| `0x0200F390` | 21 | 0x08022C2C, 0x08022C44, 0x08022C64, 0x08022E24 |
| `0x0200918C` | 20 | 0x0801174C, 0x08011860, 0x08011B30, 0x08011C60 |
| `0x0200F444` | 19 | 0x0802DFCC, 0x0802E008, 0x0802E08C, 0x0802E0DC |
| `0x03000990` | 16 | 0x0800975C, 0x08017490, 0x08029864, 0x0802A1FC |
| `0x02009188` | 15 | 0x08008818, 0x08008880, 0x080088D8, 0x08008954 |
| `0x0200F440` | 14 | 0x0802B6A0, 0x0802B6F0, 0x0802B960, 0x0802B9B4 |
| `0x02000080` | 13 | 0x08009C94, 0x08018E20, 0x0802D824, 0x0802DE10 |
| `0x0200F44C` | 13 | 0x0805F414, 0x0805F44C, 0x0805F4AC, 0x0805F540 |
| `0x020159CC` | 13 | 0x08121A48, 0x08121B8C, 0x08121BB8, 0x08121BF4 |
| `0x020084D8` | 13 | 0x081414BC, 0x08141520, 0x08141540, 0x08141570 |
| `0x03003860` | 12 | 0x08030E50, 0x0804BDDC, 0x08087160, 0x08087554 |
| `0x020101F8` | 11 | 0x080C1460, 0x080C1484, 0x080C14B0, 0x080C14D8 |
| `0x0200F3B0` | 11 | 0x08136A10, 0x08136DEC, 0x08137040, 0x0813D4A0 |
| `0x03002BCC` | 10 | 0x080007C8, 0x08000A48, 0x08000A98, 0x08000ADC |
| `0x02009000` | 10 | 0x0800A67C, 0x0800B0AC, 0x0800B568, 0x0800BB74 |
| `0x03000ED0` | 9 | 0x0800216C, 0x0800221C, 0x08009888, 0x080231C0 |
| `0x02015738` | 9 | 0x080C7240, 0x080C7260, 0x080C7284, 0x080C72F8 |
| `0x030027D8` | 9 | 0x08137B20, 0x08137B50, 0x08137C4C, 0x081380B8 |
| `0x0200F3F0` | 8 | 0x0812F2A4, 0x0812F358, 0x08130200, 0x081306E0 |
| `0x03007FF0` | 8 | 0x08144E08, 0x081453F8, 0x08145608, 0x081456AC |
| `0x03000EA0` | 7 | 0x080006D0, 0x08000788, 0x08003A98, 0x08004C40 |
| `0x02009170` | 7 | 0x0801093C, 0x08010DD0, 0x080114FC, 0x08011564 |
| `0x02009190` | 7 | 0x080185C8, 0x08018624, 0x08018790, 0x080189A0 |
