typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_000[0x970];
    u8 unknown_flags_0 : 1;
    u8 moving : 1;
    u8 unknown_flags_2 : 6;
    u8 unknown_971[7];
    u16 position_x;
    u16 position_y;
    u16 step_x;
    u16 step_y;
    u16 target_x;
    u16 target_y;
    u8 ticks_x;
    u8 ticks_y;
    u8 unknown_986[6];
    u8 ticks_z;
    u8 unknown_98d;
    u16 unknown_98e;
    u16 target_z;
    u16 step_z;
    u16 position_z;
    u16 unknown_996;
    u16 render_z;
} MotionState;

extern MotionState *data_03002818;

/* Target: 0x08073254..0x08073380, 300 bytes including literal pools. */
void func_08073254(void)
{
    if (data_03002818->ticks_x) {
        data_03002818->ticks_x--;
        if (data_03002818->ticks_x)
            data_03002818->position_x += data_03002818->step_x;
        else
            data_03002818->position_x = data_03002818->target_x;
    }

    if (data_03002818->ticks_y) {
        data_03002818->ticks_y--;
        if (data_03002818->ticks_y)
            data_03002818->position_y += data_03002818->step_y;
        else
            data_03002818->position_y = data_03002818->target_y;
    }

    if (data_03002818->ticks_z) {
        data_03002818->ticks_z--;
        if (data_03002818->ticks_z)
            data_03002818->position_z += data_03002818->step_z;
        else
            data_03002818->position_z = data_03002818->target_z;
    }

    data_03002818->render_z = data_03002818->position_z;
    if (!data_03002818->ticks_z) {
        if (!data_03002818->ticks_y) {
            if (!data_03002818->ticks_x)
                data_03002818->moving = 0;
        }
    }
}
