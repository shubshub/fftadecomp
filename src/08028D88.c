#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 unknown_0C;
    u16 height;
    u8 flags;
    u8 unknown_11[3];
} NavigationControl;

typedef struct {
    u8 unknown_00[0x58];
    NavigationControl first;
    NavigationControl second;
} NavigationState;

typedef struct {
    u8 unknown_00[6];
    u8 flags;
    u8 unknown_07[3];
    u8 selection;
} SharedNavigation;

extern u32 data_0200F3AC;
extern SharedNavigation *data_0200F438;
extern u16 func_08011860(NavigationState *state);
extern void func_08024ABC(u32 *field, u32 value);
extern void func_08017D18(NavigationControl *control, u8 flags);
extern void func_08017E28(NavigationControl *control);
extern void func_080A9478(u16 value);

static inline void deactivate_control(NavigationControl *control)
{
    if (control != 0) {
        control->flags &= ~0x40;
        func_08017E28(control);
    }
}

/* Complete target: 0x08028D88..0x08028DE0, 88 bytes. */
u32 func_08028D88(NavigationState *state)
{
    NavigationControl *first = &state->first;
    NavigationControl *second = &state->second;

    if (func_08011860(state) == 0)
        return 0;

    func_08024ABC(&data_0200F3AC, data_0200F438->selection);
    func_08017D18(first, data_0200F438->flags);
    deactivate_control(second);
    func_080A9478(0);
    return 1;
}
