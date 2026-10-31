/* Complete target [0x08127228, 0x0812737E): 342 bytes.
 * f0 b5 57 46 4e 46 45 46 e0 b4 81 b0 89 46 16 1c 09 88 80 20 40 00 81 42
 * 25 d0 81 42 02 dc 00 29 0a d0 8f e0 03 48 81 42 64 d0 02 30 81 42 00 d1
 * 82 e0 87 e0 01 01 00 00 49 46 48 68 30 60 08 7d fe f7 86 f9 04 1c 6f f7
 * 85 fd 21 1c 72 f7 74 f9 70 60 4a 46 90 68 30 81 d0 68 70 81 d0 8a b0 73
 * 10 8b b0 81 6e e0 71 68 08 23 cd 5e 08 22 b0 5e 2f 18 0c 20 0b 5e 98 46
 * 0a 21 70 5e 40 44 82 46 b0 7b 00 28 1a d1 78 1b bd 42 00 dd e8 1b 52 46
 * 43 46 d1 1a d0 45 00 dd 99 1a 02 1c 42 43 10 1c 0b 1c 4b 43 19 1c 40 18
 * 1a f0 e2 fa 00 04 00 0c b1 89 1b f0 ed f9 00 04 04 0c 00 e0 b4 89 30 1c
 * 18 30 29 1c 3b 04 1b 14 24 04 24 14 00 94 00 22 e0 f6 92 f9 30 1c 30 30
 * 41 46 52 46 13 04 1b 14 00 94 00 22 e0 f6 88 f9 01 48 4b 46 18 80 29 e0
 * 01 01 00 00 34 1c 18 34 20 1c e0 f6 e7 f9 35 1c 30 35 28 1c e0 f6 e2 f9
 * 71 68 30 8b 08 81 71 68 30 8e 88 81 20 1c e0 f6 a9 fa 04 1c 28 1c e0 f6
 * a5 fa 00 2c 0e d0 00 28 0c d0 30 68 01 21 81 71 03 20 49 46 08 80 05 e0
 * 30 68 01 21 81 71 03 20 4a 46 10 80 00 20 01 b0 38 bc 98 46 a1 46 aa 46
 * f0 bc 02 bc 08 47
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Output08127228;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u16 unknown_0A;
    s16 y;
} Object08127228;

typedef struct {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 step_first;
    u16 step_second;
    s16 delta_first;
    s16 delta_second;
    s16 error;
    s16 half_second;
    s16 remaining;
} Transition08127228;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Output08127228 *output;
    s32 x;
    s32 y;
    u32 unknown_10;
    u8 selector;
    u8 unknown_15;
    u16 mode;
    u16 value;
} Descriptor08127228;

typedef struct {
    Output08127228 *output;
    Object08127228 *object;
    s16 x;
    s16 y;
    u16 value;
    u8 mode;
    u8 unknown_0F[9];
    Transition08127228 first;
    Transition08127228 second;
} Payload08127228;

extern void *func_08125578(u8 selector);
extern void *func_08096D7C(void);
extern void *func_08099560(void *context, void *record);
extern u32 func_08141898(u32 value);
extern s32 func_081426B8(s32 first, s32 second);
extern void func_08007620(void *state, u16 first, u16 second,
                          u16 target_first, u16 target_second);
extern void func_080076F4(void *state);
extern u32 func_08007894(const void *state);

u32 func_08127228(void *task, Descriptor08127228 *descriptor,
                  Payload08127228 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        void *record;

        payload->output = descriptor->output;
        record = func_08125578(descriptor->selector);
        payload->object = func_08099560(func_08096D7C(), record);
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->mode = descriptor->mode;
        payload->value = descriptor->value;
        break;
    }
    case 0x100: {
        s32 start_x = payload->object->x;
        s32 target_x = start_x + payload->x;
        s32 start_y = payload->object->y;
        s32 target_y = start_y + payload->y;
        u16 duration;

        if (payload->mode == 0) {
            s32 distance_x = target_x - start_x;
            s32 distance_y = target_y - start_y;
            u32 squared_distance;
            u16 scalar;

            if (start_x > target_x)
                distance_x = start_x - target_x;
            if (start_y > target_y)
                distance_y = start_y - target_y;
            squared_distance = (u32)(distance_x * distance_x) +
                               (u32)(distance_y * distance_y);
            scalar = func_08141898(squared_distance);
            duration = func_081426B8(scalar, payload->value);
        } else {
            duration = payload->value;
        }
        func_08007620(&payload->first, start_x, 0, target_x, duration);
        func_08007620(&payload->second, start_y, 0, target_y, duration);
        descriptor->phase = 0x101;
        break;
    }
    case 0x101: {
        u32 first_complete;
        u32 second_complete;

        func_080076F4(&payload->first);
        func_080076F4(&payload->second);
        payload->object->x = payload->first.first;
        payload->object->y = payload->second.first;
        first_complete = func_08007894(&payload->first);
        second_complete = func_08007894(&payload->second);
        if (first_complete && second_complete) {
            payload->output->complete = 1;
            descriptor->phase = 3;
        }
        break;
    }
    case 0x103:
        payload->output->complete = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
