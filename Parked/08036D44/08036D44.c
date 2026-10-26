#include "ffta.h"

typedef struct {
    u8 active : 1;
    u8 cached : 1;
    u8 advanced : 1;
    u8 kind : 3;
    u8 unknown_06 : 2;
    u8 unknown_08 : 2;
    u8 available : 1;
    u8 mode : 2;
    u8 hidden : 1;
    u8 unknown_0E : 2;
    u8 unknown_02[0x28];
    u8 x;
    u8 unknown_2B;
    u16 y;
    u8 unknown_2E[3];
    u8 current : 4;
    u8 previous : 4;
    u8 unknown_32[2];
} SpriteSlot;

typedef struct {
    u8 unknown_00[0x0C];
    u16 scroll;
} Panel;

typedef struct {
    u32 unknown_00;
    Panel *panel;
    u8 unknown_08[0x7B0];
    SpriteSlot slots[6];
} MenuState;

typedef struct {
    u32 unknown_00;
    u8 *sprites;
} RenderState;

extern MenuState *g_state_03002810;
extern RenderState data_03000E30;
extern const u8 data_08950320[];
extern const u8 data_08951220[];
extern const u8 data_08950508[];
extern const u8 data_089512E0[];
extern const u8 data_089506F0[];
extern const u8 data_089513A0[];

void func_0804C4D4(u8 *base, u16 index, u16 selector,
                   u8 x, u8 y, u8 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes);
void func_0804C524(u8 *base, u16 index, u32 selector,
                   u8 x, u8 y, u32 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes,
                   u8 extra);

/* Complete target: [0x08036D44, 0x0803701C), 728 bytes. */
void func_08036D44(void)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        u32 y;
        u32 delay;
        u8 extra;

        if (g_state_03002810->slots[i].active &&
            !g_state_03002810->slots[i].hidden) {
            y = g_state_03002810->slots[i].y -
                g_state_03002810->panel->scroll + 11;
            if (y > 190)
                y = 240;
        } else {
            y = 240;
        }

        if (g_state_03002810->slots[i].cached &&
            g_state_03002810->slots[i].previous ==
            g_state_03002810->slots[i].current) {
            func_0804C788(data_03000E30.sprites, (u16)(i + 13),
                           g_state_03002810->slots[i].x + 8, y);
            continue;
        }

        g_state_03002810->slots[i].cached = 1;
        if (!g_state_03002810->slots[i].advanced) {
            if (g_state_03002810->slots[i].available)
                delay = 0;
            else
                delay = 2;
            func_0804C4D4(data_03000E30.sprites, (u16)(i + 13),
                           g_state_03002810->slots[i].current,
                           g_state_03002810->slots[i].x + 8, y,
                           1, delay, data_08950320, data_08951220, 0x1A6);
        } else {
            s32 kind;

            extra = 0;
            if (!g_state_03002810->slots[i].available) {
                delay = 2;
            } else if (g_state_03002810->slots[i].mode == 0) {
                delay = 1;
            } else if (g_state_03002810->slots[i].mode == 1) {
                delay = 1;
                y = 240;
            } else {
                delay = 1;
                extra = 11;
            }

            kind = g_state_03002810->slots[i].kind;
            switch (kind) {
            case 0:
                break;
            case 1:
                func_0804C524(data_03000E30.sprites, (u16)(i + 13),
                               g_state_03002810->slots[i].current,
                               g_state_03002810->slots[i].x + 8, y,
                               1, delay, data_08950508, data_089512E0,
                               0x200, extra);
                break;
            case 2:
                func_0804C524(data_03000E30.sprites, (u16)(i + 13),
                               g_state_03002810->slots[i].current,
                               g_state_03002810->slots[i].x + 8, y,
                               1, delay, data_089506F0, data_089513A0,
                               0x200, extra);
                break;
            case 3:
                func_0804C524(data_03000E30.sprites, (u16)(i + 13),
                               g_state_03002810->slots[i].current,
                               g_state_03002810->slots[i].x + 8, y,
                               1, delay, data_08950508, data_089512E0,
                               0x200, extra);
                break;
            }
        }

        g_state_03002810->slots[i].previous =
            g_state_03002810->slots[i].current;
    }
}
