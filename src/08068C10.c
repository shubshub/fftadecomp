#include "ffta.h"

/* Complete target [0x08068C10, 0x08069548): 2360 bytes, 848 instructions,
 * including the literal pools.  The shop owner task that func_08068AE0
 * (src/08068AE0.c) installs in its runner: it looks the shop's message set
 * up, greets, opens the three- or four-row command menu (flag 0x31A adds the
 * third row) whose buttons run func_08069548 and func_08069574
 * (src/08069548.c, src/08069574.c), shows the help text on SELECT and hands
 * the runner over to the chosen sub-task.  The case bodies reach the exit
 * (0x0806952E) through agbcc's long same-function BL jumps. */

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

typedef struct {
    u8 unknown_0000[0x2E54];
    u8 selection : 5;
    u8 unknown_2E54_high : 3;
} GameState;

/* The 4-byte records of the table at 0x08393B1C (read at stride 4 for five
 * records, 0x08068D00): the shop type they are chosen by, the byte
 * func_0802B048 and func_0802B56C store at +0x798 of the message window
 * (src/0802B048.c, src/0802B56C.c) and the first message of the shop's
 * message set, to which the greetings add 0, 8, 9 or 10. */
typedef struct {
    u8 type;
    u8 style;
    u8 message_base;
    u8 unknown_03;
} ShopMessages;

typedef void (*MenuCallback)(void *argument);

typedef struct {
    MenuCallback callback;
    void *argument;
    u16 buttons;
    u16 unknown_0A;
} ButtonAction;

/* The argument of func_08069548 (src/08069548.c). */
typedef struct {
    u8 *state;
    u32 next_state;
    u32 selection;
} MenuChoice;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

/* The list at +0x2C, the controls at +0x4C and +0x60 that func_0802A290
 * and func_08016234 address (src/0802A290.c, src/08016234.c). */
typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuControls controls;
    MenuControls arrows;
} Window;

typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0xCD8 - 0xB54];
    u8 message[0x1478 - 0xCD8];
    u8 state;
    u8 resume;
    u8 unknown_147A[2];
    Table runner;
    u8 unknown_148C[0x1494 - 0x148C];
    Window window;
    u8 content[0x4418 - 0x1508];
    ButtonAction actions[2];
    u8 unknown_4430[0x443C - 0x4430];
    MenuChoice choice;
    u8 unknown_4448[0x446C - 0x4448];
    u8 selection;
    u8 unknown_446D[0x4AE6 - 0x446D];
    /* The greetings still to show: message offsets ended by 0xFFFF. */
    u16 queue[5];
    u8 queue_index;
    u8 unknown_4AF1[3];
    u8 tiles_4AF4[0x4B9C - 0x4AF4];
    u8 tiles_4B9C[0x4BFB - 0x4B9C];
    u8 type;
    u8 style;
    u8 message_base;
    /* func_080CC8D0 (src/080CC8D0.c): 1 when a step reached since the
     * shop type's saved step has an entry in its table. */
    u8 new_stock;
    u8 unknown_4BFF;
    u8 unknown_4C00;
} MenuContext;

extern MenuContext *data_0200F428;
extern MenuInput data_03000000;
extern GraphicsState data_030008B0;
extern GraphicsState data_03000990;
extern GameState g_state_02000000;
extern u8 data_0600B000[];
extern u8 data_0600C800[];
extern const ShopMessages data_08393B1C[5];
extern const u16 data_08393B30[3];
extern const u16 data_08393B36[4];
extern const u16 data_0852A13E[];
extern const u8 *const g_table_085567F0[];

extern u8 func_08036350(u8 value);
extern u32 func_080CC8D0(u8 table);
extern void func_0802A4B4(u8 right, u8 bottom, u8 left, u8 top);
extern void func_08017D18(void *control, u8 flags);
extern void func_0806E960(void);
extern u8 func_0802B548(void *message);
extern void func_0802B048(void *message, u8 first, u8 second, u8 third,
                          u8 fourth, u16 fifth);
extern void func_0802B59C(void *message, u8 value);
extern void func_0802B590(void *message, u8 value);
extern void func_0806F028(void *tiles);
extern void func_0806F2E0(void *tiles);
extern u8 func_080C9540(u16 bit_index);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern void func_080CBC94(void);
extern void func_080CC788(void);
extern void func_0802B53C(void *message, u8 value);
extern void func_0802B56C(void *message, u8 value);
extern void func_0802B554(void *message, u8 value);
extern void func_0802A1FC(Window *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802B368(Window *window, u8 *destination, u8 first,
                          u8 second);
extern u8 func_08017180(Window *window);
extern void func_08016210(Window *window, const void *content, u16 first,
                          u16 second);
extern void func_0806E60C(const void *text, MenuList *list, s8 row, u8 style);
extern void func_08017AD8(MenuList *list);
extern void func_08015D58(Window *window, MenuCallback draw,
                          MenuCallback cursor);
extern void func_08017E80(void *arrows);
extern void func_08017AF4(MenuList *list, u32 row, u32 value);
extern void func_08029F7C(Window *window, u8 flags, MenuCallback scroll,
                          void *argument, const ButtonAction *actions,
                          u8 action_count);
extern void func_08016234(Window *window);
extern void func_08019AE4(void *context, u16 value, void *first, void *second,
                          u16 field);
extern void func_08013390(void *state);
extern void func_08013434(void);
extern void func_0802A290(Window *window, u8 appearance);
extern u16 func_08011860(void);
extern void func_0802A534(void);
extern void func_08006B5C(Table *runner);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_08069548(void *argument);
extern void func_08069574(void *argument);
extern void func_08069658(u8 index, u8 *state);
extern void func_0806B6D0(u8 index, u8 *state);
extern void func_0806D664(u8 index, u8 *state);

/* The cursor row is read through the controls record's address: both reads
 * add 0x14E0 to the context (0x08069364, 0x0806938E) and load [base, #0x11]
 * (0x08069394), as in src/08054E14.c, src/08055F10.c and src/0805ADA4.c. */
#define CURSOR_ROW(controls) ((controls)->row)

void func_08068C10(u8 index, u8 *state)
{
    u8 i;
    u8 count;
    u16 help;

    switch (*state) {
    case 0:
        data_0200F428->type = func_08036350(g_state_02000000.selection);
        for (i = 0; i < 5; i++) {
            if (data_08393B1C[i].type == data_0200F428->type) {
                data_0200F428->style = data_08393B1C[i].style;
                data_0200F428->message_base = data_08393B1C[i].message_base;
            }
        }
        data_0200F428->new_stock = func_080CC8D0(data_0200F428->type);
        func_0802A4B4(0, 0, 240, 160);
        func_08017D18(&data_0200F428->window.controls, 0);
        func_08017D18(&data_0200F428->window.arrows, 0);
        func_0806E960();
        func_0802B048(data_0200F428->message,
                      func_0802B548(data_0200F428->message), 4,
                      data_0200F428->message_base, data_0200F428->style,
                      (data_0600B000 - data_030008B0.tiles) / 32);
        func_0802B59C(data_0200F428->message, 0);
        func_0802B590(data_0200F428->message, 1);
        func_0806F028(data_0200F428->tiles_4AF4);
        func_0806F2E0(data_0200F428->tiles_4B9C);
        data_0200F428->unknown_4BFF = 0;
        data_0200F428->unknown_4C00 = 0;
        *state = 80;
        break;
    case 80:
        if (func_080C9540(0x3D)) {
            func_080CBC94();
            func_080C9574(0x3D, 0);
            func_0802B53C(data_0200F428->message, 1);
            func_0802B56C(data_0200F428->message, 11);
            func_0802B554(data_0200F428->message, 0x3D);
            *state = 81;
        } else if (func_080C9540(0x3A) && func_080C9540(0x31A)) {
            /* The ROM keeps both greeting bodies (0x08068E3C, 0x08068E90). */
            func_080CC788();
            func_080C9574(0x3A, 0);
            func_0802B53C(data_0200F428->message, 1);
            func_0802B56C(data_0200F428->message, 11);
            func_0802B554(data_0200F428->message, 0x3D);
            *state = 81;
        } else {
            *state = 100;
        }
        break;
    case 81:
        if (!func_0802B548(data_0200F428->message))
            *state = 100;
        break;
    case 100:
        func_0802B56C(data_0200F428->message, data_0200F428->style);
        count = 0;
        if (func_080C9540(0x3B) || data_0200F428->new_stock) {
            data_0200F428->queue[count] = 9;
            count++;
            if (func_080C9540(0x3B))
                func_080C9574(0x3B, 0);
        } else if (func_080C9540(0x3C)) {
            data_0200F428->queue[count] = 10;
            count++;
            func_080C9574(0x3C, 0);
        }
        if (count) {
            data_0200F428->queue[count] = 0xFFFF;
            data_0200F428->queue_index = 0;
            *state = 60;
        } else {
            *state = 1;
        }
        break;
    case 60:
        if (!func_0802B548(data_0200F428->message))
            func_0802B53C(data_0200F428->message, 1);
        else
            func_0802B53C(data_0200F428->message, 4);
        func_0802B554(data_0200F428->message,
                      data_0200F428->queue[data_0200F428->queue_index]
                          + data_0200F428->message_base);
        *state = 61;
        break;
    case 61:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            data_0200F428->queue_index++;
            if (data_0200F428->queue[data_0200F428->queue_index] == 0xFFFF)
                *state = 3;
            else
                *state = 60;
        }
        break;
    case 1:
        if (!func_0802B548(data_0200F428->message))
            func_0802B53C(data_0200F428->message, 1);
        else
            func_0802B53C(data_0200F428->message, 4);
        func_0802B554(data_0200F428->message, data_0200F428->message_base);
        *state = 2;
        break;
    case 2:
        if (func_0802B548(data_0200F428->message) == 5)
            *state = 3;
        break;
    case 3:
        func_0802A1FC(&data_0200F428->window, 0, 9, 12,
                      func_080C9540(0x31A) ? 11 : 9, 0x180, 0);
        func_0802B368(&data_0200F428->window, data_0200F428->text, 3, 0);
        *state = 4;
        break;
    case 4:
        if (func_08017180(&data_0200F428->window)) {
            func_08016210(&data_0200F428->window, data_0200F428->content,
                          (data_0600C800 - data_030008B0.tiles) / 32,
                          func_080C9540(0x31A) ? 11 : 9);
            if (func_080C9540(0x31A)) {
                func_0806E60C(g_table_085567F0[33], &data_0200F428->window.list, 0, 0);
                func_0806E60C(g_table_085567F0[34], &data_0200F428->window.list, 1, 0);
                func_0806E60C(g_table_085567F0[35], &data_0200F428->window.list, 2, 0);
                func_0806E60C(g_table_085567F0[32], &data_0200F428->window.list, 3, 0);
            } else {
                func_0806E60C(g_table_085567F0[33], &data_0200F428->window.list, 0, 0);
                func_0806E60C(g_table_085567F0[34], &data_0200F428->window.list, 1, 0);
                func_0806E60C(g_table_085567F0[32], &data_0200F428->window.list, 2, 0);
            }
            func_08017AD8(&data_0200F428->window.list);
            func_08015D58(&data_0200F428->window, func_08017E80, 0);
            func_08017D18(&data_0200F428->window.controls, 3);
            func_08017AF4(&data_0200F428->window.list, 0, 11);
            data_0200F428->actions[0].buttons = 2;
            data_0200F428->actions[0].callback = func_08069548;
            data_0200F428->actions[0].argument = &data_0200F428->choice;
            data_0200F428->choice.state = state;
            data_0200F428->choice.next_state = 20;
            data_0200F428->choice.selection = 40;
            data_0200F428->actions[1].buttons = 1;
            data_0200F428->actions[1].callback = func_08069574;
            data_0200F428->actions[1].argument = state;
            /* The second call of the two (0x08069288, 0x080692E4). */
            func_08017D18(&data_0200F428->window.controls, 3);
            *state = 5;
        }
        break;
    case 5:
        func_08029F7C(&data_0200F428->window, 0x80, 0, 0,
                      data_0200F428->actions, 2);
        func_08016234(&data_0200F428->window);
        if (data_03000000.pressed & 4) {
            /* Each arm forms the table and the controls' address itself
             * (0x0806935E, 0x08069388); they share the tail at 0x08069394. */
            if (func_080C9540(0x31A))
                help = data_0852A13E[data_08393B36[CURSOR_ROW(&data_0200F428->window.controls)]];
            else
                help = data_0852A13E[data_08393B30[CURSOR_ROW(&data_0200F428->window.controls)]];
            func_08019AE4(data_0200F428, help, &data_030008B0, &data_03000990, 2);
            func_08013390(data_0200F428);
            func_08013434();
            *state = 200;
            data_0200F428->resume = 5;
        }
        break;
    case 20:
        func_0802A290(&data_0200F428->window, 0);
        *state = 21;
        break;
    case 21:
        if (func_08017180(&data_0200F428->window))
            *state = data_0200F428->selection;
        break;
    case 22:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_08069658);
        break;
    case 23:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_0806B6D0);
        break;
    case 24:
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_0806D664);
        break;
    case 40:
        func_0802B53C(data_0200F428->message, 4);
        func_0802B554(data_0200F428->message, data_0200F428->message_base + 8);
        *state = 41;
        break;
    case 41:
        if (!func_0802B548(data_0200F428->message))
            *state = 255;
        break;
    case 200:
        if (func_08011860()) {
            func_08013390(data_0200F428->message);
            *state = data_0200F428->resume;
        }
        break;
    case 255:
        func_0802A534();
        func_08006B5C(&data_0200F428->runner);
        data_0200F428->state = 0xFE;
        func_0802A2C0(0, 0, 0, 0);
        break;
    }
}
