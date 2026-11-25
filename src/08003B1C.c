#include "ffta.h"

// Complete [0x08003B1C, 0x08003D20): 516 bytes, 181 instructions.

typedef struct {
    u8 mode;
    u8 unknown_01[0x11F];
    u16 unknown_120;
    u16 unknown_122;
    u8 phase;
    u8 flags;
    u16 step;
} LinkState;

extern u32 data_03000E58;
extern LinkState data_030028A0;
extern u16 data_030034D8;
extern u16 data_03002B68;
extern u16 data_03002890[];
extern u16 data_03002B50[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08004FF4(const char *string);
extern u32 func_08003E88(const char *input);

/* The first eight statements are the body of the merged func_08005028.  Both
 * calls are inlined, and cross-jumping keeps one copy of the block from
 * 0x08003CA6; each case keeps its own data_03002B68 store (0x08003C52,
 * 0x08003C9E).  The fills use sp+0 and sp+2. */
static inline void reset_link(void)
{
    u16 first_fill;
    u16 second_fill;

    data_03002B68 = 0;
    data_030028A0.step = data_030028A0.mode == 8 ? 0 : 5;
    data_03002890[0] = 0;
    data_03002B50[0] = 0;
    first_fill = 0;
    func_0814186C(&first_fill, &data_03002890[1], 0x01000006);
    second_fill = 0;
    func_0814186C(&second_fill, &data_03002B50[1], 0x01000006);
    data_030028A0.phase = 0x17;
    data_030028A0.unknown_120 = 0;
    data_030028A0.unknown_122 = 0;
}

s32 func_08003B1C(const char *first, const char *second)
{
    if (data_03000E58 != 3)
        return 0;
    if (data_030028A0.phase != 1 && data_030028A0.flags != 1)
        return 0;
    switch (data_030028A0.step) {
    case 0:
        data_030034D8 = 0;
        data_030028A0.phase = 1;
        data_030028A0.step = 1;
        break;
    case 1:
        data_030028A0.phase = 1;
        if (data_030034D8++ > 5)
            data_030028A0.step = 10;
        break;
    case 10:
        if (func_08004FF4(first)) {
            func_08003E88(second);
            data_030028A0.step = 11;
        } else {
            func_08003E88(first);
        }
        break;
    case 11:
        data_030034D8 = 0;
        data_030028A0.step = 12;
        func_08003E88(second);
        break;
    case 12:
        if (data_030034D8++ > 15 || data_030028A0.flags == 1) {
            reset_link();
            return 1;
        }
        func_08003E88(second);
        break;
    case 5:
        if (func_08004FF4(first)) {
            func_08003E88(first);
            data_030028A0.step = 6;
        }
        break;
    case 6:
        if (func_08004FF4(second)) {
            reset_link();
            return 1;
        }
        func_08003E88(first);
        break;
    }
    return 0;
}
