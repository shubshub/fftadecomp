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
    u16 count;
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
extern u16 func_08067F14(ItemRecord **entries, u8 type);
extern void func_08005B40(void *allocation);
extern void *func_08005B28(u32 size);
extern void func_08016210(ItemWindow *window, const void *content,
                         u16 tile_offset, u16 count);
extern void func_08068158(MenuState *state);
extern u32 func_08067504(MenuState *state, u32 index);
extern void func_08068620(MenuState *state);
extern u8 func_08017B50(ItemList *list);
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

/* 0x080682E4..0x080684B4: 464 bytes; rebuild the selected item menu. */
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
    cursor = &window->cursor;
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
        func_080676F8(state, (s16)i);
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
    if (cursor != 0 && (task->flags & 1))
        cursor->flags &= ~0xC;
    func_08016234(window);
}
