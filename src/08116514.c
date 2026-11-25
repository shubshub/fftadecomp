#include "ffta.h"
#include "control_flags.h"

/* Target: complete [0x08116514, 0x081168B4), 928 bytes, 423 instructions,
 * including eleven literal words.
 * f0b557464e464546e0b48db08a469046098880204000814200d119e1814202dc00290bd0
 * b3e10448814200d11de10130814200d1a8e1aae1010100000020814641464a3107914246
 * 7a3208924346ac330993444602340a9447461a370c9740463230069000244a4611013b4b
 * c8180578c288038946788778f01e0006000e8a46022801d9082e01d9061c0124f81e0006
 * 000e022801d9082f01d9071c0124002c02d0281d0006050e4c466000079c211812041214
 * 78320a80089908181b041b145033038048468400862149004144091921480c3050440068
 * 0860120412141b041b141e480090062001900021029103911b48291cbff75afb099a1519
 * 28600221faf674fd0b94002e01d0062e0cd1002f01d0062f08d110495144c878002803d1
 * 0420085600281dd0099b0b981c1820680121faf657fd0a99494401200870064850440078
 * 022801d0062817d120680121faf640fe12e00000e44a3a08e7020000f0715008062e03d1
 * 28680121faf64afd062f03d128680121faf648fd0c98484406700698484407700a984844
 * 007800283bd080256d000449b00040180068002804d0058806e0000014433a08052e01d9
 * ff252d0280225200b80040180068002801d0028803e0052f01d9ff221202002303485044
 * c078012804d1c0231b020ae0e44a3a08022802d18023db0103e0032801d180231b020999
 * 0b9c081900682904091412041214faf6d7fd484601300006000e8146172800d824e70220
 * ecf64eff0a4b3f218143181c443002780170191c453108783f200870198880273f02381c
 * 084318800a204146a0e000004009000342461088013810800004002800d096e053461888
 * 0130188091e044462088013020804048404a218889180b7802210022c0f768fe00254a34
 * 079447467a3708974046ac300990414602310a9104aa9146ab00099ce61830686c00079f
 * 39190022895e089f3c19862252004244d21847463b881268d21813782288d21812041214
 * 0023f9f6f5ff0a9948190078002831d030686c46123405af04a9221c3b1cfaf667fd224a
 * 40461a3040190078800080180168002906d0434618884000401800884946088040463230
 * 40190078800080180168002905d042461088400040180088208030684b460022995e0023
 * e25e3b88faf63afd681c0006050e172da8d94446208895281bd909981821bff781fb084a
 * 118808480840108057463888013038800de00000d8638f0844433a0814433a0840090003
 * ff7f000002205146088000200db038bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    u16 phase;
} Descriptor08116514;

/* One 16-byte row of data_083A4AE4 per piece.  scale_x and scale_y select a
 * row of data_083A4314: 0 is unscaled, 6 is mirrored, and 3-5 and 9 up are
 * the same as 0-2 and 6 up with the second set of frames. */
typedef struct {
    u8 frame;
    u8 scale_x;
    u8 scale_y;
    u8 rotation;
    s8 unknown_04;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    const u8 *offsets;
} Piece08116514;

typedef struct {
    u16 timer;
    u8 scaled[24];
    u8 scale_x[24];
    u8 scale_y[24];
    s16 x[24];
    s16 y[24];
    u8 unknown_AA[2];
    void *objects[24];
    const u8 *offsets[24];
} Payload08116514;

extern const s16 *const data_083A4314[];
extern const u8 data_083A4344[];
extern const Piece08116514 data_083A4AE4[];
extern const u8 data_085071F0[];
extern const u8 data_088F63D8[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011100(void *object, u8 value);
extern void func_080110F8(void *object, u8 value);
extern void func_080112E8(void *object, u8 value);
extern void func_08011118(void *object, u8 value);
extern void func_08011120(void *object, u8 value);
extern void func_080112CC(void *object, s16 scale_x, s16 scale_y, u16 angle);
extern u32 func_080035D0(u8);
extern void func_080D7468(const void *, u8, u16, u16);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_080D5F74(void **, u16);

u32 func_08116514(void *task, Descriptor08116514 *descriptor,
                  Payload08116514 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 i;

        for (i = 0; i < 24; i++) {
            u8 alternate = 0;
            u8 frame = data_083A4AE4[i].frame;
            s16 x = data_083A4AE4[i].x;
            s16 y = data_083A4AE4[i].y;
            u8 scale_x = data_083A4AE4[i].scale_x;
            u8 scale_y = data_083A4AE4[i].scale_y;

            if ((scale_x >= 3 && scale_x <= 5) || scale_x > 8) {
                scale_x -= 3;
                alternate = 1;
            }
            if ((scale_y >= 3 && scale_y <= 5) || scale_y > 8) {
                scale_y -= 3;
                alternate = 1;
            }
            if (alternate)
                frame += 4;
            payload->x[i] = x + 120;
            payload->y[i] = y + 80;
            payload->offsets[i] = data_083A4AE4[i].offsets;
            payload->objects[i] = func_080D5CC0(data_085071F0, frame,
                                                x + 120, y + 80,
                                                0x2E7, 6, 0, 0);
            func_08011100(payload->objects[i], 2);
            if ((scale_x != 0 && scale_x != 6) ||
                (scale_y != 0 && scale_y != 6) ||
                data_083A4AE4[i].rotation != 0 ||
                data_083A4AE4[i].unknown_04 != 0) {
                func_080110F8(payload->objects[i], 1);
                payload->scaled[i] = 1;
                if (data_083A4AE4[i].frame == 2 || data_083A4AE4[i].frame == 6)
                    func_080112E8(payload->objects[i], 1);
            } else {
                if (scale_x == 6)
                    func_08011118(payload->objects[i], 1);
                if (scale_y == 6)
                    func_08011120(payload->objects[i], 1);
            }
            payload->scale_x[i] = scale_x;
            payload->scale_y[i] = scale_y;
            if (payload->scaled[i]) {
                s16 sx, sy;
                u16 angle;

                sx = 0x100;
                if (data_083A4314[scale_x] != 0)
                    sx = *data_083A4314[scale_x];
                else if (scale_x > 5)
                    sx = -0x100;
                sy = 0x100;
                if (data_083A4314[scale_y] != 0)
                    sy = *data_083A4314[scale_y];
                else if (scale_y > 5)
                    sy = -0x100;
                angle = 0;
                if (data_083A4AE4[i].rotation == 1)
                    angle = 0xC000;
                else if (data_083A4AE4[i].rotation == 2)
                    angle = 0x4000;
                else if (data_083A4AE4[i].rotation == 3)
                    angle = 0x8000;
                func_080112CC(payload->objects[i], sx, sy, angle);
            }
        }
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.winout_hi = 0x3F;
        g_control_flags_03000940.display |= 0x8000;
        payload->timer = 10;
        break;
    }
    case 0x100:
        if (--payload->timer == 0)
            descriptor->phase++;
        break;
    case 0x101: {
        u8 j;

        /* BUG: the timer is stepped before it indexes the curves (adds at
         * 0x08116782; lookups at 0x0811678E, 0x081167DA, 0x08116822 and
         * 0x08116842), and the phase ends only once it is over 0x95 (cmp at
         * 0x08116866).  Every curve has 150 entries (the thirteen byte
         * curves at 0x083A4344-0x083A4AE2, the four scale curves at
         * 0x083A3E64-0x083A4314), and entry 0 is the state phase 0 set up.
         * So passes 1 to 149 read entries 1 to 149, and the 150th pass, the
         * one that removes the pieces (0x0811686E), reads entry 150, one
         * past the end of every curve: the next curve's first entry or the
         * pad at 0x083A4AE2.  Nothing it reads is drawn: the pieces go in
         * the same call, and its BG2 scroll lands after func_081168B4 has
         * hidden BG2.  docs/bugs/08116514/ has the case. */
        payload->timer++;
#ifdef BUGFIX
        if (payload->timer > 0x95)
            goto finish;
#endif
        func_080D7468(data_088F63D8, 2, 0, data_083A4344[payload->timer]);
        for (j = 0; j < 24; j++) {
            func_080107D4(payload->objects[j], payload->x[j],
                          payload->y[j] + payload->offsets[j][payload->timer],
                          0);
            if (payload->scaled[j]) {
                s16 sx, sy, angle;

                func_080112D4(payload->objects[j], &sx, &sy, &angle);
                if (data_083A4314[payload->scale_x[j]] != 0)
                    sx = data_083A4314[payload->scale_x[j]][payload->timer];
                if (data_083A4314[payload->scale_y[j]] != 0)
                    sy = data_083A4314[payload->scale_y[j]][payload->timer];
                func_080112CC(payload->objects[j], sx, sy, angle);
            }
        }
#ifdef BUGFIX
    finish:
#endif
        if (payload->timer > 0x95) {
            func_080D5F74(payload->objects, 24);
            g_control_flags_03000940.display &= 0x7FFF;
            descriptor->phase++;
        }
        break;
    }
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
