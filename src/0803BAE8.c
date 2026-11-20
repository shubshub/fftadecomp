#include "ffta.h"

/* Complete target: [0x0803BAE8, 0x0803C21C), 1844 bytes, 723 instructions. */

/* Byte 0 as src/08043468.c declares it; byte 0x1D is the byte
 * src/0803D290.c reads from the same object. */
typedef struct {
    u8 unknown_00 : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[0x1C];
    u8 name;
} MenuWindow0803BAE8;

/* Laid out as src/08043468.c declares it, with the u16 at 0x12
 * (ldrh at 0x0803C03A). */
typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u16 selection;
    u16 kind;
    u8 unknown_14[0x84];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot0803BAE8;

typedef struct {
    void *owner;
    MenuWindow0803BAE8 *window;
    u8 unknown_008[0x88];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_098[0x4B8 - 0x98];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x674 - 0x4C4];
    u8 field_674;
    u8 unknown_675[0x984 - 0x675];
    MenuSlot0803BAE8 slots[3];
    u8 unknown_be8[0xC4C - 0xBE8];
    u8 text_state[1];
} MenuContext0803BAE8;

/* The 0x4C-byte renderer entry, as src/0803F6F8.c declares it.  Byte 2 holds
 * the three-bit mode src/0803A07C.c names (0x0803C066-0x0803C084) and the
 * top bit src/080423D4.c names (0x0803BB48, 0x0803BB5C). */
typedef struct {
    u8 busy;
    u8 field_01;
    u8 mode : 3;
    u8 unknown_02 : 4;
    u8 visible : 1;
    u8 unknown_03[2];
    u8 status;
    u8 unknown_06[8];
    u16 border_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[2];
    u8 source_width;
    u8 source_height;
    u8 unknown_2E[6];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 field_48;
    u8 field_49;
    u8 field_4A;
    u8 field_4B;
} TileWindow0803BAE8;

/* As src/08043468.c declares it. */
typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage0803BAE8;

/* As src/0803A07C.c declares it. */
typedef struct {
    u16 held;
    u16 pressed;
} KeyState0803BAE8;

/* As src/08071888.c declares it. */
typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display0803BAE8;

extern MenuContext0803BAE8 *g_state_03002810;
extern TileWindow0803BAE8 data_030009E0[];
extern TileStorage0803BAE8 data_03002740;
extern KeyState0803BAE8 data_03000000;
extern Display0803BAE8 data_03000E30;
extern u8 data_02003CB0[];
extern u8 data_0201F480;
extern u8 data_0201F481;
extern u8 data_0201F482;
extern u8 data_06009960[];
extern u8 data_06009DE0[];
extern const u8 *const data_085668B0[];

extern s32 func_0803D094(void *list, u8 *result);
extern TileWindow0803BAE8 *func_0808A268(u32 index, u8 mode,
    u16 *first_resource, u16 *second_resource, u16 *first_tiles,
    u16 *second_tiles, u16 *first_output, u16 *second_output,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08037C84(u32 slot, void *resource, u32 renderer, u32 column,
                         u32 row, u8 mode, u32 kind, u32 enabled);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B950(u16 *destination, u16 tile, u16 width);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_0803D290(void);
extern void func_08141540(u16 song_id);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
                         u16 count, u16 flags);
extern u32 func_0808A604(u32 renderer, u16 command);
extern void func_0804C7A0(void *entries, u16 index);
extern void func_08042148(s32 slot);
extern void func_080372FC(u32 x, u32 y, u8 choice, u8 slot);
extern void func_080359E4(s32 index, u8 value);
/* Word results: the one caller of func_080423D4 (0x0803BB56, here) and
 * the three of func_080421A4 (0x0803B2C0 and 0x0803B99E in func_0803AE80,
 * 0x0803C16A here) use the returned r0 with no zero extension, and a u8
 * return here adds lsls/lsrs #24 after each call. */
extern u32 func_080423D4(u32 index);
extern u32 func_080421A4(u32 index);
extern void func_080358B0(u32 enabled);

/* The dispatch (0x0803BB0A-0x0803BBDE) is a compare tree balanced over
 * fourteen single case values: it splits at 6, then at 2 and 10, then at 4,
 * 8 and 0xFD.  Below 10, a value above 8 goes straight to the exit
 * (0x0803BB9C-0x0803BBA0) and 7 is reached with no compare, so the node
 * between 8 and 10 is the value 9, a case with an empty body.  Below 0xFD
 * the low side goes to the exit with no compare (0x0803BBD2-0x0803BBD6):
 * one more empty case, whose compare is deleted because it branches to the
 * same exit.  Its value lies in 11..0xFC (0xFE adds a compare under 0xFD; a
 * range there, or a second value, moves the root to 7) and the ROM does not
 * say which.  11 is a choice, as src/08084DA0.c and src/08135890.c choose
 * the value of such a case: it continues the numbering from 0, as other
 * switches on this state byte do (src/0803D550.c: 0-3, 0xFD, 0xFF;
 * src/0803F6F8.c: 0-4, 0xFF), and pairs with 10 as 9 does with 8. */
void func_0803BAE8(u32 index)
{
    switch (g_state_03002810->slots[index].state) {
    case 0: {
        /* The buffer address is loaded again at each use (0x0803BD40,
         * 0x0803BD6E); case 2 holds the same local in r7 (0x0803BEC4). */
        u8 *buffer = data_02003CB0;
        s32 found;
        u16 clear;

        g_state_03002810->field_674 = 0;
        found = func_0803D094(g_state_03002810->slots[index].source,
                              &data_0201F482);
        data_030009E0[4].visible = 0;
        g_state_03002810->active[index] = 0;
        g_state_03002810->window->flag_40 = 0;
        func_0808A268(4, 12, g_state_03002810->second_resource,
            g_state_03002810->first_resource, data_03002740.tiles,
            data_03002740.tiles + 0x134, 0, 0, 4, 2, 22, 14, 4, 2, 22, 14,
            22, 14);
        data_030009E0[4].x = 4;
        data_030009E0[4].y = 2;
        data_030009E0[4].border_tile = 0xEB;
        data_030009E0[4].field_01 = 0;
        data_030009E0[4].field_48 = 1;
        data_030009E0[4].field_49 = 1;
        data_030009E0[4].field_4A = 16;
        data_030009E0[4].field_4B = 7;
        clear = 0;
        func_0814186C(&clear, data_06009960, 0x01001400);
        func_08037C84(index, g_state_03002810->slots[index].source,
                      4, 0, 0, 0, 0, 0);
        func_0808B950(func_0808B8E4(4, 1, 0, 4), 0xC050,
                      data_030009E0[4].width);
        func_08016344(data_030009E0[4].second_plane,
            data_030009E0[4].width, data_030009E0[4].height,
            0xC0, data_030009E0[4].width, 5, 12);
        func_08016560(data_030009E0[4].first_plane, 22, 14, 0xC0, 22, 1, 10);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(buffer, 0x3E, 0x12), 1);
        if (data_0201F482) {
            func_08035678(0xC044, func_0808B8E4(4, 1, 17, 1),
                          func_08018524(buffer, 0x44, 0x15), 1);
        }
        func_0803D290();
        if (found) {
            g_state_03002810->slots[index].state = 5;
        } else {
            func_08141540(0x65);
            func_08015110(g_state_03002810->text_state, data_06009DE0,
                          data_085668B0[39], 0, 1);
            func_0808B7C0(4, func_0808B8E4(4, 1, 1, 5), 0xEB, 16, 0xC000);
            /* The renderer is addressed through the index just stored:
             * entry 4 is formed first and the status offset is applied at
             * the store (0x0803BE20-0x0803BE28), and the index byte is read
             * back for the call (0x0803BE2A). */
            data_0201F480 = 4;
            data_030009E0[data_0201F480].status = 3;
            func_0808A604(data_0201F480, 11);
            data_0201F481 = 1;
            g_state_03002810->slots[index].state = 6;
        }
        break;
    }
    case 1:
        if (data_03000000.pressed & 3) {
            if (data_03000000.pressed & 1)
                func_08141540(100);
            else
                func_08141540(0x69);
            func_0804C7A0(data_03000E30.entries, 3);
            g_state_03002810->slots[index].state = 0xFD;
            data_030009E0[4].status = 3;
            func_0808A604(4, 12);
        }
        break;
    case 2: {
        u8 *buffer = data_02003CB0;
        u16 clear;

        clear = 0;
        func_0814186C(&clear, data_06009960, 0x01001400);
        func_0803D290();
        func_08042148(index);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(buffer, 0x3E, 0x12), 1);
        func_080372FC(0x26, 0x30, g_state_03002810->window->name, 0);
        if (data_0201F482) {
            func_08035678(0xC044, func_0808B8E4(4, 1, 17, 1),
                          func_08018524(buffer, 0x44, 0x15), 1);
        }
        func_0808A604(4, 2);
        g_state_03002810->slots[index].state = 3;
        break;
    }
    case 8:
        func_0804C7A0(data_03000E30.entries, 3);
        func_080359E4(1, 13);
        g_state_03002810->slots[index].state = 4;
        g_state_03002810->slots[index].buttons = 0;
        break;
    case 9: /* empty: proved by the decision tree above */
        break;
    case 10:
        func_0804C7A0(data_03000E30.entries, 3);
        func_080359E4(1, 14);
        g_state_03002810->slots[index].state = 4;
        g_state_03002810->slots[index].buttons = 0;
        break;
    case 11: /* empty, value chosen: see the note on the decision tree */
        break;
    case 3:
        data_030009E0[4].visible = 1;
        if (func_080423D4(index) == 0xFF) {
            data_030009E0[4].visible = 0;
            g_state_03002810->slots[index].result = 6;
            g_state_03002810->slots[index].state = 0xFF;
        } else if (g_state_03002810->slots[index].buttons & 1) {
            data_030009E0[4].visible = 0;
            func_08141540(100);
            func_0804C7A0(data_03000E30.entries, 3);
            /* As in case 0, the status offset is applied at the store
             * (0x0803C01E-0x0803C026).  Unlike case 0, the index byte is
             * not read back for the call, which takes a constant 4
             * (0x0803C028); a literal 4 here gives the same bytes. */
            data_0201F480 = 4;
            data_030009E0[data_0201F480].status = 3;
            func_0808A604(data_0201F480, 12);
            if (g_state_03002810->slots[index].kind == 1
             || (g_state_03002810->slots[index].kind >= 8
              && g_state_03002810->slots[index].kind <= 11)) {
                g_state_03002810->window->flag_20 = 0;
                g_state_03002810->window->flag_40 = 0;
                data_030009E0[3].mode = 6;
                data_030009E0[2].mode = 6;
                data_0201F481 = 10;
                g_state_03002810->slots[index].state = 7;
            } else {
                data_0201F481 = 8;
                g_state_03002810->slots[index].state = 7;
            }
        } else if (g_state_03002810->slots[index].buttons & 2) {
            data_030009E0[4].visible = 0;
            func_08141540(0x69);
            func_0804C7A0(data_03000E30.entries, 3);
            g_state_03002810->slots[index].state = 0xFD;
            data_030009E0[4].status = 3;
            func_0808A604(4, 12);
        } else if (g_state_03002810->slots[index].result == 3) {
            func_0808A604(4, 2);
        }
        break;
    case 4:
        if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[index].state = 2;
        break;
    case 0xFD:
        if (!data_030009E0[4].busy)
            g_state_03002810->slots[index].state = 0xFF;
        break;
    case 5:
        if (func_080421A4(index) == 3) {
            data_030009E0[4].status = 3;
            func_0808A604(4, 11);
            data_0201F480 = 4;
            data_0201F481 = 3;
            g_state_03002810->slots[index].state = 6;
        }
        break;
    case 6:
        if (!data_030009E0[data_0201F480].busy) {
            func_080372FC(0x26, 0x30, g_state_03002810->window->name, 0);
            g_state_03002810->slots[index].state = data_0201F481;
        }
        break;
    case 7:
        if (!data_030009E0[data_0201F480].busy)
            g_state_03002810->slots[index].state = data_0201F481;
        break;
    case 0xFF:
        g_state_03002810->window->flag_40 = 1;
        func_080358B0(1);
        g_state_03002810->closed[index] = 0;
        break;
    }
}
