#include "ffta.h"

/* Target: [0x081287C4, 0x08128898), 212 bytes.
 * 70b581b00c1c151c218801295dd0012902dc002908d058e080204000814248d0013081424cd050e0606828601421605e68601622a15ea9601822a65eee602c1c10340002286109026160a069002802d180204000a061684669460231f5f666ff68460022815e0902a16002300022805e0302e360e661642060612869421a002a00da52426068c11a002900da49428a4201dd226200e02162100200140902091418f0fcff0004000e206180204000a0610be0281c1030fff745ff0006002804d128680121817103202080002001b070bc02bc0847 */

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Output081287C4;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Output081287C4 *output;
    u8 unknown_08[12];
    s16 x;
    s16 y;
    s16 parameter;
} Command081287C4;

typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
    s32 divisor;
    s32 span;
} Motion081287C4;

typedef struct {
    Output081287C4 *output;
    s32 x;
    s32 y;
    s32 parameter;
    Motion081287C4 motion;
} State081287C4;

void func_0801E6F0(s16 *x, s16 *y);
u16 func_08141860(s16 horizontal, s16 vertical);
u8 func_08128708(Motion081287C4 *motion);

/* Start the motion from the camera position, in 8.8 fixed point
 * (inlined at [0x0812881A, 0x08128838)). */
static inline void start_from_camera(Motion081287C4 *motion)
{
    s16 x;
    s16 y;

    func_0801E6F0(&x, &y);
    motion->current_x = x << 8;
    motion->current_y = y << 8;
}

u32 func_081287C4(void *task, Command081287C4 *command, State081287C4 *state)
{
    Motion081287C4 *motion;
    s32 parameter;
    s32 horizontal;
    s32 vertical;

    switch (command->phase) {
    case 0:
        state->output = command->output;
        state->x = command->x;
        state->y = command->y;
        parameter = command->parameter;
        state->parameter = parameter;
        motion = &state->motion;
        motion->target_x = state->x << 8;
        motion->target_y = state->y << 8;
        if (motion->speed == 0)
            motion->speed = 256;
        start_from_camera(motion);
        motion->divisor = parameter;
        motion->turn_percent = 100;
        horizontal = motion->target_x - motion->current_x;
        if (horizontal < 0)
            horizontal = -horizontal;
        vertical = motion->target_y - motion->current_y;
        if (vertical < 0)
            vertical = -vertical;
        if (horizontal > vertical)
            motion->span = horizontal;
        else
            motion->span = vertical;
        motion->angle = func_08141860((s16)(horizontal >> 8),
                                     (s16)(vertical >> 8)) >> 8;
        motion->speed = 256;
        break;
    case 1:
        break;
    case 0x100:
        if (func_08128708(&state->motion) != 0)
            break;
    case 0x101:
        state->output->complete = 1;
        command->phase = 3;
        break;
    }
    return 0;
}
