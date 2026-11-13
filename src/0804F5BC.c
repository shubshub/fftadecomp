#include "ffta.h"

// Complete [0x0804F5BC, 0x0804F744): 392 bytes.

typedef struct {
    u8 unknown_000[4];
    u16 count;
    u8 unknown_006[0x29E];
    u8 blocks[0x180];
    u8 entries[0x100];
} Table0804F5BC;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 flags;
    u8 appearance;
    u8 unknown_09[5];
    u16 blocks;
} Layout0804F5BC;

typedef struct {
    u8 unknown_00[8];
    void *destination;
    u16 *row;
    u8 unknown_10[3];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_17[5];
    u16 tile;
    u8 stride;
} Menu0804F5BC;

typedef struct {
    u8 unknown_00[0x10];
    u8 unknown_10[4];
    u8 *tiles;
} Graphics0804F5BC;

typedef struct State0804F5BC {
    Table0804F5BC *table;
    u8 unknown_04[5];
    u8 handle;
    u8 unknown_0A[2];
    Layout0804F5BC layout;
    u8 window[0x2C];
    Menu0804F5BC menu;
    u8 unknown_68[0x28];
    s8 *enabled;
    u16 *row;
} State0804F5BC;

extern void (*const data_0836D4BC)(void *, const void *, u32);
extern void (*const data_0836D4C0)(void *, u32, u32);
extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern const Layout0804F5BC data_08393798;
extern u16 g_table_08529EE4[];
extern Graphics0804F5BC data_030008B0;
extern void *func_08005B28(u32);
extern u16 func_080CED2C(void);
extern u8 func_080C9540(u16);
extern u16 func_08013B50(Layout0804F5BC *);
extern u16 func_080161A0(u8, u8, u8);
extern void func_08017490(void *, u8, u8, u8, u8, u16, u16, u16, u8);
extern void func_08013B7C(const Layout0804F5BC *, void *, const void *);
extern void func_08016C90(void *, u8);
extern u8 func_0804F938(State0804F5BC *);
extern u8 func_080098F4(u8 (*)(State0804F5BC *), State0804F5BC *);

void func_0804F5BC(State0804F5BC *state)
{
    Menu0804F5BC *menu;
    Layout0804F5BC *layout;
    void *window;
    s32 i;
    u32 size;
    u8 width;

    layout = &state->layout;
    menu = &state->menu;
    window = state->window;

    data_0836D4BC(layout, &data_08393798, sizeof(*layout));
    g_callbacks_0836D4B8[0](state->table->entries, 0x100);
    state->table->count = func_080CED2C();
    state->enabled = func_08005B28(state->table->count);
    data_0836D4C0(state->enabled, state->table->count, 1);

    for (i = 0; i < state->table->count; i++) {
        if (g_table_08529EE4[i] == 0x1A && func_080C9540(0x36))
            continue;
        if (!func_080C9540(g_table_08529EE4[i] + 0x2FF))
            state->enabled[i] = 0;
    }

    func_08013B50(layout);
    menu->x = layout->x;
    menu->y = layout->y + 2;
    width = layout->width;
    menu->width = width;
    menu->height = layout->height - 3;
    menu->tile = 0x140 + layout->blocks;
    menu->stride = width;
    size = menu->width * menu->height * 2;
    state->row = func_08005B28(size);
    g_callbacks_0836D4B8[0](state->row, size);
    menu->row = state->row;
    menu->destination = data_030008B0.tiles
                        + func_080161A0(menu->x, menu->y, 0x20) * 2;

    func_08017490(window, layout->x, layout->y, layout->width, layout->height,
                  layout->flags, 5, 1, 12);
    func_08013B7C(layout, window, state->table->blocks);
    func_08016C90(window, layout->appearance);
    state->handle = func_080098F4(func_0804F938, state);
}
