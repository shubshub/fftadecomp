#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} State08125994;

extern u8 func_080C8240(void *object);
extern u8 func_080C8194(const void *object, u8 category);
extern u8 func_080C9540(u16 bitIndex);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete 0x08125994..0x08125A5C, 200 bytes:
 * 10b5041c002c5bd0201ca2f74ffc0006002855d1218d8020c000084000284fd0201c
 * 0221a2f7ecfb0006002848d10a48a3f7bcfd000600281fd0201c0121a2f767fa0006
 * 000e0a280dd00a2806dc04280dd0092809d010e0260200000c2808d05e2808d009e0
 * 06202be0072029e0082027e0092025e00a2023e0201c0321a2f747fa013804281bd8
 * 8000024940180068874600002c5a1208405a1208445a1208485a12084c5a1208505a
 * 1208012008e0022006e0032004e0042002e0052000e0002010bc02bc0847
 */
u8 func_08125994(void *object)
{
    State08125994 *state = object;

    if (object == 0)
        return 0;
    if (func_080C8240(object))
        return 0;
    if (!(state->flags & 0x400))
        return 0;
    if (func_080C8194(object, 2))
        return 0;

    if (func_080C9540(0x226)) {
        switch ((u8)func_080C7EA4(object, 1)) {
        case 10:
            return 6;
        case 9:
            return 7;
        case 4:
            return 8;
        case 12:
            return 9;
        case 0x5E:
            return 10;
        }
    }

    switch (func_080C7EA4(object, 3)) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    }
    return 0;
}
