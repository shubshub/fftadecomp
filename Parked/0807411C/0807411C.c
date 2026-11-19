#include "ffta.h"

/*
 * Complete target [0x0807411C, 0x0807478C), 1648 bytes including pools and
 * the nine-word jump table at 0x08074180.  Task callback for the unit status
 * panel in window 2 (registered by func_08070414).  Field names follow
 * src/08071DC8.c (unit records), src/08072C78.c and src/08071888.c (state),
 * src/0807478C.c (unit_1D0C, field_452, field_454), src/0808B288.c and
 * src/0808A830.c (windows).
 */

typedef struct {
    u8 unknown_00[9];
    u8 level;
    u8 field_0A;
    u8 unknown_0B[0x0D];
    u16 current_first;
    u16 first;
    u16 current_second;
    u16 second;
    u8 unknown_20[0xB6];
    u16 value;
    u8 unknown_D8[0x30];
} Unit0807411C;

typedef struct {
    u8 unknown_00[0x80];
    Unit0807411C units[24];
} UnitTable0807411C;

typedef struct {
    u8 state;
    u8 unknown_01[3];
    u8 height;
    u8 step;
    u8 unknown_06[0x16];
    u16 *second_plane;
    u8 unknown_20[0x11];
    s8 top;
    u8 unknown_32;
    s8 bottom;
    s8 x;
    s8 y;
    u8 unknown_36[0x16];
} Window0807411C;

typedef struct {
    u8 unknown_00[4];
    u8 index;
} Record0807411C;

typedef struct {
    u8 unknown_000[0x450];
    u8 mode;
    u8 shown_unit;
    u8 field_452;
    u8 unknown_453;
    const u8 *field_454;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_45C[0x68C - 0x45C];
    u8 text[0x982 - 0x68C];
    s16 target_y;
    u8 unknown_984[3];
    u8 selected_unit;
    u8 unknown_988[3];
    u8 flag_0 : 1;
    u8 flag_1 : 1;
    u8 flag_2 : 1;
    u8 flag_3 : 1;
    u8 flag_4 : 1;
    u8 flag_5 : 1;
    u8 flag_6 : 2;
    u8 unknown_98C[0x994 - 0x98C];
    s16 camera_position;
    u8 unknown_996[0x1D0C - 0x996];
    Record0807411C *unit_1D0C;
} State0807411C;

extern State0807411C *data_03002818;
extern Window0807411C data_030009E0[];
extern UnitTable0807411C g_state_02000000;
extern u8 data_02003CB0[];
extern u8 data_06014300[];
extern u16 data_0600AEE0[];
extern u16 data_03003860[];
extern const u16 data_0894FF88[];
extern const u16 data_0894FFC4[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808A604(u32 object, u32 command);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern void func_08015110(void *context, void *destination, const u8 *text,
    u32 mode, u32 reset);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035A68(u16 *dst, u16 count, u32 value, u16 base);
extern void func_08035578(const u16 *source, u16 *destination, u32 count, u16 offset);
extern u8 func_080CB7C0(Record0807411C *unit, u8 selector);
extern u32 func_080CB808(Record0807411C *unit);
extern u8 *func_080CB868(u8 *buffer, Record0807411C *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Record0807411C *unit);

void func_0807411C(u8 index, u8 *phase)
{
    switch (*phase) {
    case 0:
        data_03002818->mode = 0;
        data_03002818->shown_unit = 0xFF;
        *phase = 1;
        break;
    case 1:
        /* Case bodies in ROM order 2, 3, 0, 1, 6, 7, 5 (0x080741A4-0x080743E0). */
        switch (data_03002818->mode) {
        case 2:
            if (data_030009E0[2].x < 0) {
                func_0814186C((u8 *)data_03002818 + 0x28,
                              data_03003860, 0x04000080);
                func_0814186C((u8 *)data_03002818 + 0x228,
                              data_03003860 + 0x100, 0x04000080);
                data_030009E0[2].x += 2;
            } else {
                data_030009E0[2].x = 0;
                data_03002818->mode = 8;
            }
            data_03002818->offset_x = data_030009E0[2].x * 8;
            func_0808A604(2, 2);
            break;
        case 3:
            if (data_030009E0[2].x <= -18) {
                data_030009E0[2].x = -18;
                data_03002818->mode = 8;
                func_0808A604(2, 4);
            } else {
                func_0814186C((u8 *)data_03002818 + 0x28,
                              data_03003860, 0x04000080);
                func_0814186C((u8 *)data_03002818 + 0x228,
                              data_03003860 + 0x100, 0x04000080);
                data_030009E0[2].x--;
                data_03002818->offset_x = data_030009E0[2].x * 8;
                func_0808A604(2, 2);
            }
            break;
        case 0:
            if (data_03002818->shown_unit != data_03002818->selected_unit) {
                data_03002818->shown_unit = data_03002818->selected_unit;
                data_03002818->mode = 7;
            }
            break;
        case 1:
            data_03002818->shown_unit = data_03002818->selected_unit;
            data_03002818->mode = 7;
            break;
        case 6:
            if (data_030009E0[2].x < -3) {
                func_0814186C((u8 *)data_03002818 + 0x28,
                              data_03003860, 0x04000080);
                func_0814186C((u8 *)data_03002818 + 0x228,
                              data_03003860 + 0x100, 0x04000080);
                data_030009E0[2].x += 4;
            } else {
                data_030009E0[2].x = 0;
                data_03002818->mode = 0;
            }
            data_03002818->offset_x = data_030009E0[2].x * 8;
            func_0808A604(2, 2);
            break;
        case 7:
            data_030009E0[2].x = -18;
            data_030009E0[2].height = 0;
            data_030009E0[2].step = 0;
            data_03002818->offset_x = data_030009E0[2].x * 8;
            func_0808A604(2, 4);
            data_03002818->mode = 5;
            break;
        case 5: {
            u8 shown = data_03002818->shown_unit;
            u8 *buffer = data_02003CB0;
            const u8 *name = (const u8 *)func_080C7EA4(data_03002818->unit_1D0C, 0);
            u16 clear;
            u16 *fill = &clear;     /* src/08035A68.c idiom: address first, 0x080743FC */
            u32 value;              /* every number drawn and the graphics size: r5 */
            void *object;

            *fill = 0;
            func_0814186C(fill, data_0600AEE0, 0x01000180);
            func_08015110(data_03002818->text, data_0600AEE0, name, 0, 1);

            value = g_state_02000000.units[shown].current_first;
            func_08035A68(func_0808B8E4(2, 1, 8, 2), 3, value, value ? 0xF000 : 0xA000);
            value = g_state_02000000.units[shown].first;
            func_08035A68(func_0808B8E4(2, 1, 12, 2), 3, value, 0xF000);
            value = g_state_02000000.units[shown].current_second;
            func_08035A68(func_0808B8E4(2, 1, 8, 3), 3, value, value ? 0xF000 : 0xA000);
            value = g_state_02000000.units[shown].second;
            func_08035A68(func_0808B8E4(2, 1, 12, 3), 3, value, 0xF000);
            value = g_state_02000000.units[shown].value;
            func_08035A68(func_0808B8E4(2, 1, 9, 4), 2, value, value ? 0xF000 : 0xA000);
            value = g_state_02000000.units[shown].level;
            func_08035A68(func_0808B8E4(2, 1, 2, 5), 2, value, 0xF000);
            value = g_state_02000000.units[shown].field_0A;
            func_08035A68(func_0808B8E4(2, 1, 6, 5), 2, value, 0xF000);

            if (data_03002818->target_y - data_03002818->camera_position + 44 > 94) {
                data_03002818->flag_2 = 1;
                data_030009E0[2].top = 2;
                data_030009E0[2].bottom = 9;
                data_030009E0[2].y = 2;
            } else {
                data_03002818->flag_2 = 0;
                data_030009E0[2].top = 13;
                data_030009E0[2].bottom = 20;
                data_030009E0[2].y = 13;
            }
            if (data_03002818->flag_2 != data_03002818->flag_3)
                func_0808A604(4, 5);

            value = func_080CB808(data_03002818->unit_1D0C);
            func_080CB868(buffer, data_03002818->unit_1D0C);
            func_0814186C(buffer, data_06014300, (value / 2) & 0x1FFFFF);
            object = (u8 *)data_03002818 + 0x2E8;
            func_080CB8D4(object, func_080CB7C0(data_03002818->unit_1D0C, 1));
            data_03002818->field_454 = func_080CB928(data_03002818->unit_1D0C);
            data_03002818->field_452 = 1;
            data_03002818->offset_y = data_030009E0[2].top * 8 + 48;
            data_03002818->mode = 6;
            break;
        }
        case 8:
            /* Table word 8 at 0x080741A0 points at the shared tail 0x08074634. */
            break;
        }
        if (data_03002818->flag_1) {
            if (data_03002818->flag_0 != data_03002818->flag_1) {
                data_03002818->flag_1 = data_03002818->flag_0;
                if (!data_03002818->flag_0)
                    func_0808A604(4, 5);
            } else if (data_03002818->flag_2 != data_03002818->flag_3
                       && data_030009E0[4].state == 0
                       && data_030009E0[2].state == 0) {
                data_03002818->flag_3 = data_03002818->flag_2;
                if (data_03002818->flag_2) {
                    data_030009E0[4].top = 19;
                    data_030009E0[4].bottom = 20;
                    data_030009E0[4].y = 19;
                } else {
                    data_030009E0[4].top = 0;
                    data_030009E0[4].bottom = 1;
                    data_030009E0[4].y = 0;
                }
                if (data_03002818->flag_5)
                    func_08035578(data_0894FF88, data_030009E0[4].second_plane, 30, 0x15B);
                else
                    func_08035578(data_0894FFC4, data_030009E0[4].second_plane, 30, 0x15B);
                func_0808A604(4, 2);
            }
        }
        break;
    case 0xFF:
        /* 0x08074128-0x08074136 tests 1 first and splits on > 1: a third case. */
        break;
    }
}
