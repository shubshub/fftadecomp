#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2a[0xde];
} Unit080B8100;

typedef struct {
    const void *resource;
    u8 unknown_04[8];
    s16 x;
    s16 y;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u16 field_16;
    u8 unknown_18[8];
} Display080B8100;

typedef struct {
    u16 current;
    u16 depth;
    u16 states[34];
} StateStack080B8100;

typedef struct {
    void *parent;
    u8 unknown_04[8];
    Unit080B8100 *units[24];
    u8 unknown_06c[0x110];
    Display080B8100 display[7];
    u8 unknown_25c[4];
    s8 count;
    u8 unknown_261[3];
    StateStack080B8100 stack;
} Menu080B8100;

typedef struct {
    u8 unknown_00[0x14];
    u8 selection;
} Selection080B8100;

typedef void (*BufferInitializer080B8100)(void *destination, u32 size);
extern BufferInitializer080B8100 const g_callbacks_0836D4B8[];
extern Selection080B8100 g_state_020020D0;
extern Unit080B8100 g_state_02000080[];
extern const u8 data_08391670[];
extern const u8 data_0839167E[];
extern const u8 data_08391644[];
extern const u8 data_0839163C[];
extern const u8 data_0839164C[];
extern const u8 data_08391660[];
extern const u8 data_08391668[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern s32 func_080C7EA4(const Unit080B8100 *unit, u32 selector);
extern void func_08071DC8(u8 selection, u8 *order);
extern void func_0802B960(void);

static inline void PushState(StateStack080B8100 *stack, u16 state)
{
    stack->current = state;
    stack->states[stack->depth++] = state;
}

/* Complete [0x080B8100, 0x080B8414): 788 bytes, 363 reachable instructions. */
Menu080B8100 *func_080B8100(void *parent, Unit080B8100 *unit, s32 count)
{
    Menu080B8100 *menu = func_08022840(sizeof(*menu));
    s32 accepted;
    u8 *order;
    s32 prefix;
    s32 i;
    s32 j;

    g_callbacks_0836D4B8[0](menu, sizeof(*menu));
    menu->parent = parent;
    accepted = 0;
    for (i = 0; i < count; i++, unit++) {
        if (!func_080C7EA4(unit, 1))
            continue;
        if (unit->flags & 4)
            continue;
        if (unit->flags & 0x18)
            continue;
        menu->units[accepted++] = unit;
    }
    menu->count = accepted;
    order = func_08022840(24);
    func_08071DC8(g_state_020020D0.selection, order);
    prefix = 0;
    for (i = 0; i < 24 && order[i] != 0xff; i++) {
        for (j = prefix; j < menu->count; j++) {
            Unit080B8100 *preferred = &g_state_02000080[order[i]];

            if (preferred == menu->units[j]) {
                menu->units[j] = menu->units[prefix];
                menu->units[prefix] = preferred;
                prefix++;
                break;
            }
        }
    }
    func_08022854(order);

    menu->display[0].resource = data_08391670;
    menu->display[0].x = 192;
    menu->display[0].y = 128;
    menu->display[0].field_14 = 2;
    menu->display[0].field_16 = 0;
    menu->display[0].field_10 = 4;
    menu->display[0].field_12 = 0;

    menu->display[1].resource = data_0839167E;
    menu->display[1].x = 192;
    menu->display[1].y = 128;
    menu->display[1].field_14 = 2;
    menu->display[1].field_16 = 0;
    menu->display[1].field_10 = 4;
    menu->display[1].field_12 = 0;

    menu->display[2].resource = data_08391644;
    menu->display[2].x = 32;
    menu->display[2].y = 16;
    menu->display[2].field_14 = 2;
    menu->display[2].field_16 = 0;
    menu->display[2].field_10 = 4;
    menu->display[2].field_12 = 0;

    menu->display[3].resource = data_0839163C;
    menu->display[3].x = 208;
    menu->display[3].y = 16;
    menu->display[3].field_14 = 2;
    menu->display[3].field_16 = 0;
    menu->display[3].field_10 = 4;
    menu->display[3].field_12 = 0;

    menu->display[4].resource = data_0839164C;
    menu->display[4].x = 80;
    menu->display[4].y = 20;
    menu->display[4].field_14 = 0;
    menu->display[4].field_16 = 2;
    menu->display[4].field_10 = 0;
    menu->display[4].field_12 = 4;

    menu->display[5].resource = data_08391660;
    menu->display[5].x = 16;
    menu->display[5].y = 88;
    menu->display[5].field_14 = 2;
    menu->display[5].field_16 = 0;
    menu->display[5].field_10 = 4;
    menu->display[5].field_12 = 0;

    menu->display[6].resource = data_08391668;
    menu->display[6].x = 224;
    menu->display[6].y = 88;
    menu->display[6].field_14 = 2;
    menu->display[6].field_16 = 0;
    menu->display[6].field_10 = 4;
    menu->display[6].field_12 = 0;

    PushState(&menu->stack, 9);
    PushState(&menu->stack, 5);
    PushState(&menu->stack, 4);
    PushState(&menu->stack, 1);
    menu->stack.current = 0;
    func_0802B960();
    return menu;
}
