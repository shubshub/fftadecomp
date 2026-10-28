#include "ffta.h"

struct Object0802304C {
    u8 unknown_00[8];
    u8 enabled;
};

struct Context0802304C {
    u8 unknown_00[0xC];
    struct Object0802304C *object;
};

struct State0802304C {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 active;
    u16 counter;
};

extern struct Context0802304C data_03002710;
extern struct State0802304C data_030028A0;
extern u8 func_080C95A8(u16 index);
extern void func_080C72B0(void);
extern void func_08004C40(void);

/* 0x0802304C..0x080230A8: 92 bytes, including literal pools. */
void func_0802304C(void)
{
    u32 enabled = func_080C95A8(13);

    if (enabled == 1) {
        func_080C72B0();
        if (data_03002710.object->enabled &&
            (data_030028A0.active ||
             (data_030028A0.counter > 60 && data_030028A0.mode != 3))) {
            func_08004C40();
            data_030028A0.active = enabled;
            data_030028A0.counter = 300;
        }
    }
}
