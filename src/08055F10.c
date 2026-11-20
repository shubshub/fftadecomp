#include "ffta.h"

/* Complete [0x08055F10, 0x080570D8): 4552 bytes, 1245 instructions,
 * including the 256-entry jump table at 0x08055F34 and the literal pools.
 * A task callback (its address is a literal of func_08054664 at 0x08054CDC
 * and of func_08057578 at 0x08057B8C) that runs a unit list menu: pick a
 * unit, quote a cost and a rank (func_080CC598), confirm, pay from the money
 * word at 0x02001F64 and apply func_080CC6F0.  The twin of func_08054E14
 * (src/08054E14.c), whose context layout and CURSOR_ROW accessor it shares:
 * the case bodies reach the shared `*state = r0` store (0x080570AA) and the
 * exit (0x080570AC) through agbcc's long same-function BL jumps. */

/* The input word, the action records, the list, its controls and the two
 * BG layers are declared identically in src/08055F10.c and src/0805ADA4.c.
 * MenuList and MenuControls take the names include/item_quantity_menu.h
 * gives them; its palette byte at +0x1F is the one func_08017618 reads
 * (src/08017618.c), and data_03000990 is the second layer, whose stride
 * (+0x0C) and map (+0x14) func_0802B164 reads. */
typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 *destination;
    u32 value;
    u32 state_value;
} ByteStore;

typedef struct {
    void (*callback)(const ByteStore *store);
    const ByteStore *argument;
    u16 buttons;
    u16 unknown_0A;
} ButtonAction;

typedef struct {
    u8 unknown_00[0x1A];
    s16 position;
    u8 unknown_1C[3];
    u8 palette;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *map;
} GraphicsState;

/* Two 0x14-byte records follow the list: the controls at +0x14DC, whose
 * cursor row func_0805872C sets, and at +0x14F0 the one whose scroll flags
 * func_080583FC sets (it takes 0x14F0 and 0x14DC). */
typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 unknown_12[0x2C - 0x12];
    MenuList list;
    MenuControls controls;
    MenuControls arrows;
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
    u8 content[0x19C8 - 0x1504];
    u8 detail[0x1C58 - 0x19C8];
    u8 control[0x2CE4 - 0x1C58];
    ButtonAction actions[2];
    u8 unknown_2CFC[0x2D08 - 0x2CFC];
    ByteStore store;
    u8 unknown_2D14[0x2D38 - 0x2D14];
    u8 next;
    u8 resume;
    u8 entries[24];
    u8 count;
    u8 unknown_2D53[2];
    u8 selected;
    u8 unknown_2D56[2];
    u32 cost;
    u8 rank;
    u8 unknown_2D5D[0x2DAF - 0x2D5D];
    u8 idle;
    u8 unknown_2DB0[0x2E08 - 0x2DB0];
    u8 *backup_first;
    u8 *backup_second;
    u8 control_flags[0x50];
} MenuContext;

/* The unit record: +0x04 is the kind func_080CC598 tests against 2 and 15,
 * +0x102 and +0x103 the counts it weights into the cost. */
typedef struct {
    u8 unknown_000[4];
    u8 kind;
    u8 unknown_005[0x102 - 0x005];
    u8 count;
    u8 base;
    u8 unknown_104[4];
} Unit;

typedef struct {
    u8 unknown_0000[0x80];
    Unit units[24];
    u8 unknown_1940[0x1F64 - 0x1940];
    u32 money;
} GameState;

extern MenuContext *data_0200F428;
extern MenuInput data_03000000;
extern GraphicsState data_030008B0;
extern GraphicsState data_03000990;
extern void *data_030027F4;
extern u8 data_0600C000[];
extern GameState g_state_02000000;
extern u8 g_state_0200F390;
/* include/control_flags.h declares this block as a structure with volatile
 * register members.  Here only its address is used, for the two 0x50-byte
 * copies through func_081443FC (0x08056F80, 0x08057074), as in the merged
 * twin 08054E14 and in 0806094C, 08070414, 080651FC and 080312A8. */
extern u8 g_control_flags_03000940[];

extern void func_08029D20(void *control, u8 mode);
extern u8 func_08029D2C(void *control);
extern void func_08029CD8(void *control, u8 first, u8 second);
extern void func_0802995C(void *control);
extern u8 func_0805459C(void);
extern void func_0802B53C(void *message, u8 value);
extern u8 func_0802B548(void *message);
extern void func_0802B554(void *message, u8 value);
extern void func_0802A1FC(Window *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802B368(Window *window, u8 *destination, u8 first,
                          u8 second);
extern u8 func_08017180(Window *window);
extern void func_0802A290(Window *window, u8 appearance);
extern void func_08016234(Window *window);
extern void func_080570D8(u8 position, u8 direction);
extern void func_0805463C(const ByteStore *store);
extern void func_08054664(u8 index, u8 *state);
extern void func_08057578(u8 index, u8 *state);
extern void func_08057270(u8 *state);
extern void func_08057298(void);
extern void func_0802B460(void *grid, u8 x, u8 y);
extern void func_0802B2E8(void *tilemap, u8 x, u8 y, u8 width, u8 height);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);
extern void func_0805872C(MenuControls *controls, u8 value);
extern u8 func_0805871C(MenuList *list, u8 value);
extern void func_08141540(u16 song_id);
extern void func_080573E8(void);
extern void func_08057500(u8 selected);
extern void func_08057454(u8 selected, u8 x, u8 y);
extern void func_080581AC(Window *window, void (*changed)(void), void *context,
                          u8 visible_count, const ButtonAction *actions,
                          u8 action_count);
extern void func_080583FC(MenuControls *arrows, MenuControls *controls);
extern void func_08017424(Window *window, u16 *first, u16 *second, u8 x, u8 y,
                          u8 width, u8 height, u16 value14, u8 value16,
                          u16 value18, u16 value1A, u8 value17);
extern void func_08016C90(Window *window, u8 mode);
extern void func_080CC598(Unit *unit, u32 *out_value, u8 *out_rank);
extern void func_0802ACA0(u16 *destination, u16 tile, u8 palette, u16 count);
extern void func_08016210(Window *window, const void *content, u16 first,
                          u16 second);
extern void func_0805843C(MenuList *list, u8 *detail, u32 value, u8 rank,
                          u8 compact);
extern void func_08017AD8(MenuList *list);
extern s8 func_08013380(void);
extern void func_080CCBFC(void);
extern void func_080CC6F0(Unit *unit, u8 mode);
extern void func_08029F18(u32 offset, void *window, u16 *buffer, u16 x, u16 y);
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08022E90(u16 duration, u8 mode);

/* The cursor row is read through the controls record's address, beside its
 * setter: at every such read the ROM adds the record's offset to the context
 * and loads [base, #0x11] next, as in src/08054E14.c. */
#define CURSOR_ROW(controls) ((controls)->row)

void func_08055F10(u8 index, u8 *state)
{
    u8 moved;
    u8 row;
    u8 selected;
    u8 x;
    u8 width;
    u8 compact;
    u8 total;
    Unit *unit;

    /* moved: 0x0805660C/0x080566CC clear it, 0x08056670/0x0805676C set it,
     * 0x08056672/0x0805676E test it. */
    switch (*state) {
    case 0:
        func_08029D20(data_0200F428->control, 4);
        data_0200F428->count = func_0805459C();
        if (data_0200F428->count == 0) {
            *state = 1;
        } else {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message, 0x62);
            *state = 20;
        }
        break;
    case 1:
        func_0802B53C(data_0200F428->message, 4);
        func_0802B554(data_0200F428->message, 0x61);
        if (func_08029D2C(data_0200F428->control) == 1) {
            func_08029D20(data_0200F428->control, 2);
            *state = 2;
        } else {
            *state = 3;
        }
        break;
    case 2:
        if (func_08029D2C(data_0200F428->control) == 4)
            *state = 3;
        break;
    case 3:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1))
            *state = 255;
        break;
    case 20:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A1FC(&data_0200F428->window, 3, 2, 0xE, 0x11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 10, 0);
            *state = 21;
        }
        break;
    case 21:
        /* 0x080564DC: the row is loaded before the list address is formed
         * (0x080564E2), as in the twin's `row` reads. */
        if (func_08017180(&data_0200F428->window)) {
            func_080570D8(0, 0);
            data_0200F428->actions[0].buttons = 2;
            data_0200F428->actions[0].callback = func_0805463C;
            data_0200F428->actions[0].argument = &data_0200F428->store;
            data_0200F428->store.destination = state;
            data_0200F428->store.value = 40;
            row = CURSOR_ROW(&data_0200F428->window.controls);
            data_0200F428->selected = func_0805871C(&data_0200F428->window.list, row);
            func_0802B460(&data_030008B0, 0x1A, 2);
            data_0200F428->idle++;
            *state = 160;
            data_0200F428->next = 22;
        }
        break;
    case 22:
        /* 0x08056560: the unit's address comes from the 0x02000080 literal
         * and the two counts are read at +0x103/+0x102 from it; the member
         * reads of cases 120 and 122 use 0x02000000 + 0x84 instead.  The sum
         * is narrowed to a byte before the compare (0x08056576). */
        unit = &g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]];
        total = unit->base + unit->count * 2;
        if (total > 6) {
            if (data_0200F428->idle > 30)
                func_08029CD8(data_0200F428->control, 0xC, 1);
            else
                data_0200F428->idle++;
        }
        if (data_03000000.pressed & 1) {
            func_08057270(state);
        } else if (data_03000000.pressed & 0x100) {
            *state = 100;
            data_0200F428->next = 22;
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x40)) {
            moved = 0;
            if (data_0200F428->window.list.position == 0) {
                if (CURSOR_ROW(&data_0200F428->window.controls) != 0) {
                    func_0805872C(&data_0200F428->window.controls, 0);
                    func_08141540(0x6D);
                    moved = 1;
                }
            } else {
                if ((s16)(data_0200F428->window.list.position - 3) < 0)
                    data_0200F428->window.list.position = 0;
                else
                    data_0200F428->window.list.position -= 3;
                func_080570D8(data_0200F428->window.list.position,
                              CURSOR_ROW(&data_0200F428->window.controls));
                func_08141540(0x6D);
                moved = 1;
            }
            if (moved) {
                row = CURSOR_ROW(&data_0200F428->window.controls);
                selected = func_0805871C(&data_0200F428->window.list, row);
                func_080573E8();
                func_08057500(selected);
                data_0200F428->idle = 0;
                data_0200F428->selected = selected;
            }
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x80)) {
            moved = 0;
            if (data_0200F428->count <= 3
                && CURSOR_ROW(&data_0200F428->window.controls)
                       != data_0200F428->count - 1) {
                func_0805872C(&data_0200F428->window.controls,
                              data_0200F428->count - 1);
                func_08141540(0x6D);
                moved = 1;
            } else if (data_0200F428->window.list.position
                       == data_0200F428->count - 3) {
                if (CURSOR_ROW(&data_0200F428->window.controls) != 2) {
                    func_0805872C(&data_0200F428->window.controls, 2);
                    func_08141540(0x6D);
                    moved = 1;
                }
            } else if (data_0200F428->count > 3) {
                if ((s16)(data_0200F428->window.list.position + 3)
                    > data_0200F428->count - 3)
                    data_0200F428->window.list.position
                        = data_0200F428->count - 3;
                else
                    data_0200F428->window.list.position += 3;
                func_080570D8(data_0200F428->window.list.position,
                              CURSOR_ROW(&data_0200F428->window.controls));
                func_08141540(0x6D);
                moved = 1;
            }
            if (moved) {
                row = CURSOR_ROW(&data_0200F428->window.controls);
                selected = func_0805871C(&data_0200F428->window.list, row);
                func_080573E8();
                func_08057500(selected);
                data_0200F428->idle = 0;
                data_0200F428->selected = selected;
            }
        } else {
            func_080581AC(&data_0200F428->window, func_08057298, 0,
                          data_0200F428->count, data_0200F428->actions, 1);
            row = CURSOR_ROW(&data_0200F428->window.controls);
            selected = func_0805871C(&data_0200F428->window.list, row);
            if (data_0200F428->selected != selected) {
                func_080573E8();
                func_08057500(selected);
                data_0200F428->idle = 0;
                data_0200F428->selected = selected;
            }
        }
        if (data_0200F428->count > 3)
            func_080583FC(&data_0200F428->window.arrows,
                          &data_0200F428->window.controls);
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
        func_0802A370(0, 0, 0, 0);
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08054664);
        data_0200F428->task_state = 20;
        break;
    case 120:
        if (g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 2
            || g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 15) {
            width = 27;
            x = 1;
        } else {
            width = 22;
            x = 4;
        }
        func_08017424(&data_0200F428->window, data_030008B0.map,
                      data_03000990.map, x, 9, width, 6, 0x800, 0x20, 0xD, 3,
                      0xB);
        func_08016C90(&data_0200F428->window, 1);
        func_0802A370(1, 9, 27, 6);
        *state = 121;
        break;
    case 121:
        if (func_08017180(&data_0200F428->window)) {
            func_080CC598(&g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]],
                          &data_0200F428->cost, &data_0200F428->rank);
            func_0802ACA0(&data_03000990.map[data_0200F428->window.y * 32
                                             + data_0200F428->window.x + 1],
                          0x340, 0xB, 4);
            func_08016210(&data_0200F428->window, data_0200F428->content,
                          (data_0600C000 - data_030008B0.tiles) / 32, 2);
            data_0200F428->window.list.palette = 11;
            if (g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 2
                || g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 15)
                compact = 1;
            else
                compact = 0;
            func_0805843C(&data_0200F428->window.list, data_0200F428->detail,
                          data_0200F428->cost, data_0200F428->rank, compact);
            func_08017AD8(&data_0200F428->window.list);
            *state = 122;
        }
        break;
    case 122:
        if (g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 2
            || g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 15) {
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message, 0x68);
        } else {
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message, 0x64);
        }
        func_0802B2E8(&data_030008B0, 0x1A, 2, 3, 2);
        *state = 123;
        break;
    case 123:
        if (func_0802B548(data_0200F428->message) != 5)
            break;
        if (func_08013380() == 0) {
            /* 0x08056B7C branches to the shortfall block at 0x08056C50,
             * placed after the payment. */
            if (g_state_02000000.money >= data_0200F428->cost) {
                if (g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 2
                    || g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]].kind == 15) {
                    *state = 240;
                } else {
                    func_0802B53C(data_0200F428->message, 4);
                    func_0802B554(data_0200F428->message, 0x65);
                    *state = 125;
                }
                func_080CCBFC();
                func_080CC6F0(&g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]],
                              data_0200F428->rank);
                data_0200F428->count = func_0805459C();
                g_state_02000000.money -= data_0200F428->cost;
                func_08029F18(0, &data_030008B0, 0, 0x14, 0x11);
            } else {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message, 0x63);
                *state = 124;
            }
        } else if (func_08013380() == 1) {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message, 0x67);
            *state = 124;
        } else if (func_08013380() == -1) {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B53C(data_0200F428->message, 6);
            *state = 124;
        }
        func_0802A290(&data_0200F428->window, 1);
        break;
    case 124:
        if (func_0802B548(data_0200F428->message) == 0
            && func_08017180(&data_0200F428->window)) {
            func_0802A370(0, 0, 0, 0);
            func_0802A1FC(&data_0200F428->window, 3, 2, 0xE, 0x11, 0xC0, 1);
            func_0802B368(&data_0200F428->window, data_0200F428->text, 10, 0);
            *state = 21;
        }
        break;
    case 125:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            if (data_0200F428->count == 0) {
                *state = 200;
                data_0200F428->next = 1;
            } else {
                func_0802B53C(data_0200F428->message, 6);
                *state = 124;
            }
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
        data_0200F428->resume = data_0200F428->next;
        func_0802A290(&data_0200F428->window, 1);
        *state = 180;
        data_0200F428->next = 221;
        break;
    case 221:
        if (func_08017180(&data_0200F428->window))
            *state = data_0200F428->resume;
        break;
    case 240:
        if (func_08017180(&data_0200F428->window)) {
            func_0802A370(0, 0, 0, 0);
            *state = 254;
        }
        break;
    case 254:
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08057578);
        data_0200F428->task_state = 0;
        break;
    case 100:
        func_081443FC(data_0200F428->control_flags, g_control_flags_03000940, 0x50);
        data_030027F4 =
            &g_state_02000000.units[data_0200F428->entries[data_0200F428->selected]];
        data_0200F428->backup_first = func_08022840(0x6C00);
        data_0200F428->backup_second = func_08022840(0x1000);
        func_0814186C(data_03000990.tiles, data_0200F428->backup_first, 0x3600);
        func_0814186C(data_03000990.map, data_0200F428->backup_second, 0x800);
        func_08022E90(4, 16);
        g_state_0200F390 = 0x1B;
        *state = 101;
        break;
    case 101:
        if (g_state_0200F390 == 0x20) {
            func_0814186C(data_0200F428->backup_first, data_03000990.tiles, 0x3600);
            func_0814186C(data_0200F428->backup_second, data_03000990.map, 0x800);
            func_08022854(data_0200F428->backup_first);
            func_08022854(data_0200F428->backup_second);
            func_081443FC(g_control_flags_03000940, data_0200F428->control_flags, 0x50);
            *state = 102;
        }
        break;
    case 102:
        if (g_state_0200F390 == 0)
            *state = data_0200F428->next;
        break;
    }
    func_0802995C(data_0200F428->control);
}
