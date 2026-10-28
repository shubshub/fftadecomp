#include "ffta.h"

/* 0x0814863C..0x08148684: 72 bytes. */
typedef struct {
    u16 reset;
    u16 remaining;
    u32 value;
    u16 limit;
    u16 unknown_0a;
    u16 progress;
} Control4;

typedef struct {
    u8 unknown_00[6];
    u16 limit;
    u16 unknown_08;
    u16 reset;
    u16 remaining;
    u16 unknown_0e;
    u32 value;
    u16 progress;
} Control8;

typedef struct {
    u16 active;
    u16 unknown_02;
    u16 mode;
    u8 unknown_06[6];
    union {
        Control4 mode4;
        Control8 mode8;
    } control;
} ControlHeader;

static inline u16 control_mode(ControlHeader *header)
{
    if (header->active == 0)
        return 0x8000;
    return header->mode;
}

void func_0814863C(ControlHeader *header, u32 value)
{
    switch (control_mode(header)) {
    case 4:
    {
        Control4 *state = &header->control.mode4;
        state->progress = 0;
        state->reset = 0;
        state->remaining = state->limit;
        state->value = value;
        break;
    }
    case 8:
    {
        Control8 *state = &header->control.mode8;
        state->progress = 0;
        state->reset = 0;
        state->remaining = state->limit;
        state->value = value;
        break;
    }
    }
}
