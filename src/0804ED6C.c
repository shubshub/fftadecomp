#include "ffta.h"

// Complete [0x0804ED6C, 0x0804EF68): 508 bytes.

typedef struct {
    u8 unknown_000[3];
    u8 total;
    u16 count;
    u8 unknown_006[0x29E];
    u8 blocks[0x180];
    u8 entries[0x100];
    u32 flags;
} Table0804ED6C;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09[7];
} Layout0804ED6C;

typedef struct State0804ED6C {
    Table0804ED6C *table;
    u16 flags;
    u8 unknown_06[2];
    u8 kind;
    u8 handle;
    u8 unknown_0A[2];
    Layout0804ED6C layout;
    u8 window[0x2C];
    u8 unknown_48[0x48];
    u8 *enabled;
    u16 *row;
} State0804ED6C;

extern void (*const data_0836D4BC)(void *, const void *, u32);
extern void (*const data_0836D4C0)(void *, u32, u32);
extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern const Layout0804ED6C data_08393718[];
extern const u8 data_083937A8[8];
extern void *func_08005B28(u32);
extern u32 func_08050C38(u32 *output);
extern u32 func_080D0AB0(void *entries, u32 size);
extern s32 func_08050C74(void *entries);
extern u32 func_08050CA4(void *entries);
extern u32 func_08050CE8(struct State0804ED6C *state, void *entries);
extern u32 func_080504BC(struct State0804ED6C *state);
/* u16 at its definition, but this caller does not re-narrow the result
   (no lsls/lsrs #16 before func_08005B28), so its view is a full word. */
extern u32 func_08013B50(Layout0804ED6C *);
extern void func_08017490(void *, u8, u8, u8, u8, u16, u16, u16, u8);
extern void func_08013B7C(const Layout0804ED6C *, void *, const void *);
extern void func_08016C90(void *, u8);
extern u8 func_0804F938(struct State0804ED6C *);
extern u8 func_080098F4(u8 (*)(struct State0804ED6C *), struct State0804ED6C *);

void func_0804ED6C(State0804ED6C *state)
{
    Layout0804ED6C *layout;
    void *window;

    layout = &state->layout;
    data_0836D4BC(layout, &data_08393718[state->kind], sizeof(*layout));
    state->enabled = func_08005B28(layout->count);
    data_0836D4C0(state->enabled, layout->count, 1);
    g_callbacks_0836D4B8[0](state->table->entries, 0x100);
    state->table->count = 0;

    switch (state->kind) {
    case 1:
        state->table->total = func_08050C38(&state->table->flags);
        layout->count = state->table->total;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 5)
            layout->y++;
        break;
    case 3:
        state->table->count = func_080D0AB0(state->table->entries, 16);
        layout->count = state->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_083937A8[layout->count];
        break;
    case 4:
        state->table->count = func_08050C74(state->table->entries);
        layout->count = state->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_083937A8[layout->count];
        break;
    case 5:
        state->table->count = func_08050CA4(state->table->entries);
        layout->count = state->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_083937A8[layout->count];
        break;
    case 6:
        state->table->count = func_08050CE8(state, state->table->entries);
        layout->count = state->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 7)
            layout->y = data_083937A8[layout->count];
        break;
    case 7:
        state->flags |= 8;
        break;
    }

    func_080504BC(state);
    window = state->window;
    state->row = func_08005B28(func_08013B50(layout));
    func_08017490(window, layout->x, layout->y, layout->width, layout->height,
                  layout->flags, 5, 1, 12);
    func_08013B7C(layout, window, state->table->blocks);
    func_08016C90(window, layout->appearance);
    state->handle = func_080098F4(func_0804F938, state);
}
