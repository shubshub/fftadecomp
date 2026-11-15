#include "ffta.h"

/* Complete [0x080A09BC, 0x080A0BB6): 506 bytes, 246 instructions, no literal
 * pool.
 * f0b557464e464546e0b485b0061c0f1c3420315e2c22b05e0a1a3023f15e2824305f091a
 * 89464846002801da494289460092002a02da131c5b420093009c0294a14501db49460291
 * 0004001411040914a0f028ff0004020e00230193301c48300024015f03908b4200dbbee0
 * 92464020801980460021049142460023d15e0b1c3224305f814200da011c834200dd031c
 * 2a20325e914200da111c934200dd131cc91a43460024185f821a0298814228dd00998945
 * 02db4b46180401e0009c2004110409140014a0f0edfe0004000e66f7e9ff000400147843
 * 0712504666f7e2ff311c5031049a891800040014784300120860504666f7ccff311c5831
 * 049bc91811e0504666f7ceff311c5031049c091900040014784300120860504666f7b8ff
 * 311c5831091900040014784300120860582001990d1c4543301c78304019002200230260
 * 4360341c80346419301c44300023c25e101cd117030c0a04191c1143000420606160341c
 * 883464190298c117030c0a04191c1143000420606160301c903040190021002201604260
 * 341c9834641942460023d05e2a21725e801ac117030c0a04191c1143000420606160341c
 * a03464193222b05e2a23f25e801ac117030c0a04191c11430004206061600224a0440498
 * 04300490019901310191039a0023d05e814200da46e705b038bc9846a146aa46f0bc01bc
 * 0047
 */

typedef signed long long s64;

typedef struct {
    s64 times[3];
    s64 heights[3];
    u8 coefficients[0x28];
} Curve;

typedef struct {
    u8 unknown_00[0x28];
    s16 start_x;
    s16 start_y;
    s16 start_z;
    u8 unknown_2E[2];
    s16 end_x;
    s16 end_y;
    s16 end_z;
    u8 unknown_36[0x0A];
    s16 heights[2];
    s16 unknown_44;
    s16 unknown_46;
    s16 count;
    u8 unknown_4A[6];
    s32 velocity_x[2];
    s32 velocity_z[2];
    u8 unknown_60[0x18];
    Curve curves[3];
} Motion;

extern s32 abs(s32 value);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);

void func_080A09BC(Motion *motion, s32 speed)
{
    s32 dz = motion->end_z - motion->start_z;
    s32 dx = motion->end_x - motion->start_x;
    s32 abs_x;
    s32 abs_z;
    s32 i;
    s32 distance;
    s32 angle;

    abs_x = abs(dx);
    abs_z = abs(dz);
    distance = abs_z;
    if (abs_x >= abs_z)
        distance = abs_x;
    angle = func_08141860(dx, dz) >> 8;

    for (i = 0; i < motion->count; i++) {
        s32 top = motion->heights[i];
        s32 bottom = motion->heights[i];
        s32 span;
        s32 rise;

        if (top < motion->end_y)
            top = motion->end_y;
        if (bottom > motion->end_y)
            bottom = motion->end_y;
        if (top < motion->start_y)
            top = motion->start_y;
        if (bottom > motion->start_y)
            bottom = motion->start_y;
        span = top - bottom;
        rise = motion->heights[i] - motion->start_y;

        if (span > distance) {
            if (abs_x >= abs_z)
                speed = (func_08007A60(func_08141860(abs_x, rise) >> 8) * speed) >> 8;
            else
                speed = (func_08007A60(func_08141860(abs_z, rise) >> 8) * speed) >> 8;
            motion->velocity_x[i] = (func_08007A60(angle) * speed) >> 8;
            motion->velocity_z[i] = ((s16)func_08007A4C(angle) * speed) >> 8;
        } else {
            motion->velocity_x[i] = (func_08007A60(angle) * speed) >> 8;
            motion->velocity_z[i] = ((s16)func_08007A4C(angle) * speed) >> 8;
        }

        motion->curves[i].times[0] = 0;
        motion->curves[i].times[1] = (s64)motion->unknown_44 << 16;
        motion->curves[i].times[2] = (s64)distance << 16;
        motion->curves[i].heights[0] = 0;
        motion->curves[i].heights[1] = (s64)(motion->heights[i] - motion->start_y) << 16;
        motion->curves[i].heights[2] = (s64)(motion->end_y - motion->start_y) << 16;
    }
}
