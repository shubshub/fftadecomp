#include "ffta.h"

/* Complete target [0x0806B6D0, 0x0806D2B4): 7140 bytes, including the
 * 256-word case table and the literal pools.  The shop's "sell" sub-task,
 * which func_08068C10 (state 23) installs in the runner at +0x147C and which
 * reinstalls func_08068C10 when it closes (case 0xFF).  The case bodies reach
 * the common tail (0x0806D22A) through agbcc's long same-function BL jumps. */

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 height;
    u8 unknown_0E[2];
    u8 *tiles;
    u16 *map;
} GraphicsState;

/* g_state_020020D0 as src/0805ADA4.c types it: the word at +8 is the
 * number the next message prints (a count there, the price here; named
 * amount as in src/08063314.c). */
typedef struct {
    u8 unknown_00[8];
    u32 amount;
    u8 unknown_0C[0xB6 - 0xC];
    u8 unknown_B6;
} MessageArguments;

typedef struct {
    u16 name;
    u8 unknown_02[4];
    u16 unknown_06;
    u8 unknown_08[0x18];
} ItemInfo;

typedef void (*MenuCallback)(void *argument);

typedef struct {
    MenuCallback callback;
    void *argument;
    u16 buttons;
    u16 unknown_0A;
} ButtonAction;

typedef struct {
    u8 unknown_00[0x1A];
    s16 position;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

/* The list at +0x2C, the controls at +0x4C and +0x60, as in
 * src/08068C10.c. */
typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuControls controls;
    MenuControls arrows;
} Window;

/* The category bar func_0806EC20 and func_0806EFA8 work on
 * (src/0806EC20.c, src/0806EFA8.c). */
typedef struct {
    u8 selection;
    u8 entries[6];
    u8 count;
    u8 unknown_08[0x74];
} Menu;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item;

/* The context at data_0200F428: the window, runner and actions as in
 * src/08068C10.c, the layout from 0x446C on as in src/0806D428.c and
 * src/0806B4C4.c. */
typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0xCD4 - 0xB54];
    u8 restore_context;
    u8 unknown_0CD5[3];
    u8 message[0x1478 - 0xCD8];
    u8 state;
    u8 resume;
    u8 unknown_147A[2];
    Table runner;
    u8 unknown_148C[4];
    u8 unknown_1490;
    u8 unknown_1491[3];
    Window window;
    u8 content[0x1A88 - 0x1508];
    u8 context[0x395C - 0x1A88];
    u8 dialog[0x39F4 - 0x395C];
    u8 panel[0x4418 - 0x39F4];
    ButtonAction actions[2];
    u8 unknown_4430[0x446C - 0x4430];
    u8 next;
    u8 count;
    u8 unknown_446E[2];
    Menu menu;
    u16 item;
    u8 selection;
    u8 unknown_44EF;
    u8 menu_index;
    u8 values[6];
    u8 choices[6];
    u8 unknown_44FD[3];
    u32 amount;
    Item items[0x178];
    u16 error;
    u8 unknown_4AE6[0x4AF4 - 0x4AE6];
    u8 left_panel[0x4B9C - 0x4AF4];
    u8 right_panel[0x4BF8 - 0x4B9C];
    u8 panels_shown;
    u8 unknown_4BF9;
    u8 unknown_4BFA[3];
    u8 message_base;
    u8 unknown_4BFE[2];
    u8 saved_menu_selection;
    u8 saved_menu_entry;
    u8 unknown_4C02;
    u8 unknown_4C03;
    u8 refresh_window;
    u8 unknown_4C05;
    u8 detail_shown;
    u8 unknown_4C07;
    u16 map_backup[0x400];
    u16 map_backup_2[0x400];
    u8 tile_backup[0x4000];
} MenuContext;

extern MenuContext *data_0200F428;
extern MenuInput data_03000000;
extern GraphicsState data_030008B0;
extern GraphicsState data_03000990;
extern MessageArguments g_state_020020D0;
extern const ItemInfo g_table_0851D180[];
extern const u8 *const g_table_08526680[];

extern void func_0806F0D4(void *panel, u8 value);
extern void func_0806F3C0(void *panel, u8 value);
extern void func_0806F050(void *panel, s32 x, s32 y);
extern void func_0806F33C(void *panel, s32 x, s32 y);
extern void func_0806F0D8(void *panel, u16 item);
extern void func_0806F3C4(void *panel, u16 item);
extern void func_0806F0DC(void *panel);
extern void func_0806F3C8(void *panel);
extern u32 func_0806F1EC(void *panel, s8 target);
extern u32 func_0806F46C(void *panel, s8 target);
extern void func_0802AB4C(void *dialog, u8 value);
extern u8 func_0802AB54(void *dialog);
extern u8 func_0802AB5C(void *dialog);
extern void func_0802A5CC(void *dialog, void *panel, u16 index, u16 field,
                          u8 mode, u8 x, u8 y);
extern void func_0802A6A0(void *dialog);
extern u8 func_0806FE14(void *context);
extern void func_0806FE18(void *context, u8 value);
extern void func_0806F7B8(void *context, u16 tile, void *panel,
                          GraphicsState *first, GraphicsState *second,
                          u16 item, u8 x, u8 y);
extern u8 func_0806F8DC(void *context, u16 item);
extern u8 func_0806D5F4(void);
extern void func_0802B53C(void *message, u8 value);
extern void func_0802B554(void *message, u8 value);
extern u8 func_0802B548(void *message);
extern void func_0802B164(void *panel, GraphicsState *first,
                          GraphicsState *second, u16 tile, u16 identifier,
                          u8 x, u8 y);
extern void func_0802B2A8(GraphicsState *first, GraphicsState *second, u8 x,
                          u8 y);
extern void func_0802A1FC(Window *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802B368(Window *window, u8 *destination, u8 first,
                          u8 second);
extern u8 func_08017180(Window *window);
extern void func_08070120(Window *window, u16 first, u16 second);
extern void func_0802A290(Window *window, u8 appearance);
extern void func_0806E48C(Window *window);
extern void func_08016234(Window *window);
extern void func_08029F7C(Window *window, u8 flags, MenuCallback scroll,
                          void *argument, ButtonAction *actions,
                          u8 action_count);
extern void func_08017D18(MenuControls *controls, u8 flags);
extern void func_08017FB0(MenuControls *controls, u8 row);
extern void func_08017FBC(MenuControls *controls, u32 direction);
extern u16 func_08017B68(MenuList *list, s8 row);
extern void func_0806EC20(Menu *menu, const void *resource, u8 x, u8 y,
                          u8 field_08, u8 field_09);
extern void func_0806EC60(Menu *menu);
extern u8 func_0806EFE4(Menu *menu);
extern void func_0806EFA8(Menu *menu, u16 input);
extern void func_0806EE98(Menu *menu);
extern void func_0806EFF0(Menu *menu);
extern void func_0806E384(u8 entry, u8 position, u8 row);
/* The top row goes over sign-extended (0x0806C070, 0x0806C1F4). */
extern void func_0806E170(s16 top, u8 row, u8 mode);
extern void func_0806E528(void);
extern void func_0806EB08(void);
extern void func_080023D0(MenuInput *input);
extern void func_08141540(u16 sound);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern void func_08019A8C(void *context, u16 value, void *first,
                          void *second);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_08006ADC(Table *runner, u8 index, u32 value);
extern s8 func_08013380(void);
extern Item *func_080CB210(u32 identifier, s32 *count);
extern u16 func_080CC86C(u16 identifier);
extern void func_0806EBF8(u32 amount);
extern void func_08029F18(u32 offset, GraphicsState *window, u16 *buffer,
                          u16 x, u16 y);
extern u16 func_08011860(void);
extern u8 func_080CBD34(u16 id);
extern void func_0801174C(void *context, u32 kind, u8 index, void *first,
                          void *second, u32 x, u32 y, u32 width, u32 height,
                          u32 tile);
extern void func_0801339C(u16 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_080CB5A8(u8 unit, u16 item);
extern void func_080701BC(GraphicsState *map, void *graphics, u32 graphic,
                          u8 keep_palette, u8 x, u8 y);
extern u16 func_080161BC(const u8 *text);
extern void func_080702E8(GraphicsState *map, u8 *graphics, u16 id, u8 x,
                          u8 y);
extern void func_0806D2B4(void *argument);
extern void func_0806D300(void);
extern void func_0806D428(void *argument);
extern void func_0806D590(void *argument);
extern void func_08068C10(u8 index, u8 *state);

/* plausible: LCD display control; 0x0806CD28 and 0x0806CE58 clear its
 * window 0 enable. */
#define REG_DISPCNT (*(volatile u16 *)0x04000000)

/* The cursor row is read through the controls record's address
 * (0x0806BFEE/0x0806BFF0, 0x0806C0A0/0x0806C0A8), as in src/08068C10.c. */
#define CURSOR_ROW(controls) ((controls)->row)

void func_0806B6D0(u8 index, u8 *state)
{
    u8 i;
    u8 count;
    u8 selection;
    u8 old;
    u8 moved;
    u8 left_done;
    u8 right_done;
    s16 top;
    u16 j;
    u16 k;
    u16 unit;
    u16 width;
    Item *items;

    switch (*state) {
    case 0:
        data_0200F428->detail_shown = 0;
        data_0200F428->refresh_window = 1;
        data_0200F428->saved_menu_entry = 0xFF;
        func_0806F0D4(data_0200F428->left_panel, 0);
        func_0806F3C0(data_0200F428->right_panel, 0);
        func_0806F050(data_0200F428->left_panel, -15, 11);
        func_0806F33C(data_0200F428->right_panel, 30, 11);
        data_0200F428->panels_shown = 0;
        data_0200F428->unknown_4BF9 = 0;
        for (i = 0; i < 6; i++) {
            data_0200F428->values[i] = 0;
            data_0200F428->choices[i] = 0;
        }
        func_0802AB4C(data_0200F428->dialog, 8);
        func_0806FE18(data_0200F428->context, 4);
        if (!func_0806D5F4()) {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message,
                          data_0200F428->message_base + 4);
            *state = 1;
        } else {
            func_0802B53C(data_0200F428->message, 6);
            *state = 2;
        }
        break;
    case 1:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1))
            *state = 0xFF;
        break;
    case 2:
        if (!func_0802B548(data_0200F428->message))
            *state = 0x14;
        break;
    case 0x14:
        func_0802A1FC(&data_0200F428->window, 1, 0, 26, 11, 0xC0, 1);
        func_0802B368(&data_0200F428->window, data_0200F428->text, 0, 12);
        *state = 0x15;
        break;
    case 0x15:
        if (func_08017180(&data_0200F428->window)) {
            data_0200F428->unknown_4BF9 = 1;
            func_08070120(&data_0200F428->window, 0x340, 0x346);
            *state = 0x16;
        }
        break;
    case 0x16:
        func_0806EC20(&data_0200F428->menu, &data_030008B0, 2, 0, 15, 9);
        func_0806EC60(&data_0200F428->menu);
        if (data_0200F428->menu.count <= data_0200F428->saved_menu_selection)
            data_0200F428->menu.selection = data_0200F428->menu.count - 1;
        else
            data_0200F428->menu.selection = data_0200F428->saved_menu_selection;
        func_0806E384(func_0806EFE4(&data_0200F428->menu),
                      data_0200F428->values[func_0806EFE4(&data_0200F428->menu)],
                      data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)]);
        func_0806EE98(&data_0200F428->menu);
        data_0200F428->actions[0].buttons = 2;
        data_0200F428->actions[0].callback = func_0806D2B4;
        data_0200F428->actions[0].argument = state;
        data_0200F428->actions[1].buttons = 0x100;
        data_0200F428->actions[1].callback = func_0806D590;
        data_0200F428->actions[1].argument = state;
        func_0806F0D4(data_0200F428->left_panel, 1);
        func_0806F3C0(data_0200F428->right_panel, 1);
        *state = 0xC8;
        data_0200F428->next = 0x17;
        break;
    case 0x17:
        data_0200F428->unknown_4C03 = 1;
        if (data_03000000.repeated & 0x20) {
            func_080023D0(&data_03000000);
            old = func_0806EFE4(&data_0200F428->menu);
            func_0806EFA8(&data_0200F428->menu, 0x20);
            if (old == func_0806EFE4(&data_0200F428->menu))
                break;
            func_08141540(0x65);
            func_0806E384(func_0806EFE4(&data_0200F428->menu),
                          data_0200F428->values[func_0806EFE4(&data_0200F428->menu)],
                          data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)]);
            data_0200F428->saved_menu_selection = data_0200F428->menu.selection;
            data_0200F428->unknown_4C05 = 0;
        } else if (data_03000000.repeated & 0x10) {
            old = func_0806EFE4(&data_0200F428->menu);
            func_0806EFA8(&data_0200F428->menu, 0x10);
            if (old == func_0806EFE4(&data_0200F428->menu))
                break;
            func_08141540(0x65);
            func_0806E384(func_0806EFE4(&data_0200F428->menu),
                          data_0200F428->values[func_0806EFE4(&data_0200F428->menu)],
                          data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)]);
            data_0200F428->saved_menu_selection = data_0200F428->menu.selection;
            data_0200F428->unknown_4C05 = 0;
        } else if (data_03000000.pressed & 1) {
            func_0806D428(state);
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x40)) {
            moved = 0;
            if (data_0200F428->count <= 4
                && CURSOR_ROW(&data_0200F428->window.controls) != 0) {
                func_08017FB0(&data_0200F428->window.controls, 0);
                func_08017FBC(&data_0200F428->window.controls, 0x40);
                func_0806E528();
                func_08141540(0x6D);
            } else if (data_0200F428->window.list.position == 0
                       && CURSOR_ROW(&data_0200F428->window.controls) != 0) {
                func_08017FB0(&data_0200F428->window.controls, 0);
                func_08017FBC(&data_0200F428->window.controls, 0x40);
                func_0806E528();
                func_08141540(0x6D);
            } else {
                if (data_0200F428->count > 4) {
                    top = data_0200F428->window.list.position - 4;
                    if (top < 0)
                        top = 0;
                    if (data_0200F428->window.list.position != top) {
                        func_08141540(0x6D);
                        func_0806E170(top,
                                      CURSOR_ROW(&data_0200F428->window.controls), 2);
                        moved = 1;
                    }
                }
                if (!moved)
                    break;
            }
            selection = CURSOR_ROW(&data_0200F428->window.controls);
            data_0200F428->selection =
                func_08017B68(&data_0200F428->window.list, selection);
            data_0200F428->item =
                data_0200F428->items[data_0200F428->selection].item;
            func_0806F0D8(data_0200F428->left_panel, data_0200F428->item);
            func_0806F3C4(data_0200F428->right_panel, data_0200F428->item);
            data_0200F428->values[func_0806EFE4(&data_0200F428->menu)] =
                data_0200F428->window.list.position;
            data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
                CURSOR_ROW(&data_0200F428->window.controls);
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x80)) {
            moved = 0;
            if (data_0200F428->count <= 4
                && CURSOR_ROW(&data_0200F428->window.controls)
                       != data_0200F428->count - 1) {
                func_08017FB0(&data_0200F428->window.controls,
                              data_0200F428->count - 1);
                func_08017FBC(&data_0200F428->window.controls, 0x80);
                func_0806E528();
                func_08141540(0x6D);
            } else if (data_0200F428->window.list.position
                           == data_0200F428->count - 4
                       && CURSOR_ROW(&data_0200F428->window.controls) != 3) {
                func_08017FB0(&data_0200F428->window.controls, 3);
                func_08017FBC(&data_0200F428->window.controls, 0x80);
                func_0806E528();
                func_08141540(0x6D);
            } else {
                if (data_0200F428->count > 4) {
                    top = data_0200F428->window.list.position + 4;
                    if (top > data_0200F428->count - 4)
                        top = data_0200F428->count - 4;
                    if (data_0200F428->window.list.position != top) {
                        func_08141540(0x6D);
                        func_0806E170(top,
                                      CURSOR_ROW(&data_0200F428->window.controls), 2);
                        moved = 1;
                    }
                }
                if (!moved)
                    break;
            }
            selection = CURSOR_ROW(&data_0200F428->window.controls);
            data_0200F428->selection =
                func_08017B68(&data_0200F428->window.list, selection);
            data_0200F428->item =
                data_0200F428->items[data_0200F428->selection].item;
            func_0806F0D8(data_0200F428->left_panel, data_0200F428->item);
            func_0806F3C4(data_0200F428->right_panel, data_0200F428->item);
            data_0200F428->values[func_0806EFE4(&data_0200F428->menu)] =
                data_0200F428->window.list.position;
            data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
                CURSOR_ROW(&data_0200F428->window.controls);
        } else if (data_03000000.pressed & 4) {
            data_0200F428->refresh_window = 0;
            if (func_0806FE14(data_0200F428->context) == 1) {
                func_0806FE18(data_0200F428->context, 4);
                data_0200F428->restore_context = 1;
            } else {
                data_0200F428->restore_context = 0;
            }
            func_08019A8C(data_0200F428,
                          func_080CA7A4(data_0200F428->item, 1),
                          &data_030008B0, &data_03000990);
            data_0200F428->resume = 0x17;
            func_0802A2C0(2, 2, 26, 6);
            *state = 0x8C;
        } else {
            if (data_0200F428->count <= 4)
                func_08029F7C(&data_0200F428->window, 1, 0, 0,
                              data_0200F428->actions, 2);
            else
                func_08029F7C(&data_0200F428->window, 0,
                              (MenuCallback)func_0806D300, 0,
                              data_0200F428->actions, 2);
            /* One u8 holds the cursor row and then the list entry at that
             * row: the entry is narrowed into the register the compares
             * and the store use (0x0806C3E4, 0x0806C402, 0x0806C40E). */
            selection = CURSOR_ROW(&data_0200F428->window.controls);
            selection = func_08017B68(&data_0200F428->window.list, selection);
            if (data_0200F428->items[selection].item == data_0200F428->item
                && data_0200F428->selection == selection)
                break;
            data_0200F428->selection = selection;
            data_0200F428->item =
                data_0200F428->items[data_0200F428->selection].item;
            func_0806E528();
            func_0806F0D8(data_0200F428->left_panel, data_0200F428->item);
            func_0806F3C4(data_0200F428->right_panel, data_0200F428->item);
            data_0200F428->values[func_0806EFE4(&data_0200F428->menu)] =
                data_0200F428->window.list.position;
            data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
                CURSOR_ROW(&data_0200F428->window.controls);
        }
        break;
    case 0x28:
        func_08017D18(&data_0200F428->window.arrows, 0);
        data_0200F428->unknown_4C03 = 0;
        data_0200F428->unknown_4BF9 = 0;
        *state = 0xDC;
        data_0200F428->next = 0x29;
        break;
    case 0x29:
        count = data_0200F428->items[data_0200F428->selection].quantity
                - data_0200F428->items[data_0200F428->selection].unknown_03;
        func_0802A5CC(data_0200F428->dialog, data_0200F428->panel, 0x330, 0x334,
                      count, 19, 11);
        *state = 0x2A;
        break;
    case 0x2A:
        if (func_0802AB54(data_0200F428->dialog) == 1)
            *state = 0x2B;
        break;
    case 0x2B:
        func_08017D18(&data_0200F428->window.arrows, 0);
        if (data_03000000.pressed & 1) {
            func_08141540(0x64);
            func_0802AB4C(data_0200F428->dialog, 2);
            *state = 0x64;
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x69);
            func_0802AB4C(data_0200F428->dialog, 4);
            data_0200F428->unknown_4BF9 = 1;
            func_0806E48C(&data_0200F428->window);
            *state = 0xC8;
            data_0200F428->next = 0x17;
        }
        break;
    case 0x3C:
        func_08017D18(&data_0200F428->window.arrows, 0);
        func_0806F7B8(data_0200F428->context,
                      ((u8 *)0x0600B000 - data_030008B0.tiles) / 32,
                      data_0200F428->panel, &data_030008B0, &data_03000990,
                      data_0200F428->item, 16, 1);
        func_0806F3C0(data_0200F428->right_panel, 0);
        *state = 0x3D;
        break;
    case 0x3D:
        if (func_0806FE14(data_0200F428->context) == 1)
            *state = data_0200F428->next;
        break;
    case 0x3E:
        func_0806FE18(data_0200F428->context, 2);
        *state = 0x3F;
        break;
    case 0x3F:
        if (func_0806FE14(data_0200F428->context) == 4) {
            func_0806E48C(&data_0200F428->window);
            func_0806F3C0(data_0200F428->right_panel, 1);
            *state = data_0200F428->next;
        }
        break;
    case 0x50:
        if (func_0806FE14(data_0200F428->context) == 1) {
            *state = 0x3E;
            data_0200F428->next = 0x50;
        } else {
            *state = 0xDC;
            data_0200F428->next = 0x51;
        }
        break;
    case 0x51:
        func_0802A290(&data_0200F428->window, 1);
        func_0806EFF0(&data_0200F428->menu);
        data_0200F428->unknown_4BF9 = 0;
        *state = 0x52;
        break;
    case 0x52:
        if (func_08017180(&data_0200F428->window))
            *state = 0xFF;
        break;
    case 0xFF:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_08068C10);
        data_0200F428->unknown_1490 = 1;
        break;
    case 0x64:
        func_0802A290(&data_0200F428->window, 1);
        data_0200F428->unknown_4BF9 = 0;
        *state = 0x65;
        break;
    case 0x65:
        if (func_08017180(&data_0200F428->window)) {
            data_0200F428->amount =
                g_table_0851D180[data_0200F428->item].unknown_06
                * func_0802AB5C(data_0200F428->dialog);
            g_state_020020D0.amount = data_0200F428->amount;
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message,
                          data_0200F428->message_base + 3);
            func_0802B164(data_0200F428->panel, &data_030008B0, &data_03000990,
                          ((u8 *)0x0600C800 - data_030008B0.tiles) / 32,
                          data_0200F428->item, 5, 11);
            *state = 0x66;
        }
        break;
    case 0x66:
        if (func_0802B548(data_0200F428->message) == 5) {
            if (func_08013380() == 0) {
                items = func_080CB210(data_0200F428->item, 0);
                items[func_080CC86C(data_0200F428->item)].quantity -=
                    func_0802AB5C(data_0200F428->dialog);
                func_0806EBF8(data_0200F428->amount);
                func_08029F18(0, &data_030008B0, 0, 20, 17);
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message,
                              data_0200F428->message_base + 6);
                func_0802AB4C(data_0200F428->dialog, 4);
                *state = 0x67;
            } else if (func_08013380() == 1) {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message,
                              data_0200F428->message_base + 11);
                func_0802AB4C(data_0200F428->dialog, 4);
                *state = 0x68;
            } else if (func_08013380() == -1) {
                func_0802B53C(data_0200F428->message, 6);
                *state = 0x6A;
            }
            func_0802B2A8(&data_030008B0, &data_03000990, 5, 11);
        }
        break;
    case 0x67:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            if (func_0806D5F4() == 1) {
                func_0802B53C(data_0200F428->message, 6);
                *state = 0x68;
            } else {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message,
                              data_0200F428->message_base + 4);
                *state = 0x69;
            }
        }
        break;
    case 0x68:
        if (!func_0802B548(data_0200F428->message)) {
            func_0802A1FC(&data_0200F428->window, 1, 0, 26, 11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 0, 12);
            *state = 0x15;
        }
        break;
    case 0x69:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1))
            *state = 0xFF;
        break;
    case 0x6A:
        if (!func_0802B548(data_0200F428->message)) {
            func_0802A1FC(&data_0200F428->window, 1, 0, 26, 11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 0, 12);
            *state = 0x6B;
        }
        break;
    case 0x6B:
        if (func_08017180(&data_0200F428->window)) {
            func_08070120(&data_0200F428->window, 0x340, 0x346);
            func_0806E384(func_0806EFE4(&data_0200F428->menu),
                          data_0200F428->values[func_0806EFE4(&data_0200F428->menu)],
                          data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)]);
            func_0806EE98(&data_0200F428->menu);
            func_08017D18(&data_0200F428->window.arrows, 0);
            *state = 0x2A;
            func_0802AB4C(data_0200F428->dialog, 1);
        }
        break;
    case 0x78:
        func_0802A290(&data_0200F428->window, 1);
        data_0200F428->unknown_4BF9 = 0;
        *state = 0x79;
        break;
    case 0x79:
        if (func_08017180(&data_0200F428->window)) {
            *state = 0xDC;
            data_0200F428->next = 0x7A;
        }
        break;
    case 0x7A:
        func_0802B53C(data_0200F428->message, 1);
        func_0802B554(data_0200F428->message, data_0200F428->message_base + 5);
        *state = 0x7B;
        break;
    case 0x7B:
        if (!func_0802B548(data_0200F428->message))
            *state = 0x14;
        break;
    case 0x8C:
        if (func_08011860()) {
            data_0200F428->refresh_window = 1;
            if (data_0200F428->restore_context)
                func_0806FE18(data_0200F428->context, 1);
            REG_DISPCNT &= ~0x2000;
            func_0802A2C0(0, 0, 0, 0);
            if (func_080CBD34(data_0200F428->item) != 5)
                *state = 0xB4;
            else
                *state = data_0200F428->resume;
        }
        break;
    case 0xB4:
        data_0200F428->refresh_window = 0;
        if (func_0806FE14(data_0200F428->context) == 1) {
            func_0806FE18(data_0200F428->context, 4);
            data_0200F428->restore_context = 1;
        } else {
            data_0200F428->restore_context = 0;
        }
        func_0801174C(data_0200F428, 1, 0x28, &data_030008B0, &data_03000990,
                      2, 2, 24, 4, 0x360);
        func_0801339C(2);
        data_0200F428->resume = 0x17;
        func_0802A2C0(2, 2, 26, 6);
        func_0801339C(4);
        *state = 0xB5;
        break;
    case 0xB5:
        if (func_08011860()) {
            data_0200F428->refresh_window = 1;
            if (data_0200F428->restore_context)
                func_0806FE18(data_0200F428->context, 1);
            REG_DISPCNT &= ~0x2000;
            func_0802A2C0(0, 0, 0, 0);
            if (g_state_020020D0.unknown_B6)
                *state = 0xA0;
            else
                *state = data_0200F428->resume;
        }
        break;
    case 0xA0:
        data_0200F428->detail_shown = 1;
        data_0200F428->unknown_4BF9 = 0;
        data_0200F428->refresh_window = 0;
        func_0806F0D4(data_0200F428->left_panel, 0);
        func_0806F3C0(data_0200F428->right_panel, 0);
        *state = 0xA1;
        break;
    case 0xA1:
        func_08141540(0x69);
        func_0814186C(data_030008B0.map, data_0200F428->map_backup,
                      data_030008B0.width * data_030008B0.height);
        func_0814186C(data_03000990.map, data_0200F428->map_backup_2,
                      data_03000990.width * data_03000990.height);
        func_0814186C((void *)0x0600B000, data_0200F428->tile_backup, 0x2000);
        /* CpuFill16 of both layers' maps, in the text of src/0807B858.c and
         * src/08070C94.c: the SDK's vu16 temporary, spelled through a pointer
         * until fftadecomp-kit#164.  Each fill has its own halfword (sp+0x18
         * and sp+0x1A here, sp+0x1C and sp+0x1E in state 0xA2) and takes its
         * address before the zero (0x0806CF2C, 0x0806CF46). */
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_030008B0.map,
                          (data_030008B0.width * data_030008B0.height) | 0x01000000);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_03000990.map,
                          (data_03000990.width * data_03000990.height) | 0x01000000);
        }
        /* The icons go to VRAM 0x0600B000 on, the block saved above, as a
         * number: agbcc folds the - 2 * 0x100 into the pool word 0x0600AE00
         * (ldr at 0x0806CF88); through a data symbol the subtraction stays
         * and the function is 7148 bytes. */
        unit = 2;
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 7; k++) {
                func_080701BC(&data_030008B0, (u8 *)0x0600B000 + (unit - 2) * 0x100,
                              unit, func_080CB5A8(unit, data_0200F428->item),
                              k * 4 + 1, j * 3 + 2);
                unit++;
            }
        }
        width = func_080161BC(
                    g_table_08526680[g_table_0851D180[data_0200F428->item].name])
                + 2;
        func_080702E8(&data_030008B0, (u8 *)0x0600AC00, data_0200F428->item,
                      ((13 - width) >> 1) + 9, 0);
        *state = 0xA2;
        break;
    case 0xA2:
        if (data_03000000.pressed & 3) {
            func_08141540(0x69);
            data_0200F428->detail_shown = 0;
            data_0200F428->unknown_4BF9 = 1;
            data_0200F428->refresh_window = 1;
            func_0806F0D4(data_0200F428->left_panel, 1);
            if (func_0806FE14(data_0200F428->context) == 1)
                func_0806F3C0(data_0200F428->right_panel, 0);
            else
                func_0806F3C0(data_0200F428->right_panel, 1);
            /* As in state 0xA1 (0x0806D0BC, 0x0806D0D6). */
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_030008B0.map,
                              (data_030008B0.width * data_030008B0.height) | 0x01000000);
            }
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_03000990.map,
                              (data_03000990.width * data_03000990.height) | 0x01000000);
            }
            func_0814186C(data_0200F428->map_backup, data_030008B0.map,
                          data_030008B0.width * data_030008B0.height);
            func_0814186C(data_0200F428->map_backup_2, data_03000990.map,
                          data_03000990.width * data_03000990.height);
            func_0814186C(data_0200F428->tile_backup, (void *)0x0600B000, 0x2000);
            *state = data_0200F428->resume;
        }
        break;
    case 0xC8:
        if (data_0200F428->panels_shown == 0) {
            left_done = func_0806F1EC(data_0200F428->left_panel, 1);
            right_done = func_0806F46C(data_0200F428->right_panel, 15);
            if (left_done && right_done) {
                *state = data_0200F428->next;
                data_0200F428->panels_shown = 1;
            }
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 0xDC:
        if (data_0200F428->panels_shown == 1) {
            left_done = func_0806F1EC(data_0200F428->left_panel, -15);
            right_done = func_0806F46C(data_0200F428->right_panel, 30);
            if (left_done && right_done) {
                *state = data_0200F428->next;
                data_0200F428->panels_shown = 0;
            }
        } else {
            *state = data_0200F428->next;
        }
        break;
    }

    if (data_0200F428->refresh_window)
        func_08016234(&data_0200F428->window);
    func_0806F0DC(data_0200F428->left_panel);
    func_0806F3C8(data_0200F428->right_panel);
    func_0806EB08();
    func_0802A6A0(data_0200F428->dialog);
    if (!data_0200F428->detail_shown)
        func_0806F8DC(data_0200F428->context, data_0200F428->item);
}
