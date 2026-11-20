#include "ffta.h"

/* Complete target: [0x0803A07C, 0x0803A7C0), 1860 bytes, 742 instructions. */

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[6];
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
} Group0803A07C;

typedef struct {
    u8 unknown_000[0xB0];
    Group0803A07C groups[30];
} Groups0803A07C;

typedef struct {
    u8 unknown_00 : 5;
    u8 hidden : 1;
    u8 suppressed : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[0x1C];
    u8 group;
} Panel0803A07C;

typedef struct {
    u8 unknown_00[3];
    u8 state;
    u8 unknown_04[0xC8];
} Slot0803A07C;

typedef struct {
    Groups0803A07C *groups;
    Panel0803A07C *panel;
    u8 unknown_008[0x4B0];
    u8 active[6];
    u8 markers[6];
    u8 unknown_4C4[0x4C0];
    Slot0803A07C slots[2];
    u8 unknown_B1C[0x130];
    u8 text_state[1];
} State0803A07C;

typedef struct {
    u16 held;
    u16 pressed;
} KeyState0803A07C;

typedef struct __attribute__((packed)) {
    u8 mode : 3;
    u8 unknown_03 : 5;
} DisplayFlags0803A07C;

typedef struct {
    u8 unknown_00[0x9A];
    DisplayFlags0803A07C flags_9A;
    u8 unknown_9B[0x4B];
    DisplayFlags0803A07C flags_E6;
    u8 unknown_E7[0x95];
    u8 busy;
    u8 unknown_17D[4];
    u8 status;
} DisplayState0803A07C;

typedef struct {
    u8 first;
    u8 second;
    u16 id;
} Entry0803A07C;

extern State0803A07C *g_state_03002810;
extern KeyState0803A07C data_03000000;
extern DisplayState0803A07C data_030009E0;
extern u8 data_0201F468;
extern u16 data_0201F46A;
extern u16 data_0201F46C[4];
extern s32 data_0201F474;
extern s32 data_0201F478;
extern const Entry0803A07C data_08391BBC[];
extern const Entry0803A07C data_08391BD0[];
extern const Entry0803A07C data_08391BE8[];
extern const Entry0803A07C data_08391C08[];
extern const u16 data_08391C78[];
extern const u8 *const data_085668B0[];

extern void func_08003398(void);
extern void func_08011B30(u8 kind, u16 entry);
extern u16 func_08011860(void);
extern void func_08011C60(void);
extern void func_08013364(void);
extern u16 func_08015110(void *context, void *tiles, const u8 *text,
                         u8 mode, u8 reset);
extern void func_08031708(u8 value);
extern void func_08031714(void);
extern void func_080354AC(u8 x, u8 y, u16 selection);
extern void func_080358B0(u32 enabled);
extern void func_080359E4(s32 index, u8 value);
extern void func_08038820(void);
extern s32 func_08038858(u16 id, u8 kind, u16 quantity);
extern s32 func_0803890C(void);
extern void func_08039D1C(void);
extern void func_08039DF4(u16 id);
extern void func_0808A604(u32 object, u32 command);
extern void func_08141540(u16 song_id);

/* The panel's current group.  The ROM recomputes it from both pointers and
 * the group index at every use (0x0803A27C, 0x0803A2E4, 0x0803A4A2,
 * 0x0803A540): an accessor that re-evaluates the address. */
#define CURRENT_GROUP \
    (g_state_03002810->groups->groups[g_state_03002810->panel->group - 1])

void func_0803A07C(s32 index)
{
    s32 i;
    u8 item;

    switch (g_state_03002810->slots[index].state) {
    case 0:
        data_0201F478 = 0;
        g_state_03002810->markers[index] = 0;
        g_state_03002810->panel->hidden = 0;
        g_state_03002810->panel->suppressed = 0;
        data_0201F474 = 0;
        func_08031708(0x42);
        func_080354AC(10, 0, 0);
        data_0201F468 = 4;
        g_state_03002810->slots[index].state = 1;
        break;
    case 1:
        if (func_08011860())
            g_state_03002810->slots[index].state = data_0201F468;
        break;
    case 4:
        if (data_03000000.pressed & 1) {
            data_0201F46A = 0;
            func_08141540(0x98);
            func_08039D1C();
            g_state_03002810->slots[index].state = 6;
        }
        break;
    case 6:
        if (!(data_0201F46A & 1)) {
            func_08003398();
            /* The VRAM address is a plain number, as in src/08038ECC.c:
             * named data_0600AFE0, it loads into r2, not r3 (0x0803A0FA). */
            func_08015110(g_state_03002810->text_state,
                          (u16 *)0x0600AFE0 + data_0201F46A, data_085668B0[78], 0, 1);
        }
        if (data_0201F46A < 0x40)
            data_0201F46A++;
        else
            g_state_03002810->slots[index].state = 5;
        break;
    case 5:
        data_030009E0.status = 3;
        func_0808A604(5, 12);
        g_state_03002810->slots[index].state = 8;
        break;
    case 8:
        data_0201F46A = 0;
        func_08141540(0x99);
        /* An item byte of 0 or 0xFF is empty.  Without bit 7 it is a 1-based
         * index into the slot's own table; with it, item - 0x81 indexes
         * data_08391C78, and the ROM forms that u8 index before the
         * destination address (0x0803A2C8). */
        item = CURRENT_GROUP.third;
        if (item != 0 && item != 0xFF) {
            if (!(item & 0x80)) {
                data_0201F46C[data_0201F474] = data_08391BE8[item - 1].id;
            } else {
                item -= 0x81;
                data_0201F46C[data_0201F474] = data_08391C78[item];
            }
            CURRENT_GROUP.third = 0xFF;
        } else {
            item = CURRENT_GROUP.second;
            if (item != 0 && item != 0xFF) {
                if (!(item & 0x80)) {
                    data_0201F46C[data_0201F474] = data_08391BD0[item - 1].id;
                } else {
                    item -= 0x81;
                    data_0201F46C[data_0201F474] = data_08391C78[item];
                }
                CURRENT_GROUP.second = 0xFF;
            } else {
                item = CURRENT_GROUP.first;
                if (item != 0 && item != 0xFF) {
                    if (!(item & 0x80)) {
                        data_0201F46C[data_0201F474] = data_08391BBC[item - 1].id;
                    } else {
                        item -= 0x81;
                        data_0201F46C[data_0201F474] = data_08391C78[item];
                    }
                    CURRENT_GROUP.first = 0xFF;
                } else {
                    item = CURRENT_GROUP.fourth;
                    if (item != 0 && item != 0xFF) {
                        if (!(item & 0x80)) {
                            data_0201F46C[data_0201F474] = data_08391C08[item - 1].id;
                        } else {
                            item -= 0x81;
                            data_0201F46C[data_0201F474] = data_08391C78[item];
                        }
                        CURRENT_GROUP.fourth = 0xFF;
                    }
                }
            }
        }
        if ((CURRENT_GROUP.first == 0 || CURRENT_GROUP.first == 0xFF)
         && (CURRENT_GROUP.second == 0 || CURRENT_GROUP.second == 0xFF)
         && (CURRENT_GROUP.third == 0 || CURRENT_GROUP.third == 0xFF)
         && (CURRENT_GROUP.fourth == 0 || CURRENT_GROUP.fourth == 0xFF))
            CURRENT_GROUP.flags ^= 4;
        func_08039DF4(data_0201F46C[data_0201F474]);
        g_state_03002810->slots[index].state = 9;
        break;
    case 9:
        if (data_0201F46A > 0x3C && (data_03000000.pressed & 1)) {
            if (CURRENT_GROUP.flags & 4) {
                data_0201F474++;
                data_0201F46A = 0;
                func_08013364();
                func_08011B30(10, 1);
                data_030009E0.status = 1;
                func_0808A604(5, 12);
                data_0201F468 = 7;
                g_state_03002810->slots[index].state = 1;
            } else {
                g_state_03002810->slots[index].state = 10;
            }
        }
        if (data_0201F46A++ > 200)
            data_0201F46A = 200;
        break;
    case 7:
        data_0201F46A = 0;
        func_08141540(0x98);
        func_08039D1C();
        g_state_03002810->slots[index].state = 6;
        break;
    case 10:
        func_08038820();
        for (i = 0; i < data_0201F474 + 1; i++) {
            if (data_0201F46C[i] < 0x178)
                func_08038858(data_0201F46C[i], 0, 1);
            else
                func_08038858(data_0201F46C[i] - 0x177, 1, 1);
        }
        if (func_0803890C() == 0)
            data_0201F478 = 1;
        g_state_03002810->slots[index].state = 13;
        break;
    case 13:
        func_08013364();
        func_08011B30(10, 2);
        func_0808A604(5, 1);
        data_0201F468 = 0xFD;
        g_state_03002810->slots[index].state = 1;
        break;
    case 14:
        if (data_030009E0.busy == 0) {
            func_08039D1C();
            g_state_03002810->slots[index].state = data_0201F468;
        }
        break;
    case 0xFD:
        if (data_03000000.pressed & 1) {
            func_08013364();
            if (data_0201F478) {
                data_030009E0.flags_9A.mode = 6;
                data_030009E0.flags_E6.mode = 6;
                data_0201F468 = 11;
            } else {
                data_0201F468 = 0xFF;
            }
            g_state_03002810->slots[index].state = 1;
        }
        break;
    case 11:
        func_080359E4(1, 0x11);
        g_state_03002810->slots[index].state = 12;
        break;
    case 12:
        if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[index].state = 0xFF;
        break;
    case 0xFF:
        func_08031714();
        g_state_03002810->panel->hidden = 1;
        g_state_03002810->panel->suppressed = 1;
        data_030009E0.flags_E6.mode = 5;
        data_030009E0.flags_9A.mode = 5;
        func_080358B0(1);
        g_state_03002810->active[index] = 0;
        break;
    }
    func_08011C60();
}
