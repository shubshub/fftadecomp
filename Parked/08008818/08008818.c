#include "ffta.h"

typedef struct {
    u16 flags;
    u16 selector;
    u8 unknown_04[0x14];
    u32 first;
    u32 second;
    u8 unknown_20[0x1BAC];
    u32 tail;
} State;

typedef struct {
    u8 unknown_00[0xB0];
    u16 setting;
    u8 unknown_B2[0xE3E];
    u32 tail;
} Control;

typedef void (*ClearBuffer)(void *destination, u32 size);

void *func_081443FC(void *destination, const void *source, u32 size);

/* Target: 0x08008818, 104 bytes including alignment and literal pool. */
void func_08008818(State *state, u32 first, u32 second, u16 selector, u32 setting)
{
    State **active = (State **)0x02009188;
    Control *control = (Control *)0x020020D0;

    *active = state;
    (*(ClearBuffer const *)0x0836D4B8)(state, sizeof(*state));
    (*active)->first = first;
    (*active)->second = second;
    (*active)->selector = selector;
    control->setting = setting;
    func_081443FC(&(*active)->tail, &control->tail, 4);
    (*active)->flags = 0;
}
