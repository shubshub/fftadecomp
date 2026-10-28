#include "ffta.h"

/* 0x0804F0F4..0x0804F14C: 88 bytes, 36 reachable instructions. */
typedef struct {
    u8 unknown_00;
    u8 palette;
    u8 unknown_02[4];
    u16 image_count;
} MenuPanel;

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 flags;
    u8 unknown_11[3];
} CursorState;

typedef struct {
    MenuPanel *panel;
    u8 unknown_04[0x64];
    CursorState upper;
    CursorState lower;
} MenuState;

extern u16 func_08011860(void);
extern void func_08017D18(CursorState *cursor, u8 flags);
extern void func_08017E28(CursorState *cursor);
extern void func_080C9574(u16 bit_index, u16 enabled);

static inline void deactivate_cursor(CursorState *cursor)
{
    if (cursor) {
        cursor->flags &= ~0x40;
        func_08017E28(cursor);
    }
}

u32 func_0804F0F4(MenuState *state)
{
    CursorState *upper = &state->upper;
    CursorState *lower = &state->lower;

    if (func_08011860() == 0)
        return 0;

    func_08017D18(upper, state->panel->palette);
    deactivate_cursor(lower);
    if (state->panel->image_count == 0x479)
        func_080C9574(0x581, 1);
    return 1;
}
