#include "ffta.h"

typedef struct {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 first_step;
    u16 second_step;
    u16 first_delta;
    u16 second_delta;
    u16 error;
    u16 half_delta;
    u16 remaining;
    u16 unknown_16;
} Transition08022F00;

typedef struct {
    u8 unknown_00[0x0D];
    u8 countdown;
    u8 unknown_0E[0x36];
    Transition08022F00 transition;
    u16 *buffer;
} State08022F00;

extern State08022F00 g_state_0200F390;
extern u16 data_03003860[];
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern void func_0801DB3C(void);
extern void func_0801DB78(void);
extern u32 func_08007894(const void *transition);
extern void func_08022E58(void);
extern void func_080076F4(void *transition);
extern s16 func_08007A60(u8 phase);
extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete target [0x08022F00, 0x0802304C): 332 bytes, 146 instructions.
 * f0b54f464646c0b40006000e024d0f2804d0102816d033e0
 * d4f30002291c4439487b013848730006000eff2801d1faf7
 * 05fe281ce4f7aefc002821d0fff78cff012079e0291c4439
 * 487b013848730006000eff2801d1faf70ffe281ce4f79afc
 * 00280dd0044a05488021c90012681ff16df9012060e00000
 * b8d4360860380003281ce4f7b7fb2f48c46d802080002618
 * 2d4f021cd21990460620295e40201ff18bfb0022a95e4843
 * 0006000ee4f758fd0004c0142021091a0904090cff208446
 * 1f251f2291462020431a218848460840021c5a4352110904
 * 480d28405843401140010243890e2940081c584340118002
 * 02433a800237318848460840021c5a4352110904480d2840
 * 5843401140010243890e2940081c58434011800202434046
 * 028002229044012040428444023402366246002ac9da0020
 * 18bc9846a146f0bc02bc084790f3000260380003
 */
u32 func_08022F00(u8 mode)
{
    State08022F00 *state = &g_state_0200F390;
    Transition08022F00 *transition = &state->transition;
    u16 *first_source;
    u16 *second_source;
    u16 *first_destination;
    u16 *second_destination;
    u32 phase;
    u16 scale;
    s32 factor;
    s32 i;
    u16 color;
    u32 low;
    u32 middle;
    u32 high;

    switch (mode) {
    case 15:
        if (--state->countdown == 0xFF)
            func_0801DB3C();
        if (func_08007894(transition)) {
            func_08022E58();
            return 1;
        }
        break;
    case 16:
        if (--state->countdown == 0xFF)
            func_0801DB78();
        if (func_08007894(transition)) {
            g_callbacks_0836D4B8[0](data_03003860, 0x400);
            return 1;
        }
        break;
    }

    func_080076F4(transition);
    first_source = state->buffer;
    second_source = first_source + 0x100;
    first_destination = data_03003860;
    second_destination = first_destination + 0x100;
    phase = func_081426B8(64, (s16)transition->target_second);
    phase *= (s16)transition->first;
    scale = 32 - (func_08007A60(phase) >> 3);
    factor = 32 - scale;

    for (i = 255; i >= 0; i--) {
        color = *first_source++;
        low = ((color & 31) * factor) >> 5;
        middle = (((color >> 5) & 31) * factor) >> 5;
        high = (((color >> 10) & 31) * factor) >> 5;
        *first_destination++ = low | (middle << 5) | (high << 10);

        color = *second_source++;
        low = ((color & 31) * factor) >> 5;
        middle = (((color >> 5) & 31) * factor) >> 5;
        high = (((color >> 10) & 31) * factor) >> 5;
        *second_destination++ = low | (middle << 5) | (high << 10);
    }
    return 0;
}
