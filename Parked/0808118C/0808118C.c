#include "ffta.h"

typedef struct {
    u8 unknown_00[0x16];
    u8 value;
} Owner0808118C;

typedef struct {
    u32 unknown_00;
    Owner0808118C *owner;
    u16 x;
    u16 y;
    u16 counter;
    u16 unknown_0e;
    u8 flags;
} Control0808118C;

typedef struct {
    u8 unknown_00;
    u8 layer;
    u8 unknown_02[0x32];
    s8 x;
    s8 y;
    u8 unknown_36[0x12];
    s8 x_offset;
    s8 y_offset;
    u8 unknown_4a[2];
} Render0808118C;

typedef struct {
    u8 unknown_000[0x44d];
    u8 field_44d;
    u8 unknown_44e[0x18b6];
    u8 field_1d04;
} Context0808118C;

extern Context0808118C *data_03002818;
extern Render0808118C data_030009E0[];
extern const u8 data_0851BA62[];
extern u16 func_08017FC4(const Control0808118C *control);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                         u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                         u32 value, u8 mode, const void *transform);

static inline void draw_control(u32 index, Control0808118C *control)
{
    if (control->flags & 4) {
        func_08001F34(data_0851BA62,
            (data_030009E0[index].x + data_030009E0[index].x_offset - 1) * 8 +
                control->x,
            (data_030009E0[index].y + data_030009E0[index].y_offset - 1) * 8 +
                control->y - ((control->counter >> 3) & 1),
            0, 0, 0, 0, 0, 0, data_030009E0[index].layer, 0);
    }
    if (control->flags & 8) {
        s32 y = func_08017FC4(control);

        y += (data_030009E0[index].y + data_030009E0[index].y_offset - 1) * 8;
        y += (control->counter >> 3) & 1;
        func_08001F34(data_0851BA62,
            (data_030009E0[index].x + data_030009E0[index].x_offset - 1) * 8 +
                control->x,
            y,
            0, 0, 0, 0, 1, 0, data_030009E0[index].layer, 0);
    }
}

/* Complete target [0x0808118C, 0x080812E8): 348 bytes, 160 instructions.
 * f0b5474680b487b0061c0d1ca8464e4802684e4950180178022909d14c48fe235b00c0180078000600161e2800dc84e0012904d1474fd019007807287dd8297c04200840002834d04348414a4c21714389188c4634310978090609166246483212781206121689180139c9002a89891862463532127812061216634649331b781b061b16d218013ad2006b89d218ab89db0801242340d21a00240094019402940394049467467b7805930694002380f77bfe297c0820084000283ad0281c96f7bbfe021c1204120c21494c2070434018844635300078000600166146493109780906091640180138c0001218a889c008012108401218184861463431097809060916634648331b781b061b16c9180139c9002d894919002400940194029401230393049465466b7805930694002380f73bfe4746b8890130b88107b008bc9846f0bc01bc00470000182800034d040000e0090003041d000062ba5108
 */
void func_0808118C(u32 index, Control0808118C *control)
{
    if (data_03002818->field_44d == 2 && data_030009E0[6].x <= 30)
        return;
    if (data_03002818->field_44d == 1 && data_03002818->field_1d04 > 7)
        return;

    draw_control(index, control);
    control->counter++;
}
