#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 reference_quantity;
} ItemRecord;

typedef struct {
    u16 position;
    u8 row;
    u8 unknown_03;
} SavedPosition;

typedef struct {
    u8 unknown_00[0xE];
    u16 count;
    u8 unknown_010[0x414];
    ItemRecord *entries[376];
    u8 unknown_A04[0x20];
    SavedPosition positions[1];
} ItemMenu;

typedef struct {
    u8 unknown_00[4];
    u16 count;
    u8 unknown_06[8];
    u16 tile_offset;
} ListLayout;

typedef struct {
    u32 callback;
    void *context;
    u8 unknown_08[8];
    u16 flags;
    u8 depth;
    u8 unknown_13[2];
    u8 row;
    u8 visible;
    u8 unknown_17;
    s16 count;
    u16 position;
    u8 unknown_1C[4];
} ItemList;

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
    u8 unknown_11[3];
} ListCursor;

typedef struct {
    u8 unknown_00[0x2C];
    ItemList list;
    ListCursor arrows;
    ListCursor cursor;
} ItemWindow;

typedef struct {
    ItemMenu *menu;
    u16 flags;
    u8 unknown_06[4];
    u8 visible;
    s8 selection;
    u8 unknown_0C[4];
    void *task;
    ListLayout layout;
    ItemWindow window;
    u8 *enabled;
    void *content;
    u8 unknown_A0[0x14];
    u8 types[1];
} MenuState;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} TaskContext;

typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferFiller)(void *destination, u32 size, u32 value);
typedef void (*CursorCallback)(void *cursor);

extern BufferInitializer g_callbacks_0836D4B8[];
extern BufferFiller data_0836D4C0[];
extern u32 func_08067F14(ItemRecord **entries, u8 type);
extern void func_08005B40(void *allocation);
extern void *func_08005B28(u32 size);
extern void func_08016210(ItemWindow *window, const void *content,
                         u16 tile_offset, u16 count);
extern void func_08068158(MenuState *state);
extern u32 func_08067504(MenuState *state, u32 index);
extern void func_08068620(MenuState *state);
extern u16 func_08017B50(ItemList *list);
extern void func_080676F8(MenuState *state, s16 row);
extern void func_08017AD8(ItemList *list);
extern void func_08067E48(MenuState *state, u8 row, u8 skip_empty);
extern void func_08015D58(ItemWindow *window, CursorCallback arrows,
                         CursorCallback cursor);
extern void func_08017E80(void *arrows);
extern void func_08017F04(void *cursor);
extern void func_08017FB0(ListCursor *cursor, u8 row);
extern TaskContext *func_08005BFC(void *task);
extern void func_08016234(ItemWindow *window);

/* Complete target [0x080682E4, 0x080684B4), 464 bytes, 197 instructions:
 * f0b557464e464546e0b484b0051c243000901421491988462f1c50372a1c70320192002302930b21695689004b480918
 * 2868411803914a4a4a4989464844bc21c9001268d9f090ff286848440b22aa56291cb43189180978fff7eafd2968c881
 * 2868c089424690802e1c98363068002801d09df7f3fb434698889df7e3fb3060394a4346998813680122d9f06fff0024
 * 28689c2149198c46842252199246029bc1898b4211da321c0023a100484440180168c8788978884202d1106800190370
 * 01342868c1898c42efdbbc7c6246116880235b001a1c4046c08912181204120c404683880098adf721ffbc74281cfff7
 * c1fe1e49381c2a1caff772fba98804200843a880039908887883281c00f016f9381caff7abfba8720024844208da2104
 * 0914281cfff776f90134aa7a9442f6db381caff75ffb039b9978281c0022fff711fda8880a4a0240aa80b87d41468988
 * 884211d2074a029212e00000240a0000b8d4360824040000c0d4360805750608efff0000057f01081021101c0843a880
 * 12490098029aadf775fc039b99780198aff79cfd28699df7bffb5146002909d0417a01200840002804d05246117cf320
 * 084010740098adf7cbfe04b038bc9846a146aa46f0bc01bc00470000817e0108
 * Rebuilds the selected item menu.
 */
void func_080682E4(MenuState *state)
{
    ItemWindow *window = &state->window;
    ListLayout *layout = &state->layout;
    ItemList *list = &window->list;
    ListCursor *arrows = &window->arrows;
    ListCursor *cursor;
    CursorCallback cursor_callback = 0;
    SavedPosition *position = &state->menu->positions[state->selection];
    s32 i;
    u8 depth;
    TaskContext *task;

    g_callbacks_0836D4B8[0](state->menu->entries, sizeof(state->menu->entries));
    state->menu->count = func_08067F14(state->menu->entries,
                                      state->types[state->selection]);
    layout->count = state->menu->count;
    if (state->enabled != 0)
        func_08005B40(state->enabled);
    state->enabled = func_08005B28(layout->count);
    data_0836D4C0[0](state->enabled, layout->count, 1);
    for (i = 0; i < state->menu->count; i++) {
        ItemRecord *item = state->menu->entries[i];

        if (item->reference_quantity == item->quantity)
            state->enabled[i] = 0;
    }
    depth = list->depth;
    func_08016210(window, state->content, layout->tile_offset + 0x100,
                  layout->count);
    list->depth = depth;
    func_08068158(state);
    func_08017AC4((Struct08017AC4 *)list, (u32)func_08067504, (u32)state);
    state->flags |= 4;
    list->position = position->position;
    func_08068620(state);
    state->visible = func_08017B50(list);
    for (i = 0; i < state->visible; i++)
        func_080676F8(state, i);
    func_08017AD8(list);
    func_08067E48(state, position->row, 0);
    state->flags &= ~0x10;
    if (list->visible < layout->count)
        cursor_callback = func_08017F04;
    else
        state->flags |= 0x10;
    func_08015D58(window, func_08017E80, cursor_callback);
    func_08017FB0(arrows, position->row);
    task = func_08005BFC(state->task);
    cursor = &window->cursor;
    /* The ROM null-tests the member address itself: sl = state + 0x84
     * (0x0806837C) is compared with zero at 0x0806847E, as src/0806890C.c
     * does for the same member at 0x08068922. */
    if (cursor != 0 && (task->flags & 1))
        cursor->flags &= ~0xC;
    func_08016234(window);
}
