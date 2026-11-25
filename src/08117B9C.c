#include "ffta.h"
#include "control_flags.h"

/* Target: complete [0x08117B9C, 0x0811802C), 1168 bytes, including the
 * literal pools.
 * f0b557464e464546e0b48eb0061c0691904609880648814200d163e181420edc012900d1
 * 29e2012904dc002916d024e20101000080204000814231d01de20648814200d1e4e18142
 * 00da58e10130814200d1fbe111e20000030100000d4800910191002102220023bff70cfb
 * 0a48311cbcf746f9b6214900414408600748311cbcf772fdb8214900414408600b204146
 * 0880f2e1cc468f08f8dc9408f0c2940842461088013810800004002800d0e4e100239946
 * 4a320c9244467a340d944746ac37079740460230089041461a310991183a0b9200244b46
 * 19013b4fc8190578c288038946788778f01e0006000e8a46022801d9082e01d9061c0124
 * f81e0006000e022801d9082f01d9071c0124002c02d0281d0006050e494648000c9c2118
 * 1204121478320a800d9908181b041b145033038048468400862149004144091921480c30
 * 504400680860120412141b041b141e480090062001900021029103911b48291cbdf7deff
 * 079a151928600221f9f6f8f90a94002e01d0062e0cd1002f01d0062f08d110495144c878
 * 002803d10420085600281dd0079b0a981c1820680121f9f6dbf908994944012008700648
 * 50440078022801d0062817d120680121f9f6c4fa12e000006c5e3a08cf020000f0715008
 * 062e03d128680121f9f6cef9062f03d128680121f9f6ccf90998484406700b9848440770
 * 08984844007800283bd080256d000449b00040180068002804d0058806e000009c563a08
 * 052e01d9ff252d0280225200b80040180068002801d0028803e0052f01d9ff2212020023
 * 03485044c078012804d1c0231b020ae06c5e3a08022802d18023db0103e0032801d18023
 * 1b0207990a9c081900682904091412041214f9f65bfa484601300006000e8146172800d8
 * 24e71448002100910191012103220023bff7f4f90220ebf6c9fb0f4d3f24211c8143281c
 * 4430027801700320ebf6befb8443291c453108780c70298880273f02381c084328800a20
 * 41460880069a10880130cde0cc468f084009000343461888013818800004002800d0c2e0
 * 069c208801302080bde047463888013038800025381c4a300c90391c7a310d913a1cac32
 * 07923b1c0233089304aca146ab00079ffe1830686c000c9a11190027c95f0d9a14198622
 * 52004244d21847463b881268d21813782288d218120412140023f8f66ffc089948190078
 * 002831d030686c46123405af04a9221c3b1cf9f6e1f9234a40461a304019007880008018
 * 0168002906d0434618884000401800884946088040463230401900788000801801680029
 * 05d042461088400040180088208030684b460022995e0023e25e3b88f9f6b4f9681c0006
 * 050e172da8d94446208895284fd907981821bdf7fbff094c21880948084020800220ebf6
 * 0dfb218881432180069f3888013038803be000009c563a0840090003ff7f0000b6256d00
 * 45442868bbf7a8ff286000282bd1b824640044442068bcf7d5fb2060002822d10448311c
 * bbf762ff2860069908880130088018e00cdd9408b624640044442068bbf78aff20600028
 * 0dd10320ebf6d4fa094a11888143002011804a32117810700220069a108000200eb038bc
 * 9846a146aa46f0bc02bc084740090003
 */

typedef struct {
    u16 phase;
} Descriptor08117B9C;

/* One 16-byte row of data_083A5E6C per piece.  scale_x and scale_y select a
 * row of data_083A569C: 0 is unscaled, 6 is mirrored, and 3-5 and 9 up are
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
} Piece08117B9C;

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
    void *timeline;
    void *overlay;
} Payload08117B9C;

extern const s16 *const data_083A569C[];
extern const Piece08117B9C data_083A5E6C[];
extern const u8 data_085071F0[];
extern const u8 data_088F46CC[];
extern const u8 data_0894C2F0[];
extern const u8 data_0894DCF8[];
extern const u8 data_0894DD0C[];

extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011100(void *object, u8 value);
extern void func_080110F8(void *object, u8 value);
extern void func_080112E8(void *object, u8 value);
extern void func_08011118(void *object, u8 value);
extern void func_08011120(void *object, u8 value);
extern void func_080112CC(void *object, s16 scale_x, s16 scale_y, u16 angle);
extern u32 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_080D5F74(void **, u16);

u32 func_08117B9C(void *task, Descriptor08117B9C *descriptor,
                  Payload08117B9C *payload)
{
    switch (descriptor->phase) {
    case 0:
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        payload->timeline = func_080D3E9C(data_0894DCF8, task);
        payload->overlay = func_080D4704(data_0894C2F0, task);
        payload->timer = 11;
        break;
    case 1:
        break;
    case 0x100: {
        u8 i;

        if (--payload->timer != 0)
            break;
        for (i = 0; i < 24; i++) {
            u8 alternate = 0;
            u8 frame = data_083A5E6C[i].frame;
            s16 x = data_083A5E6C[i].x;
            s16 y = data_083A5E6C[i].y;
            u8 scale_x = data_083A5E6C[i].scale_x;
            u8 scale_y = data_083A5E6C[i].scale_y;

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
            payload->offsets[i] = data_083A5E6C[i].offsets;
            payload->objects[i] = func_080D5CC0(data_085071F0, frame,
                                                x + 120, y + 80,
                                                0x2CF, 6, 0, 0);
            func_08011100(payload->objects[i], 2);
            if ((scale_x != 0 && scale_x != 6) ||
                (scale_y != 0 && scale_y != 6) ||
                data_083A5E6C[i].rotation != 0 ||
                data_083A5E6C[i].unknown_04 != 0) {
                func_080110F8(payload->objects[i], 1);
                payload->scaled[i] = 1;
                if (data_083A5E6C[i].frame == 2 || data_083A5E6C[i].frame == 6)
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
                if (data_083A569C[scale_x] != 0)
                    sx = *data_083A569C[scale_x];
                else if (scale_x > 5)
                    sx = -0x100;
                sy = 0x100;
                if (data_083A569C[scale_y] != 0)
                    sy = *data_083A569C[scale_y];
                else if (scale_y > 5)
                    sy = -0x100;
                angle = 0;
                if (data_083A5E6C[i].rotation == 1)
                    angle = 0xC000;
                else if (data_083A5E6C[i].rotation == 2)
                    angle = 0x4000;
                else if (data_083A5E6C[i].rotation == 3)
                    angle = 0x8000;
                func_080112CC(payload->objects[i], sx, sy, angle);
            }
        }
        func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.winout_hi = 0x3F & ~func_080035D0(3);
        g_control_flags_03000940.display |= 0x8000;
        payload->timer = 10;
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (--payload->timer == 0)
            descriptor->phase++;
        break;
    case 0x102: {
        u8 j;

        /* BUG: the timer is stepped before it indexes the curves (adds at
         * 0x08117E9E; lookups at 0x08117EE6, 0x08117F2E and 0x08117F4E), and
         * the phase ends only once it is over 0x95 (cmp at 0x08117F72).
         * Every curve has 150 entries (the thirteen byte curves at
         * 0x083A56CC-0x083A5E6A, the four scale curves at
         * 0x083A51EC-0x083A569C), and entry 0 is the state phase 0x100 set
         * up.  So passes 1 to 149 read entries 1 to 149, and the 150th
         * pass, the one that removes the pieces (0x08117F7A), reads entry
         * 150, one past the end of every curve: the next curve's first
         * entry or the pad at 0x083A5E6A.  Nothing it reads is drawn: the
         * pieces go in the same call.  The same code is in func_08116514.
         * docs/bugs/08117B9C/ has the case. */
        payload->timer++;
#ifdef BUGFIX
        if (payload->timer > 0x95)
            goto finish;
#endif
        for (j = 0; j < 24; j++) {
            func_080107D4(payload->objects[j], payload->x[j],
                          payload->y[j] + payload->offsets[j][payload->timer],
                          0);
            if (payload->scaled[j]) {
                s16 sx, sy, angle;

                func_080112D4(payload->objects[j], &sx, &sy, &angle);
                if (data_083A569C[payload->scale_x[j]] != 0)
                    sx = data_083A569C[payload->scale_x[j]][payload->timer];
                if (data_083A569C[payload->scale_y[j]] != 0)
                    sy = data_083A569C[payload->scale_y[j]][payload->timer];
                func_080112CC(payload->objects[j], sx, sy, angle);
            }
        }
#ifdef BUGFIX
    finish:
#endif
        if (payload->timer > 0x95) {
            func_080D5F74(payload->objects, 24);
            g_control_flags_03000940.display &= 0x7FFF;
            g_control_flags_03000940.display &= ~func_080035A8(2);
            descriptor->phase++;
        }
        break;
    }
    case 0x103:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->overlay = func_080D4774(payload->overlay);
        if (payload->overlay != 0)
            break;
        payload->timeline = func_080D3E9C(data_0894DD0C, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        g_control_flags_03000940.bldcnt_lo = 0;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
