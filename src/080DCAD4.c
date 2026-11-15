#include "ffta.h"

/* Complete [0x080DCAD4, 0x080DCBBC): 232 bytes, 110 instructions, no literal
 * pool.
 * 70b50d1c141c2988012969d0012902dc002908d064e080204000814211d00130814255d0
 * 5ce069680868206008792071c888e0800889208148796071a88a60814ee02089002802d0
 * 0138208148e0217901290dd0012902dc002903d02de015290cd02ae020680622a15e00f0
 * 83fb27e020680622a15e00f09dfb21e00026206800f0d6fb618901200840002818d10220
 * 0840002801d0012606e004200840002800d00226002e04d0301c8d2164f0f6fc06e08d20
 * 64f0cafc02e0206800f09afb607900280ad0607920812888013006e02089013820810004
 * 002801d102202880002070bc02bc0847
 */

/* The block the spawners (src/080DD1AC.c, src/080DD1E0.c, src/080DD214.c)
 * fill and hand over through the descriptor, under their type names.  The
 * member names are from this function's use of each value. */
typedef struct SchedulerPayload080DCAD4 {
    void *object;
    u8 effect;
    u8 delay;
    u16 value;
    u16 timer;
} SchedulerPayload080DCAD4;

typedef struct SchedulerDescriptor080DCAD4 {
    u16 state;
    u8 unknown_02[2];
    SchedulerPayload080DCAD4 *payload;
    u8 unknown_08[12];
    u16 flags;
    u8 unknown_16[6];
} SchedulerDescriptor080DCAD4;

/* The task's own 12 bytes: the spawners' block field for field, then the
 * descriptor's flags. */
typedef struct {
    void *object;
    u8 effect;
    u8 delay;
    s16 value;
    u16 timer;
    u16 flags;
} Payload080DCAD4;

extern void func_080DD248(void *object, s16 value);
extern void func_080DD288(void *object, s16 value);
extern void func_080DD2C8(void *object, u8 effect);
extern void func_080DD304(void *object);
extern void func_08141520(u16 value);
extern void func_08141570(s32 player_id, u16 song_id);

u32 func_080DCAD4(void *task, SchedulerDescriptor080DCAD4 *descriptor,
                  Payload080DCAD4 *payload)
{
    switch (descriptor->state) {
    case 0: {
        const SchedulerPayload080DCAD4 *parameters = descriptor->payload;

        payload->object = parameters->object;
        payload->effect = parameters->effect;
        payload->value = parameters->value;
        payload->timer = parameters->timer;
        payload->delay = parameters->delay;
        payload->flags = descriptor->flags;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (payload->timer != 0) {
            payload->timer--;
            break;
        }
        switch (payload->effect) {
        case 0:
            func_080DD248(payload->object, payload->value);
            break;
        case 1:
            func_080DD288(payload->object, payload->value);
            break;
        case 21: {
            /* The sound selection of func_080D8DC0 (src/080D8DC0.c); the ROM
             * zeroes the player before the call below. */
            s32 player_id = 0;

            func_080DD304(payload->object);
            if (payload->flags & 1)
                break;
            if (payload->flags & 2)
                player_id = 1;
            else if (payload->flags & 4)
                player_id = 2;
            if (player_id != 0)
                func_08141570(player_id, 0x8D);
            else
                func_08141520(0x8D);
            break;
        }
        default:
            func_080DD2C8(payload->object, payload->effect);
            break;
        }
        if (payload->delay == 0) {
            descriptor->state = 2;
        } else {
            payload->timer = payload->delay;
            descriptor->state++;
        }
        break;
    case 0x101:
        payload->timer--;
        if (payload->timer == 0)
            descriptor->state = 2;
        break;
    }
    return 0;
}
