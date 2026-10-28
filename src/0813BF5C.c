#include "ffta.h"

extern u8 data_0300280C;
extern Table data_0200F3A0;
extern u32 data_0200F3B8[];
extern u8 data_0200F3B4[];
extern u8 g_state_0200F390;

void func_0813C064(void);
void func_08006A7C(Table *state, u32 *words, u8 *flags, u8 count);
void func_080069F4(Table *state, u8 count);
u8 func_080C9540(u16 flag);
void func_08009AFC(u8 value);
void func_08009FD0(void);
void func_0813C0EC(u8 index, u8 *flag);
void func_0813DB34(u8 index, u8 *flag);
void func_0813C0A8(void);
u8 func_0800395C(void);
void func_08003918(void);
void func_080038C8(u8 value);

/* 0x0813BF5C - 264 bytes, including literal pools. */
void func_0813BF5C(u8 index, u8 *phase)
{
    switch (*phase) {
    case 0:
        data_0300280C = 0;
        func_0813C064();
        func_08006A7C(&data_0200F3A0, data_0200F3B8, data_0200F3B4, 1);
        func_08006ADC(&data_0200F3A0, 0, (u32)func_0813C0EC);
        g_state_0200F390 = *phase = 1;
        break;
    case 1:
        func_080069F4(&data_0200F3A0, 1);
        *phase = g_state_0200F390;
        if (func_080C9540(0x44) && *phase == 2) {
            func_08009AFC(5);
            func_08009FD0();
            *phase = 0xFF;
        }
        break;
    case 2:
        func_08006A7C(&data_0200F3A0, data_0200F3B8, data_0200F3B4, 1);
        func_08006ADC(&data_0200F3A0, 0, (u32)func_0813DB34);
        g_state_0200F390 = *phase = 3;
        break;
    case 3:
        func_080069F4(&data_0200F3A0, 1);
        *phase = g_state_0200F390;
        break;
    case 0xFF:
        func_0813C0A8();
        if (func_0800395C())
            func_08003918();
        else
            func_080038C8(5);
        break;
    }
}
