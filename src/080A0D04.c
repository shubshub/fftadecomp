#include "ffta.h"

/* Complete [0x080A0D04, 0x080A0DEA): 230 bytes, 114 instructions, no literal
 * pool.
 * f0b54f464646c0b482b0051c8c46171c1e1c8b005030c01881460268002a00da5242281c
 * 5830c01880460068002800da4042011c8a4200dd111c3c1c4c435820634643437833eb18
 * 2212101ce117040c0a04211c114300041a1c1832009218320192032267f7b2fc0b04020c
 * 181c10436a8d80187080494608687843011231804246106878430212b2800020345e002c
 * 00da64420420335e002b00da5b42288d08183080a88d1018b0802822a95e3026a85f0a1a
 * 002a00da52422c20295e3426a85f081a002800da4042a24203dc984201dc002000e00120
 * 02b018bc9846a146f0bc02bc0847
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

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Position;

extern s32 abs(s32 value);
extern s64 func_080086D0(s64 time, s32 count, s64 *times,
                         s64 *heights, void *coefficients);

/* Samples the motion at step `progress`.  The height is the indexed curve
 * evaluated at (progress * the larger absolute planar velocity) >> 8, shifted
 * up 16 bits; the planar offset on each axis is (velocity * progress) >> 8.
 * Returns 1 while the start-to-end distance still exceeds the sampled offset
 * on either planar axis, else 0. */
s32 func_080A0D04(Motion *motion, s32 index, s32 progress, Position *out)
{
    s32 abs_x = abs(motion->velocity_x[index]);
    s32 abs_z = abs(motion->velocity_z[index]);
    s32 longest;
    s32 scaled;
    Curve *curve;
    s32 travel_x;
    s32 travel_z;

    longest = abs_z;
    if (abs_x > abs_z)
        longest = abs_x;
    scaled = progress * longest;
    curve = &motion->curves[index];
    out->y = func_080086D0((s64)(scaled >> 8) << 16, 3, curve->times,
                           curve->heights, curve->coefficients) >> 16;
    out->y += motion->start_y;
    out->x = (motion->velocity_x[index] * progress) >> 8;
    out->z = (motion->velocity_z[index] * progress) >> 8;
    travel_x = abs(out->x);
    travel_z = abs(out->z);
    out->x += motion->start_x;
    out->z += motion->start_z;
    abs_x = abs(motion->start_x - motion->end_x);
    abs_z = abs(motion->start_z - motion->end_z);
    if (abs_x <= travel_x && abs_z <= travel_z)
        return 0;
    return 1;
}
