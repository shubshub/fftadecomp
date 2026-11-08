#include "ffta.h"

typedef union AnimationXY {
    u32 packed;
    struct { s16 x, y; } fields;
} AnimationXY;

typedef struct AnimationPosition {
    AnimationXY xy;
    s16 z;
    u16 unknown_06;
} AnimationPosition;

typedef struct AnimationFollower {
    Struct08011040 **object;
    u16 delay;
    u16 unknown_06;
} AnimationFollower;

typedef struct AnimationState {
    u16 status;
    u16 unknown_02;
    Struct08011040 **object;
    AnimationPosition start;
    AnimationPosition target;
    u16 *x_samples;
    u16 *y_samples;
    u16 *z_samples;
    u16 duration;
    u8 follower_count;
    u8 unknown_27;
    AnimationFollower followers[4];
    u16 frame;
    u16 flags;
} AnimationState;

typedef struct AnimationSetup {
    Struct08011040 **object;
    AnimationPosition *start;
    AnimationPosition *target;
    u16 *x_samples;
    u16 *y_samples;
    u16 *z_samples;
    u16 duration;
} AnimationSetup;

typedef struct AnimationMessage {
    u16 code;
    u16 unknown_02;
    AnimationSetup *setup;
    u8 unknown_08[12];
    u16 flags;
} AnimationMessage;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

void func_080107D4(void *object, s16 x, s16 y, s16 z);
void func_0801115C(void *object, u8 visible);
void func_080112A4(void *object, u8 enabled);
void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
void func_080E064C(InterpolationState *state);
u8 func_080E0690(InterpolationState *state);

u32 func_080D5594(void *task, AnimationMessage *message, AnimationState *state)
{
    InterpolationState interpolation;

    switch (message->code) {
    case 0: {
        AnimationSetup *setup = message->setup;
        state->object = setup->object;
        state->start.xy.fields.x = setup->start->xy.fields.x;
        state->start.xy.fields.y = setup->start->xy.fields.y;
        state->start.z = setup->start->z;
        state->target.xy.fields.x = setup->target->xy.fields.x;
        state->target.xy.fields.y = setup->target->xy.fields.y;
        state->target.z = setup->target->z;
        state->x_samples = setup->x_samples;
        state->y_samples = setup->y_samples;
        state->z_samples = setup->z_samples;
        state->duration = setup->duration;
        state->flags = message->flags;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (state->start.xy.packed == state->target.xy.packed &&
            state->start.z == state->target.z) {
            state->status = 4;
            message->code = 2;
        }
        if (state->x_samples) {
            u16 i = 0;
            func_080E0608(&interpolation, state->start.xy.fields.x,
                         state->target.xy.fields.x, state->duration - 1);
            state->x_samples[0] = state->start.xy.fields.x;
            do {
                i++;
                func_080E064C(&interpolation);
                state->x_samples[i] = interpolation.current;
            } while (!func_080E0690(&interpolation));
        }
        if (state->y_samples) {
            u16 i = 0;
            func_080E0608(&interpolation, state->start.xy.fields.y,
                         state->target.xy.fields.y, state->duration - 1);
            state->y_samples[0] = state->start.xy.fields.y;
            do {
                i++;
                func_080E064C(&interpolation);
                state->y_samples[i] = interpolation.current;
            } while (!func_080E0690(&interpolation));
        }
        if (state->z_samples) {
            u16 i = 0;
            func_080E0608(&interpolation, state->start.z,
                         state->target.z, state->duration - 1);
            state->z_samples[0] = state->start.z;
            do {
                i++;
                func_080E064C(&interpolation);
                state->z_samples[i] = interpolation.current;
            } while (!func_080E0690(&interpolation));
        }
        state->status = 1;
        message->code++;
        break;
    case 0x101: {
        u16 x, y, z;
        u8 i;
        if (state->status != 2)
            break;
        if (state->follower_count) {
            func_08011040(*state->object, &x, &y, &z);
            for (i = 0; i < state->follower_count; i++) {
                if (state->x_samples)
                    x = state->x_samples[0];
                if (state->y_samples)
                    y = state->y_samples[0];
                if (state->z_samples)
                    z = state->z_samples[0];
                func_080107D4(*state->followers[i].object, (s16)x, (s16)y, (s16)z);
            }
        }
        message->code++;
        break;
    }
    case 0x102: {
        u16 x, y, z;
        u8 i;
        func_08011040(*state->object, &x, &y, &z);
        if (state->x_samples)
            x = state->x_samples[state->frame];
        if (state->y_samples)
            y = state->y_samples[state->frame];
        if (state->z_samples)
            z = state->z_samples[state->frame];
        func_080107D4(*state->object, (s16)x, (s16)y, (s16)z);
        if (state->follower_count) {
            for (i = 0; i < state->follower_count; i++) {
                s16 elapsed = state->frame - state->followers[i].delay;
                if (elapsed < 0)
                    continue;
                if (elapsed == 0) {
                    func_0801115C(*state->followers[i].object, 1);
                    func_080112A4(*state->followers[i].object, 0);
                } else if (elapsed >= state->duration) {
                    func_0801115C(*state->followers[i].object, 0);
                    continue;
                }
                func_08011040(*state->followers[i].object, &x, &y, &z);
                if (state->x_samples)
                    x = state->x_samples[elapsed];
                if (state->y_samples)
                    y = state->y_samples[elapsed];
                if (state->z_samples)
                    z = state->z_samples[elapsed];
                func_080107D4(*state->followers[i].object, (s16)x, (s16)y, (s16)z);
            }
        }
        state->frame++;
        if (state->frame < state->duration)
            break;
        if (!(state->flags & 1))
            func_0801115C(*state->object, 0);
        state->status = 3;
        message->code++;
        break;
    }
    case 0x103: {
        u16 x, y, z;
        u32 done = 1;
        if (state->follower_count) {
            s16 elapsed = 0;
            u8 i;
            state->frame++;
            for (i = 0; i < state->follower_count; i++) {
                elapsed = state->frame - state->followers[i].delay;
                if (elapsed < 0) {
                    done = 0;
                    continue;
                }
                if (elapsed == 0) {
                    func_0801115C(*state->followers[i].object, 1);
                } else if (elapsed >= state->duration) {
                    func_0801115C(*state->followers[i].object, 0);
                    continue;
                }
                func_08011040(*state->followers[i].object, &x, &y, &z);
                if (state->x_samples)
                    x = state->x_samples[elapsed];
                if (state->y_samples)
                    y = state->y_samples[elapsed];
                if (state->z_samples)
                    z = state->z_samples[elapsed];
                func_080107D4(*state->followers[i].object, (s16)x, (s16)y, (s16)z);
            }
            if (elapsed < state->duration)
                done = 0;
        }
        if (done) {
            state->status = 4;
            message->code = 2;
        }
        break;
    }
    }
    return 0;
}
