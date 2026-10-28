#include "ffta.h"

/* 0x0805F708..0x0805F772: 106 bytes, 48 instructions. */
typedef struct {
    u8 unknown_00[0x20];
} ListState;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
    u8 unknown_12[2];
} CursorState;

typedef struct {
    u8 unknown_00[0x3C];
    ListState list;
    CursorState cursor;
    CursorState secondary;
} MenuState;

extern void func_08017FBC(CursorState *cursor, u8 mode);
extern void func_08017FB0(CursorState *cursor, u8 selection);
extern void func_080601D0(MenuState *state, s8 selection);
extern void func_08017884(ListState *list, u8 mode, u32 option);
extern void func_08017AF4(ListState *list, s32 selection, u32 limit);

void func_0805F708(MenuState *state, u8 mode, u8 selection, u8 alternate)
{
    CursorState *cursor = &state->cursor;
    CursorState *secondary = &state->secondary;
    ListState *list = &state->list;

    func_08017FBC(secondary, mode);
    if (!alternate) {
        func_08017FB0(cursor, selection);
    } else {
        func_080601D0(state, (s8)selection);
        func_08017884(list, mode, 1);
    }
    func_08017AF4(list, cursor->selection, 11);
}
