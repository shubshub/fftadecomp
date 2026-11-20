#include "oam_lists.h"

/* Complete [0x080A0BB8, 0x080A0D02), 330 bytes and 157 reached instructions.
 * f0b557464e464546e0b499b0071c2198229c239d249eb446259eb0460904090c89461204120c
 * 92461b041b0c16930004060c2404240c2d042d0c60460004010c179142461204120c90461448
 * c02149000268381ca1f01efb2698002820d14a4611040914504602041214169803041b143004
 * 00140090200400140190280400140290179c200400140390279e049626980590381cfff702fe
 * 2ee00000b8d4360831040914220412142b041b144c462004001400905646300400140190169c
 * 200400140290179e3004001403902798049001200590381cfff7e1fd2822b95e388e38853986
 * 2a24395f788e788579862c26b95fb88eb885b986404601040914381cfff780fe0024381c4830
 * 0022815e051c8c4212da5820211c4143783179180a1c18320b1c303306ae0096032067f7ccfb
 * 01340021685e8442ecdb19b038bc9846a146aa46f0bc01bc0047
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

extern void func_080A0854(Motion *motion, s16 start_x, s16 start_y, s16 start_z,
                          s16 end_x, s16 end_y, s16 end_z, s16 limit,
                          s32 keep_end_height, s32 reversed);
extern void func_080A09BC(Motion *motion, s32 speed);
extern void func_08008480(s32 count, s64 *times, s64 *heights,
                          s64 *coefficients, void *scratch);

void func_080A0BB8(Motion *motion, s16 start_x, s16 start_y, s16 start_z,
                   s16 end_x, s16 end_y, s16 end_z, s16 limit,
                   s16 speed, s32 reversed, s32 keep_end_height)
{
    s64 scratch[8];
    s32 i;

    g_callbacks_0836D4B8[0](motion, sizeof(*motion));
    if (reversed == 0) {
        func_080A0854(motion, start_x, start_y, start_z, end_x, end_y, end_z,
                      limit, keep_end_height, reversed);
    } else {
        s32 temp;
        func_080A0854(motion, end_x, end_y, end_z, start_x, start_y, start_z,
                      limit, keep_end_height, 1);
        temp = motion->start_x;
        motion->start_x = motion->end_x;
        motion->end_x = temp;
        temp = motion->start_y;
        motion->start_y = motion->end_y;
        motion->end_y = temp;
        temp = motion->start_z;
        motion->start_z = motion->end_z;
        motion->end_z = temp;
    }
    func_080A09BC(motion, speed);
    for (i = 0; i < motion->count; i++) {
        Curve *curve = &motion->curves[i];
        func_08008480(3, curve->times, curve->heights,
                      (s64 *)curve->coefficients, scratch);
    }
}
