#include "ffta.h"

typedef struct {
    u8 enabled : 1;
    u8 unknown_00 : 7;
    u8 unknown_01[5];
    u8 width;
} MenuPanel080358B0;

typedef struct {
    u32 unknown_00;
    MenuPanel080358B0 *panel;
    u8 unknown_08[0xF36];
    u8 mode;
} MenuState080358B0;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} RenderState080358B0;

extern MenuState080358B0 *g_state_03002810;
extern RenderState080358B0 data_03000E30;
extern const u8 data_08950258[];
extern const u8 data_089511A4[];
extern void func_0804C598(Entry *base, u16 index, u16 selector,
                         u8 width, u8 count, u8 mode, u8 delay,
                         const u8 *graphics, const u8 *layout, u16 attributes);

/* Target [0x080358B0, 0x0803591C), 108 complete bytes:
 * 10b586b0134b19684c680121084022780221494211400143217018680e494018
 * 0022062101700d484068196849688b79f0210091012101910292094903910949
 * 049109490591002116f04efe06b010bc01bc0047102800033e0f0000300e0003
 * 58029508a4119508a6ff0000
 */
void func_080358B0(u32 enabled)
{
    g_state_03002810->panel->enabled = enabled;
    g_state_03002810->mode = 6;
    func_0804C598(data_03000E30.surface, 0, 0,
                  g_state_03002810->panel->width, 240, 1, 0,
                  data_08950258, data_089511A4, 0xFFA6);
}
