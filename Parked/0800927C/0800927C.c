#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
} Unit08017BE8;

typedef struct {
    u8 unknown_00[0x16];
    u8 value_16;
    s16 value_18;
} Struct08017B50;

typedef struct {
    u8 unknown_00[0x16];
    u8 field_16;
    u8 unknown_17;
    s16 field_18;
    s16 field_1A;
} Rec08017A90;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[3];
    u8 field_15;
} Struct08017AF4;

typedef struct {
    u8 unknown_00[0x11];
    s8 position;
} ScrollState;

void func_080023D0(void *state);
u16 func_08017B68(ClampState08017B68 *state, u32 index);
s16 func_08017BE8(Unit08017BE8 *state);
u16 func_08017B50(Struct08017B50 *state);
u8 func_08017A90(Rec08017A90 *state, u16 direction);
void func_08017AF4(Struct08017AF4 *state, u8 position, u8 mode);
void func_08141540(u16 sound);
void func_08009394(u8 direction, u8 position, u8 scroll);

/* Target: 0x0800927C, 278 bytes including three internal literal words. */
u8 func_0800927C(u16 keys)
{
    u8 **active = (u8 **)0x02009188;
    void *list = *active + 0x2F0;
    ScrollState *scroll = (ScrollState *)(*active + 0x310);
    s8 position;
    s8 next;

    if (keys & 0x80) {
        func_080023D0((void *)0x03000000);
        position = scroll->position;
        if (func_08017B68(list, position) < func_08017BE8(list))
            func_08017AF4(list, position, 255);
        next = position + 1;
        if (next < func_08017B50(list)) {
            if ((*active)[0x21] > 1)
                func_08141540(109);
            func_08009394(0x80, next, 0);
            return 8;
        }
        if (func_08017A90(list, 0x80)) {
            func_08141540(109);
            func_08009394(0x80, next, 1);
            return 1;
        }
    } else if (keys & 0x40) {
        func_080023D0((void *)0x03000000);
        position = scroll->position;
        if (func_08017B68(list, position))
            func_08017AF4(list, position, 255);
        next = position - 1;
        if (next >= 0) {
            if ((*active)[0x21] > 1)
                func_08141540(109);
            func_08009394(0x40, next, 0);
            return 8;
        }
        if (func_08017A90(list, 0x40)) {
            func_08141540(109);
            func_08009394(0x40, next, 1);
            return 1;
        }
    }
    return 0;
}
