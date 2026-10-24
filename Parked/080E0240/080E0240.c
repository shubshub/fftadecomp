/* Target 0x080E0240, 440 bytes:
 * f0b587b00f1c151c398880204000814227d0814202dc00290bd0c8e08120400081427ad0814260db0130814200d19be0bde0796808882880488868808888a880c888e88008892881488968818889a881c889e88108692861486968618869a861a5e02a8968881218120452141204120ca889121812041014d117030c0a04191c114300046862a96202202a5e101cd117030c0a04191c11430004e861296208202a5e101cd117030c0a04191c11430004e8622963002000216863a963ea8950080021030c0a04191c11430004e8632964e8890138c117030c0a04191c114300046864a9643888013060e0291c34312a1c1c326b69e8890090032000f0b3f92869002807d1a86900284fd001484ee00000030100003888013048e00020295e06202a5eeb89013b1b041b1401a800f04cf9296928880880012401a800f067f928696100091801a800880880601c0004040c01a800f07df900060028edd0a869002823d03888013021e004ac0420295e0a202a5eeb89013b1b041b14201c00f024f9a969a88808800126201c00f03ff9a9697000401821880180701c0004060c201c00f056f900060028eed002203880002007b0f0bc02bc0847
 */

#include "ffta.h"

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 start_x;
    s16 start_y;
    s16 start_z;
    s16 end_x;
    s16 end_y;
    s16 end_z;
    s16 midpoint_bias;
    u16 samples;
    s16 *output_x;
    s16 *output_y;
    s16 *output_z;
} CurveTaskParameters;

typedef struct {
    u16 phase;
    const CurveTaskParameters *parameters;
} CurveTaskState;

typedef struct {
    s16 start_x;
    s16 start_y;
    s16 start_z;
    s16 end_x;
    s16 end_y;
    s16 end_z;
    s16 midpoint_bias;
    u16 samples;
    s16 *output_x;
    s16 *output_y;
    s16 *output_z;
    signed long long values[3];
    signed long long coordinates[3];
} CurveTaskPayload;

void func_080E06A4(u16 knots, const signed long long *coordinates,
                  const signed long long *values, s16 *output, u16 samples);
void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
void func_080E064C(InterpolationState *state);
u8 func_080E0690(InterpolationState *state);

u32 func_080E0240(void *task, void *state_pointer, void *payload_pointer)
{
    CurveTaskState *state = state_pointer;
    CurveTaskPayload *payload = payload_pointer;

    switch (state->phase) {
    case 0: {
        const CurveTaskParameters *parameters = state->parameters;

        payload->start_x = parameters->start_x;
        payload->start_y = parameters->start_y;
        payload->start_z = parameters->start_z;
        payload->end_x = parameters->end_x;
        payload->end_y = parameters->end_y;
        payload->end_z = parameters->end_z;
        payload->midpoint_bias = parameters->midpoint_bias;
        payload->samples = parameters->samples;
        payload->output_x = parameters->output_x;
        payload->output_y = parameters->output_y;
        payload->output_z = parameters->output_z;
        break;
    }
    case 0x100: {
        s16 midpoint;

        midpoint = payload->start_y + payload->end_y;
        midpoint = (midpoint >> 1) + payload->midpoint_bias;
        payload->values[1] = (signed long long)midpoint * 65536;
        payload->values[0] = (signed long long)payload->start_y * 65536;
        payload->values[2] = (signed long long)payload->end_y * 65536;
        payload->coordinates[0] = 0;
        payload->coordinates[1] = (signed long long)(payload->samples >> 1) * 65536;
        payload->coordinates[2] = (signed long long)(payload->samples - 1) * 65536;
        state->phase++;
        break;
    }
    case 0x101:
        func_080E06A4(3, payload->coordinates, payload->values,
                      payload->output_y, payload->samples);
        if (payload->output_x != 0)
            state->phase++;
        else if (payload->output_z != 0)
            state->phase = 0x103;
        else
            state->phase = 2;
        break;
    case 0x102: {
        InterpolationState x_interpolation;
        u16 index;

        func_080E0608(&x_interpolation, payload->start_x, payload->end_x,
                      payload->samples - 1);
        payload->output_x[0] = payload->start_x;
        index = 1;
        do {
            func_080E064C(&x_interpolation);
            payload->output_x[index] = x_interpolation.current;
            index++;
        } while (!func_080E0690(&x_interpolation));
        if (payload->output_z != 0)
            state->phase++;
        else
            state->phase = 2;
        break;
    }
    case 0x103: {
        InterpolationState z_interpolation;
        u16 index;

        func_080E0608(&z_interpolation, payload->start_z, payload->end_z,
                      payload->samples - 1);
        payload->output_z[0] = payload->start_z;
        index = 1;
        do {
            func_080E064C(&z_interpolation);
            payload->output_z[index] = z_interpolation.current;
            index++;
        } while (!func_080E0690(&z_interpolation));
        state->phase = 2;
        break;
    }
    }
    return 0;
}
