#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 identifier : 10;
    u16 unknown_0A : 6;
    u8 unknown_02[2];
    u8 required[2];
} Unit;

typedef struct {
    u8 unknown_00[0x16];
    u16 identifier;
} SelectionEntry;

typedef struct {
    u8 unknown_0000[0x1199];
    u8 state;
    u8 next;
    u8 resume;
    u8 timer;
    u8 selection;
    u8 unknown_119E[2];
    u8 unknown_11A0;
    u8 initialized;
    u8 unknown_11A2[2];
    u16 cost;
    u16 unknown_11A6;
    u8 unit_count;
    u8 unknown_11A9[0x43];
    void *units[23];
    u8 unknown_1248[0x208];
    Unit *current;
    SelectionEntry *selected;
} MenuState;

typedef struct {
    void *resource;
    u8 unknown_04[12];
    u8 selection;
    u8 count;
} ResourceSelection;

typedef struct {
    u16 held;
    u16 pressed;
} Input;

typedef struct {
    u8 unknown_0000[0x219E];
    u16 pending;
} RootState;

extern MenuState *data_0200F448;
extern RootState g_state_02000000;
extern ResourceSelection g_state_020020D0;
extern Input data_03000000;
extern u8 data_030008B0[];
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 width, s16 height, u8 enabled);
extern void func_0805E798(void);
extern void func_0805E864(void);
extern void func_0805E924(void);
extern void func_0805EA0C(void);
extern void func_0805F44C(u8 id);
extern void func_0805F540(void *const *entries, s32 count);
extern s16 func_0805F4AC(void);
extern u16 func_08011860(void);
extern void func_08061028(void *context, u8 entry);
extern void func_08061518(void *context, u8 index);
extern void func_080610F8(u8 entry);
extern u8 func_0805DA10(u8 selection, u8 count, u8 mode);
extern u8 func_0805D4EC(void);
extern void func_0805DAA8(u8 option);
extern void func_0805D948(void);
extern u32 func_0805DF94(void);
extern u8 func_08060DE0(void);
extern u8 func_0805E354(void);
extern u8 func_0805E5C0(void);
extern s8 func_08013380(void);
extern void func_08013390(void *state);
extern void func_08013364(void);
extern void func_08060DEC(u8 index, u8 value);
extern void func_080D0B48(Unit *record, SelectionEntry *object, u16 first,
                          u16 second);
extern void func_0805D108(u16 value);
extern void func_0805D13C(u16 value);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern Unit *func_080D2D54(void);
extern void func_080D0ED4(Unit *unit);

/* Target [0x0805EAA8, 0x0805EFEA), 1346 bytes including the jump table
 * and literal pools. */
u32 func_0805EAA8(void)
{
    s8 result;
    u16 finished;
    u8 next;
    u8 handled;
    Unit *unit;

    switch (data_0200F448->state) {
    case 0:
        func_0805E798();
        data_0200F448->next = 4;
        data_0200F448->state = 1;
        break;
    case 1:
        if (func_0805F4AC())
            data_0200F448->state = data_0200F448->next;
        break;
    case 2:
        if (func_08011860())
            data_0200F448->state = data_0200F448->next;
        func_0805D948();
        break;
    case 3:
        finished = func_08011860();
        func_0805F4AC();
        if (finished)
            data_0200F448->state = data_0200F448->next;
        break;
    case 18:
        func_08061028(data_0200F448, data_0200F448->selection);
        data_0200F448->next = data_0200F448->resume;
        data_0200F448->state = 2;
        break;
    case 19:
        func_08061518(data_0200F448, g_state_020020D0.selection);
        data_0200F448->next = data_0200F448->resume;
        data_0200F448->state = 2;
        break;
    case 4:
        if (func_0805DA10(0, 3, 0))
            return func_0805D4EC();
        break;
    case 5:
        func_0805DAA8(0);
        func_0805D948();
        break;
    case 6:
        next = func_0805DF94();
        if (next == 0)
            data_0200F448->unknown_11A0 = 1;
        func_08061028(data_0200F448, data_0200F448->selection);
        data_0200F448->next = next;
        data_0200F448->state = 2;
        break;
    case 7:
        func_0802A2C0(0, 0, 0, 0);
        func_0805F44C(4);
        func_0805F540(data_0200F448->units, data_0200F448->unit_count);
        data_0200F448->next = 8;
        data_0200F448->state = 1;
        break;
    case 8:
        func_0805E864();
        break;
    case 20:
        func_08013364();
        if (data_0200F448->selected != 0)
            data_0200F448->selected->identifier = 0;
        func_080610F8(0x4C);
        data_0200F448->next = 7;
        data_0200F448->state = 2;
        break;
    case 9:
        func_0805E924();
        break;
    case 10:
        handled = 0;
        switch (func_08060DE0()) {
        case 5:
            handled = func_0805E354();
            break;
        case 6:
            handled = func_0805E5C0();
            break;
        }
        if (handled)
            func_0805F4AC();
        break;
    case 11:
        func_0802A2C0(0, 0, 0, 0);
        func_0805F44C(6);
        func_08060DEC(6, 0);
        data_0200F448->next = 10;
        data_0200F448->state = 1;
        func_0805F4AC();
        break;
    case 12:
        func_08013364();
        if (g_state_020020D0.count == 4)
            func_080610F8(0x56);
        data_0200F448->resume = 5;
        data_0200F448->next = 19;
        data_0200F448->state = 2;
        break;
    case 13:
        result = func_08013380();
        func_08013390(data_0200F448);
        if (result < 0) {
            data_0200F448->state = 5;
            break;
        }
        if (result > 0) {
            func_08013364();
            data_0200F448->selection = 0x55;
            data_0200F448->resume = 15;
            data_0200F448->next = 18;
            data_0200F448->state = 2;
        } else {
            func_08013364();
            data_0200F448->next = 14;
            data_0200F448->state = 2;
        }
        break;
    case 14:
        if (data_0200F448->cost == 0) {
            data_0200F448->selection = 0x4F;
            data_0200F448->resume = 17;
            data_0200F448->state = 18;
        } else {
            data_0200F448->unknown_11A6 = 0;
            data_0200F448->timer = 0;
            data_0200F448->selection = 0x4E;
            data_0200F448->resume = 16;
            data_0200F448->state = 18;
        }
        func_08029E48(data_030008B0, 0, 0, 20, 17, 1);
        break;
    case 16:
        func_0805EA0C();
        break;
    case 15:
        func_08013364();
        data_0200F448->initialized = 0;
        data_0200F448->unknown_11A0 = 1;
        data_0200F448->next = 0;
        data_0200F448->state = 2;
        break;
    case 17:
        if (data_03000000.pressed & 1) {
            data_0200F448->initialized = 0;
            func_08060DEC(3, 0);
            func_080D0B48(data_0200F448->current, data_0200F448->selected,
                          data_0200F448->current->required[0],
                          data_0200F448->current->required[1]);
            func_0805D108(data_0200F448->current->identifier);
            g_state_02000000.pending = data_0200F448->current->identifier;
            if (data_0200F448->current->identifier == 0x17F) {
                func_080C9574(0x36, 0);
                while ((unit = func_080D2D54()) != 0) {
                    func_0805D13C(unit->identifier);
                    func_080D0ED4(unit);
                }
            }
            data_0200F448->state = 0;
            return 7;
        }
        break;
    }
    return 4;
}
