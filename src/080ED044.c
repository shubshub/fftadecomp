/* 0x080ED044 .. 0x080ED308: 708 target bytes, 338 instructions plus the
 * literal pools.
 * Target:
 *   f0b557464e464546e0b486b0171c0a88012a0cd0012a02dc002a05d046e1802040008242
 *   09d041e1486878603ee1381c08300f21e8f77cff38e100208046391c0831049143469800
 *   04990e18356805905b009946002d2bd14846404480002b4bc4183888217888421ed16178
 *   a27820791218e37860791b18f3208000009006200190029503952248e8f7f8fd30604346
 *   da00b918a079000244310880391c48318918e078000208603068002800d1f2e04046c200
 *   bb1844334c464444a400134964182089198840181880391c483189180a20225e08688018
 *   08601988090a8a460012e17840180004050c50461af796fc00040014227980235b009a42
 *   40d0c02a08d1000441148014081839e0f8923908d8714f08a02a02d10004411407e0802a
 *   01d140082ce0602a04d100048114c014081825e0402a01d1800821e0302a04d10004c114
 *   001508181ae0202a01d1c00816e0182a04d100040115401508180fe0102a01d100090be0
 *   0c2a04d1000441158015081804e0082a01d1400900e0002000044c464444a4000b496418
 *   000ca378c0180004060c50461af736fc000400146279802149008a423ed0c02a06d10004
 *   41148014081837e0f8923908a02a02d10004411407e0802a01d140082ce0602a04d10004
 *   8114c014081825e0402a01d1800821e0302a04d10004c114001508181ae0202a01d1c008
 *   16e0182a04d100040115401508180fe0102a01d100090be00c2a04d10004411580150818
 *   04e0082a01d1400900e000200004001429040a1480180004040c484640448000204bc018
 *   c07900280bd1080c9f2808d8796850004018018830040014401a0004060c049805994518
 *   28683104091424042414221c002323f78dfa514640390906c90f286823f738ff10204042
 *   844204da286824f7a9f800202860404601300004000c80460e2800d8cee6388801303880
 *   002006b038bc9846a146aa46f0bc02bc08470000f8923908
 */
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *offsets;
} Descriptor080ED044;

typedef struct {
    u16 angle;
    u16 unknown_02;
    s32 ordinate;
} Motion080ED044;

typedef struct {
    u16 counter;
    u16 unknown_02;
    s16 *offsets;
    void *objects[15];
    Motion080ED044 motion[15];
} Payload080ED044;

typedef struct {
    u8 time;
    u8 kind;
    u8 x;
    u8 y;
    u8 x_amplitude;
    u8 y_amplitude;
    u8 angle;
    u8 flag;
    u16 angle_step;
    s16 ordinate_step;
} Event080ED044;

extern const Event080ED044 g_events_083992F8[];

extern void func_080D5F74(void **slots, u16 count);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                         s16 depth, u8 a6, u8 a7, u8 a8);
extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);
extern void func_08011138(void *object, u8 value);
extern void func_08011428(void *object);

/* The ROM carries this chain twice, at 0x080ED138 and 0x080ED1E4, and
 * nowhere else; there is no out-of-line copy.  Both sites keep the test
 * against 0x100 although the amplitudes they pass are bytes. */
static inline s16 Scale080ED044(s16 value, s16 scale)
{
    if (scale == 0x100)
        return value;
    if (scale == 0xC0)
        return (value >> 1) + (value >> 2);
    if (scale == 0xA0)
        return (value >> 1) + (value >> 3);
    if (scale == 0x80)
        return value >> 1;
    if (scale == 0x60)
        return (value >> 2) + (value >> 3);
    if (scale == 0x40)
        return value >> 2;
    if (scale == 0x30)
        return (value >> 3) + (value >> 4);
    if (scale == 0x20)
        return value >> 3;
    if (scale == 0x18)
        return (value >> 4) + (value >> 5);
    if (scale == 0x10)
        return value >> 4;
    if (scale == 0x0C)
        return (value >> 5) + (value >> 6);
    if (scale == 8)
        return value >> 5;
    return 0;
}

u32 func_080ED044(void *task, Descriptor080ED044 *descriptor,
                  Payload080ED044 *payload)
{
    const Event080ED044 *events = g_events_083992F8;
    u16 i;
    u8 angle;
    u8 half;
    s16 ordinate;
    s16 x;
    s16 y;

    switch (descriptor->phase) {
    case 0:
        payload->offsets = descriptor->offsets;
        break;
    case 1:
        func_080D5F74(payload->objects, 15);
        break;
    case 0x100:
        for (i = 0; i < 15; i++) {
            if (payload->objects[i] == 0) {
                if (payload->counter == events[i].time) {
                    payload->objects[i] = func_080D5CC0((const void *)0x084F71D8,
                        events[i].kind, events[i].x + events[i].x_amplitude,
                        events[i].y + events[i].y_amplitude, 0x3CC, 6, 0, 0);
                    payload->motion[i].angle = events[i].angle << 8;
                    payload->motion[i].ordinate = events[i].y << 8;
                }
                if (payload->objects[i] == 0)
                    continue;
            }
            payload->motion[i].angle += events[i].angle_step;
            payload->motion[i].ordinate += events[i].ordinate_step;
            angle = payload->motion[i].angle >> 8;
            ordinate = (payload->motion[i].ordinate >> 8) + events[i].y;
            x = Scale080ED044(func_08007A60(angle), events[i].x_amplitude);
            x += events[i].x;
            y = Scale080ED044(func_08007A4C(angle), events[i].y_amplitude);
            y += ordinate;
            if (events[i].flag == 0 && (u16)ordinate < 160)
                x -= payload->offsets[ordinate];
            func_080107D4(payload->objects[i], x, y, 0);
            half = (u8)(angle - 0x40) >> 7;
            func_08011138(payload->objects[i], half);
            if (y < -16) {
                func_08011428(payload->objects[i]);
                payload->objects[i] = 0;
            }
        }
        payload->counter++;
        break;
    }
    return 0;
}
