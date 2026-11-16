#include "ffta.h"

typedef struct Transition08022F00 {
    s16 first;
    s16 second;
    s16 target_first;
    s16 target_second;
    u8 unknown_08[0x10];
} Transition08022F00;

typedef struct State08022F00 {
    u8 unknown_00[0x0D];
    u8 half_duration;
    u8 unknown_0E[0x36];
    Transition08022F00 transition;
    u16 *buffer;
} State08022F00;

typedef void (*PaletteInitializer08022F00)(void *destination, u32 size);

extern State08022F00 g_state_0200F390;
extern u16 data_03003860[512];
extern PaletteInitializer08022F00 const g_callbacks_0836D4B8[];
extern void func_0801DB3C(void);
extern void func_0801DB78(void);
extern u32 func_08007894(const void *transition);
extern void func_08022E58(void);
extern void func_080076F4(Transition08022F00 *transition);
extern s16 func_08007A60(u8 index);
extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete [0x08022F00, 0x0802304C): 332 bytes, 146 instructions.
 * f0b54f464646c0b40006000e024d0f2804d0102816d033e0d4f30002291c4439487b0138
 * 48730006000eff2801d1faf705fe281ce4f7aefc002821d0fff78cff012079e0291c4439
 * 487b013848730006000eff2801d1faf70ffe281ce4f79afc00280dd0044a05488021c900
 * 12681ff16df9012060e00000b8d4360860380003281ce4f7b7fb2f48c46d802080002618
 * 2d4f021cd21990460620295e40201ff18bfb0022a95e48430006000ee4f758fd0004c014
 * 2021091a0904090cff2084461f251f2291462020431a218848460840021c5a4352110904
 * 480d28405843401140010243890e2940081c58434011800202433a800237318848460840
 * 021c5a4352110904480d28405843401140010243890e2940081c58434011800202434046
 * 028002229044012040428444023402366246002ac9da002018bc9846a146f0bc02bc0847
 * 90f3000260380003
 * Steps the palette fade of mode 15 or 16; returns 1 when it is done. */
u32 func_08022F00(u8 mode)
{
    Transition08022F00 *transition = &g_state_0200F390.transition;
    u16 *first;
    u16 *second;
    u16 *out_first;
    u16 *out_second;
    u16 amount;
    s32 i;

    switch (mode) {
    case 15:
        if (--g_state_0200F390.half_duration == 0xFF)
            func_0801DB3C();
        if (func_08007894(transition)) {
            func_08022E58();
            return 1;
        }
        break;
    case 16:
        if (--g_state_0200F390.half_duration == 0xFF)
            func_0801DB78();
        if (func_08007894(transition)) {
            g_callbacks_0836D4B8[0](data_03003860, sizeof(data_03003860));
            return 1;
        }
        break;
    }

    func_080076F4(transition);
    first = g_state_0200F390.buffer;
    second = first + 256;
    out_first = data_03003860;
    out_second = data_03003860 + 256;
    amount = 32 - (func_08007A60(func_081426B8(64, transition->target_second)
                                 * transition->first) >> 3);

    /* Unlike src/0804BDDC.c, the ROM counts down (i = 255 at 0x08022FBC,
     * bge at 0x08023034) and shifts without rounding (asrs #5 at
     * 0x08022FD4). */
    for (i = 255; i >= 0; --i, ++first, ++second) {
        *out_first++ = (*first & 31) * (32 - amount) >> 5
            | ((((*first >> 5) & 31) * (32 - amount) >> 5) << 5)
            | ((((*first >> 10) & 31) * (32 - amount) >> 5) << 10);
        *out_second++ = (*second & 31) * (32 - amount) >> 5
            | ((((*second >> 5) & 31) * (32 - amount) >> 5) << 5)
            | ((((*second >> 10) & 31) * (32 - amount) >> 5) << 10);
    }
    return 0;
}
