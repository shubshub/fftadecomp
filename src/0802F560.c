#include "control_flags.h"

// Complete [0x0802F560, 0x0802FB64): 1540 bytes, including the jump table
// and literal pools.  The 48-byte function at 0x0802FB64 (called from
// 0x080B8A5C and 0x080B8E7E) is separate and has its own index row.

typedef struct Root0802F560 {
    u8 unknown_0000[0x1F3C];
    u16 selections[0];
    u8 unknown_1F3C[0x1CF8];
    u16 items[0];
} Root0802F560;

typedef struct ItemEntry0802F560 {
    u8 unknown_00;
    u8 text;
    u8 unknown_02[14];
} ItemEntry0802F560;

typedef struct Input0802F560 {
    u16 unknown_00;
    u16 pressed;
    u16 repeated;
} Input0802F560;

typedef struct Menu0802F560 {
    u8 unknown_00[3];
    u8 sound;
} Menu0802F560;

typedef struct Map0802F560 Map0802F560;

typedef struct DrawState0802F560 {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
} DrawState0802F560;

typedef struct Panel0802F560 {
    u16 x;
    u16 y;
    u8 state;
    u8 next_state;
    u8 unknown_06[2];
    u8 height;
    u8 unknown_09;
    u8 cursor_active;
    u8 unknown_0B;
    s16 selected;
    u8 unknown_0E;
    u8 page;
    u8 unknown_10[0x457];
    u8 visible;
    s16 cursor_x;
    u8 unknown_46A[0x3DA];
    u8 text_state[0xA04];
    DrawState0802F560 draw;
} Panel0802F560;

extern Panel0802F560 *data_0200F444;
extern Root0802F560 g_state_02000000;
extern Menu0802F560 g_state_0200F390;
extern const ItemEntry0802F560 g_table_08528F34[];
extern Input0802F560 data_03000000;
extern Map0802F560 data_030008B0;
extern Map0802F560 data_03000990;

extern void func_0802E160(void);
extern void func_0802F4F4(void);
extern u8 func_0802E3E0(void);
extern u8 func_0802E338(void);
extern u8 func_0802E520(void);
extern u8 func_0802E68C(void);
extern u8 func_0802E890(void);
extern void func_0802542C(u8 sound);
extern s32 func_08025464(void);
extern s32 func_080254A0(void);
extern void func_080294F0(s16 value);
extern void func_0802ECEC(u8 filter);
extern void func_0802EC24(u8 identifier);
extern void func_0802EB58(void);
extern void func_0802ED88(void);
extern void func_0802EEF8(void);
extern void func_0802F100(void);
extern void func_0801174C(void *context, u8 kind, u16 selection,
                          Map0802F560 *first, Map0802F560 *second, u32 field5,
                          s32 field6, u32 width, u32 height, u32 tile);
extern void func_0801339C(u16 value);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_0802F040(void);
extern void func_08141540(u16 sound);
extern void func_08141570(s32 player, u16 sound);
extern void func_0802E070(void);
extern void func_080023D0(void *input);
extern void func_0802F35C(u8 update);
extern void func_08019A8C(void *state, u16 text, Map0802F560 *first,
                          Map0802F560 *second);
extern void func_0802E0DC(void);

s16 func_0802F560(void)
{
    u16 pressed;
    u16 repeated;
    u16 item;
    u16 text;
    s16 result;
    s8 choice;

    switch (data_0200F444->state) {
    case 0:
        func_0802E160();
        data_0200F444->state = 3;
        break;
    case 1:
        choice = data_0200F444->selected;
        func_0802F4F4();
        return choice;
    case 3:
        if (func_0802E3E0()) {
            data_0200F444->visible = func_0802E338();
            data_0200F444->state = 5;
        }
        break;
    case 4:
        if (func_0802E520())
            data_0200F444->state = 1;
        break;
    case 6:
        if (func_0802E68C())
            data_0200F444->state = data_0200F444->next_state;
        break;
    case 7:
        if (func_0802E890())
            data_0200F444->state = data_0200F444->next_state;
        break;
    case 9:
        data_0200F444->unknown_0E = 1;
        func_0802542C(g_state_0200F390.sound);
        g_control_flags_03000940.winout_lo = 0x1F;
        g_control_flags_03000940.winin_lo = 0x3F;
        g_control_flags_03000940.win0h_hi = 0x88;
        g_control_flags_03000940.win0v_hi = 0x30;
        g_control_flags_03000940.win0h_lo = 0xF8;
        g_control_flags_03000940.win0v_lo = 0x90;
        g_control_flags_03000940.display |= 0x2000;
        data_0200F444->state = 10;
        break;
    case 10:
        if ((result = func_08025464()) != 0) {
            u8 selection;

            if (result < 0) {
                data_0200F444->state = 6;
                data_0200F444->next_state = 5;
                data_0200F444->unknown_0B = 6;
                data_0200F444->selected = 0;
                break;
            }
            data_0200F444->selected = func_080254A0();
            selection = g_state_02000000.selections[data_0200F444->selected];
            func_080294F0(selection);
            if (selection > 0x55) {
                func_0802ECEC(selection);
                data_0200F444->cursor_active = 0;
                data_0200F444->state = 6;
                data_0200F444->next_state = 0xD;
                data_0200F444->unknown_0B = 6;
            } else {
                func_0802EC24(selection);
                data_0200F444->cursor_active = 1;
                data_0200F444->state = 6;
                data_0200F444->next_state = 0xB;
                data_0200F444->unknown_0B = 6;
            }
        }
        break;
    case 11:
        {
            s16 x = data_0200F444->cursor_x;
            s16 next = 8;
            s32 distance = 8 - x;

            if (distance != 0) {
                s32 step = distance / 4;

                if (step == 0)
                    step = distance / (distance < 0 ? -distance : distance);
                next = x + step;
            }
            if (next != x)
                data_0200F444->cursor_x = next;
            else {
                data_0200F444->state = 8;
                data_0200F444->next_state = 0xF;
            }
        }
        func_0802EB58();
        break;
    case 12:
        data_0200F444->cursor_x -= 0x10;
        if (data_0200F444->cursor_x < -0x68) {
            data_0200F444->cursor_x = -0x68;
            data_0200F444->state = 9;
        }
        func_0802EB58();
        break;
    case 13:
        func_0802ED88();
        data_0200F444->state = 0xF;
        break;
    case 14:
        func_0802EEF8();
        data_0200F444->state = 9;
        break;
    case 8:
        func_0802F100();
        data_0200F444->state = data_0200F444->next_state;
        break;
    case 15:
        g_control_flags_03000940.win0v_hi = 0x50;
        func_0801174C(data_0200F444->text_state, 1, 8, &data_030008B0,
                      &data_03000990, 2, 2, 0x18, 4, 0x3A0);
        func_0801339C(2);
        data_0200F444->state = 0x10;
        func_0802EB58();
        break;
    case 16:
        func_0802EB58();
        if (func_08011860()) {
            if (!func_08013380()) {
                data_0200F444->state = 2;
            } else {
                /* Both arms store unknown_0B (0x0802F8A2, 0x0802F8BA) and
                 * reload the panel through r3 (0x0802F8A4, 0x0802F8BC); only
                 * the tail from 0x0802F8C0 is shared. */
                if (g_state_02000000.selections[data_0200F444->selected] > 0x55) {
                    data_0200F444->unknown_0B = 0;
                    data_0200F444->next_state = 0xE;
                    data_0200F444->state = 7;
                } else {
                    data_0200F444->unknown_0B = 0;
                    data_0200F444->next_state = 0xC;
                    data_0200F444->state = 7;
                }
                g_control_flags_03000940.win0v_hi = 0x30;
            }
        }
        break;
    case 2:
        func_0802EB58();
        func_0802F040();
        data_0200F444->selected = 1;
        data_0200F444->state = 4;
        break;
    case 5:
        pressed = data_03000000.pressed;
        repeated = data_03000000.repeated;
        data_0200F444->unknown_0E = 0;
        if (pressed & 4) {
            item = g_state_02000000.items[data_0200F444->selected];
            /* The 0x11 store at 0x0802F956 uses the panel pointer loaded at
             * 0x0802F910 for both of its paths, and one sound call at
             * 0x0802F938 serves two tests. */
            if (item == 0)
                func_08141570(1, 0x6B);
            else if (data_0200F444->page == 0)
                data_0200F444->state = 0x11;
            else if ((g_table_08528F34 + item)->text == 0)
                func_08141570(1, 0x6B);
            else
                data_0200F444->state = 0x11;
        } else if (pressed & 1) {
            func_08141540(0x64);
            if (data_0200F444->visible) {
                data_0200F444->unknown_0B = 0;
                data_0200F444->state = 7;
                data_0200F444->next_state = 9;
            } else {
                func_0802E070();
                data_0200F444->selected = 1;
                data_0200F444->state = 4;
                func_080294F0(-1);
                break;
            }
        } else if (pressed & 2) {
            func_08141570(1, 0x69);
            func_0802E070();
            data_0200F444->selected = -1;
            data_0200F444->state = 4;
            func_080294F0(-1);
            break;
        } else {
            if (repeated & 0x30) {
                data_0200F444->page ^= 1;
                if (data_0200F444->page == 0)
                    data_0200F444->draw.x = (data_0200F444->x - 1) * 8 + 2;
                else
                    data_0200F444->draw.x = (data_0200F444->x + 11) * 8 + 6;
                func_08141540(0x6D);
            }
            if (data_0200F444->height > 1) {
                if (repeated & 0x80) {
                    func_080023D0(&data_03000000);
                    func_08141540(0x6D);
                    if (data_0200F444->selected < data_0200F444->height - 1)
                        data_0200F444->selected++;
                    else
                        data_0200F444->selected = 0;
                } else if (repeated & 0x40) {
                    func_080023D0(&data_03000000);
                    func_08141540(0x6D);
                    if (data_0200F444->selected > 0)
                        data_0200F444->selected--;
                    else
                        data_0200F444->selected = data_0200F444->height - 1;
                }
            }
        }
        func_0802F35C(1);
        break;
    case 0x11:
        text = g_state_02000000.items[data_0200F444->selected] + 0x4B8;
        if (data_0200F444->page != 0)
            text += 0x106;
        g_control_flags_03000940.bldcnt_lo =
            (g_control_flags_03000940.bldcnt_hi = 0);
        g_control_flags_03000940.winout_lo = 0;
        g_control_flags_03000940.winin_lo = 0;
        g_control_flags_03000940.win0h_hi = (g_control_flags_03000940.win0v_hi = 0);
        g_control_flags_03000940.win0h_lo = (g_control_flags_03000940.win0v_lo = 0);
        g_control_flags_03000940.display &= 0xDFFF;
        func_08019A8C(data_0200F444->text_state, text, &data_030008B0,
                      &data_03000990);
        func_0802F35C(0);
        data_0200F444->state = 0x12;
        break;
    case 0x12:
        func_0802F35C(0);
        if (func_08011860())
            data_0200F444->state = 5;
        break;
    }
    func_0802E0DC();
    return 0;
}
