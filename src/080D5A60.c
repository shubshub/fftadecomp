#include "ffta.h"

/* Complete [0x080D5A60, 0x080D5C1E): 446 bytes, 212 instructions, three literal
 * words in three pools.
 * f0b557464e464546e0b488b006900f1c151c39880648814200d1a5e081420edc012900d1
 * c2e0012904dc00290ed0bde00101000080204000814221d0b6e00248814200d197e0b1e0
 * 030100007968bc680a4a281c083013681c226cf0c9fb002c00d1a3e06078291c26310870
 * 20782a1c2532107002390120087097e0bcd436080e202b5ea98a5b181b041222a95eec8a
 * 091909042e8ab1461022a85eac890c26aa5f801a021c4243101c0e0c079609141e0c1b14
 * c91a0a1c4a43111c401800026bf0bafe0004010d502902dd18239c4604e06820401a0004
 * 000c8446614608040014302801dd302294460023984621040a144c462004041482468946
 * a24209d13004079e3104031c0e1cb34209da0120804606e0330407990e04a24201dd0122
 * 9046281c24300078002807d0281c263000788046281c2530007884464c46201419145346
 * 1a14331464460094464601962c8b0294ec6903942c6a0494069c05940af0b6fd68601ee0
 * 68680af015fe686000281bd117e0a86800680026aa5fe969520051180023c95e2b6ad218
 * 0024125f00233af7effd2888013028800026a85f2d8ba84202db388801303880002008b0
 * 38bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    void **object;
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    s16 start_offset;
    s16 end_offset;
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
extern u32 func_08141898(u32 value);
extern void *func_080E0730(s16 start_x, s16 start_y, s16 end_x, s16 end_y,
                           u16 speed, u8 direction, u16 count,
                           const s16 *x, const s16 *y, void *parent);
extern void *func_080E07F8(void *animation);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);

u32 func_080D5A60(void *task, Command *command, Runtime *runtime)
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
    case 1:
        break;
    case 0x100:
        {
            s16 start_x = runtime->movement.start_x;
            s16 start_y = runtime->movement.start_y;
            s16 end_x = runtime->movement.end_x;
            s16 end_y = runtime->movement.end_y;
            s32 distance;
            s16 speed;
            u8 direction;

            start_y += runtime->movement.start_offset;
            end_y += runtime->movement.end_offset;
            distance = (u16)func_08141898(((end_x - start_x) * (end_x - start_x) +
                                            (end_y - start_y) * (end_y - start_y)) << 8) >> 4;
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
                                               runtime->movement.y, task);
            command->phase++;
        }
        break;
    case 0x101:
        runtime->animation = func_080E07F8(runtime->animation);
        if (runtime->animation == 0)
            command->phase++;
        break;
    case 0x102:
        break;
    case 0x103:
        func_080107D4(*runtime->movement.object,
                      runtime->movement.x[runtime->index],
                      runtime->movement.y[runtime->index], 0);
        runtime->index++;
        if (runtime->index >= runtime->movement.count)
            command->phase++;
        break;
    case 0x104:
        break;
    }
    return 0;
}
