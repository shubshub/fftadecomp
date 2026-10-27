#include "ffta.h"

struct Control08028CA4 {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 unknown_0C;
    u16 height;
    u8 flags;
    u8 unknown_11[3];
};

struct State08028CA4 {
    u8 unknown_00[0x58];
    struct Control08028CA4 first;
    struct Control08028CA4 second;
};

struct Shared08028CA4 {
    u8 unknown_00[4];
    u8 kind;
    u8 unknown_05;
    u8 flags;
    u8 unknown_07;
    u16 index;
    u8 selection;
    u8 unknown_0B[0x1D];
    void *data;
};

struct Global08028CA4 {
    u8 unknown_00[0x1C];
    u32 field_1C;
    u8 selection;
};

typedef void (*Callback08028CA4)(void);

extern struct Shared08028CA4 *data_0200F438;
extern struct Global08028CA4 g_state_0200F390;
extern u8 data_02003CB0[];
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_08024ABC(u32 *field, u32 value);
extern void func_08019A8C(void *data, u16 index, void *first, void *second);
extern void func_08013404(Callback08028CA4 first, Callback08028CA4 second);
extern void func_08028BBC(void);
extern void func_08028BDC(void);
extern void func_08028C34(void);
extern void func_08028C84(void);
extern void func_08028B94(void);
extern void func_08028BA8(void);
extern void func_08017D18(struct Control08028CA4 *control, u8 flags);
extern void func_080A9478(u16 value);

static inline void activate_control(struct Control08028CA4 *control)
{
    if (control != 0) {
        if (control->x <= 0xE0 && control->y <= 0x40)
            control->flags &= ~4;
        control->flags |= 0x40;
    }
}

/* Complete [0x08028CA4, 0x08028D88): 228 bytes, 80 instructions. */
void func_08028CA4(struct State08028CA4 *state)
{
    struct Control08028CA4 *first = &state->first;
    struct Control08028CA4 *second = &state->second;

    data_0200F438->selection = g_state_0200F390.selection;
    func_08024ABC(&g_state_0200F390.field_1C, 0);
    data_0200F438->data = data_02003CB0;
    func_08019A8C(data_02003CB0, data_0200F438->index,
                  data_030008B0, data_03000990);
    switch (data_0200F438->kind) {
    case 3:
        func_08013404(func_08028BBC, func_08028BDC);
        break;
    case 13:
    case 14:
    case 15:
        func_08013404(func_08028C34, func_08028C84);
        break;
    default:
        func_08013404(func_08028B94, func_08028BA8);
        break;
    }
    data_0200F438->flags = first->flags;
    if (first->y + first->height <= 0x40)
        func_08017D18(first, 0);
    else
        func_08017D18(first, 1);
    activate_control(second);
    func_080A9478(2);
}
