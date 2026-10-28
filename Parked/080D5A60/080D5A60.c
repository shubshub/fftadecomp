#include "ffta.h"

/* 0x080D5A60..0x080D5C1E: 446 bytes, 212 instructions. */
typedef struct {
    void **object;
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    u16 start_offset;
    u16 end_offset;
    u16 count;
    u16 unknown_12;
    const s16 *x;
    const s16 *y;
} Movement;

typedef struct {
    u16 phase;
    u16 unknown_02;
    const Movement *movement;
    const u8 *options;
} Command;

typedef struct {
    s16 index;
    u16 unknown_02;
    void *animation;
    Movement movement;
    u8 override;
    u8 speed;
    u8 direction;
} Runtime;

typedef void (*BufferCopier)(void *, const void *, u32);
extern BufferCopier data_0836D4BC[];
extern u16 func_08141898(u32 value);
extern void *func_080E0730(s16 start_x, s16 start_y, s16 end_x, s16 end_y,
                           u16 speed, u8 direction, u16 count,
                           const s16 *x, const s16 *y, void *owner);
extern void *func_080E07F8(void *animation);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);

static inline s16 offset_position(s16 position, u16 offset)
{
    return position + offset;
}

static inline s32 square(s32 value)
{
    return value * value;
}

u32 func_080D5A60(void *owner, Command *command, Runtime *runtime)
{
    switch (command->phase) {
    case 0:
        {
            const Movement *movement = command->movement;
            const u8 *options = command->options;

            data_0836D4BC[0](&runtime->movement, movement,
                             sizeof(runtime->movement));
            if (options != 0) {
                runtime->direction = options[1];
                runtime->speed = options[0];
                runtime->override = 1;
            }
        }
        break;
    case 0x100:
        {
            s16 start_x;
            s16 start_y;
            s16 end_x;
            s16 end_y;
            s32 distance;
            s16 speed;
            s32 direction;

            start_y = offset_position(runtime->movement.start_y, runtime->movement.start_offset);
            end_y = offset_position(runtime->movement.end_y, runtime->movement.end_offset);
            end_x = runtime->movement.end_x;
            start_x = runtime->movement.start_x;
            distance = func_08141898((square(end_x - start_x) +
                                           square(end_y - start_y)) << 8) >> 4;
            if (distance > 80)
                speed = 24;
            else
                speed = 104 - distance;
            if (speed > 48)
                speed = 48;
            direction = 0;
            if (start_x == end_x) {
                if (start_y < end_y)
                    direction = 1;
            } else {
                if (start_x > end_x)
                    direction = 1;
            }
            if (runtime->override) {
                direction = runtime->direction;
                speed = runtime->speed;
            }
            runtime->animation = func_080E0730(start_x, start_y, end_x, end_y,
                                               speed, direction,
                                               runtime->movement.count,
                                               runtime->movement.x,
                                               runtime->movement.y, owner);
            command->phase++;
        }
        break;
    case 0x101:
        runtime->animation = func_080E07F8(runtime->animation);
        if (runtime->animation == 0)
            command->phase++;
        break;
    case 0x103:
        func_080107D4(*runtime->movement.object,
                      runtime->movement.x[runtime->index],
                      runtime->movement.y[runtime->index], 0);
        runtime->index++;
        if (runtime->index >= runtime->movement.count)
            command->phase++;
        break;
    case 1:
        return 0;
    default:
        break;
    }
    return 0;
}
