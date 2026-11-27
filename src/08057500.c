#include "ffta.h"

/* The unit records, the menu context and its control block are laid out as
 * in func_08057454 (src/08057454.c), which reads the same unit list and
 * appearance byte; the control block is the State of func_08029C34
 * (src/08029C34.c). */
typedef struct {
    u8 unknown_00[9];
    u8 appearance;
    u8 unknown_0A[0x108 - 0xA];
} MenuUnit;

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 unknown_12[0x6A];
    void *item;
    void *context;
    u8 unknown_84[0x1000];
    u8 field_1084;
    u8 field_1085;
    u8 field_1086;
    u8 field_1087;
    u8 field_1088;
    u8 unknown_1089;
    u8 field_108A;
    u8 field_108B;
} State;

typedef struct {
    u8 unknown_0000[0x1C58];
    State control;
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
extern void func_08029C34(State *state, u8 value, u8 first, u8 second,
                          u8 fourth, u8 fifth, u8 sixth);

/* Complete [0x08057500, 0x08057578): 120 bytes, 49 instructions,
 * including the four literal words. */
void func_08057500(u8 selected)
{
    u8 palette;
    u8 value = func_08022238(&g_state_02000000.units[data_0200F428->unit_ids[selected]],
                             &palette);

    func_08029C34(&data_0200F428->control,
                  g_state_02000000.units[data_0200F428->unit_ids[selected]].appearance,
                  value, 0, palette, 1, 0);
}
