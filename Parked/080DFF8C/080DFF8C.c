/* Target 0x080DFF8C, 690 bytes:
 * f0b557464e464546e0b487b00191171c098880204000814225d0814202dc0029
 * 0cd03de10448814200d11de10130814200d128e134e100000101000001984168
 * 08883880488878808888b880c888f88008893881887ab8728889b88108693861
 * 486978611ce139887c88ba88fe88b87a002836d18020c0018246002081460904
 * 0b141004021404910590934209d12004310480460691884559dbc02109028a46
 * 55e021040d143004041488460690a5420dd1934205da00229246c02000028146
 * 45e000218a468022d20191463fe0d11a601b0004000c824609044942090c8946
 * 35e0c020000282460020814609040b141004021404910590934209d120043104
 * 80460691884522db8021c9018a461ee021040d143004041488460690a5420dd1
 * 934205da002292468020c00181460ee000218a46c0221202914608e0d01a0004
 * 000c8146601b00044042000c82465146080400144a461104091461f0bbfb041c
 * 240405980014029004990d14401b401028180004000c8246069a121403924046
 * 0614901b401030180004000c8146240e201c27f79ffc000400143a8950430012
 * 51460a0412148018c117030c0a04191c1143000438627962201c27f781fc0004
 * 00143a895043001249460a0412148018c117030c0a04191c11430004b863f963
 * 281c049ad117030c0a04191c11430004b861f961301c4246d117030c0a04191c
 * 11430004386379630298059ad117030c0a04191c11430004b862f9620398069a
 * d117030c0a04191c114300043864796400200021b864f964ba8950080021030c
 * 0a04191c1143000438657965b8890138c117030c0a04191c11430004b865f965
 * 0199088801301ae0391c48313a1c18323b69b8890090032000f04efa019a1088
 * 013010800ce0391c48313a1c30327b69b8890090032000f03ffa022001990880
 * 002007b038bc9846a146aa46f0bc02bc0847
 */

#include "ffta.h"

typedef struct {
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    u16 magnitude;
    u8 direction;
    u16 sample_count;
    s16 *x_output;
    s16 *y_output;
} CurveTaskParameters;

typedef struct {
    u16 phase;
    const CurveTaskParameters *parameters;
} CurveTaskState;

typedef struct {
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    u16 magnitude;
    u8 direction;
    u16 sample_count;
    s16 *x_output;
    s16 *y_output;
    signed long long x_values[3];
    signed long long y_values[3];
    signed long long coordinates[3];
} CurveTaskPayload;

u16 func_08141860(s16 horizontal, s16 vertical);
s16 func_08007A60(u8 index);
s32 func_08007A4C(u8 index);
void func_080E06A4(u16 knots, const signed long long *coordinates,
                  const signed long long *values, s16 *output, u16 samples);

u32 func_080DFF8C(void *task, void *state_pointer, void *payload_pointer)
{
    CurveTaskState *state = state_pointer;
    CurveTaskPayload *payload = payload_pointer;

    switch (state->phase) {
    case 0: {
        const CurveTaskParameters *parameters = state->parameters;

        payload->start_x = parameters->start_x;
        payload->start_y = parameters->start_y;
        payload->end_x = parameters->end_x;
        payload->end_y = parameters->end_y;
        payload->magnitude = parameters->magnitude;
        payload->direction = parameters->direction;
        payload->sample_count = parameters->sample_count;
        payload->x_output = parameters->x_output;
        payload->y_output = parameters->y_output;
        break;
    }
    case 0x100: {
        s16 start_x = payload->start_x;
        s16 start_y = payload->start_y;
        s16 end_x = payload->end_x;
        s16 end_y = payload->end_y;
        s16 horizontal;
        s16 vertical;
        s16 midpoint_x;
        s16 midpoint_y;
        u8 index;

        if (payload->direction == 0) {
            if (start_x == end_x) {
                horizontal = start_y < end_y ? 0x4000 : -0x4000;
                vertical = 0;
            } else if (start_y == end_y) {
                horizontal = 0;
                vertical = start_x < end_x ? -0x4000 : 0x4000;
            } else {
                horizontal = end_y - start_y;
                vertical = -(end_x - start_x);
            }
        } else {
            if (start_x == end_x) {
                horizontal = start_y < end_y ? -0x4000 : 0x4000;
                vertical = 0;
            } else if (start_y == end_y) {
                horizontal = 0;
                vertical = start_x < end_x ? 0x4000 : -0x4000;
            } else {
                horizontal = -(end_y - start_y);
                vertical = end_x - start_x;
            }
        }
        index = func_08141860(horizontal, vertical) >> 8;
        midpoint_x = start_x + ((end_x - start_x) >> 1);
        midpoint_y = start_y + ((end_y - start_y) >> 1);
        payload->x_values[1] = (signed long long)(midpoint_x +
            ((func_08007A60(index) * payload->magnitude) >> 8)) * 65536;
        payload->y_values[1] = (signed long long)(midpoint_y +
            (((s16)func_08007A4C(index) * payload->magnitude) >> 8)) * 65536;
        payload->x_values[0] = (signed long long)start_x * 65536;
        payload->y_values[0] = (signed long long)start_y * 65536;
        payload->x_values[2] = (signed long long)end_x * 65536;
        payload->y_values[2] = (signed long long)end_y * 65536;
        payload->coordinates[0] = 0;
        payload->coordinates[1] = (signed long long)(payload->sample_count >> 1) * 65536;
        payload->coordinates[2] = (signed long long)(payload->sample_count - 1) * 65536;
        state->phase++;
        break;
    }
    case 0x101:
        func_080E06A4(3, payload->coordinates, payload->x_values,
                      payload->x_output, payload->sample_count);
        state->phase++;
        break;
    case 0x102:
        func_080E06A4(3, payload->coordinates, payload->y_values,
                      payload->y_output, payload->sample_count);
        state->phase = 2;
        break;
    }
    return 0;
}
