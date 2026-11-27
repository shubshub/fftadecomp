/* Target 0x080DFF8C, 690 bytes [0x080DFF8C, 0x080E023E):
 * f0b557464e464546e0b487b00191171c098880204000814225d0814202dc00290cd03de10448814200d11de101308142
 * 00d128e134e10000010100000198416808883880488878808888b880c888f88008893881887ab8728889b88108693861
 * 486978611ce139887c88ba88fe88b87a002836d18020c00182460020814609040b141004021404910590934209d12004
 * 310480460691884559dbc02109028a4655e021040d143004041488460690a5420dd1934205da00229246c02000028146
 * 45e000218a468022d20191463fe0d11a601b0004000c824609044942090c894635e0c020000282460020814609040b14
 * 1004021404910590934209d12004310480460691884522db8021c9018a461ee021040d143004041488460690a5420dd1
 * 934205da002292468020c00181460ee000218a46c0221202914608e0d01a0004000c8146601b00044042000c82465146
 * 080400144a461104091461f0bbfb041c240405980014029004990d14401b401028180004000c8246069a121403924046
 * 0614901b401030180004000c8146240e201c27f79ffc000400143a895043001251460a0412148018c117030c0a04191c
 * 1143000438627962201c27f781fc000400143a895043001249460a0412148018c117030c0a04191c11430004b863f963
 * 281c049ad117030c0a04191c11430004b861f961301c4246d117030c0a04191c11430004386379630298059ad117030c
 * 0a04191c11430004b862f9620398069ad117030c0a04191c114300043864796400200021b864f964ba8950080021030c
 * 0a04191c1143000438657965b8890138c117030c0a04191c11430004b865f9650199088801301ae0391c48313a1c1832
 * 3b69b8890090032000f04efa019a1088013010800ce0391c48313a1c30327b69b8890090032000f03ffa022001990880
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
    u16 samples;
    s16 *output_x;
    s16 *output_y;
} CurveParameters;

typedef struct {
    u16 phase;
    u16 unknown_02;
    CurveParameters *parameters;
} CurveDescriptor;

typedef struct {
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    u16 magnitude;
    u8 direction;
    u16 samples;
    s16 *output_x;
    s16 *output_y;
    signed long long x_values[3];
    signed long long y_values[3];
    signed long long coordinates[3];
} CurvePayload;

extern u16 func_08141860(s16 horizontal, s16 vertical);
extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);
void func_080E06A4(u16 knots, const signed long long *coordinates,
                  const signed long long *values, s16 *output, u16 samples);

u32 func_080DFF8C(void *task, CurveDescriptor *descriptor, CurvePayload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        CurveParameters *parameters = descriptor->parameters;

        payload->start_x = parameters->start_x;
        payload->start_y = parameters->start_y;
        payload->end_x = parameters->end_x;
        payload->end_y = parameters->end_y;
        payload->magnitude = parameters->magnitude;
        payload->direction = parameters->direction;
        payload->samples = parameters->samples;
        payload->output_x = parameters->output_x;
        payload->output_y = parameters->output_y;
        break;
    }
    case 0x100: {
        s16 start_x = payload->start_x;
        s16 start_y = payload->start_y;
        s16 end_x = payload->end_x;
        s16 end_y = payload->end_y;
        /* x and y hold the perpendicular direction given to func_08141860,
         * then the chord midpoint: sl/sb carry both (0x080E00DA-0x080E00E4,
         * 0x080E0102, 0x080E0118). */
        u16 x;
        u16 y;
        u16 angle;
        s32 offset_x;
        s32 offset_y;

        if (payload->direction == 0) {
            /* Defaults stored before any coordinate test (0x080E0000-0x080E0008;
             * 0xC000 at 0x080E006E for the other direction). */
            x = 0x4000;
            y = 0;
            if (start_x == end_x) {
                if (start_y >= end_y)
                    x = 0xC000;
            } else if (start_y == end_y) {
                /* Each arm stores x = 0 (0x080E0044, 0x080E0050). */
                if (start_x < end_x) {
                    x = 0;
                    y = 0xC000;
                } else {
                    x = 0;
                    y = 0x4000;
                }
            } else {
                s16 dx = end_x - start_x;

                x = end_y - start_y;
                y = -dx;
            }
        } else {
            x = 0xC000;
            y = 0;
            if (start_x == end_x) {
                if (start_y >= end_y)
                    x = 0x4000;
            } else if (start_y == end_y) {
                /* Each arm stores x = 0 (0x080E00B2, 0x080E00BE). */
                if (start_x < end_x) {
                    x = 0;
                    y = 0x4000;
                } else {
                    x = 0;
                    y = 0xC000;
                }
            } else {
                s16 dy;

                y = end_x - start_x;
                dy = end_y - start_y;
                x = -dy;
            }
        }
        angle = func_08141860(x, y);
        x = start_x + ((end_x - start_x) >> 1);
        y = start_y + ((end_y - start_y) >> 1);
        /* Built in steps, like 080E0240's midpoint; one expression puts the magnitude in r1, not r2 (0x080E0126, 0x080E014E). */
        offset_x = func_08007A60(angle >> 8);
        offset_x *= payload->magnitude;
        offset_x >>= 8;
        payload->x_values[1] = (signed long long)(offset_x + (s16)x) << 16;
        offset_y = (s16)func_08007A4C(angle >> 8);
        offset_y *= payload->magnitude;
        offset_y >>= 8;
        payload->y_values[1] = (signed long long)(offset_y + (s16)y) << 16;
        payload->x_values[0] = (signed long long)start_x << 16;
        payload->y_values[0] = (signed long long)start_y << 16;
        payload->x_values[2] = (signed long long)end_x << 16;
        payload->y_values[2] = (signed long long)end_y << 16;
        payload->coordinates[0] = 0;
        payload->coordinates[1] = (signed long long)(payload->samples >> 1) << 16;
        payload->coordinates[2] = (signed long long)(payload->samples - 1) << 16;
        descriptor->phase++;
        break;
    }
    case 0x101:
        func_080E06A4(3, payload->coordinates, payload->x_values,
                      payload->output_x, payload->samples);
        descriptor->phase++;
        break;
    case 0x102:
        func_080E06A4(3, payload->coordinates, payload->y_values,
                      payload->output_y, payload->samples);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
