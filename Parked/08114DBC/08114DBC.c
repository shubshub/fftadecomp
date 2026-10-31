#include "ffta.h"

struct Descriptor {
    u16 phase;
    u8 unknown_02[0x12];
    u16 x;
    u16 y;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 unknown_00;
    u16 x;
    u16 y;
    u16 unknown_06;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
};

struct DisplayState {
    u16 control;
    u8 unknown_02[0x38];
    u16 window0_right : 8;
    u16 window0_left : 8;
    u16 window1_right : 8;
    u16 window1_left : 8;
    u8 window0_bottom;
    u16 window0_top : 8;
    s16 window1_bottom : 8;
    u16 window1_top : 8;
    u16 window0_layers : 8;
    u16 window1_layers : 8;
    u16 outside_layers : 8;
};

extern struct DisplayState g_control_flags_03000940;
extern u8 data_06008000[];
extern u8 data_06007000[];

extern void func_080D74E0(u8, u8, u8, s16, s16, void *, void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern u32 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);

/* Complete target [0x08114DBC, 0x08114F1A), 350 bytes, 153 instructions.
 * Observed offset views; original complete object extents are unknown.
 * Target bytes:
 * f0b583b00e1c141c318880204000814213d0814202dc00290ad09be003488142
 * 5ad00130814200d192e093e001010000b08a6080f08aa0808ce0638858331b04
 * 1b14a088e8380004001400901f4801901f480290012002210122c2f763fb201c
 * 08305821494278221e23cbf7effb201c1430e82170221e23cbf7e8fb154d291c
 * 3b310878002008702a1c3a3211781070053211781070291c3e310878a0200870
 * 043108783f243f2008700120eef6b2fb8443281c443001780470298880229201
 * 101c084328803088013042e00080000600700006400900030120eef687fb1a4d
 * 298801432980271c0837381ccbf7d0fb201c1430cbf7ccfb21890822a05e0028
 * 05dda27888182a1c3a321178107060882189401a000400140121eef617fba088
 * a18a401a000400140121eef637fb381ccbf7d0fb000600280cd0288803490140
 * 29803088013004e040090003ffdf000002203080002003b0f0bc02bc0847
 */
u32 func_08114DBC(void *task, struct Descriptor *descriptor,
                  struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        break;
    case 0x100:
        func_080D74E0(1, 2, 1, (s16)(payload->x + 88),
                       (s16)(payload->y - 232),
                       data_06008000, data_06007000);
        func_080E0608(&payload->x_motion, -88, 120, 30);
        func_080E0608(&payload->y_motion, 232, 112, 30);
        g_control_flags_03000940.window0_left = 0;
        g_control_flags_03000940.window0_right = 0;
        g_control_flags_03000940.window0_top = 0;
        g_control_flags_03000940.window0_bottom = 160;
        g_control_flags_03000940.window0_layers = 0x3f;
        g_control_flags_03000940.outside_layers =
            0x3f & ~func_080035D0(1);
        g_control_flags_03000940.control |= 0x2000;
        descriptor->phase++;
        break;
    case 0x101: {
        u32 mask = func_080035A8(1);
        g_control_flags_03000940.control |= mask;
        func_080E064C(&payload->x_motion);
        func_080E064C(&payload->y_motion);
        if (payload->x_motion.current > 0)
            g_control_flags_03000940.window0_right =
                (u8)payload->x + payload->x_motion.current;
        func_08003508((s16)(payload->x - payload->x_motion.current), 1);
        func_08003558((s16)(payload->y - payload->y_motion.current), 1);
        if (func_080E0690(&payload->x_motion)) {
            g_control_flags_03000940.control &= 0xdfff;
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
