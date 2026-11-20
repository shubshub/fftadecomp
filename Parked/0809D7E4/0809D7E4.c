#include "ffta.h"

typedef struct {
    u16 camera_x;
    u16 camera_y;
    u8 unknown_04[0x1c];
    void *actor;
    u32 value;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_2C[4];
} CameraState0809D7E4;

typedef void (*BufferInitializer0809D7E4)(void *destination, u32 size);

extern BufferInitializer0809D7E4 const g_callbacks_0836D4B8[];
extern void func_0801E6F0(u16 *x, u16 *y);

/* Complete [0x0809D7E4, 0x0809D844), 96 bytes including the two literals. */
void func_0809D7E4(void *actor, u32 value, s16 offset_x, s16 offset_y)
{
    BufferInitializer0809D7E4 const *callbacks = g_callbacks_0836D4B8;
    CameraState0809D7E4 *state = (CameraState0809D7E4 *)0x0200F740;
    u16 x;
    u16 y;

    callbacks[0](state, sizeof(*state));
    state->actor = actor;
    state->value = value;
    state->offset_x = offset_x;
    state->offset_y = offset_y;
    func_0801E6F0(&x, &y);
    state->camera_x = x;
    state->camera_y = y;
}
