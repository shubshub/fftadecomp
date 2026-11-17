// Complete [0x080A10D4, 0x080A11DC): 264 bytes.
// f0b557464e464546e0b481b0071c884691461d1c099c2d042d0c2406240e364936480268
// 381ca1f0a7f8354978180e9a0260ef235b00f8186946898d0180ed225200b8186b461b8e
// 03802406e414f0214900781804800832b8186b461b8d0380e62464003a194046106010397b
// 184c462068616818605960ec21490078180580204c38190d990160116808240a5f90460a22
// 885e81460c200c5ea24600229e5ee9235b00f8180022845e00940233f8180024055f803108
// 68f8f750fd041c0f480268381c4c21a1f057f8414639804a467a805346bb80fe806846008838
// 817d81fc60381cfff71aff01b038bc9846a146aa46f0bc01bc0047380a0000b8d43608ec0900
// 00e8090000
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Position080A10D4;

typedef struct {
    u8 unknown_00[8];
    void *field_08;
} Object08099C30;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x80 - 0x0E];
    const Object08099C30 *object;
} Source080A10D4;

typedef struct {
    s16 from[3];
    s16 to[3];
    void *owner;
    u8 unknown_10[0x4C - 0x10];
    u8 unknown_4C[0x1CC - 0x4C];
    Source080A10D4 *source;
    Position080A10D4 target;
    u16 unknown_1D8;
    u16 unknown_1DA;
    u8 unknown_1DC[2];
    u16 unknown_1DE;
    s16 unknown_1E0;
    u16 unknown_1E2;
    u8 unknown_1E4[0x9E8 - 0x1E4];
    u32 unknown_9E8;
    u32 unknown_9EC;
    u8 unknown_9F0[0xA38 - 0x9F0];
} State080A10D4;

extern BufferInitializer g_callbacks_0836D4B8[];
extern void *func_08099C30(const Object08099C30 *object);
extern void func_080A0FF0(State080A10D4 *state);

void func_080A10D4(State080A10D4 *state, Source080A10D4 *source,
                   const Position080A10D4 *target, u16 arg3, u8 arg4,
                   s32 arg5, s32 arg6, s32 arg7, u32 arg8, u32 arg9)
{
    s32 from_x;
    s32 from_y;
    s32 from_z;
    s32 to_x;
    s32 to_y;
    s32 to_z;
    void *owner;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->unknown_9EC = arg9;
    state->unknown_1DE = arg6;
    state->unknown_1DA = arg7;
    state->unknown_1E0 = (s8)arg4 << 5;
    state->unknown_1E2 = arg5;
    state->source = source;
    state->target = *target;
    state->unknown_1D8 = arg3;
    state->unknown_9E8 = arg8;

    from_x = state->source->x;
    from_y = state->source->y;
    from_z = state->source->z;
    to_x = state->target.x;
    to_y = state->target.y;
    to_z = state->target.z;
    owner = func_08099C30(state->source->object);

    g_callbacks_0836D4B8[0](state, 0x4C);
    state->from[0] = from_x;
    state->from[1] = from_y;
    state->from[2] = from_z;
    state->to[0] = to_x;
    state->to[1] = to_y;
    state->to[2] = to_z;
    state->owner = owner;
    func_080A0FF0(state);
}
