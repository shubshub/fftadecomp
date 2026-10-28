#include "ffta.h"

struct Module08024108 {
    void *resource;
    u8 unknown_04[0x76];
    u16 mode;
};

struct Display08024108 {
    u8 unknown_00[7];
    u8 flags : 8;
};

struct Script08024108 {
    u8 unknown_0000[0x3C24];
    u32 flags;
};

struct State08024108 {
    u8 unknown_00[0x96];
    u16 counter;
};

extern struct Module08024108 data_0200F3AC;
extern struct Display08024108 data_03000000;
extern struct Script08024108 g_state_02000000;
extern struct State08024108 g_state_0200F390;
extern u16 data_03003860;

extern void func_080247FC(struct Module08024108 *object);
extern void func_08096CB8(void);
extern void func_08022DD0(void);
extern void func_0802282C(void);
extern void func_080231C0(void);
extern u8 func_0800395C(void);
extern void func_08003934(u8 value);
extern u8 func_080C9540(u16 flag);
extern u16 func_080038E8(u16 value);
extern void func_080038C8(u8 value);
extern void func_080891BC(void);

/* 0x08024108..0x080241B4: 172 bytes, including literal pools. */
u32 func_08024108(void)
{
    func_080247FC(&data_0200F3AC);
    func_08096CB8();
    func_08022DD0();
    func_0802282C();
    data_03000000.flags &= ~1;

    if (data_0200F3AC.mode == 3) {
        func_080231C0();
    } else {
        data_03003860 = 0;
        /* Clear the first palette RAM color. */
        *(u16 *)0x05000000 = 0;
        if (func_0800395C())
            func_08003934(3);
        else if (func_080C9540(0x44))
            func_080038E8(9);
        else
            func_080038C8(1);
    }

    if (g_state_02000000.flags & 8) {
        func_080891BC();
        g_state_02000000.flags &= ~8;
    }
    g_state_0200F390.counter = 0;
    return 1;
}
