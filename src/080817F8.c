#include "ffta.h"

// Complete target [0x080817F8, 0x080818A0): 168 bytes, 74 instructions.

typedef struct {
    u8 unknown_00[8];
    u16 *buffer;
    u8 unknown_0C[9];
    u8 width;
    u8 rows;
    u8 unknown_17[7];
    u8 stride;
    u8 unknown_1F;
} Window080817F8;

typedef struct {
    u8 unknown_00[0x14];
} Control080817F8;

typedef struct {
    u8 unknown_00[0x3A];
    u8 active;
    u8 unknown_3B[0x3D];
    Window080817F8 window;
    Control080817F8 first;
    Control080817F8 second;
    u8 unknown_C0[0x0C];
} Slot080817F8;

typedef struct {
    u8 unknown_0000[0x2C88];
    Slot080817F8 slots[1];
} State080817F8;

extern State080817F8 *data_03002818;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08017D18(Control080817F8 *control, u8 flags);

static inline void fill16(u16 value, void *destination, u32 size)
{
    func_0814186C(&value, destination, ((size / 2) & 0x1FFFFF) | 0x01000000);
}

static inline void clear_window(Window080817F8 *window)
{
    u16 *buffer = window->buffer;
    u32 size = window->width * sizeof(u16);
    int row;

    for (row = 0; row < window->rows * 2; row++) {
        fill16(0, buffer, size);
        buffer += window->stride;
    }
}

void func_080817F8(u32 slot)
{
    State080817F8 *state;

    clear_window(&data_03002818->slots[slot].window);
    /* The ROM loads the global before the slot index for this call only. */
    state = data_03002818;
    func_08017D18(&state->slots[slot].first, 0);
    func_08017D18(&data_03002818->slots[slot].second, 0);
    data_03002818->slots[slot].active = 0;
}
