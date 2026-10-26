#include "ffta.h"

/* Complete [0x08035844, 0x080358B0): 108 bytes, 40 instructions. */
typedef struct {
    u8 enabled : 1;
    u8 unknown_01 : 7;
    u8 unknown_01_05[5];
    u8 width;
} MenuPanel08035844;

typedef struct {
    u32 unknown_00;
    MenuPanel08035844 *panel;
    u8 unknown_08[0xF36];
    u8 mode;
} MenuState08035844;

typedef struct {
    u32 unknown_00;
    void *surface;
} RenderState08035844;

extern MenuState08035844 *g_state_03002810;
extern RenderState08035844 data_03000E30;
extern const u8 data_08950258[];
extern const u8 data_089511A4[];
extern void func_0804C4D4(void *, u32, u32, u32, u8, u32, u32,
                         const u8 *, const u8 *, u16);

void func_08035844(u32 enabled)
{
    g_state_03002810->panel->enabled = enabled;
    g_state_03002810->mode = 0;
    func_0804C4D4(data_03000E30.surface, 0, 0,
                  g_state_03002810->panel->width, 240, 0, 10,
                  data_08950258, data_089511A4, 0xFFA6);
}
