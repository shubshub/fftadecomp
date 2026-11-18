#include "ffta.h"

/* Complete 080D89D0..080D8A58 (136 bytes):
 * F0 B5 57 46 4E 46 45 46 E0 B4 8E B0 16 9C A4 46 17 9F 1A 9D 1B 9E 1C 9C
 * A0 46 1D 9C A1 46 1E 9C A2 46 1F 9C 00 94 09 06 09 0E 12 06 12 0E 1B 06
 * 1B 0E 08 AC 20 70 61 70 A2 70 E3 70 A5 80 60 46 E0 80 27 81 18 9B E3 60
 * 19 98 20 61 26 75 43 46 63 75 48 46 A0 75 53 46 E3 75 02 94 07 48 00 68
 * 07 49 08 4A 01 AB 2C F7 8D FF 0E B0 38 BC 98 46 A1 46 AA 46 F0 BC 02 BC
 * 08 47 00 00 30 F4 00 02 09 7B 0D 08 3C 10 00 00
 */

typedef struct {
    u8 unknown_00;
    u8 unknown_01;
    u8 unknown_02;
    u8 unknown_03;
    u16 unknown_04;
    u16 unknown_06;
    u16 unknown_08;
    void *unknown_0C;
    void *unknown_10;
    u8 unknown_14;
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
} Payload;

typedef struct {
    u32 unknown_00;
    Payload *payload;
    u32 unknown_08[5];
} Descriptor;

typedef int (*TaskCallback)(void *, void *, void *);

extern void *data_0200F430;
extern int func_080D7B08(void *, void *, void *);
extern void *func_08005954(void *, TaskCallback, u16, void *, void *);

void *func_080D89D0(u8 a0, u8 a1, u8 a2, u8 a3, u16 a4, u16 a5,
                    void *a6, void *a7, u16 a8, u8 a9, u8 a10, u8 a11,
                    u8 a12, void *parent)
{
    Descriptor descriptor;
    Payload payload;

    payload.unknown_00 = a0;
    payload.unknown_01 = a1;
    payload.unknown_02 = a2;
    payload.unknown_03 = a3;
    payload.unknown_04 = a8;
    payload.unknown_06 = a4;
    payload.unknown_08 = a5;
    payload.unknown_0C = a6;
    payload.unknown_10 = a7;
    payload.unknown_14 = a9;
    payload.unknown_15 = a10;
    payload.unknown_16 = a11;
    payload.unknown_17 = a12;
    descriptor.payload = &payload;
    return func_08005954(data_0200F430, func_080D7B08, 0x103C,
                         &descriptor, parent);
}
