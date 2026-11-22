#include "ffta.h"

/* Complete target [0x080775A8, 0x08078818): 4720 bytes, 1360 instructions.
 * A state-machine step of the equipment screen, called through a function
 * pointer as (unused, &state); *state selects one of 256 jump-table slots. */

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u16 equipment[5];
    u8 unknown_34[0xD4];
} Unit080775A8;

typedef struct {
    u8 unknown_0000[0x80];
    Unit080775A8 units[24];
    u8 unknown_1940[0x2FC1 - 0x1940];
    u8 flags;
} Game080775A8;

typedef struct {
    u32 active : 1;
    u32 unknown_01 : 31;
    u8 unknown_004[0x101];
    u8 option;
    u8 unknown_106[2];
    s16 offset;
    u8 unknown_10A[0x3F6];
} Menu080775A8;

typedef struct {
    u8 unknown_000[0x25];
    u8 timer;
    u8 unknown_026[0x404];
    u8 field_42A;
    u8 unknown_42B[0xD];
    s16 marker_y;
    u8 field_43A;
    u8 field_43B;
    u8 unknown_43C[0x10];
    u8 field_44C;
    u8 unknown_44D[5];
    u8 field_452;
    u8 unknown_453;
    const u8 *field_454;
    s16 offset_x;
    s16 offset_y;
    Menu080775A8 menu;
    u8 item_count;
    u8 unknown_95D[0x13];
    u8 control;
    u8 unknown_971[0x15];
    u8 selected_entry;
    u8 selected_unit;
    u8 unknown_988[0x268];
    s16 target_x;
    s16 target_y;
    u8 unknown_BF4;
    u8 ready;
    u8 unknown_BF6[0x16];
    u16 counter;
    u8 unknown_C0E[0xE];
    u8 mode;
    u8 unknown_C1D[3];
    u8 field_C20;
    u8 unknown_C21[0x17];
    u8 field_C38;
    u8 unknown_C39[0x23];
    u16 entries[6];
    u8 unknown_C68[0x109C];
    u8 field_1D04;
    u8 field_1D05;
    u8 field_1D06;
    u8 unknown_1D07[2];
    u8 selected_category;
    u8 unknown_1D0A[2];
    Unit080775A8 *selected_record;
} State080775A8;

typedef struct {
    u8 state;
    u8 unknown_01[0x33];
    s8 offset;
    u8 unknown_35[0x17];
} Window080775A8;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input080775A8;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display080775A8;

typedef struct {
    u8 unknown_00[2];
    u16 name;
    u8 unknown_04[0x1C];
} Item080775A8;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry080775A8;

extern State080775A8 *data_03002818;
extern Game080775A8 g_state_02000000;
extern Unit080775A8 g_state_02000080[];
extern Window080775A8 data_030009E0[];
extern Input080775A8 data_03000000;
extern Display080775A8 data_03000E30;
extern Table data_03002730;
extern const Item080775A8 g_table_0851D180[];
extern const MenuEntry080775A8 data_08393B94[];
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_06014300[];
extern u16 data_03003860[];
extern u8 data_0200F22C;
extern u8 data_0200F22D;

extern void func_08141540(u16 sound);
extern void func_08141520(u16 sound);
extern void func_08074CE8(u32 width);
extern void func_08074908(Unit080775A8 *unit);
extern void func_08074A54(Unit080775A8 *unit);
extern void func_080748AC(Unit080775A8 *unit);
extern void func_08088DF0(Menu080775A8 *menu, const MenuEntry080775A8 *entries,
                          s32 count, s32 graphic, u32 palette, u32 visible,
                          u32 enabled, u32 mode, u32 variant, u32 style,
                          u32 option);
extern u16 func_08088FEC(Menu080775A8 *menu, u16 input);
extern void func_080774B4(Menu080775A8 *menu, int alternate);
extern void func_0808A604(u8 index, u8 command);
extern void func_08076420(s32 selected);
extern void func_08075620(s32 mode, Unit080775A8 *unit, s32 redraw, s32 numbered);
extern u8 func_080CB54C(Unit080775A8 *unit, u8 enabled);
extern void func_0801174C(void *object, u8 kind, u16 selector,
                          void *primary, void *secondary, u32 field0e,
                          s32 field0f, u32 field1a, u32 field11, u32 offset);
extern void func_08013364(void);
extern u16 func_08011860(void);
extern void func_0808A1EC(Menu080775A8 *menu);
extern void func_08073254(void);
extern void func_08089CE4(Menu080775A8 *menu);
extern void func_08019A8C(void *context, u16 value, void *first, void *second);
extern void func_0808C354(void);
extern void func_0808C630(u16 item);
extern void func_080CAF78(Unit080775A8 *unit, u16 entry, u8 slot);
extern void func_080CA2E8(Unit080775A8 *unit);
extern void func_08072C78(u16 keys, int fast);
extern void func_0808CACC(void);
extern void func_0807A79C(void *unused, u8 *state);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern u8 func_080CB7C0(Unit080775A8 *unit, u8 selector);
extern const u8 *func_080CB808(Unit080775A8 *unit);
extern u8 *func_080CB868(u8 *buffer, Unit080775A8 *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit080775A8 *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* An inlined copy of func_08080E80 (src/08080E80.c).  The ROM holds four
 * copies (0x080779D6, 0x0807817A, 0x08078256, 0x080782EA), each reloading the
 * 0xC5C offset inside its loop (0x080779EC, 0x0807818A, 0x08078266,
 * 0x080782FA), as the inlined body compiles; written as a plain loop the
 * offset load sits ahead of the loop instead.  The sibling dispatchers
 * 08076560 and 08078818 and 0807F168 carry the same in-loop load. */
static inline void reset_entries(u8 mode)
{
    int i;

    data_03002818->mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}

void func_080775A8(void *unused, u8 *state)
{
    s32 i;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        reset_entries(0);
        data_03002818->ready = 2;
        func_08074CE8(0x1E);
        func_08074908(data_03002818->selected_record);
        func_08088DF0(&data_03002818->menu, data_08393B94, 5, 0x1C,
                      0, 0, 0, 0, 0, 1, 0);
        func_08088FEC(&data_03002818->menu, 0);
        data_03002818->field_1D06 = 0;
        data_03002818->field_1D05 = 0;
        func_080774B4(&data_03002818->menu, 0);
        func_0808A604(4, 3);
        data_0200F22C = 3;
        *state = 0x22;
        break;
    case 1:
        data_03002818->selected_record =
            &g_state_02000080[data_03002818->selected_unit];
        data_03002818->selected_category =
            data_03002818->selected_record->flags & 0x1C;
        data_03002818->selected_category |= 1;
        func_08076420(data_03002818->selected_entry);
        func_08074CE8(0x1E);
        func_08074908(data_03002818->selected_record);
        func_08088DF0(&data_03002818->menu, data_08393B94, 5, 0x1C,
                      0, 0, 0, 0, 0, 1, data_03002818->menu.option);
        func_08088FEC(&data_03002818->menu, 0);
        func_080774B4(&data_03002818->menu, 0);
        func_0808A604(2, 3);
        func_0808A604(4, 3);
        data_0200F22C = 3;
        *state = 0x23;
        break;
    case 0x23:
        if (data_030009E0[2].state)
            break;
        if (data_030009E0[4].state)
            break;
        func_08075620(data_03002818->field_44C != 0,
                      data_03002818->selected_record, 0, 1);
        func_0808A604(3, 3);
        func_0808A604(2, 2);
        *state = 0x24;
        break;
    case 0x24:
        if (data_030009E0[3].state)
            break;
        *state = 0x22;
        break;
    case 2:
        if (func_080CB54C(data_03002818->selected_record, 1) == 0) {
            *state = 0xE;
        } else {
            data_03002818->menu.active = 0;
            data_03002818->field_1D04 = 0;
            *state = 0xC;
        }
        break;
    case 0xC: {
        /* The buffer address is loaded first, at 0x08077C30, ahead of the
         * three stores; 08078818 opens the same block the same way
         * (0x08078AF4). */
        u8 *buffer = data_02003CB0;

        data_03002818->field_43B = data_03002818->field_43A;
        data_03002818->field_43A = 3;
        data_03002818->timer = 0;
        func_0801174C(buffer, 1, 0x22, data_03000990, data_03000E80,
                      2, 2, 0x18, 4, 0x3A0);
        *state = 0xD;
        break;
    }
    case 0xD:
        if (data_03002818->timer++ > 0x46) {
            s32 count;

            func_08013364();
            data_03002818->field_43A = data_03002818->field_43B;
            count = 0;
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].active)
                    count++;
            }
            if (count > 1) {
                data_03002818->field_1D04 = 1;
            } else {
                data_03002818->field_42A = data_03002818->field_1D04 = 0;
            }
            data_0200F22C = 0xE;
            *state = 0x2F;
        }
        func_08011860();
        break;
    case 0xE:
        if (data_03002818->field_44C == 0)
            data_03002818->selected_record =
                &g_state_02000080[data_03002818->selected_unit];
        data_03002818->selected_category =
            data_03002818->selected_record->flags & 0x1C;
        data_03002818->selected_category |= 1;
        func_08076420(data_03002818->selected_entry);
        func_08074CE8(0x1E);
        func_08074908(data_03002818->selected_record);
        data_03002818->menu.active = 1;
        func_080774B4(&data_03002818->menu, 0);
        func_0808A604(2, 3);
        func_0808A604(4, 3);
        data_0200F22C = 3;
        *state = 0x23;
        break;
    case 0x2F:
        if (func_08011860() == 0)
            break;
        *state = data_0200F22C;
        break;
    case 0xA:
        if (func_08011860() == 0)
            break;
        data_03002818->timer = 0x14;
        data_03002818->field_43A = data_03002818->field_43B;
        data_03002818->field_1D04 = data_03002818->field_42A;
        *state = 0xB;
        break;
    case 0xB:
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer) {
            data_03002818->timer--;
        } else {
            func_0808A1EC(&data_03002818->menu);
            *state = 3;
        }
        break;
    case 3: {
        s32 count;

        func_08073254();
        if (data_03002818->selected_category & 0x1C) {
            data_03002818->field_1D05 = 0;
            data_03002818->field_1D06 = 0;
        } else if (data_03002818->selected_record->equipment[
                       data_03002818->menu.option]) {
            data_03002818->field_1D05 = 1;
            data_03002818->field_1D06 = 2;
        } else {
            data_03002818->field_1D05 = 0;
            data_03002818->field_1D06 = 0;
        }
        if (func_08088FEC(&data_03002818->menu, data_03000000.repeated)) {
            func_080774B4(&data_03002818->menu, 0);
            func_0808A604(4, 3);
        }
        if (data_03000000.pressed == 4) {
            u16 item = data_03002818->selected_record->equipment[
                data_03002818->menu.option];

            if (item == 0)
                break;
            data_03002818->field_42A = data_03002818->field_1D04;
            func_08089CE4(&data_03002818->menu);
            data_03002818->field_1D04 = 0;
            data_03002818->field_43B = data_03002818->field_43A;
            data_03002818->counter = 0;
            data_03002818->field_43A = 3;
            func_08019A8C(data_02003CB0, g_table_0851D180[item].name,
                          data_03000990, data_03000E80);
            *state = 0xA;
            break;
        }
        if (data_03000000.pressed & 1) {
            if (data_03002818->selected_category & 0x1C) {
                func_08141540(0x6A);
                break;
            }
            data_03002818->field_1D06 = 0;
            data_03002818->field_1D05 = 0;
            func_08141520(0x64);
            data_0200F22C = 4;
            *state = 0x26;
            break;
        }
        if (data_03000000.pressed == 2) {
            data_03002818->field_1D06 = 0;
            data_03002818->field_1D05 = 0;
            func_08141540(0x68);
            data_0200F22C = 0xFE;
            *state = 0x25;
            break;
        }
        if (data_03002818->selected_record->equipment[
                data_03002818->menu.option] &&
            data_03000000.pressed == 0x100) {
            func_0808C354();
            func_08089CE4(&data_03002818->menu);
            data_03002818->field_42A = data_03002818->field_1D04;
            data_03002818->field_1D04 = 0;
            func_08141540(0x64);
            data_03002818->field_C20 = 1;
            data_03002818->field_C38 = 1;
            func_0808C630(data_03002818->selected_record->equipment[
                data_03002818->menu.option]);
            *state = 6;
            break;
        }
        if (data_03000000.pressed == 0x200) {
            if (!(data_03002818->selected_category & 0x1C) &&
                data_03002818->selected_record->equipment[
                    data_03002818->menu.option]) {
                func_08141540(0x9C);
                func_080CAF78(data_03002818->selected_record, 0,
                              data_03002818->menu.option);
                func_080CA2E8(data_03002818->selected_record);
                if (g_state_02000000.flags & 2) {
                    reset_entries(0);
                }
                *state = 2;
                break;
            }
            func_08141540(0x6B);
            break;
        }
        if (data_03002818->field_44C)
            break;
        count = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].active)
                count++;
        }
        if (count > 1) {
            data_03002818->field_1D04 = 1;
        } else {
            data_03002818->field_42A = data_03002818->field_1D04 = 0;
        }
        if (data_03000000.pressed & 0x20) {
            if (data_03002818->item_count == 1)
                break;
            if (data_03002818->control & 2)
                break;
            reset_entries(0);
            func_08141540(0x74);
            func_08072C78(0x2000, 1);
            data_03002818->counter = 0;
            data_0200F22C = 1;
            *state = 0x28;
            break;
        }
        if (!(data_03000000.pressed & 0x10))
            break;
        if (data_03002818->item_count == 1)
            break;
        if (data_03002818->control & 2)
            break;
        reset_entries(0);
        func_08141540(0x74);
        func_08072C78(0x1000, 1);
        data_03002818->counter = 0;
        data_0200F22C = 1;
        *state = 0x28;
        break;
    }
    case 6:
        if (data_030009E0[6].offset >= 0) {
            data_030009E0[6].offset = 0;
            *state = 7;
        } else {
            data_030009E0[6].offset += 2;
        }
        func_0808A604(6, 2);
        break;
    case 7:
        if (data_03000000.pressed & 0x103) {
            func_08141540(0x68);
            data_03002818->field_C20 = 0;
            func_0808A1EC(&data_03002818->menu);
            func_0808A604(6, 0xA);
            data_030009E0[6].offset = -12;
            *state = 3;
        } else if (data_03000000.pressed == 4) {
            u16 item = data_03002818->selected_record->equipment[
                data_03002818->menu.option];

            if (item) {
                data_03002818->field_42A = data_03002818->field_1D04;
                func_08089CE4(&data_03002818->menu);
                data_03002818->field_1D04 = 0;
                data_03002818->field_43B = data_03002818->field_43A;
                data_03002818->counter = 0;
                data_03002818->field_43A = 3;
                func_08019A8C(data_02003CB0, g_table_0851D180[item].name,
                              data_03000990, data_03000E80);
                *state = 8;
            }
        }
        func_0808CACC();
        break;
    case 8:
        if (func_08011860() == 0)
            break;
        data_03002818->timer = 0x14;
        data_03002818->field_43A = data_03002818->field_43B;
        *state = 9;
        break;
    case 9:
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer)
            data_03002818->timer--;
        else
            *state = 7;
        break;
    case 4:
        func_08141540(0x65);
        func_08089CE4(&data_03002818->menu);
        func_08006ADC(&data_03002730, 3, (u32)func_0807A79C);
        *state = 5;
        break;
    case 5:
        if (data_03002730.flags[3] != 0xFF)
            break;
        *state = 2;
        break;
    case 0x22:
        if (data_030009E0[4].offset == 16)
            *state = data_0200F22C;
        else if (data_030009E0[4].offset > 16)
            data_030009E0[4].offset -= 2;
        /* Always true here; the ROM keeps the test (cmp #0xf; bgt at
         * 0x08078548), as 08078818 does at 0x0807937C. */
        else if (data_030009E0[4].offset < 16)
            data_030009E0[4].offset += 2;
        data_03002818->menu.offset = data_030009E0[4].offset * 8;
        func_0808A604(4, 3);
        break;
    case 0x25:
        if (data_030009E0[4].offset > 30)
            *state = data_0200F22C;
        else
            data_030009E0[4].offset += 2;
        data_03002818->menu.offset = data_030009E0[4].offset * 8;
        func_0808A604(4, 3);
        break;
    case 0x26:
        if (data_030009E0[4].offset > 22)
            *state = data_0200F22C;
        else
            data_030009E0[4].offset += 2;
        data_03002818->menu.offset = data_030009E0[4].offset * 8;
        func_0808A604(4, 3);
        break;
    case 0x28:
        if (data_03002818->counter++ < 10) {
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8 - data_03002818->counter * 8;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
            data_03002818->field_452 = 3;
            data_03002818->offset_x -= 8;
            data_03002818->offset_y = 0x38;
        } else {
            /* From the func_080CB808 call on, the text of func_0807478C
             * (src/0807478C.c), with field_452 = 3 where it stores 1.  The
             * buffer address is reloaded at each use (0x080786D2,
             * 0x080786DE). */
            u8 *buffer = data_02003CB0;
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8;
            const u8 *resource;
            void *object;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
            func_080748AC(data_03002818->selected_record);
            data_03002818->offset_x = 0;
            data_03002818->offset_y = 0x38;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
            resource = func_080CB808(data_03002818->selected_record);
            func_080CB868(buffer, data_03002818->selected_record);
            func_0814186C(buffer, data_06014300, ((u32)resource << 10) >> 11);
            object = (u8 *)data_03002818 + 0x2E8;
            func_080CB8D4(object,
                          func_080CB7C0(data_03002818->selected_record, 1));
            data_03002818->field_454 =
                func_080CB928(data_03002818->selected_record);
            data_03002818->field_452 = 3;
            func_0814186C((u8 *)data_03002818 + 0x28,
                          data_03003860, 0x04000080);
            func_0814186C((u8 *)data_03002818 + 0x228,
                          data_03003860 + 0x100, 0x04000080);
            func_0808A604(4, 1);
            *state = data_0200F22C;
        }
        break;
    case 0x29:
        /* Both arms set *state; cross-jumping leaves one store here
         * (0x080787CE), and 08078818 keeps both (0x080795FC, 0x08079626). */
        if (data_03002818->ready == 2) {
            data_03002818->ready = 3;
            func_08074CE8(0x1E);
            func_08074A54(data_03002818->selected_record);
            *state = 0x22;
        } else {
            data_03002818->ready = 2;
            func_08074CE8(0x1E);
            func_08074908(data_03002818->selected_record);
            *state = 0x22;
        }
        func_0808A604(4, 3);
        break;
    case 0x2E:
        if (data_030009E0[data_0200F22D].state)
            break;
        *state = data_0200F22C;
        break;
    case 0xFE:
        *state = 0xFF;
        break;
    case 0xFF:
        /* The table covers 0..0xFF: cmp #0xff at 0x080775B8, 256 words. */
        break;
    }
}
