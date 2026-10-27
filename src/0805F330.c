#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 state;
    u8 unknown_119A[8];
    u8 pending;
} MenuState;

extern MenuState *data_0200F448;
extern u8 data_030008B0[];
extern u32 func_0800A5EC(void);
extern void func_08013364(void);
extern u16 func_08011860(void);
extern void func_08029E48(void *graphics, u32 x, u32 y,
                          u32 width, u32 height, u32 value);
extern void func_0802A2C0(u32 first, u32 second, u32 third, u32 fourth);

/* Complete target: 0x0805F330..0x0805F3C2, 146 bytes. */
u32 func_0805F330(void)
{
    switch (data_0200F448->state)
    {
    case 0:
        if (!func_0800A5EC())
        {
            data_0200F448->state = 11;
            return 2;
        }
        func_08013364();
        data_0200F448->state = 1;
        break;

    case 1:
        if (func_08011860())
        {
            func_08029E48(data_030008B0, 0, 0, 20, 17, 0);
            func_0802A2C0(0, 0, 0, 0);
            data_0200F448->pending = 0;
            data_0200F448->state = 0xFF;
            return 8;
        }
        break;
    }
    return 7;
}
