#include "ffta.h"

/* Target: complete [0x08135890, 0x08135982), 242 bytes including literals. */
extern Table data_0200F3A0;
extern u32 data_0200F3C0;
extern u8 data_0200F3BC;
extern u8 g_state_0200F390;
extern void *data_0200F3B8;
extern u8 data_0300284C;

extern void func_08137A9C(void);
extern void func_08006A7C(Table *, u32 *, u8 *, u8);
extern void func_08136084(u8, u8 *);
extern void func_080069F4(Table *, u8);
extern void func_08006B5C(Table *);
extern void func_08137AD0(void);
extern void *func_08137AEC(u32);
extern void func_08137B20(void *, u32);
extern void func_080038C8(u32);
extern void func_0800363C(void);
extern void func_08009AFC(u32);

void func_08135890(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
        func_08137A9C();
        func_08006A7C(&data_0200F3A0, &data_0200F3C0, &data_0200F3BC, 1);
        func_08006ADC(&data_0200F3A0, 0, (u32)func_08136084);
        *state = 1;
        g_state_0200F390 = 1;
        break;
    case 1:
        func_080069F4(&data_0200F3A0, 1);
        *state = g_state_0200F390;
        break;
    case 2:
        func_08006B5C(&data_0200F3A0);
        func_08137AD0();
        func_08137A9C();
        data_0200F3B8 = func_08137AEC(0x22e0);
        func_08137B20(data_0200F3B8, 0);
        data_0300284C = 0;
        func_080038C8(7);
        *state = 3;
        g_state_0200F390 = 3;
        break;
    case 3:
        func_080069F4(&data_0200F3A0, 1);
        *state = g_state_0200F390;
        break;
    case 4:
        func_0800363C();
        func_08009AFC(1);
        func_080038C8(2);
        *state = 255;
        break;
    case 5:
        func_080038C8(11);
        *state = 255;
        break;
    }
}
