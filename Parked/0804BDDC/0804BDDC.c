#include "ffta.h"

typedef struct
{
    u8 unknown_00[0xA0];
    u16 first[256];
    u16 second[256];
} State0804BDDC;

extern State0804BDDC *g_state_03002810;
extern u16 data_03003860[];
extern s32 func_081426B8(s32 input0, s32 input1);
extern s16 func_08007A60(u8 index);

/* Complete target [0x0804BDDC, 0x0804BEE8), 268 bytes.
 * f0b557464e464546e0b481b0021c0c1c1206120e2406240e3a480068a02109188846a821
 * 8900471837488246a039514400914020111cf6f051fc60430006000ebbf720fe0004c014
 * 2021091a0904090c002294461f261f2081462020441a424611884846084060435546aa1c
 * 9246002800da1f3043110a04500d30406043002800da1f30401141011943900e30406043
 * 002800da1f3040118002014329803988484608406043009daa1c0092002800da1f304311
 * 0a04500d30406043002800da1f30401141011943900e30406043002800da1f3040118002
 * 01432980604601300004000c84460220804402376146ff29b5d901b038bc9846a146aa46
 * f0bc01bc004700001028000360380003
 */
void func_0804BDDC(u8 input0, u8 input1)
{
    const u16 *first = g_state_03002810->first;
    const u16 *second = g_state_03002810->second;
    u16 *first_output = data_03003860;
    u16 *second_output = data_03003860 + 256;
    u8 selector = (u32)func_081426B8(64, input0) * input1;
    u16 weight = 32 - (func_08007A60(selector) >> 3);
    s32 factor = 32 - weight;
    u16 index;

    for (index = 0; index < 256; index++)
    {
        u16 value = *first++;

        *first_output++ = ((value & 31) * factor / 32)
                        | ((((value >> 5) & 31) * factor / 32) << 5)
                        | ((((value >> 10) & 31) * factor / 32) << 10);
        value = *second++;
        *second_output++ = ((value & 31) * factor / 32)
                         | ((((value >> 5) & 31) * factor / 32) << 5)
                         | ((((value >> 10) & 31) * factor / 32) << 10);
    }
}
