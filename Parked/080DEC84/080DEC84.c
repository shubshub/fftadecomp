#include "ffta.h"

/* Observed object fields retain the byte at +0x1F used by the defining getter. */
typedef struct {
    u8 unknown_00[0x0E];
    s16 field_0E;
    s16 field_10;
    u8 unknown_12[0x0D];
    u8 value;
} ObjectState;

typedef struct {
    ObjectState *object;
    u8 mode;
    u8 magnitude;
    u8 period;
    u8 unknown_07;
    s16 remaining;
} Parameters080DEC84;

typedef struct {
    u16 state;
    u16 unknown_02;
    Parameters080DEC84 *parameters;
    u8 unknown_08[12];
    u16 delay;
} Descriptor080DEC84;

typedef struct {
    ObjectState *object;
    u8 reverse;
    u8 unknown_05;
    u16 countdown;
    s16 first;
    s16 second;
    u8 mode;
    u8 magnitude;
    u8 period;
    u8 unknown_0F;
    s16 remaining;
    u16 delay;
    u16 final_countdown;
} Payload080DEC84;

extern s8 func_080DBC88(const ObjectState *state);

/* 0x080DEC84..0x080DEDFA: complete 374-byte target.
 * Target: 70b50e1c141c318880204000814224d0814204dc00290dd0012919d0a7e00448814260d0
 *         0130814200d196e09fe000000101000071680868206008792073487960738879a0730889
 *         2082b08a60828ee021680020c881088289e0608a002805d0013860820004002800d080e0
 *         2068fcf7c9ff0006020e207b05282fd880000249401800688746000010ed0d0828ed0d08
 *         38ed0d0848ed0d084eed0d0852ed0d085aed0d0810060016002801d0022809d1607b12e0
 *         10060016002803d0022801d0607b0ae0607b208108e0607b05e0607b2081404201e0607b
 *         20816081a07be0803088013042e0e0880138e0800004002807d100212079002800d10121
 *         2171a07be080238965892079002805d018044042030c28044042050c22680e20115e1804
 *         0014814205d11020115e28040014814201d0d3811582238a1020215e01204042814214d0
 *         581e20820004001400280ed1d08110823088013008e0a08a002804d00138a08200040028
 *         01d102203080002070bc02bc0847
 */
u32 func_080DEC84(void *context, void *descriptor, void *payload)
{
    Descriptor080DEC84 *event = descriptor;
    Payload080DEC84 *state = payload;

    switch (event->state) {
    case 0:
    {
        Parameters080DEC84 *parameters = event->parameters;

        state->object = parameters->object;
        state->mode = parameters->mode;
        state->magnitude = parameters->magnitude;
        state->period = parameters->period;
        state->remaining = parameters->remaining;
        state->delay = event->delay;
        break;
    }
    case 1:
        state->object->field_0E = 0;
        state->object->field_10 = 0;
        break;
    case 0x100:
    {
        s8 value;

        if (state->delay != 0) {
            if (--state->delay != 0)
                break;
        }
        value = func_080DBC88(state->object);
        switch (state->mode) {
        case 0:
            if (value == 0 || value == 2)
                state->second = state->magnitude;
            else
                state->first = state->magnitude;
            break;
        case 1:
            if (value == 0 || value == 2)
                state->first = state->magnitude;
            else
                state->second = state->magnitude;
            break;
        case 2:
            state->first = state->magnitude;
            break;
        case 3:
            state->second = state->magnitude;
            break;
        case 4:
            state->first = state->magnitude;
            state->second = -state->magnitude;
            break;
        case 5:
            state->first = state->magnitude;
            state->second = state->magnitude;
            break;
        }
        state->countdown = state->period;
        event->state++;
        break;
    }
    case 0x101:
    {
        s16 first;
        s16 second;

        if (--state->countdown == 0) {
            state->reverse = !state->reverse;
            state->countdown = state->period;
        }
        first = state->first;
        second = state->second;
        if (state->reverse != 0) {
            first = -first;
            second = -second;
        }
        if (state->object->field_0E != first ||
            state->object->field_10 != second) {
            state->object->field_0E = first;
            state->object->field_10 = second;
        }
        if (state->remaining != -1) {
            if (--state->remaining == 0) {
                state->object->field_0E = 0;
                state->object->field_10 = 0;
                event->state++;
            }
        }
        break;
    }
    case 0x102:
        if (state->final_countdown != 0) {
            if (--state->final_countdown != 0)
                break;
        }
        event->state = 2;
        break;
    }
    return 0;
}
