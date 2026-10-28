#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    s16 top;
    u8 unknown_1C[4];
} NavigationUnit;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[0x2A];
} NavigationCursor;

typedef struct {
    u8 unknown_00[8];
    u8 index;
    s8 kind;
    u8 unknown_0A[0x2E];
    NavigationUnit unit;
    NavigationCursor cursor;
    u32 *entries;
} NavigationState;

typedef struct {
    s16 top;
    s16 row;
} NavigationPosition;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[0x13];
    u32 selected;
    u8 unknown_1C[0x428];
    NavigationPosition positions[1];
} NavigationControl;

extern NavigationControl *data_0200F438;
extern s16 func_08017BE8(NavigationUnit *unit);
extern u16 func_08017B68(NavigationUnit *unit, u32 row);
extern void func_08141540(u32 sound);
extern void func_08025DC8(NavigationState *state, u32 update);

/* Complete target: 0x080284A0..0x08028584, 228 bytes. */
void func_080284A0(NavigationState *state, u8 direction)
{
    NavigationUnit *unit = &state->unit;
    NavigationCursor *cursor = &state->cursor;
    NavigationPosition *position = &data_0200F438->positions[state->index];
    s32 original = unit->top;
    s32 top = original;
    s32 count = func_08017BE8(unit) + 1;
    s32 row = cursor->row;
    s32 remaining = state->kind;

    while (remaining != 0)
    {
        remaining--;
        if (direction == 0x80)
        {
            if (top + state->kind < count)
                top++;
            else
            {
                remaining = 0;
                if (original == count - state->kind)
                    row = state->kind - 1;
            }
        }
        else
        {
            if (top > 0)
                top--;
            else
            {
                remaining = 0;
                if (original == 0)
                    row = 0;
            }
        }
    }

    if (original != top || cursor->row != row)
    {
        position->top = top;
        position->row = row;
        func_08141540(0x6D);
        func_08025DC8(state, 0);
        if (data_0200F438->mode == 2)
            data_0200F438->selected = state->entries[func_08017B68(unit, (s8)row)];
    }
}
