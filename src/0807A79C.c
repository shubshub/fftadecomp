#include "ffta.h"

/* Complete target [0x0807A79C, 0x0807B858): 4284 bytes, 1601 instructions,
 * including the literal pools.
 *
 * The switch is a compare tree with far `bl` jumps into the case bodies.
 * The three page and unit copies are struct assignments: agbcc calls its
 * memcpy, the ROM routine func_081443FC, with the destination address formed
 * as (state + index * 0xcc) + 0xc68 (0x0807B11A-0x0807B122). */

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2a[0xde];
} Unit0807A79C;

typedef struct {
    u8 unknown_00[0x32];
    u8 phase;
    u8 unknown_33[0x0b];
    u16 result;
    u16 value;
    u8 unknown_42[0x86];
    void *context;
} Page0807A79C;

typedef struct {
    u8 unknown_0000[0x26];
    u16 timer;
    u8 unknown_0028[0x403];
    u8 unknown_042b;
    u8 unknown_042c[0x0e];
    u8 unknown_043a;
    u8 unknown_043b[0x11];
    u8 unknown_044c;
    u8 unknown_044d[0x114];
    u8 initial_choice;
    u8 unknown_0562[2];
    u16 unknown_0564;
    u8 unknown_0566[0x421];
    u8 selected_unit;
    u8 previous_unit;
    u8 unknown_0989[0x293];
    u8 unknown_0c1c;
    u8 selection;
    u8 previous_selection;
    u8 choice;
    u8 unknown_0c20;
    u8 count;
    u8 unknown_0c22[0x16];
    u8 unknown_0c38;
    u8 unknown_0c39[0x23];
    u16 entries[5];
    u8 unknown_0c66[2];
    Page0807A79C pages[5];
    u8 unknown_1064[0xb80];
    Unit0807A79C unit;
    u8 unknown_1cec[0x18];
    u8 unknown_1d04;
    u8 unknown_1d05[4];
    u8 selected_category;
    u8 unknown_1d0a[2];
    Unit0807A79C *selected_record;
    u8 unknown_1d10[0xf78];
    Page0807A79C page;
} State0807A79C;

typedef struct {
    u8 state;
    u8 unknown_01[4];
    u8 unknown_05;
    u8 unknown_06[0x2c];
    u8 unknown_32;
    u8 unknown_33;
    s8 x;
    u8 unknown_35[0x17];
} Window0807A79C;

typedef struct {
    u16 held;
    u16 pressed;
} Input0807A79C;

extern State0807A79C *data_03002818;
extern Window0807A79C data_030009E0[];
extern Input0807A79C data_03000000;
extern u8 g_state_02000000[];
extern Unit0807A79C g_state_02000080[];
extern u8 data_0200F230;
extern u8 data_0200F231;
extern u8 data_0200F232;

extern void func_0807B858(void);
extern void func_08079838(void);
extern void func_0808C16C(void);
extern int func_080799C0(u16 index, void *context, u16 *result);
extern void func_0807974C(s32 selected, const u16 *entries);
extern int func_0807A094(u8 index, void *context);
extern void func_08141540(u32 sound);
extern void func_0808A604(u32 object, u32 command);
extern u8 func_08082AEC(u32, u32);
extern void func_080CAF78(void *unit, u16 item, u8 slot);
extern void func_080CA2E8(void *unit);
extern void func_08003398(void);
extern u8 func_0807A734(void);
extern u8 func_0807A6CC(void);
extern void func_0808EF4C(void);
extern void func_0808AA18(u32 index);
extern void func_0808CACC(void);
extern void func_080CB0D8(void *unit, u16 item, u8 slot);
extern void func_0807614C(void *unit);
extern void func_08075620(u32, void *, u32, u32);
extern void func_0808C9C4(void);

void func_0807A79C(void *unused, u8 *state)
{
    u8 result;
    int count;
    int i;

    switch (*state) {
    case 0:
        if (!(g_state_02000000[0x2fc1] & 2)) {
            int keep;

            data_03002818->choice = data_03002818->initial_choice;
            data_03002818->unknown_0c20 = 0;
            data_03002818->unknown_0c38 = 0;
            func_0807B858();
            func_08079838();
            func_0808C16C();
            if (data_03002818->choice == data_03002818->initial_choice
                && data_03002818->unknown_0c1c)
                keep = 1;
            else
                keep = 0;
            if ((g_state_02000000[0x2fc1] & 2) && !keep)
                data_03002818->unknown_0c1c = 0;
            if (data_03002818->unknown_0c1c == 0) {
                int first = -1;
                u16 found;

                count = 0;
                for (i = 0; i < 5; i++) {
                    found = func_080799C0(i, data_03002818->page.context,
                        &data_03002818->page.value);
                    if (found) {
                        if (first == -1)
                            first = i;
                        data_03002818->entries[i] = 1;
                        count++;
                    } else {
                        data_03002818->entries[i] = 0;
                    }
                }
                data_03002818->count = count;
                if (data_03002818->previous_selection < 0xff)
                    data_03002818->selection = data_03002818->previous_selection;
                else
                    data_03002818->selection = first;
                data_03002818->unknown_0c1c = 1;
                func_0807974C(data_03002818->selection, data_03002818->entries);
                func_080799C0(data_03002818->selection,
                    data_03002818->page.context, &data_03002818->page.value);
            } else if (func_0807A094(data_03002818->selection,
                           data_03002818->page.context)) {
                func_0807974C(data_03002818->selection, data_03002818->entries);
                if (data_03002818->previous_unit == data_03002818->selected_unit) {
                    data_03002818->page.phase = 4;
                } else {
                    func_080799C0(data_03002818->selection,
                        data_03002818->page.context, &data_03002818->page.value);
                    data_03002818->previous_unit = data_03002818->selected_unit;
                }
            } else {
                int first = -1;
                u16 found;

                count = 0;
                for (i = 0; i < 5; i++) {
                    found = func_080799C0(i, data_03002818->page.context,
                        &data_03002818->page.value);
                    if (found) {
                        if (first == -1)
                            first = i;
                        data_03002818->entries[i] = 1;
                        count++;
                    } else {
                        data_03002818->entries[i] = 0;
                    }
                }
                data_03002818->count = count;
                data_03002818->selection = first;
                data_03002818->unknown_0c1c = 1;
                func_0807974C(data_03002818->selection, data_03002818->entries);
                func_080799C0(data_03002818->selection,
                    data_03002818->page.context, &data_03002818->page.value);
            }
            if (data_03002818->count == 0) {
                func_08141540(0x6a);
                data_03002818->unknown_1d04 = 0;
                *state = 0xff;
            } else {
                if (data_03002818->count > 1) {
                    data_0200F231 = 3;
                } else {
                    /* +0x1d04 is stored twice on this path: 0 here
                     * (0x0807AB64) and the copy of data_0200F231 below
                     * (0x0807AB72).  The ROM keeps both stores at every copy:
                     * 0x0807AE14/0x0807AE22, 0x0807B02E/0x0807B040,
                     * 0x0807B3CE/0x0807B3E0, and 0x0807B468/0x0807B472 for 9. */
                    data_0200F231 = data_03002818->unknown_1d04 = 0;
                }
                data_03002818->unknown_1d04 = data_0200F231;
                func_0808A604(5, 2);
                *state = 1;
            }
        } else {
            int keep;

            if (data_03002818->choice == data_03002818->initial_choice
                && data_03002818->unknown_0c1c)
                keep = 1;
            else
                keep = 0;
            data_03002818->choice = data_03002818->initial_choice;
            data_03002818->unknown_0c20 = 0;
            data_03002818->unknown_0c38 = 0;
            func_0807B858();
            func_08079838();
            func_0808C16C();
            if ((g_state_02000000[0x2fc1] & 2) && !keep)
                data_03002818->unknown_0c1c = 0;
            if (data_03002818->unknown_0c1c == 0) {
                int first = -1;
                u16 found;

                count = 0;
                for (i = 0; i < 5; i++) {
                    found = func_080799C0(i, data_03002818->page.context,
                        &data_03002818->page.value);
                    if (found) {
                        if (first == -1)
                            first = i;
                        data_03002818->entries[i] = 1;
                        count++;
                    } else {
                        data_03002818->entries[i] = 0;
                    }
                }
                data_03002818->count = count;
                data_03002818->selection = first;
                data_03002818->unknown_0c1c = 1;
                func_0807974C(data_03002818->selection, data_03002818->entries);
                func_080799C0(data_03002818->selection,
                    data_03002818->page.context, &data_03002818->page.value);
            } else if (func_0807A094(data_03002818->selection,
                           data_03002818->page.context)) {
                func_0807974C(data_03002818->selection, data_03002818->entries);
                data_03002818->page.phase = 4;
            } else {
                int first = -1;
                u16 found;

                count = 0;
                for (i = 0; i < 5; i++) {
                    found = func_080799C0(i, data_03002818->page.context,
                        &data_03002818->page.value);
                    if (found) {
                        if (first == -1)
                            first = i;
                        data_03002818->entries[i] = 1;
                        count++;
                    } else {
                        data_03002818->entries[i] = 0;
                    }
                }
                data_03002818->count = count;
                data_03002818->selection = first;
                data_03002818->unknown_0c1c = 1;
                func_0807974C(data_03002818->selection, data_03002818->entries);
                func_080799C0(data_03002818->selection,
                    data_03002818->page.context, &data_03002818->page.value);
            }
            if (data_03002818->count == 0) {
                func_08141540(0x6a);
                data_03002818->unknown_1d04 = 0;
                *state = 0xff;
            } else {
                if (data_03002818->count > 1) {
                    data_0200F231 = 3;
                } else {
                    data_0200F231 = data_03002818->unknown_1d04 = 0;
                }
                data_03002818->unknown_1d04 = data_0200F231;
                func_0808A604(5, 2);
                *state = 1;
            }
        }
        break;
    case 1:
        result = func_08082AEC(0, 0);
        if (result == 0xff) {
            data_03002818->page.phase = 8;
            data_03002818->unknown_1d04 = 0;
            data_0200F230 = 0xff;
            *state = 25;
        } else if (data_03002818->unknown_042b == 0) {
            /* result is tested against 6 here (0x0807AE98) and again after
             * the input handling (0x0807B50C); the arms that end in break
             * skip the second test. */
            if (result == 6) {
                if (data_03002818->page.result & 1) {
                    func_08141540(0x9b);
                    data_03002818->previous_selection = data_03002818->selection;
                    data_03002818->unknown_0c38 = 0;
                    if (g_state_02000000[0x2fc1] & 2)
                        data_03002818->unknown_0c1c = 0;
                    data_03002818->unknown_1d04 = 0;
                    func_080CAF78(data_03002818->selected_record,
                        data_03002818->page.value, data_03002818->choice);
                    func_080CA2E8(data_03002818->selected_record);
                    func_0807A094(data_03002818->selection,
                        data_03002818->page.context);
                    data_0200F232 = 5;
                    if (data_03002818->unknown_0c20) {
                        data_030009E0[5].unknown_32 = 23;
                        data_030009E0[11].unknown_32 = 22;
                        func_0808A604(6, 5);
                    }
                    func_08003398();
                    data_030009E0[data_0200F232].unknown_05 = 3;
                    func_0808A604(data_0200F232, 12);
                    data_0200F230 = 0xff;
                    data_03002818->timer = 6;
                    *state = 28;
                } else if (data_03002818->page.result & 2) {
                    data_03002818->previous_selection = data_03002818->selection;
                    data_03002818->unknown_0c38 = 0;
                    if (data_03002818->unknown_0c20) {
                        if (data_03002818->count > 1) {
                            data_0200F231 = 3;
                        } else {
                            data_0200F231 = data_03002818->unknown_1d04 = 0;
                        }
                        data_03002818->unknown_1d04 = data_0200F231;
                        func_08141540(0x68);
                        data_03002818->unknown_0c20 = 0;
                        data_03002818->unknown_0c38 = 0;
                        data_03002818->unknown_043a = 3;
                        data_0200F232 = 6;
                        func_08003398();
                        func_0808A604(data_0200F232, 5);
                        data_0200F230 = 15;
                        *state = 26;
                    } else {
                        if (data_03000000.pressed & 2)
                            func_08141540(0x68);
                        data_03002818->unknown_1d04 = 0;
                        data_0200F232 = 5;
                        data_030009E0[data_0200F232].unknown_05 = 3;
                        func_0808A604(data_0200F232, 12);
                        data_0200F230 = 0xff;
                        *state = 25;
                    }
                    break;
                } else if (data_03000000.pressed & 0x20) {
                    data_03000000.pressed = 0;
                    if (data_03002818->count == 1)
                        break;
                    data_03002818->pages[data_03002818->selection] = data_03002818->page;
                    data_03002818->entries[data_03002818->selection] = 2;
                    data_03002818->selection = func_0807A734();
                    if (data_03002818->entries[data_03002818->selection] > 1) {
                        data_03002818->page = data_03002818->pages[data_03002818->selection];
                        data_03002818->page.value = 0;
                        func_0807974C(data_03002818->selection, data_03002818->entries);
                        func_080799C0(data_03002818->selection,
                            data_03002818->page.context, &data_03002818->page.value);
                        func_0808A604(11, 5);
                        data_03002818->page.phase = 4;
                        data_0200F232 = 5;
                        data_0200F230 = 1;
                        *state = 26;
                        break;
                    }
                    data_03002818->page.value = 0;
                    func_0807974C(data_03002818->selection, data_03002818->entries);
                    func_080799C0(data_03002818->selection,
                        data_03002818->page.context, &data_03002818->page.value);
                    func_0808A604(11, 5);
                    data_03002818->page.phase = 1;
                } else if (data_03000000.pressed & 0x10) {
                    data_03000000.pressed = 0;
                    if (data_03002818->count == 1)
                        break;
                    data_03002818->pages[data_03002818->selection] = data_03002818->page;
                    data_03002818->entries[data_03002818->selection] = 2;
                    data_03002818->selection = func_0807A6CC();
                    if (data_03002818->entries[data_03002818->selection] > 1) {
                        data_03002818->page = data_03002818->pages[data_03002818->selection];
                        data_03002818->page.value = 0;
                        func_0807974C(data_03002818->selection, data_03002818->entries);
                        func_080799C0(data_03002818->selection,
                            data_03002818->page.context, &data_03002818->page.value);
                        func_0808A604(11, 5);
                        data_03002818->page.phase = 4;
                        data_0200F232 = 5;
                        data_0200F230 = 1;
                        *state = 26;
                        break;
                    }
                    data_03002818->page.value = 0;
                    func_0807974C(data_03002818->selection, data_03002818->entries);
                    func_080799C0(data_03002818->selection,
                        data_03002818->page.context, &data_03002818->page.value);
                    func_0808A604(11, 5);
                    data_03002818->page.phase = 1;
                } else if (data_03000000.pressed & 8) {
                    data_03002818->unknown_1d04 = 0;
                    func_08141540(0x6c);
                    data_0200F232 = 5;
                    func_0808A604(data_0200F232, 5);
                    data_0200F230 = 6;
                    *state = 25;
                } else if (data_03000000.pressed == 0x100) {
                    if (data_03002818->unknown_0c20) {
                        func_08141540(0x68);
                        if (data_03002818->count > 1) {
                            data_0200F231 = 3;
                        } else {
                            data_0200F231 = data_03002818->unknown_1d04 = 0;
                        }
                        data_03002818->unknown_1d04 = data_0200F231;
                        data_03002818->unknown_0c20 = 0;
                        data_03002818->unknown_0c38 = 0;
                        data_03002818->unknown_043a = 3;
                        data_0200F232 = 6;
                        func_0808A604(data_0200F232, 5);
                        data_0200F230 = 13;
                        *state = 25;
                    } else {
                        func_08141540(0x64);
                        if (data_03002818->count > 1) {
                            data_0200F231 = 8;
                            data_03002818->unknown_1d04 = data_0200F231;
                        } else {
                            /* Two stores to +0x1d04: 0x0807B468 and 0x0807B472. */
                            data_0200F231 = data_03002818->unknown_1d04 = 9;
                            data_03002818->unknown_1d04 = data_0200F231;
                        }
                        data_03002818->unknown_0c20 = 1;
                        data_03002818->unknown_0c38 = 1;
                        data_03002818->unknown_043a = 3;
                        func_0808EF4C();
                        data_03002818->page.phase = 5;
                        data_030009E0[4].x = 30;
                        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
                        func_0808A604(4, 3);
                        func_0808A604(5, 2);
                        data_03002818->unknown_042b = 10;
                        data_0200F232 = 6;
                        func_0808AA18(data_0200F232);
                        *state = 12;
                    }
                    break;
                }
            }
            if (result == 6) {
                func_0808CACC();
                func_0808A604(5, 2);
            }
        }
        break;
    case 28:
        if (data_03002818->timer)
            data_03002818->timer--;
        else
            *state = data_0200F230;
        break;
    case 17:
        if (data_030009E0[4].x > 30)
            *state = data_0200F230;
        else
            data_030009E0[4].x += 2;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 18:
        if (data_030009E0[4].x > 22)
            *state = data_0200F230;
        else
            data_030009E0[4].x += 2;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 6:
        if (data_03002818->unknown_044c == 0)
            data_03002818->selected_record =
                &g_state_02000080[data_03002818->selected_unit];
        data_03002818->selected_category =
            data_03002818->selected_record->flags & 0x1c;
        data_03002818->selected_category |= 1;
        if (data_03002818->page.value) {
            data_03002818->unit = *data_03002818->selected_record;
            func_080CB0D8(&data_03002818->unit, data_03002818->page.value,
                data_03002818->choice);
            func_080CA2E8(&data_03002818->unit);
            func_0807614C(&data_03002818->unit);
        } else {
            func_08075620(0, data_03002818->selected_record, 1, 1);
        }
        func_0808A604(3, 2);
        *state = 7;
        break;
    case 7:
        if (!(data_03000000.held & 8)) {
            data_03002818->unknown_1d04 = data_0200F231;
            func_0807B858();
            func_0808A604(3, 5);
            func_0808A604(5, 2);
            *state = 1;
        }
        break;
    case 26:
        func_08082AEC(0, 1);
        /* fall through: 0x0807B6C4 runs straight into case 25 */
    case 25:
        if (data_030009E0[data_0200F232].state == 0)
            *state = data_0200F230;
        break;
    case 12:
        if (data_030009E0[data_0200F232].state == 0) {
            data_030009E0[6].x = 31;
            *state = 11;
        }
        func_08082AEC(0, 1);
        break;
    case 11:
        func_08082AEC(0, 1);
        if (data_030009E0[6].x > 17) {
            data_030009E0[6].x -= 2;
            func_0808A604(6, 2);
        } else if (data_030009E0[6].x < 17) {
            data_030009E0[6].x += 2;
            func_0808A604(6, 2);
        } else {
            func_0808C9C4();
            data_030009E0[5].unknown_32 = 17;
            data_030009E0[11].unknown_32 = 17;
            func_0808A604(6, 2);
            *state = 1;
        }
        break;
    case 15:
        func_08082AEC(0, 1);
        if (data_030009E0[5].state == 0)
            *state = 13;
        break;
    case 13:
        func_08082AEC(0, 1);
        data_0200F232 = 5;
        data_030009E0[5].unknown_32 = 23;
        data_030009E0[11].unknown_32 = 22;
        func_0808A604(data_0200F232, 2);
        func_0808A604(2, 2);
        data_0200F230 = 14;
        *state = 26;
        break;
    case 14:
        func_08082AEC(0, 1);
        data_0200F232 = 4;
        data_030009E0[4].x = 24;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(data_0200F232, 2);
        data_0200F230 = 1;
        *state = 25;
        break;
    case 0xff:
        /* No code, but the tree shows the case: its root is 14, the eighth
         * of fifteen values (0x0807A7AC), and fourteen cases over 0..28
         * would have made a jump table.  0xff is the state stored at
         * 0x0807AB20 and 0x0807ADD0. */
        break;
    }
}
