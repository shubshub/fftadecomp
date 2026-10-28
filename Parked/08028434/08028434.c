#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} NavigationUnit;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
} NavigationCursor;

typedef struct {
    u8 unknown_00;
} NavigationMotion;

typedef struct {
    u8 unknown_00[0x38];
    NavigationUnit unit;
    NavigationCursor cursor;
    NavigationMotion motion;
} NavigationState;

extern void func_08017FBC(NavigationMotion *motion, u32 direction);
extern void func_08017FB0(NavigationCursor *cursor, u8 row);
extern void func_08025B54(NavigationState *state, s8 row);
extern void func_08017884(NavigationUnit *unit, u32 direction, u32 enabled);
extern void func_08017AF4(NavigationUnit *unit, s32 row, u32 value);

/* Complete target: 0x08028434..0x0802849E, 106 bytes. */
void func_08028434(void *object, u8 direction, u8 row, u8 wrap)
{
    NavigationState *state = object;
    NavigationCursor *cursor = &state->cursor;
    NavigationMotion *motion = &state->motion;
    NavigationUnit *unit = &state->unit;

    func_08017FBC(motion, direction);
    if (wrap == 0) {
        func_08017FB0(cursor, row);
    } else {
        func_08025B54(state, (s8)row);
        func_08017884(unit, direction, 1);
    }
    func_08017AF4(unit, cursor->row, 0x0B);
}
