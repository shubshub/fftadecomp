#include "ffta.h"

typedef struct {
    s16 top;
    s16 row;
} SavedPosition0802800C;

typedef struct {
    u8 unknown_000[2];
    u8 finished;
    u8 unknown_003[0x441];
    SavedPosition0802800C positions[1];
} MenuControl0802800C;

typedef struct {
    u8 unknown_00[4];
    void *parent;
    u8 index;
    u8 unknown_09[0x49];
    s16 top;
    u8 unknown_54[0x15];
    u8 row;
    u8 unknown_6A[0x2A];
    void *objects[4];
} WindowState0802800C;

extern MenuControl0802800C *data_0200F438;
extern void func_08005B40(void *object);

/* Complete [0x0802800C, 0x0802807C): 112 bytes, 48 instructions. */
void func_0802800C(WindowState0802800C *state)
{
    SavedPosition0802800C *position;

    if (state->objects[0] != 0)
        func_08005B40(state->objects[0]);
    if (state->objects[1] != 0)
        func_08005B40(state->objects[1]);
    if (state->objects[2] != 0)
        func_08005B40(state->objects[2]);
    if (state->objects[3] != 0)
        func_08005B40(state->objects[3]);

    position = &data_0200F438->positions[state->index];
    position->top = state->top;
    position->row = state->row;
    if (state->parent == 0)
        data_0200F438->finished = 1;
}
