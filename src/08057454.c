#include "ffta.h"

typedef struct {
    u8 unknown_00[9];
    u8 appearance;
    u8 unknown_0A[0x108 - 0xA];
} MenuUnit;

typedef struct {
    u8 unknown_00[0x1084];
    u8 value_1084;
    u8 value_1085;
    u8 value_1086;
    u8 value_1087;
    u8 value_1088;
    u8 value_1089;
    u8 value_108a;
    u8 value_108b;
} State08029864;

typedef struct {
    u8 unknown_0000[0x1C58];
    State08029864 control;
    u8 unknown_2CE4[0x2D3A - 0x2CE4];
    u8 unit_ids[24];
} MenuContext;

extern MenuContext *data_0200F428;
typedef struct {
    u8 unknown_00[0x80];
    MenuUnit units[24];
} GameState;
extern GameState g_state_02000000;
extern u16 func_08022238(void *unit, u8 *output);
extern void func_08029864(State08029864 *state, u8 a, u8 b, u8 c,
                          u8 d, u8 e, u8 f, u8 g, u8 h, u8 i);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);

/* 0x08057454..0x08057500, 172 bytes including four literal words. */
void func_08057454(u8 selected, u8 x, u8 y)
{
    u8 palette;
    u8 value = func_08022238(&g_state_02000000.units[data_0200F428->unit_ids[selected]],
                             &palette);

    func_08029864(&data_0200F428->control, x, y, 7,
                  g_state_02000000.units[data_0200F428->unit_ids[selected]].appearance,
                  value, 0, palette, 1, 0);
    func_0802A370(x, y, 10, 10);
}
