/* 0x0813E348..0x0813E750: 1032 bytes. */
#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    s32 fixed_x;
    s32 fixed_y;
    const void *source;
    u16 field_14;
    u16 field_16;
    u8 field_18;
    u8 unknown_19;
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
    u8 visible;
    u8 transform;
    u8 unknown_22[2];
} Entry0813E348;

typedef struct {
    u32 tick;
    s16 x;
    s16 y;
    u16 first;
    u16 second;
    u16 duration;
    u8 flag;
    u8 value;
} Spawn0813E348;

typedef struct {
    s8 anchor;
    u8 unknown_01;
    u16 divisor;
    u8 count;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 active;
    u8 draw_mode;
    u8 spawn_mode;
    u8 movement_mode;
    u8 layer;
    u8 unknown_0F;
    u16 descriptor[4];
    Entry0813E348 entries[125];
    Spawn0813E348 *spawns;
    u16 spawn_index;
    u16 unknown_11B2;
    u32 tick;
    u8 scripted;
} State0813E348;

typedef struct {
    u8 unknown_00[0x0A];
    s16 first_x;
    s16 first_y;
    s16 second_x;
    s16 second_y;
} Control0813E348;

extern Control0813E348 g_control_flags_03000940;
extern u32 func_08002804(void);
extern void func_0813EFDC(Entry0813E348 *, u16 *, s16, s16, u16, u16,
                          u8, u16, u8, u8);
extern void func_0813EF4C(Entry0813E348 *, u16 *, s16, u16, u16, u8, u8);
extern void func_0813E8FC(Entry0813E348 *, u16 *);
extern void func_0813E7A4(Entry0813E348 *, u16 *, s16, s16);
extern void func_08001CF0(const void *, s32, s32, u8, u8, u8, u8, u8,
                          u32, u8, u32);
extern void func_08001E18(const void *, s32, s32, u8, u8, u8, u8, u8,
                          u32, u8, u32);
extern void func_08001F34(const void *, s32, s32, u8, u8, u8, u8, u8,
                          u32, u8, u32);
extern void func_08002050(const void *, s32, s32, u8, u8, u8, u8, u8,
                          u32, u8, u32);

void func_0813E348(State0813E348 *state, u16 x, u16 y, u16 amount)
{
    u16 offset_x = 0;
    u16 offset_y = 0;
    u32 first_x = 0;
    u32 second_x = 0;
    u32 first_y = 0;
    u32 second_y = 0;
    u8 index;
    u8 chance;

    if (!state->active)
        return;
    if (state->spawn_mode == 4) {
        first_x = (u16)(s32)((double)(s16)x * 1.3);
        second_x = (u16)(s32)((double)(s16)x * 1.5);
        first_y = (u16)(s32)((double)(s32)y * 1.3);
        second_y = (u16)(s32)((double)(s32)y * 1.5);
    }
    switch (state->anchor) {
    case -1:
        offset_x = 0;
        break;
    case 0: {
        Control0813E348 *control = &g_control_flags_03000940;
        offset_x = (u16)(control->first_x + state->x);
        offset_y = (u16)(control->first_y + state->y);
        state->x = -control->first_x;
        state->y = -control->first_y;
        break;
    }
    case 1: {
        Control0813E348 *control = &g_control_flags_03000940;
        offset_x = (u16)(control->second_x + state->x);
        offset_y = (u16)(control->second_y + state->y);
        state->x = -control->second_x;
        state->y = -control->second_y;
        break;
    }
    }
    for (index = 0; index < state->count; ++index) {
        if (!state->entries[index].active) {
            if (state->scripted) {
                if (state->spawns[state->spawn_index].tick &&
                    state->spawns[state->spawn_index].tick == state->tick) {
                    func_0813EFDC(&state->entries[index], state->descriptor,
                        state->spawns[state->spawn_index].x,
                        state->spawns[state->spawn_index].y,
                        state->spawns[state->spawn_index].first,
                        state->spawns[state->spawn_index].second,
                        state->spawns[state->spawn_index].flag,
                        state->spawns[state->spawn_index].duration,
                        state->spawn_mode,
                        state->spawns[state->spawn_index].value);
                    ++state->spawn_index;
                }
            } else if ((s16)func_08002804() % state->divisor == 0) {
                if (state->spawn_mode == 4) {
                    chance = (s16)func_08002804() % 100;
                    if (chance < 70)
                        func_0813EF4C(&state->entries[index], state->descriptor,
                            (s16)x, y, amount, 1, state->movement_mode);
                    else if (chance < 90)
                        func_0813EF4C(&state->entries[index], state->descriptor,
                            (s16)first_x, first_y, amount, 2, state->movement_mode);
                    else
                        func_0813EF4C(&state->entries[index], state->descriptor,
                            (s16)second_x, second_y, amount, 3, state->movement_mode);
                } else
                    func_0813EF4C(&state->entries[index], state->descriptor,
                        (s16)x, y, amount, state->spawn_mode, state->movement_mode);
            }
            if (!state->entries[index].active)
                continue;
        }
        switch (state->movement_mode) {
        case 0:
            func_0813E8FC(&state->entries[index], state->descriptor);
            break;
        case 1:
            func_0813E7A4(&state->entries[index], state->descriptor,
                          -offset_x, -offset_y);
            break;
        }
        if (state->entries[index].visible) {
            switch (state->layer) {
            case 0:
                func_08001CF0(state->entries[index].source,
                    state->entries[index].x, state->entries[index].y,
                    0, 0, 0, 0, 0, 0, state->draw_mode,
                    state->entries[index].transform);
                break;
            case 1:
                func_08001E18(state->entries[index].source,
                    state->entries[index].x, state->entries[index].y,
                    0, 0, 0, 0, 0, 0, state->draw_mode,
                    state->entries[index].transform);
                break;
            case 2:
                func_08001F34(state->entries[index].source,
                    state->entries[index].x, state->entries[index].y,
                    0, 0, 0, 0, 0, 0, state->draw_mode,
                    state->entries[index].transform);
                break;
            case 3:
                func_08002050(state->entries[index].source,
                    state->entries[index].x, state->entries[index].y,
                    0, 0, 0, 0, 0, 0, state->draw_mode,
                    state->entries[index].transform);
                break;
            }
        }
    }
    if (state->scripted)
        ++state->tick;
}
