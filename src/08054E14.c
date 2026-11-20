#include "ffta.h"

/* Complete [0x08054E14, 0x08055C38): 3620 bytes, 910 instructions,
 * including the 256-entry jump table at 0x08054E38 and the literal pools.
 * A task callback (registered through func_08006ADC at 0x08054CCC) that runs
 * the unit list menu: pick a unit, quote its cost (func_080CCC6C), confirm,
 * pay from the money word at 0x02001F64 and apply func_080CC65C.  The case
 * bodies reach the shared `*state = r0` store (0x08055C0E) and the exit
 * (0x08055C10) through agbcc's long same-function BL jumps. */

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input;

typedef struct {
    u8 *destination;
    u32 value;
    u32 state_value;
} Update;

typedef struct {
    void (*callback)(const Update *);
    const Update *argument;
    u16 buttons;
    u16 unknown_0A;
} Action;

typedef struct {
    u8 unknown_00[0x1A];
    s16 position;
    u8 unknown_1C[4];
} List;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Controls;

/* Two 0x14-byte records follow the list: the cursor at +0x14DC, whose row
 * func_0805872C sets, and at +0x14F0 the one whose scroll flags
 * func_080583FC sets (it takes 0x14F0 and 0x14DC). */
typedef struct {
    u8 unknown_00[0x2C];
    List list;
    Controls cursor;
    Controls arrows;
} Window;

typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0xCD4 - 0xB54];
    u8 message[0x1478 - 0xCD4];
    Table tasks;
    u8 unknown_1488[4];
    u8 task_state;
    u8 unknown_148D[3];
    Window window;
    u8 unknown_1504[0x1C58 - 0x1504];
    u8 control[0x2CE4 - 0x1C58];
    Action actions[2];
    u8 unknown_2CFC[0x2D08 - 0x2CFC];
    Update update;
    u8 unknown_2D14[0x2D38 - 0x2D14];
    u8 next;
    u8 unknown_2D39;
    u8 entries[24];
    u8 count;
    u8 unknown_2D53[2];
    u8 selected;
    u8 unknown_2D56[2];
    u32 cost;
    u8 unknown_2D5C[0x2E08 - 0x2D5C];
    u8 *backup_first;
    u8 *backup_second;
    u8 control_flags[0x50];
} MenuContext;

typedef struct {
    u8 unknown_000[0x108];
} Unit;

/* The record at 0x020020D0, in the same view as func_0804CBB4's.  Neither
 * shared type fits: include/ffta.h's Record has two u16 placeholders at +0x08,
 * where this function stores a word (0x08055746), and include/
 * selection_state.h's SelectionState leaves +0x00..+0x9F unknown. */
typedef struct {
    u32 unknown_00;      /* +0x00 */
    u32 field_04;        /* +0x04 */
    u32 cost;            /* +0x08 */
    u16 field_0c;        /* +0x0C */
    u8 unknown_0e[4];
    u8 unknown_12;       /* +0x12 */
} Selection;

typedef struct {
    u8 unknown_0000[0x80];
    Unit units[24];
    u8 unknown_1940[0x1F64 - 0x1940];
    u32 money;
    u8 unknown_1F68[0x20D0 - 0x1F68];
    Selection selection;
} GameState;

typedef struct {
    u8 unknown_00[0x10];
    void *first;
    void *second;
} Graphics;

extern MenuContext *data_0200F428;
extern Input data_03000000;
extern u8 data_030008B0[];
extern Graphics data_03000990;
extern void *data_030027F4;
extern GameState g_state_02000000;
extern u8 g_state_0200F390;
/* include/control_flags.h declares this block as a structure with volatile
 * register members.  Here only its address is used, for the two 0x50-byte
 * copies through func_081443FC (0x08055AE0, 0x08055BCE); the merged 0806094C,
 * 08070414, 080651FC and 080312A8 declare it this way for the same copies. */
extern u8 g_control_flags_03000940[];

extern void func_08029D20(void *control, u8 mode);
extern u8 func_08029D2C(void *control);
extern void func_08029CD8(void *control, u8 first, u8 second);
extern void func_0802995C(void *control);
extern u8 func_0805451C(void);
extern void func_0802B53C(void *message, u8 enabled);
extern u8 func_0802B548(void *message);
extern void func_0802B554(void *message, u8 id);
extern void func_0802A1FC(Window *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802B368(Window *window, u8 *destination, u8 first,
                          u8 second);
extern u8 func_08017180(Window *window);
extern void func_0802A290(Window *window, u8 appearance);
extern void func_08016234(Window *window);
extern void func_08055C38(u8 position, u8 direction);
extern void func_0805463C(const Update *update);
extern void func_08054664(u8 index, u8 *state);
extern void func_08055DC4(void);
extern void func_0802B460(void *grid, u8 x, u8 y);
extern void func_0802B2E8(void *tilemap, u8 x, u8 y, u8 width, u8 height);
extern void func_08055EC0(u8 *state);
extern void func_0805872C(Controls *controls, u8 value);
extern u8 func_0805871C(List *list, u8 value);
extern void func_08141540(u16 song_id);
extern void func_080573E8(void);
extern void func_08057500(u8 selected);
extern void func_08057454(u8 selected, u8 x, u8 y);
extern void func_080581AC(Window *window, void (*changed)(void), void *context,
                          u8 visible_count, const Action *actions,
                          u8 action_count);
extern void func_080583FC(Controls *arrows, Controls *cursor);
extern u32 func_080CCC6C(Unit *unit);
extern void func_080CC65C(Unit *unit);
extern s8 func_08013380(void);
extern void func_08029F18(u32 offset, void *window, u16 *buffer, u16 x, u16 y);
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08022E90(u16 duration, u8 mode);

/* The cursor's row is read through the cursor's address, beside its setter
 * func_0805872C: at every read the ROM adds 0x14DC to the context (0x0805544A,
 * 0x0805548A, 0x080554A6, 0x080554F8, 0x08055530, 0x08055576, 0x08055590,
 * 0x080555EC) and loads [base, #0x11] next; the folded 0x14ED offset of a
 * member chain appears nowhere. */
#define CURSOR_ROW(cursor) ((cursor)->row)

/* The 0x020020D0 record is reached the same way: 0x08055742..0x08055744 add
 * 0x2050 to the unit array base and 0x08055746 stores at [base, #8]. */
#define SELECTION (&g_state_02000000.selection)

void func_08054E14(u8 index, u8 *state)
{
    u8 moved;
    u8 row;
    u8 selected;

    /* moved: 0x08055434/0x080554E4 clear it, 0x08055498/0x08055584 set it,
     * 0x0805549A/0x08055586 test it. */
    switch (*state) {
    case 0:
        func_08029D20(data_0200F428->control, 4);
        data_0200F428->count = func_0805451C();
        if (data_0200F428->count == 0) {
            *state = 1;
        } else {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message, 0x5C);
            *state = 20;
        }
        break;
    case 1:
        func_0802B53C(data_0200F428->message, 4);
        func_0802B554(data_0200F428->message, 0x5B);
        *state = 180;
        data_0200F428->next = 2;
        break;
    case 2:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1))
            *state = 255;
        break;
    case 20:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A1FC(&data_0200F428->window, 2, 2, 0x12, 0x11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 10, 0);
            *state = 21;
        }
        break;
    case 21:
        if (func_08017180(&data_0200F428->window)) {
            func_08055C38(0, 0);
            data_0200F428->actions[0].buttons = 2;
            data_0200F428->actions[0].callback = func_0805463C;
            data_0200F428->actions[0].argument = &data_0200F428->update;
            data_0200F428->update.destination = state;
            data_0200F428->update.value = 40;
            func_0802B460(data_030008B0, 0x1A, 2);
            *state = 160;
            data_0200F428->next = 22;
        }
        break;
    case 22:
        if (data_03000000.pressed & 1) {
            func_08055EC0(state);
        } else if (data_03000000.pressed & 0x100) {
            *state = 220;
            data_0200F428->next = 22;
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x40)) {
            moved = 0;
            if (data_0200F428->window.list.position == 0) {
                if (CURSOR_ROW(&data_0200F428->window.cursor) != 0) {
                    func_0805872C(&data_0200F428->window.cursor, 0);
                    func_08141540(0x6D);
                    moved = 1;
                }
            } else {
                /* 0x08055470: the new top row is tested as a 16-bit value
                 * (lsls #16; cmp #0) and 0x0805547C stores the difference. */
                if ((s16)(data_0200F428->window.list.position - 3) < 0)
                    data_0200F428->window.list.position = 0;
                else
                    data_0200F428->window.list.position -= 3;
                func_08055C38(data_0200F428->window.list.position,
                              CURSOR_ROW(&data_0200F428->window.cursor));
                func_08141540(0x6D);
                moved = 1;
            }
            /* 0x080554A6: the row is loaded before the list address is
             * formed (0x080554AA); the same order at 0x08055590 and
             * 0x080555EC. */
            if (moved) {
                row = CURSOR_ROW(&data_0200F428->window.cursor);
                selected = func_0805871C(&data_0200F428->window.list, row);
                func_080573E8();
                func_08057500(selected);
                data_0200F428->selected = selected;
            }
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x80)) {
            moved = 0;
            if (data_0200F428->count <= 3
                && CURSOR_ROW(&data_0200F428->window.cursor)
                       != data_0200F428->count - 1) {
                func_0805872C(&data_0200F428->window.cursor,
                              data_0200F428->count - 1);
                func_08141540(0x6D);
                moved = 1;
            } else if (data_0200F428->window.list.position
                       == data_0200F428->count - 3) {
                if (CURSOR_ROW(&data_0200F428->window.cursor) != 2) {
                    func_0805872C(&data_0200F428->window.cursor, 2);
                    func_08141540(0x6D);
                    moved = 1;
                }
            } else if (data_0200F428->count > 3) {
                /* 0x0805555A: the same 16-bit test against count - 3. */
                if ((s16)(data_0200F428->window.list.position + 3)
                    > data_0200F428->count - 3)
                    data_0200F428->window.list.position
                        = data_0200F428->count - 3;
                else
                    data_0200F428->window.list.position += 3;
                func_08055C38(data_0200F428->window.list.position,
                              CURSOR_ROW(&data_0200F428->window.cursor));
                func_08141540(0x6D);
                moved = 1;
            }
            if (moved) {
                row = CURSOR_ROW(&data_0200F428->window.cursor);
                selected = func_0805871C(&data_0200F428->window.list, row);
                func_080573E8();
                func_08057500(selected);
                data_0200F428->selected = selected;
            }
        } else {
            func_080581AC(&data_0200F428->window, func_08055DC4, 0,
                          data_0200F428->count, data_0200F428->actions, 1);
            row = CURSOR_ROW(&data_0200F428->window.cursor);
            selected = func_0805871C(&data_0200F428->window.list, row);
            if (data_0200F428->selected != selected) {
                func_080573E8();
                func_08057500(selected);
                data_0200F428->selected = selected;
            }
        }
        if (data_0200F428->count > 3)
            func_080583FC(&data_0200F428->window.arrows,
                          &data_0200F428->window.cursor);
        func_08016234(&data_0200F428->window);
        break;
    case 40:
        func_0802A290(&data_0200F428->window, 1);
        *state = 180;
        data_0200F428->next = 41;
        break;
    case 41:
        if (func_08017180(&data_0200F428->window))
            *state = 255;
        break;
    case 255:
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08054664);
        data_0200F428->task_state = 20;
        break;
    case 100:
        *state = 200;
        data_0200F428->next = 101;
        break;
    case 101:
        func_0802B53C(data_0200F428->message, 1);
        func_0802B554(data_0200F428->message, 0x5E);
        func_0802B2E8(data_030008B0, 0x1A, 2, 3, 2);
        data_0200F428->cost = func_080CCC6C(
            &g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]]);
        SELECTION->cost = data_0200F428->cost;
        *state = 102;
        break;
    case 102:
        if (func_0802B548(data_0200F428->message) != 5)
            break;
        func_0802B53C(data_0200F428->message, 4);
        if (func_08013380() == 0) {
            if (g_state_02000000.money < data_0200F428->cost) {
                func_0802B554(data_0200F428->message, 0x5F);
                *state = 103;
                break;
            }
            g_state_02000000.money -= data_0200F428->cost;
            func_08029F18(0, data_030008B0, 0, 0x14, 0x11);
            func_08029CD8(data_0200F428->control, 0x18, 1);
            func_080CC65C(
                &g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]]);
            data_0200F428->count = func_0805451C();
            func_0802B554(data_0200F428->message, 0x60);
            *state = 104;
        } else if (func_08013380() == 1) {
            func_0802B554(data_0200F428->message, 0x67);
            *state = 103;
        } else if (func_08013380() == -1) {
            func_0802B53C(data_0200F428->message, 6);
            *state = 103;
        }
        break;
    case 103:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A1FC(&data_0200F428->window, 2, 2, 0x12, 0x11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 3, 0);
            *state = 21;
        }
        break;
    case 104:
        *state = 105;
        break;
    case 105:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            if (data_0200F428->count == 0) {
                *state = 1;
            } else {
                func_0802B53C(data_0200F428->message, 6);
                *state = 103;
            }
        }
        break;
    case 120:
        *state = 200;
        data_0200F428->next = 121;
        break;
    case 121:
        func_0802B53C(data_0200F428->message, 1);
        func_0802B554(data_0200F428->message, 0x5D);
        func_0802B2E8(data_030008B0, 0x1A, 2, 3, 2);
        *state = 122;
        break;
    case 122:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A1FC(&data_0200F428->window, 2, 2, 0x12, 0x11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 10, 0);
            *state = 21;
        }
        break;
    case 160:
        if (func_08029D2C(data_0200F428->control) == 4) {
            func_08057454(data_0200F428->selected, 0x16, 9);
            *state = 161;
        } else {
            func_08057500(data_0200F428->selected);
            *state = data_0200F428->next;
        }
        break;
    case 161:
        if (func_08029D2C(data_0200F428->control) == 1)
            *state = data_0200F428->next;
        break;
    case 180:
        if (func_08029D2C(data_0200F428->control) == 1) {
            func_08029D20(data_0200F428->control, 2);
            *state = 181;
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 181:
        if (func_08029D2C(data_0200F428->control) == 4)
            *state = data_0200F428->next;
        break;
    case 200:
        func_0802A290(&data_0200F428->window, 1);
        *state = 201;
        break;
    case 201:
        if (func_08017180(&data_0200F428->window))
            *state = data_0200F428->next;
        break;
    case 220:
        func_081443FC(data_0200F428->control_flags, g_control_flags_03000940, 0x50);
        data_030027F4 =
            &g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]];
        data_0200F428->backup_first = func_08022840(0x6C00);
        data_0200F428->backup_second = func_08022840(0x1000);
        func_0814186C(data_03000990.first, data_0200F428->backup_first, 0x3600);
        func_0814186C(data_03000990.second, data_0200F428->backup_second, 0x800);
        func_08022E90(4, 16);
        g_state_0200F390 = 0x1B;
        *state = 221;
        break;
    case 221:
        if (g_state_0200F390 == 0x20) {
            func_0814186C(data_0200F428->backup_first, data_03000990.first, 0x3600);
            func_0814186C(data_0200F428->backup_second, data_03000990.second, 0x800);
            func_08022854(data_0200F428->backup_first);
            func_08022854(data_0200F428->backup_second);
            func_081443FC(g_control_flags_03000940, data_0200F428->control_flags, 0x50);
            *state = 222;
        }
        break;
    case 222:
        if (g_state_0200F390 == 0)
            *state = data_0200F428->next;
        break;
    }
    func_0802995C(data_0200F428->control);
}
