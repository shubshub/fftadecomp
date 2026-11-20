/* Complete target: [0x08052870, 0x080530A0), 2096 bytes. */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 scroll;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
    u8 unknown_11[3];
} ScrollArrows;

/* The ROM never folds a cursor member into the context offset: every read of
 * the row first forms the cursor's own address, base + 0xD3C, and then loads
 * the byte at +0x11 (0x08052C46, 0x08052C80, 0x08052CC6, 0x08052CFC,
 * 0x08052D48), while the list's scroll position right beside it is always
 * the single folded offset 0xD36.  The cursor is therefore reached as a
 * pointer wherever it is named, which is what an array member decays to. */
typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuControls controls[1];
    ScrollArrows arrows;
    u8 unknown_74[0x188];
} MenuWindow;

typedef struct {
    u8 unknown_00[0x74];
    u8 buffer[0xA0];
} InfoWindow;

typedef struct {
    u8 unknown_00[0x74];
    u8 buffer[0x138];
} TotalWindow;

typedef struct {
    u8 *state;
    u32 next_state;
    u32 selection;
} TransitionRequest;

typedef struct {
    void (*handler)(TransitionRequest *request);
    TransitionRequest *request;
    u16 count;
} DeferredAction;

typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0x180];
    u8 phase;
    u8 saved_state;
    u8 unknown_0CD6[2];
    Table runner;
    u8 unknown_0CE8[8];
    MenuWindow menu;
    InfoWindow item;
    InfoWindow quantity;
    TotalWindow totals;
    u8 message[0x7A0];
    u8 text_state[0x290];
    DeferredAction deferred;
    u8 unknown_1CFC[0x18];
    TransitionRequest transition;
    u8 unknown_1D20[0x24];
    u8 selection;
    u8 unknown_1D45;
    u8 item_index;
    u8 item_count;
    u8 active[20];
    u8 active_index;
    u8 unknown_1D5D[3];
    u8 animation[0x1C];
} MenuContext;

typedef struct {
    u8 unknown_0000[0x1F3C];
    u16 entries[20];
    u8 unknown_1F64[0xF00];
    u8 item_types[20];
} GlobalState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

extern MenuContext *data_0200F428;
extern InputState data_03000000;
extern GlobalState g_state_02000000;
extern GraphicsState data_030008B0;
extern u8 data_03000990[];
extern const u16 data_0852A212[];
extern const u8 data_08422764[];
extern const u8 data_0841CE18[];

extern u8 func_080CCA80(void);
extern u8 func_0802B548(void *window);
extern void func_0802B53C(void *window, u8 mode);
extern void func_0802B554(void *window, u8 message);
extern void func_0802A1FC(void *window, u8 x, u8 y, u8 width, u8 height,
                          u16 tile, u8 enabled);
extern void func_0802B368(void *window, u8 *text, u8 first, u8 second);
extern void func_0805391C(InfoWindow *window, u8 *buffer, u16 tile,
                          u8 x, u8 y);
extern void func_08053AA0(InfoWindow *window, u8 *buffer, u16 tile,
                          u8 x, u8 y);
extern void func_08053BE0(TotalWindow *window, u8 *buffer, u16 tile,
                          u8 x, u8 y);
extern void func_0802A424(u8 x, u8 y, u8 width, u8 height);
extern u8 func_08017180(void *window);
extern void func_080539B4(InfoWindow *window, u8 *text_state, u16 item);
extern u8 func_080CC218(u16 item);
extern void func_08053B34(InfoWindow *window, u8 *text_state, u8 quantity);
extern void func_080535BC(void);
extern void func_08053568(u8 *count, u8 *total);
extern void func_08053C74(TotalWindow *window, u8 *text_state, u8 count,
                          u8 total, u8 rebuild);
extern void func_08053348(u16 scroll, u16 row);
extern void func_08051084(TransitionRequest *request);
extern void func_0802B3A8(void *animation, const void *frames,
                          const u8 *script, u16 index, u8 value);
extern void *func_0802B3D4(void *animation);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_080530A0(u8 *state);
extern void func_08013390(void *window);
extern void func_08019A8C(void *window, u16 value, GraphicsState *graphics,
                          u8 *scratch);
extern void func_080543DC(MenuControls *controls, u8 row);
extern void func_08141540(u16 sound);
extern u8 func_080543CC(MenuList *list, u8 row);
extern void func_080534F4(void);
extern void func_0802B108(MenuList *list);
extern void func_080531F0(void);
extern void func_08053FE0(MenuWindow *window, void (*scroll)(void *),
                          void *scroll_context, u8 row_count,
                          DeferredAction *bindings, u8 binding_count);
extern void func_080541B0(ScrollArrows *arrows, MenuControls *controls);
extern void func_08016234(void *window);
extern s8 func_08013380(void);
extern void func_08141570(s32 player, u16 sound);
extern void func_08051048(void);
extern void func_080CC2B4(void);
extern void func_080CCAAC(u16 item);
extern void func_080CC300(void);
extern void func_0802A290(void *window, u8 close);
extern u16 func_08011860(void);
extern void func_08051DB4(u8 index, u8 *state);

void func_08052870(u8 index, u8 *state)
{
    u8 count;
    u8 total;
    u8 changed;
    s8 selected;

    switch (*state) {
    case 0:
        if (func_080CCA80() == 0) {
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message, 0x70);
            *state = 1;
        } else {
            *state = 20;
        }
        break;
    case 1:
        if (func_0802B548(data_0200F428->message) == 5 &&
            (data_03000000.pressed & 1))
            *state = 255;
        break;
    case 20:
        func_0802A1FC(&data_0200F428->menu, 2, 5, 15, 15, 0xC0, 1);
        func_0802B368(&data_0200F428->menu, data_0200F428->text, 0, 10);
        func_0805391C(&data_0200F428->item, data_0200F428->item.buffer,
                      ((u8 *)0x0600D000 - data_030008B0.tiles) / 32, 2, 1);
        func_08053AA0(&data_0200F428->quantity,
                      data_0200F428->quantity.buffer,
                      ((u8 *)0x0600D960 - data_030008B0.tiles) / 32, 18, 3);
        func_08053BE0(&data_0200F428->totals, data_0200F428->totals.buffer,
                      ((u8 *)0x0600E2C0 - data_030008B0.tiles) / 32, 18, 6);
        func_0802A424(2, 6, 15, 15);
        *state = 21;
        break;
    case 21:
        if (func_08017180(&data_0200F428->menu) &&
            func_08017180(&data_0200F428->item) &&
            func_08017180(&data_0200F428->quantity) &&
            func_08017180(&data_0200F428->totals)) {
            func_080539B4(&data_0200F428->item, data_0200F428->text_state,
                          g_state_02000000.item_types[data_0200F428->item_index]);
            func_08053B34(&data_0200F428->quantity,
                          data_0200F428->text_state,
                          func_080CC218(g_state_02000000.item_types[data_0200F428->item_index]));
            func_080535BC();
            func_08053568(&count, &total);
            func_08053C74(&data_0200F428->totals, data_0200F428->text_state,
                          count, total, 1);
            func_08053348(0, 0);
            data_0200F428->deferred.count = 2;
            data_0200F428->deferred.handler = func_08051084;
            data_0200F428->deferred.request = &data_0200F428->transition;
            data_0200F428->transition.state = state;
            data_0200F428->transition.next_state = 200;
            data_0200F428->transition.selection = 255;
            func_0802B3A8(data_0200F428->animation, data_08422764,
                          data_0841CE18, 0, 1);
            *state = 22;
        }
        break;
    case 22:
        func_08001F34(func_0802B3D4(data_0200F428->animation), 70, 48, 0,
                      0, 0, 0, 0, 0x2C0, 0, 0);
        if (data_03000000.pressed & 1) {
            func_080530A0(state);
        } else if (data_03000000.pressed & 4) {
            func_08013390(data_0200F428);
            func_08019A8C(data_0200F428,
                          data_0852A212[g_state_02000000.entries[data_0200F428->active_index]],
                          &data_030008B0, data_03000990);
            func_0802A424(2, 8, 15, 12);
            *state = 220;
            data_0200F428->saved_state = 22;
        } else if ((data_03000000.held & 0x200) &&
                   (data_03000000.repeated & 0x40)) {
            changed = 0;
            if (data_0200F428->menu.list.scroll == 0) {
                if (data_0200F428->menu.controls->row != 0) {
                    func_080543DC(data_0200F428->menu.controls, 0);
                    func_08141540(0x6D);
                    changed = 1;
                }
            } else {
                /* The test is on the 16-bit result (lsls #16 at 0x08052C6A)
                 * and both arms store (0x08052C70, 0x08052C74). */
                if ((s16)(data_0200F428->menu.list.scroll - 4) < 0)
                    data_0200F428->menu.list.scroll = 0;
                else
                    data_0200F428->menu.list.scroll -= 4;
                func_08053348(data_0200F428->menu.list.scroll,
                              data_0200F428->menu.controls->row);
                func_08141540(0x6D);
                changed = 1;
            }
            if (changed) {
                /* The cursor's address is formed before the list's
                 * (0x08052C9E, 0x08052D64), as in the merged
                 * src/0805BFC0.c and src/0805AB34.c. */
                MenuControls *controls = data_0200F428->menu.controls;

                data_0200F428->active_index =
                    func_080543CC(&data_0200F428->menu.list, controls->row);
                func_080534F4();
                func_0802B108(&data_0200F428->menu.list);
            }
        } else if ((data_03000000.held & 0x200) &&
                   (data_03000000.repeated & 0x80)) {
            changed = 0;
            if (data_0200F428->item_count <= 4 &&
                data_0200F428->menu.controls->row !=
                    data_0200F428->item_count - 1) {
                func_080543DC(data_0200F428->menu.controls,
                              data_0200F428->item_count - 1);
                func_08141540(0x6D);
                changed = 1;
            } else if (data_0200F428->menu.list.scroll ==
                       data_0200F428->item_count - 4) {
                if (data_0200F428->menu.controls->row != 3) {
                    func_080543DC(data_0200F428->menu.controls, 3);
                    func_08141540(0x6D);
                    changed = 1;
                }
            } else if (data_0200F428->item_count > 4) {
                if ((s16)(data_0200F428->menu.list.scroll + 4) >
                    data_0200F428->item_count - 4)
                    data_0200F428->menu.list.scroll =
                        data_0200F428->item_count - 4;
                else
                    data_0200F428->menu.list.scroll += 4;
                func_08053348(data_0200F428->menu.list.scroll,
                              data_0200F428->menu.controls->row);
                func_08141540(0x6D);
                changed = 1;
            }
            if (changed) {
                MenuControls *controls = data_0200F428->menu.controls;

                data_0200F428->active_index =
                    func_080543CC(&data_0200F428->menu.list, controls->row);
                func_080534F4();
                func_0802B108(&data_0200F428->menu.list);
            }
        } else {
            func_08053FE0(&data_0200F428->menu,
                          (void (*)(void *))func_080531F0, 0,
                          data_0200F428->item_count,
                          &data_0200F428->deferred, 1);
            {
                /* Cursor before list again, at 0x08052DC2. */
                MenuControls *controls = data_0200F428->menu.controls;

                selected = func_080543CC(&data_0200F428->menu.list,
                                         controls->row);
            }
            if (data_0200F428->active_index != selected) {
                func_080534F4();
                func_0802B108(&data_0200F428->menu.list);
                data_0200F428->active_index = selected;
            }
        }
        if (data_0200F428->item_count > 4)
            func_080541B0(&data_0200F428->menu.arrows,
                          data_0200F428->menu.controls);
        func_08016234(&data_0200F428->menu);
        break;
    case 100:
        *state = 200;
        data_0200F428->selection = 101;
        break;
    case 101:
        func_0802B53C(data_0200F428->message, 1);
        func_0802B554(data_0200F428->message, 0x71);
        *state = 102;
        break;
    case 102:
        if (func_0802B548(data_0200F428->message) == 5) {
            if (func_08013380() == 0) {
                func_08141570(1, 0x88);
                func_08051048();
                func_080CC2B4();
                func_080CCAAC(g_state_02000000.item_types[data_0200F428->item_index]);
                g_state_02000000.item_types[data_0200F428->item_index] = 0;
                func_080CC300();
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message, 0x72);
                *state = 104;
            } else {
                if (func_08013380() == 1) {
                    func_0802B53C(data_0200F428->message, 4);
                    func_0802B554(data_0200F428->message, 0x74);
                } else if (func_08013380() == -1) {
                    func_0802B53C(data_0200F428->message, 6);
                }
                *state = 103;
            }
        }
        break;
    case 103:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = 20;
        break;
    case 104:
        if (func_0802B548(data_0200F428->message) == 5 &&
            (data_03000000.pressed & 1))
            *state = 255;
        break;
    case 200:
        func_0802A290(&data_0200F428->menu, 1);
        func_0802A290(&data_0200F428->item, 1);
        func_0802A290(&data_0200F428->quantity, 1);
        func_0802A290(&data_0200F428->totals, 1);
        *state = 201;
        break;
    case 201:
        if (func_08017180(&data_0200F428->menu) &&
            func_08017180(&data_0200F428->item) &&
            func_08017180(&data_0200F428->quantity) &&
            func_08017180(&data_0200F428->totals))
            *state = data_0200F428->selection;
        break;
    case 220:
        if (func_08011860()) {
            func_0802A424(2, 6, 15, 15);
            *state = data_0200F428->saved_state;
        }
        break;
    case 255:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_08051DB4);
        break;
    }
}
