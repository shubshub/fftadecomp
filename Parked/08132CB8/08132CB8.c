#include "ffta.h"

// 0x08132CB8..0x08132D84: 204 bytes.
typedef struct {
    u8 unknown_00[8];
    void *unit;
    u8 unknown_0C[0x0C];
    u16 selected_entry;
} PickState;

extern s32 func_080C7EA4(void *unit, u8 field);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern s16 func_08002804(void);
extern void func_080CAF78(void *unit, int, u8);
extern void func_080CB54C(void *unit, int);
extern u8 func_08131BB8(void *unit);
extern void func_080CA9E8(u16, int);
extern void func_080CA900(u16, int);
extern void func_080CA2E8(void *unit);

int func_08132CB8(PickState *state, u16 wanted)
{
    u8 found[8];
    int count = 0;
    int i;
    s32 pick;
    u16 entry;

    for (i = 0; i < 5; i++) {
        pick = func_080C7EA4(state->unit, 0x1D + i);
        if (pick && func_080CA7A4(pick, 3) == wanted)
            found[count++] = i;
    }
    if (count == 0)
        return 0;
    pick = found[func_08002804() % count];
    entry = func_080C7EA4(state->unit, 0x1D + pick);
    state->selected_entry = entry;
    func_080CAF78(state->unit, 0, pick);
    func_080CB54C(state->unit, 1);
    if (func_08131BB8(state->unit))
        func_080CA9E8(entry, 1);
    if (func_08131BB8(*(void **)state))
        func_080CA900(entry, 1);
    func_080CA2E8(state->unit);
    return 1;
}
