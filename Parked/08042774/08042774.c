#include "ffta.h"

typedef struct {
    u16 id;
    u16 available;
    u16 quantity;
    u8 unknown_06[6];
    u16 extra;
    u8 kind;
    u8 unknown_0f[5];
} Item08042774;

typedef struct {
    u8 unknown_00[0x18];
    Item08042774 *items;
} Container08042774;

typedef struct {
    u8 unknown_00[0x16];
    u8 visible;
    u8 unknown_17;
    u16 total;
    u16 top;
    u8 unknown_1c[4];
} List08042774;

typedef struct {
    u8 unknown_00[0x11];
    u8 index;
    u8 unknown_12[2];
} Cursor08042774;

typedef struct {
    u32 words[5];
} Settings08042774;

typedef struct {
    u8 unknown_00[0x36];
    u8 cancel;
    u8 unknown_37;
    u16 extra;
    u8 flag;
    u8 unknown_3b[3];
    u16 direction;
    u16 quantity;
    u16 id;
    u16 kind;
    u8 unknown_46[2];
    Container08042774 *info;
    u8 unknown_4c[0x2c];
    List08042774 list;
    u8 cursor[0x14];
    Settings08042774 settings;
    u8 unknown_c0[8];
    Container08042774 *data;
} Record08042774;

typedef struct {
    u8 unknown_000[0x4a0];
    Settings08042774 saved;
    u8 mode;
    u8 unknown_4b5[0x49f];
    Record08042774 records[1];
} State08042774;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08042774;

extern Input08042774 data_03000000;
extern State08042774 *g_state_03002810;
extern u16 func_08017B68(List08042774 *, u32);
extern u16 func_08017B50(List08042774 *);
extern u8 func_08017A90(List08042774 *, u16);
extern void func_08017AF4(List08042774 *, s8, u8);
extern void func_08017E28(Settings08042774 *);
extern u8 func_080356A0(s32, u8);
extern void func_080426A4(s32, u16, s8, s32);
extern void func_08085374(void);
extern void func_08141540(s32);

/* 0x08042774..0x08042B70: 1020 bytes, 411 instructions. */
u8 func_08042774(s32 index)
{
    u16 down;
    s8 current;
    u8 next;

    if (data_03000000.pressed & 4) {
        s8 selected;
        selected = func_08017B68(&g_state_03002810->records[index].list,
                                (s8)((Cursor08042774 *)g_state_03002810->records[index].cursor)->index);
        g_state_03002810->records[index].extra =
            g_state_03002810->records[index].info->items[selected].extra;
        g_state_03002810->saved = g_state_03002810->records[index].settings;
        g_state_03002810->mode = func_080356A0(index, 0);
        g_state_03002810->records[index].flag = 0;
        return 9;
    }
    if (data_03000000.pressed & 1) {
        Container08042774 *data = g_state_03002810->records[index].data;
        s8 selection = ((Cursor08042774 *)g_state_03002810->records[index].cursor)->index;
        u16 selected = func_08017B68(&g_state_03002810->records[index].list, selection);
        if (data->items[selected].available) {
            g_state_03002810->records[index].quantity = data->items[selected].quantity;
            g_state_03002810->records[index].id = data->items[selected].id;
            g_state_03002810->records[index].kind = data->items[selected].kind;
            g_state_03002810->records[index].direction = 1;
            return 0xff;
        }
        func_08141540(0x6a);
    }
    if (data_03000000.pressed & 2) {
        g_state_03002810->records[index].direction = 2;
        g_state_03002810->records[index].cancel = 0xff;
        return 0xff;
    }
    down = data_03000000.repeated & 0x80;
    if (down) {
        g_state_03002810->records[index].direction = 0x80;
        func_08085374();
        current = ((Cursor08042774 *)g_state_03002810->records[index].cursor)->index;
        next = (u8)current + 1;
        if (data_03000000.held & 0x200) {
            u8 visible = g_state_03002810->records[index].list.visible;
            u16 top = g_state_03002810->records[index].list.top;
            u16 total = g_state_03002810->records[index].list.total;

            if (top + g_state_03002810->records[index].cursor[0x11] < total - 1) {
                if (visible + top < total) {
                    if (visible * 2 + top < total)
                        g_state_03002810->records[index].list.top = visible + top;
                    else
                        g_state_03002810->records[index].list.top =
                            (visible + top) - ((visible * 2 + top) - total);
                    func_08141540(0x6d);
                    func_08017E28(&g_state_03002810->records[index].settings);
                    return 5;
                } else {
                    if (visible > total)
                        next = total - 1;
                    else
                        next = visible - 1;
                }
            }
        }
        if ((s8)next < func_08017B50(&g_state_03002810->records[index].list)) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->records[index].list, (s8)current, 12);
            func_080426A4(index, 0x80, (s8)next, 0);
            return 3;
        } else if (func_08017A90(&g_state_03002810->records[index].list, 0x80)) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->records[index].list, (s8)current, 12);
            func_080426A4(index, 0x80, (s8)next, 1);
            return 4;
        }
    } else if (data_03000000.repeated & 0x40) {
        g_state_03002810->records[index].direction = 0x40;
        func_08085374();
        next = ((Cursor08042774 *)g_state_03002810->records[index].cursor)->index - 1;
        current = ((Cursor08042774 *)g_state_03002810->records[index].cursor)->index;
        if (data_03000000.held & 0x200) {
            u8 visible = g_state_03002810->records[index].list.visible;
            u16 top = g_state_03002810->records[index].list.top;
            u8 cursor = g_state_03002810->records[index].cursor[0x11];

            if (top == 0) {
                if (cursor != 0)
                    next = 0;
            } else {
                if (top - visible >= 0)
                    g_state_03002810->records[index].list.top = top - visible;
                else
                    g_state_03002810->records[index].list.top = 0;
                func_08141540(0x6d);
                func_08017E28(&g_state_03002810->records[index].settings);
                return 5;
            }
        }
        if ((s8)next < 0) {
            if (func_08017A90(&g_state_03002810->records[index].list, 0x40)) {
                func_08141540(0x6d);
                func_08017AF4(&g_state_03002810->records[index].list, (s8)current, 12);
                func_080426A4(index, 0x40, (s8)next, 1);
                return 4;
            }
        } else {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->records[index].list, (s8)current, 12);
            func_080426A4(index, 0x40, (s8)next, 0);
        }
    }
    return 3;
}
