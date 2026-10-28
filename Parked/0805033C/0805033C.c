#include "ffta.h"

/* 0x0805033C..0x08050392: 86 bytes. */
struct State0805033C {
    u8 unknown_000[0x560];
    u8 mode;
    u8 unknown_561;
    u8 selection;
    u8 phase;
} __attribute__((packed));

struct Object0805033C {
    struct State0805033C *state;
};

static inline u8 move_selection(struct State0805033C *state, u16 buttons,
                                u32 limit)
{
    u8 selection = state->selection;

    if (state->mode == 0x10 && state->phase == 2)
        return selection;

    if (buttons & 0x10) {
        if (selection < limit)
            ++selection;
        else
            selection = 0;
    } else {
        if (selection != 0)
            --selection;
        else
            selection = limit;
    }
    return selection;
}

u8 func_0805033C(struct Object0805033C *object, u16 buttons)
{
    return move_selection(object->state, buttons, 5);
}
