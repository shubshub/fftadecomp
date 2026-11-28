#include "ffta.h"

/* One 27-byte row of g_table_08564670 (src/0803F6F8.c, src/080CF7F4.c).
 * The selection/y pairs are the arguments func_080354AC takes; bytes 4-6 hold
 * the first pair as two eight-bit fields from bit 36 (ldrb/lsrs #4,
 * ldrb/ands #15/lsls #4 at 0x0803E88A).  item/count are what the row costs
 * and reward/quantity what it gives: 0 is nothing, 0x8000 is money in units
 * of 200, 0x4000 and ids from 0x178 up select the other two item lists. */
typedef struct {
    u8 name_index;
    u16 mode : 1;
    u16 unknown_09 : 1;
    u16 type : 3;
    u16 value : 8;
    u16 unknown_15 : 3;
    u16 unknown_24 : 12;
    u16 first_selection : 8;
    u16 first_y : 8;
    u16 unknown_52 : 4;
    u16 item;
    u8 count;
    u16 reward;
    s8 quantity;
    u8 flags;
    u8 second_selection;
    u8 second_y;
    u8 third_selection;
    u8 third_y;
    u8 unknown_12[9];
} __attribute__((packed)) SelectionRecord;

/* The six-byte entries at +0x224 of the context's source, as
 * src/0804409C.c declares them. */
typedef struct {
    u8 slot : 3;
    u8 unknown_03 : 5;
    u8 unknown_01;
    u8 selection : 5;
    u8 unknown_15 : 2;
    u8 unknown_17 : 1;
    u8 unknown_03_byte;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) EntrySpecification;

typedef struct {
    u8 unknown_000[0x224];
    EntrySpecification entries[5];
} Source;

typedef struct {
    u8 unknown_00[0x20];
    u16 id;
    u16 unknown_22;
    u8 unknown_24[0x84];
    u8 selector;
    u8 mode;
    u8 entry;
    u8 unknown_AB[2];
    u8 previous_mode;
} Window;

/* Laid out as src/0803F6F8.c declares it. */
typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u16 choice;
    u8 unknown_12[0xBA];
} MenuSlot;

typedef struct {
    Source *source;
    Window *window;
    u8 unknown_008[0x95];
    u8 timer;
    u8 unknown_09E[0x4B8 - 0x9E];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4C4[0x984 - 0x4C4];
    MenuSlot slots[3];
    u8 unknown_BE8[0xC0C - 0xBE8];
    s32 amount;
} MenuContext;

/* The 0x4C-byte renderer entry (src/0803DE40.c, src/0803A07C.c). */
typedef struct {
    u8 active;
    u8 unknown_01;
    u8 mode : 3;
    u8 unknown_02 : 5;
    u8 unknown_03[2];
    u8 enabled;
    u8 unknown_06[0x46];
} Renderer;

typedef struct {
    u16 held;
    u16 pressed;
} KeyState;

/* As src/0805ADA4.c types g_state_020020D0. */
typedef struct {
    u8 unknown_00[8];
    u32 amount;
    u8 unknown_0C[2];
    u16 item;
} MessageArguments;

typedef struct {
    u8 unknown_0000[0x1F3C];
    u16 values[20];
    u32 money;
} GameState;

extern MenuContext *g_state_03002810;
extern GameState g_state_02000000;
extern MessageArguments g_state_020020D0;
extern KeyState data_03000000;
extern Renderer data_030009E0[];
extern u8 data_0201F498;
extern u8 data_0201F499;
extern u8 data_0201F49A;
extern const SelectionRecord g_table_08564670[];
extern const u16 *const data_085668B0[];

/* u16, where src/08011860.c returns u32: all four tests narrow the result
 * (lsls #16 at 0x0803EE34, 0x0803F424, 0x0803F480 and 0x0803F498). */
extern u16 func_08011860(void);
extern void func_08011B30(u8 kind, u16 entry);
extern void func_08011C60(void);
extern void func_08013364(void);
extern void func_08031708(u8 value);
extern void func_080354AC(u8 x, u8 y, u16 selection);
extern void func_080359E4(s32 index, u8 value);
extern void func_08035C48(void);
extern s32 func_080385A8(u16 value, s32 limit);
extern s32 func_080385E4(u16 value);
extern s32 func_080386C8(u16 value, s32 limit);
extern u32 func_08038704(u16 value);
extern void func_08038820(void);
extern s32 func_08038858(u16 id, u8 kind, u16 quantity);
extern s32 func_0803890C(void);
extern void func_0803E078(s32 inset);
extern void func_0803E1C0(u16 id, u8 count, const u16 *label, u32 option);
extern void func_0803E2E0(u32 value, const u16 *label);
extern int func_0808A604(int index, u16 mode);
extern s32 func_080CA9E8(u16 identifier, u8 quantity);
extern u8 func_080CB2B4(u32 identifier);
extern void func_08141540(u16 song_id);
extern void func_08141570(s32 player_id, u16 song_id);

/* Complete target: [0x0803E3B4, 0x0803F650), 4764 bytes, 1404 instructions
 * (the index row's 2382 is half the byte count). */
void func_0803E3B4(u32 index)
{
    switch (g_state_03002810->slots[index].state) {
    case 0:
        data_0201F499 = 0;
        g_state_03002810->active[index] = 0;
        if (data_030009E0[3].mode)
            break;
        func_08031708(0x42);
        g_state_03002810->slots[index].state = 1;
        break;
    case 1: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        func_08141570(1, 0xA6);
        if (row->item != 0) {
            if (row->item == 0x8000) {
                g_state_020020D0.amount = row->count * 200;
            } else {
                g_state_020020D0.item = row->item;
                g_state_020020D0.amount = row->count;
            }
        }
        data_0201F499 = 1;
        func_080354AC(12, row->first_y, row->first_selection | 0x8000);
        func_080359E4(1, 15);
        data_0201F498 = 9;
        g_state_03002810->slots[index].state = 2;
        break;
    }
    case 9:
        if (g_state_03002810->slots[1].state != 0xFF)
            break;
        func_08141540(0x64);
        if (g_state_03002810->slots[1].choice == 0) {
            func_08013364();
            data_0201F498 = 10;
            g_state_03002810->slots[index].state = 2;
        } else if (g_state_03002810->slots[1].choice == 1) {
            func_08013364();
            data_0201F498 = 11;
            g_state_03002810->slots[index].state = 2;
        }
        break;
    case 11:
        g_state_03002810->window->mode = 5;
        data_0201F498 = 0x1D;
        g_state_03002810->slots[index].state = 2;
        break;
    case 10: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        u16 id;
        u8 count;
        if (row->item == 0) {
            func_08013364();
            data_0201F498 = 0x14;
            g_state_03002810->slots[index].state = 2;
        } else if (row->item > 0x7FFF) {
            if (g_state_02000000.money >= row->count * 200) {
                func_0803E078(6);
                func_0803E2E0(row->count * 200, data_085668B0[47]);
                data_0201F498 = 0x17;
                g_state_03002810->slots[index].state = 0x17;
            } else {
                func_08013364();
                data_0201F498 = 0x11;
                g_state_03002810->slots[index].state = 2;
            }
        } else if (row->item > 0x3FFF) {
            /* The mask is applied to the item already compared, as case 12
             * masks its id (ands r5, r1 at 0x0803EA5C). */
            id = row->item;
            id &= 0x7FFF;
            count = func_08038704(id);
            if (count >= row->count) {
                /* BUG: count is still the number held, so func_080386C8
                 * clears every copy instead of the row's count, which the
                 * message below reports and the plain-item branch removes
                 * (func_080CA9E8); only a row asking for none is changed to
                 * one (0x0803EA6E).  No row of g_table_08564670 costs an
                 * item of this list, so this copy never runs. */
#ifdef BUGFIX
                count = row->count;
#endif
                if (row->count == 0)
                    count = 1;
                func_080386C8(id, count);
                func_08031708(0x77);
                func_08013364();
                func_0803E078(0);
                func_0803E1C0(id, row->count, data_085668B0[47], 2);
                func_08141540(0x65);
                data_030009E0[5].enabled = 1;
                func_0808A604(5, 11);
                data_0201F498 = 0x14;
                g_state_03002810->slots[index].state = 2;
            } else {
                func_08013364();
                data_0201F498 = 0x11;
                g_state_03002810->slots[index].state = 2;
            }
        } else if (row->item >= 0x178) {
            /* 0x178 is the first id of this list; the ROM adds 0x0000FE89
             * (pool word 0x0803EB90), a u16 sum, not 0xFFFFFE89. */
            id = row->item;
            id = (id & 0x3FFF) - 0x178 + 1;
            count = func_080385E4(id);
            if (count >= row->count) {
                /* BUG: as in the branch above (0x0803EB2E), the limit is the
                 * number held, not the row's count.  func_080385E4 counts only
                 * free copies (holder 0), but func_080385A8 clears entries by
                 * id alone, in table order, attached or free: as many as there
                 * are free copies.  With none attached that is every copy; an
                 * attached copy early in the list can go in place of a free
                 * one, which BUGFIX does not change (docs/bugs/0803E3B4,
                 * section 3).  Rows 44 and 46 cost one copy of list items 0x77
                 * and 0x34; holding two free copies loses both. */
#ifdef BUGFIX
                count = row->count;
#endif
                if (row->count == 0)
                    count = 1;
                func_080385A8(id, count);
                func_08031708(0x77);
                func_08013364();
                func_0803E078(0);
                func_0803E1C0(id, row->count, data_085668B0[47], 1);
                func_08141540(0x65);
                data_030009E0[5].enabled = 1;
                func_0808A604(5, 11);
                data_0201F498 = 0x14;
                g_state_03002810->slots[index].state = 2;
            } else {
                func_08013364();
                data_0201F498 = 0x11;
                g_state_03002810->slots[index].state = 2;
            }
        } else {
            count = func_080CB2B4(row->item);
            if (count >= row->count) {
                func_080CA9E8(row->item, row->count);
                func_08031708(0x77);
                func_08013364();
                func_0803E078(0);
                func_0803E1C0(row->item, row->count, data_085668B0[47], 0);
                func_08141540(0x65);
                data_030009E0[5].enabled = 1;
                func_0808A604(5, 11);
                data_0201F498 = 0x14;
                g_state_03002810->slots[index].state = 2;
            } else {
                func_08013364();
                data_0201F498 = 0x11;
                g_state_03002810->slots[index].state = 2;
            }
        }
        break;
    }
    case 17: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        func_080354AC(14, row->third_y, row->third_selection | 0x8000);
        data_0201F498 = 0x12;
        g_state_03002810->slots[index].state = 2;
        break;
    }
    case 18:
        g_state_03002810->timer = 60;
        data_0201F498 = 0x13;
        g_state_03002810->slots[index].state = 0x1E;
        break;
    case 20: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        func_080354AC(13, row->second_y, row->second_selection | 0x8000);
        g_state_03002810->timer = 30;
        data_0201F498 = 0x15;
        g_state_03002810->slots[index].state = 4;
        break;
    }
    case 21: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        if (row->item == 0) {
            g_state_03002810->slots[index].state = 0xC;
            break;
        }
        func_08141540(0x69);
        data_0201F49A = 5;
        /* Indexed through the renderer number just stored: base + 0x17C,
         * then strb [r0, #5] (0x0803ED84), not the folded base + 0x181. */
        data_030009E0[data_0201F49A].enabled = 1;
        func_0808A604(5, 12);
        data_0201F498 = 0xC;
        g_state_03002810->slots[index].state = 6;
        break;
    }
    case 23: {
        s32 *amount = &g_state_03002810->amount;
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        *amount = row->count * 200;
        func_08141540(0x65);
        func_08031708(0x77);
        func_0808A604(5, 2);
        func_080354AC(13, row->second_y, row->second_selection | 0x8000);
        data_0201F498 = 0x18;
        g_state_03002810->slots[index].state = 0x1A;
        break;
    }
    case 24:
        if (func_08011860())
            g_state_03002810->slots[index].state = 0xC;
        break;
    case 26: {
        s32 *amount = &g_state_03002810->amount;
        s32 size = *amount;
        s32 step;
        if (size < 0)
            size = -size;
        if (size > 10000)
            step = 100;
        else
            step = 50;
        if (*amount > 0) {
            if (*amount % 100 == 0)
                func_08141540(0x73);
            *amount -= step;
            g_state_02000000.money -= step;
            func_08035C48();
        } else {
            g_state_03002810->timer = 30;
            g_state_03002810->slots[index].state = 0x1C;
        }
        break;
    }
    case 27: {
        s32 *amount = &g_state_03002810->amount;
        s32 size = *amount;
        s32 step;
        if (size < 0)
            size = -size;
        if (size > 10000)
            step = 100;
        else
            step = 50;
        if (*amount > 0) {
            if (*amount % 100 == 0)
                func_08141540(0x73);
            *amount -= step;
            g_state_02000000.money += step;
            if (g_state_02000000.money > 99999999)
                g_state_02000000.money = 99999999;
            func_08035C48();
        } else {
            g_state_03002810->timer = 30;
            g_state_03002810->slots[index].state = 0x1C;
        }
        break;
    }
    case 28:
        if (g_state_03002810->timer-- <= 0 || (data_03000000.pressed & 1)) {
            func_08141540(0x69);
            func_0808A604(5, 1);
            g_state_03002810->slots[index].state = data_0201F498;
        }
        break;
    case 12: {
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        if (row->reward == 0) {
            g_state_03002810->slots[index].state = 0x10;
        } else if (row->reward == 0x8000) {
            s32 *amount = &g_state_03002810->amount;
            *amount = row->quantity * 200;
            data_0201F498 = 0x19;
            func_08141540(0x65);
            func_0803E078(6);
            func_08031708(0x77);
            if (*amount > 0) {
                func_0803E2E0(*amount, data_085668B0[48]);
                g_state_03002810->slots[index].state = 0x1B;
            } else {
                *amount = -*amount;
                func_0803E2E0(*amount, data_085668B0[47]);
                g_state_03002810->slots[index].state = 0x1A;
            }
            func_0808A604(5, 2);
        } else {
            u16 id = row->reward;
            s32 kind;
            if (id & 0x4000) {
                kind = 2;
                id &= 0xFFF;
            } else if (id >= 0x178) {
                kind = 1;
                id = id - 0x178 + 1; /* pool word 0x0000FE89 at 0x0803F078 */
            } else {
                kind = 0;
            }
            func_0803E078(4);
            func_08031708(0x77);
            func_0803E1C0(id, row->quantity, data_085668B0[48], kind);
            func_08141540(0x65);
            data_030009E0[5].enabled = 1;
            func_0808A604(5, 11);
            func_08038820();
            func_08038858(id, kind, row->quantity);
            g_state_03002810->timer = 120;
            data_0201F498 = 0x16;
            g_state_03002810->slots[index].state = 5;
        }
        break;
    }
    case 22:
        if (func_0803890C()) {
            func_08141540(0x69);
            data_030009E0[5].enabled = 1;
            func_0808A604(5, 12);
            g_state_03002810->slots[index].state = 0x10;
        } else {
            func_08141540(0x69);
            data_030009E0[5].enabled = 1;
            func_0808A604(5, 12);
            func_08013364();
            data_030009E0[2].mode = 6;
            data_0201F498 = 0x10;
            g_state_03002810->slots[index].state = 0xE;
        }
        break;
    case 25:
        g_state_03002810->slots[index].state = 0x10;
        break;
    case 13:
        if (data_03000000.pressed & 1) {
            func_08141540(0x64);
            func_08013364();
            func_08011B30(4, 0x50);
            data_0201F498 = 0xFD;
            g_state_03002810->slots[index].state = 2;
        }
        break;
    case 16: {
        EntrySpecification *entries = g_state_03002810->source->entries;
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        if ((row->flags & 0x30) == 0x20) {
            g_state_03002810->window->mode = 6;
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            data_0201F498 = 0x1F;
            g_state_03002810->slots[index].state = 2;
        } else if ((row->flags & 0x30) == 0x30) {
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            g_state_03002810->window->mode = 4;
            data_0201F498 = 0x1D;
            g_state_03002810->slots[index].state = 2;
        } else {
            g_state_03002810->slots[index].choice = 0;
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            g_state_03002810->window->mode = 6;
            g_state_03002810->window->previous_mode =
                g_state_03002810->window->mode;
            g_state_03002810->slots[index].state = 0x1F;
        }
        break;
    }
    case 19: {
        EntrySpecification *entries = g_state_03002810->source->entries;
        const SelectionRecord *row =
            &g_table_08564670[g_state_03002810->window->selector];
        if ((row->flags & 0xC0) == 0x80) {
            g_state_03002810->window->mode = 7;
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            data_0201F498 = 0x1F;
            g_state_03002810->slots[index].state = 2;
        } else if ((row->flags & 0xC0) == 0xC0) {
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            g_state_03002810->window->mode = 5;
            data_0201F498 = 0x1D;
            g_state_03002810->slots[index].state = 2;
        } else {
            g_state_03002810->slots[index].choice = 0;
            g_state_03002810->window->id =
                entries[g_state_03002810->window->entry - 1].id;
            g_state_03002810->window->unknown_22 = 0xFFFF;
            g_state_03002810->window->mode = 6;
            g_state_03002810->window->previous_mode =
                g_state_03002810->window->mode;
            g_state_03002810->slots[index].state = 0x1F;
        }
        break;
    }
    case 14:
        if (func_08011860()) {
            func_080359E4(1, 0x11);
            g_state_03002810->slots[index].state = 0xF;
        }
        break;
    case 15:
        if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[index].state = data_0201F498;
        break;
    case 2:
        if (func_08011860())
            g_state_03002810->slots[index].state = data_0201F498;
        break;
    case 4:
        if (func_08011860()) {
            if (g_state_03002810->timer == 0 || (data_03000000.pressed & 1)) {
                if (data_03000000.pressed & 1)
                    func_08141540(0x69);
                g_state_03002810->slots[index].state = 0x1E;
            } else {
                g_state_03002810->timer--;
            }
        }
        break;
    case 6:
        if (data_030009E0[data_0201F49A].active == 0)
            g_state_03002810->slots[index].state = data_0201F498;
        break;
    case 5:
        if (data_030009E0[data_0201F49A].active)
            break;
        /* fall through */
    case 30:
        if (g_state_03002810->timer > 30) {
            g_state_03002810->timer--;
            break;
        }
        if (g_state_03002810->timer-- <= 0 || (data_03000000.pressed & 1)) {
            if (data_03000000.pressed & 1)
                func_08141540(0x69);
            g_state_03002810->slots[index].state = data_0201F498;
        }
        break;
    case 29:
        g_state_03002810->slots[index].choice = 1;
        func_08013364();
        data_0201F498 = 0xFD;
        g_state_03002810->slots[index].state = 2;
        break;
    case 31:
        func_08013364();
        data_0201F498 = 0xFD;
        g_state_03002810->slots[index].state = 2;
        break;
    case 0xFD:
        if (data_030009E0[5].active == 0) {
            func_08031708(0xFE);
            g_state_03002810->slots[index].state = 0xFF;
        }
        break;
    case 0xFF:
        g_state_03002810->closed[index] = 0;
        break;
    }
    if (data_0201F499)
        func_08011C60();
}
