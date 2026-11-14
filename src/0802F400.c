#include "control_flags.h"

// Complete [0x0802F400, 0x0802F4F4): 244 bytes including twelve literal words.

typedef void (*StateCallback)(void *, u32);

typedef struct {
    u8 unknown_00[0x3C32];
    u8 mode;
} State0802F400;

typedef struct {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 value;
    u8 extra;
    s16 timer;
} DrawState;

typedef struct {
    u16 x;
    u16 y;
    u8 unknown_04;
    u8 unknown_05;
    u8 first_value;
    u8 count;
    u8 mode;
    u8 unknown_09[0xF - 0x9];
    u8 selected;
    u8 unknown_10[0x2A0 - 0x10];
    void *allocation;
    u8 unknown_2a4[0x46C - 0x2A4];
    const u8 *first_sprite;
    const u8 *second_sprite;
    u8 unknown_474[4];
    const u8 *third_sprite;
    u8 unknown_47c[0x1248 - 0x47C];
    DrawState draw;
} Panel0802F400;

extern Panel0802F400 *data_0200F444;
extern StateCallback g_callbacks_0836D4B8[];
extern State0802F400 g_state_02000000;
extern u8 g_state_0200F390[];
extern const u8 data_0839173C[];
extern const u8 data_08391756[];
extern const u8 data_0839176A[];
extern void func_080CC2B4(void);
extern void *func_08022840(u32 size);
extern u8 func_080CCA80(void);
extern u8 func_0802D764(void);
extern void func_0802F27C(u8 alternate);
extern void func_08017FA8(DrawState *animation, const u8 *graphics, s16 x, s16 y);
extern void func_080255FC(u8 value);
extern void func_08141540(u32 sound);

void func_0802F400(u32 size)
{
    Panel0802F400 *panel;
    s16 x;
    s16 y;

    g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
    func_080CC2B4();
    panel = func_08022840(size);
    data_0200F444 = panel;
    g_callbacks_0836D4B8[0](panel, sizeof(Panel0802F400));
    data_0200F444->mode = g_state_02000000.mode;
    data_0200F444->x = 1;
    data_0200F444->y = 9;
    data_0200F444->allocation = panel;
    data_0200F444->first_value = func_080CCA80();
    data_0200F444->count = func_0802D764();
    data_0200F444->selected = 0;
    data_0200F444->first_sprite = data_0839173C;
    data_0200F444->second_sprite = data_08391756;
    data_0200F444->third_sprite = data_0839176A;
    func_0802F27C(0);
    x = (data_0200F444->x - 1) * 8 + 2;
    y = (data_0200F444->y + 2) * 8;
    func_08017FA8(&data_0200F444->draw, data_0839176A, x, y);
    func_080255FC(g_state_0200F390[3]);
    func_08141540(0x65);
    data_0200F444->unknown_04 = 0;
}
