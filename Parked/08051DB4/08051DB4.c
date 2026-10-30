#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[0x1A];
    s16 scroll;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuControls controls;
    u8 cursor[0x10];
} MenuWindow;

typedef struct {
    u8 unknown_00[0x74];
    u8 buffer[1];
    u8 unknown_75[0x35F];
} DetailWindow;

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
    u32 handlers[1];
    u8 handler_flags[1];
    u8 unknown_0CED[3];
    MenuWindow menu;
    u8 unknown_0D60[0x18C];
    DetailWindow detail;
    u8 outer_window[1];
    u8 unknown_12C1[0x79F];
    u8 detail_buffer[0x290];
    DeferredAction deferred;
    u8 unknown_1CFC[0x18];
    TransitionRequest transition;
    u8 unknown_1D20[0x24];
    u8 selection;
    u8 item_count;
    u8 selected_index;
} MenuContext;

typedef struct {
    u8 unknown_0000[0x2E64];
    u8 values[256];
} ValueState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

extern MenuContext *data_0200F428;
extern InputState data_03000000;
extern ValueState g_state_02000000;
extern GraphicsState data_030008B0;
extern u8 data_03000990[];
extern u8 data_0600D000[];
extern const u16 data_0852A212[];
extern u8 func_0802B548(void *window);
extern void func_0802B53C(void *window, u8 enabled);
extern void func_0802B554(void *window, u8 message);
extern u8 func_080CCA54(void);
extern void func_0802A1FC(void *window, u8 x, u8 y, u8 width, u8 height,
                         u16 tile, u8 enabled);
extern void func_0802B368(void *window, u8 *text, u8 first, u8 second);
extern void func_08053714(DetailWindow *window, u8 *buffer, u16 tile,
                         u8 width, u8 height);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern u8 func_08017180(void *window);
extern void func_0805262C(u16 scroll, u8 row);
extern u8 func_080CC218(u8 value);
extern u8 func_080CCA20(u8 value);
extern void func_080537A8(DetailWindow *window, u8 *buffer, u8 first,
                         u8 second, u32 initial);
extern void func_08051084(TransitionRequest *request);
extern void func_080524C0(u8 *state);
extern void func_08013390(void *window);
extern void func_08019A8C(void *window, u16 value, GraphicsState *graphics,
                         u8 *scratch);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);
extern void func_08017FB0(MenuControls *controls, u8 row);
extern void func_08017FBC(void *cursor, u32 direction);
extern void func_08141540(u16 sound);
extern void func_08052790(void);
extern void func_0802B108(MenuList *list);
extern u16 func_08017B68(MenuList *list, s8 row);
extern void func_08029F7C(MenuWindow *window, u8 wrap, void (*callback)(void),
                         void *argument, DeferredAction *action, u8 enabled);
extern void func_080524E8(void);
extern void func_08016234(MenuWindow *window);
extern void func_0802A290(void *window, u8 close);
extern u16 func_08011860(void);
extern void func_08052870(u8 index, u8 *state);
extern void func_080510B0(u8 index, u8 *state);

/* Complete target: [0x08051DB4, 0x080524C0), 1804 bytes, 685 instructions. */
void func_08051DB4(u8 index, u8 *state)
{
    u8 first;
    u8 second;
    u8 changed;
    s16 next;
    s8 selected;

    switch (*state) {
    case 0:
        if (func_0802B548(data_0200F428->outer_window) == 0)
            func_0802B53C(data_0200F428->outer_window, 1);
        else
            func_0802B53C(data_0200F428->outer_window, 4);
        if (func_080CCA54() == 0) {
            func_0802B554(data_0200F428->outer_window, 0x6F);
            *state = 1;
        } else {
            func_0802B554(data_0200F428->outer_window, 0x6E);
            *state = 2;
        }
        break;
    case 1:
        if (func_0802B548(data_0200F428->outer_window) == 5 &&
            (data_03000000.pressed & 1))
            *state = 0xFF;
        break;
    case 2:
        if (func_0802B548(data_0200F428->outer_window) == 0)
            *state = 20;
        break;
    case 20:
        func_0802A1FC(&data_0200F428->menu, 2, 2, 15, 17, 0xC0, 1);
        func_0802B368(&data_0200F428->menu, data_0200F428->text, 10, 0);
        func_08053714(&data_0200F428->detail, data_0200F428->detail.buffer,
                      (data_0600D000 - data_030008B0.tiles) / 32, 19, 4);
        func_0802A2C0(18, 0, 12, 20);
        *state = 21;
        break;
    case 21:
        if (func_08017180(&data_0200F428->menu) &&
            func_08017180(&data_0200F428->detail)) {
            func_0805262C(0, 0);
            first = func_080CC218(g_state_02000000.values[data_0200F428->selected_index]);
            second = func_080CCA20(g_state_02000000.values[data_0200F428->selected_index]);
            func_080537A8(&data_0200F428->detail, data_0200F428->detail_buffer,
                          first, second, 1);
            data_0200F428->deferred.count = 2;
            data_0200F428->deferred.handler = func_08051084;
            data_0200F428->deferred.request = &data_0200F428->transition;
            data_0200F428->transition.state = state;
            data_0200F428->transition.next_state = 200;
            data_0200F428->transition.selection = 255;
            *state = 22;
        }
        break;
    case 22:
        if (data_03000000.pressed & 1) {
            func_080524C0(state);
        } else if (data_03000000.pressed & 4) {
            func_08013390(data_0200F428);
            func_08019A8C(data_0200F428,
                          data_0852A212[g_state_02000000.values[data_0200F428->selected_index]],
                          &data_030008B0, data_03000990);
            func_0802A370(2, 2, 26, 6);
            *state = 220;
            data_0200F428->saved_state = 22;
        } else if (data_03000000.held & 0x200) {
            if (data_03000000.repeated & 0x40) {
                changed = 0;
                if (data_0200F428->menu.list.scroll == 0) {
                    if (data_0200F428->menu.controls.row != 0) {
                        func_08017FB0(&data_0200F428->menu.controls, 0);
                        func_08017FBC(data_0200F428->menu.cursor, 0x40);
                        func_08141540(0x6D);
                        goto refresh;
                    }
                } else {
                    next = data_0200F428->menu.list.scroll - 7;
                    if (next < 0)
                        data_0200F428->menu.list.scroll = 0;
                    else
                        data_0200F428->menu.list.scroll = next;
                    func_0805262C(data_0200F428->menu.list.scroll,
                                  data_0200F428->menu.controls.row);
                    func_08141540(0x6D);
                    changed = 1;
                }
            } else if (data_03000000.repeated & 0x80) {
                changed = 0;
                if (data_0200F428->item_count <= 7 &&
                    data_0200F428->menu.controls.row != data_0200F428->item_count - 1) {
                    func_08017FB0(&data_0200F428->menu.controls,
                                  data_0200F428->item_count - 1);
                    func_08017FBC(data_0200F428->menu.cursor, 0x80);
                    func_08141540(0x6D);
                    goto refresh;
                } else if (data_0200F428->menu.list.scroll == data_0200F428->item_count - 7) {
                    if (data_0200F428->menu.controls.row != 6) {
                        func_08017FB0(&data_0200F428->menu.controls, 6);
                        func_08017FBC(data_0200F428->menu.cursor, 0x80);
                        func_08141540(0x6D);
                        goto refresh;
                    }
                } else if (data_0200F428->item_count > 7) {
                    next = data_0200F428->menu.list.scroll + 7;
                    if (next > data_0200F428->item_count - 7)
                        data_0200F428->menu.list.scroll = data_0200F428->item_count - 7;
                    else
                        data_0200F428->menu.list.scroll = next;
                    func_0805262C(data_0200F428->menu.list.scroll,
                                  data_0200F428->menu.controls.row);
                    func_08141540(0x6D);
                    changed = 1;
                }
            } else {
                goto navigate;
            }
            if (changed) {
refresh:
                func_08052790();
                func_0802B108(&data_0200F428->menu.list);
                data_0200F428->selected_index = func_08017B68(&data_0200F428->menu.list,
                                                            (s8)data_0200F428->menu.controls.row);
                first = func_080CC218(g_state_02000000.values[data_0200F428->selected_index]);
                second = func_080CCA20(g_state_02000000.values[data_0200F428->selected_index]);
                func_080537A8(&data_0200F428->detail, data_0200F428->detail_buffer,
                              first, second, 0);
            }
        } else {
navigate:
            if (data_0200F428->item_count <= 7)
                func_08029F7C(&data_0200F428->menu, 1, 0, 0, &data_0200F428->deferred, 1);
            else
                func_08029F7C(&data_0200F428->menu, 0, func_080524E8, 0,
                              &data_0200F428->deferred, 1);
            selected = func_08017B68(&data_0200F428->menu.list,
                                    (s8)data_0200F428->menu.controls.row);
            if (data_0200F428->selected_index != selected) {
                func_08052790();
                func_0802B108(&data_0200F428->menu.list);
                data_0200F428->selected_index = selected;
                first = func_080CC218(g_state_02000000.values[data_0200F428->selected_index]);
                second = func_080CCA20(g_state_02000000.values[data_0200F428->selected_index]);
                func_080537A8(&data_0200F428->detail, data_0200F428->detail_buffer,
                              first, second, 0);
            }
        }
        func_08016234(&data_0200F428->menu);
        break;
    case 200:
        func_0802A290(&data_0200F428->menu, 1);
        func_0802A290(&data_0200F428->detail, 1);
        *state = 201;
        break;
    case 201:
        if (func_08017180(&data_0200F428->menu) &&
            func_08017180(&data_0200F428->detail))
            *state = data_0200F428->selection;
        break;
    case 220:
        if (func_08011860()) {
            *(volatile u16 *)0x04000000 &= 0xBFFF;
            func_0802A370(0, 0, 0, 0);
            func_08013390(data_0200F428->outer_window);
            *state = data_0200F428->saved_state;
        }
        break;
    case 254:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_08052870);
        break;
    case 255:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_080510B0);
        data_0200F428->handler_flags[0] = 20;
        break;
    }
}
