#include "ffta.h"

/* Complete [0x08028DE0, 0x08028FF4): 532 bytes, 222 instructions, eleven
 * literal words in nine pools.
 * 70b50d1c141c2988064eb14276d0b14214dc80225200914231d0914204dc002926d0f1e0
 * 03010000034881425ed00130814276d0e8e000000101000083267600b14200d1b6e0b142
 * 07dc82204000814228d0013081422ad0d6e084204000814256d0814233db0130814200d1
 * aae0cbe02060dcf7d1fe6060a88a2072c4e0201cfef79eff201cfff735fa201cfff758fe
 * 0006002802d083204000b4e00048b2e001010000201cfff7c1f80320abe0201c0c30eef7
 * 75f90006002800d1a4e0201c8030807c2168fcf783fa2e809ce005480168207a01300871
 * 201cfff7f3f9024891e0000038f4000201010000201cfff73ffa0006002800d186e082e0
 * 201cfff75dfa0006002800d17ee0822040007ae0201cfff749ff000600284bd081204000
 * 47e0201cfff734fd0006002842d0074908680023c25e02204042824211d0824206dc0138
 * 824212d016e0000038f4000201204042824202d0002a0dd12ae02e8028e0201cfff7aefe
 * 8420400021e001481fe0000009010000201c90300a680023c15e0023d05e814212d1207a
 * 8000064940181018211c523109880180211c693109784180014804e04404000005010000
 * 03482880201c0c30edf74cf924e0000003010000201c6c30eef73eff201c0c30edf740f9
 * 0e4e30680079022811d1201c3830211c6931097809060916eef7ccfd32680004211c9431
 * 0968800b401800689061812040002880002070bc02bc084738f40002
 */
/* The object and control are those of src/08028970.c (window, unit, cursor,
 * entries; status, mode, selected); task, index, top, row and the options
 * at 0x80 are those of src/08028B20.c, which restores the position this
 * function saves; the saved positions at 0x444 are those of src/080284A0.c;
 * the second control at 0x6C is that of src/08028D88.c. */
typedef struct {
    u8 unknown_00[0x1A];
    s16 top;
    u8 unknown_1C[4];
} NavigationUnit;

typedef struct {
    u8 unknown_00[0x10];
    s16 selection;
    u8 mode;
    u8 unknown_13;
} NavigationOptions;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
    u8 second[0x14];
    NavigationOptions options;
} NavigationCursor;

typedef struct NavigationState {
    void *task;
    void *parent;
    u8 index;
    u8 unknown_09;
    u8 byte_0A;
    u8 unknown_0B;
    u8 window[0x2C];
    NavigationUnit unit;
    NavigationCursor cursor;
    u32 *entries;
} NavigationState;

typedef struct {
    s16 top;
    s16 row;
} NavigationPosition;

typedef struct {
    s16 status;
    u8 unknown_02[2];
    u8 mode;
    u8 byte_05;
    u8 unknown_06[2];
    u16 value_08;
    u8 unknown_0A[6];
    u16 value_10;
    u8 unknown_12[2];
    u32 value_14;
    u32 selected;
    u32 value_1C;
    u8 unknown_20[0x424];
    NavigationPosition positions[1];
} NavigationControl;

typedef struct TaskEvent {
    u16 state;
    u8 unknown_02[0x12];
    u16 argument;
    u8 unknown_16[6];
} TaskEvent;

extern NavigationControl *data_0200F438;
extern void *func_08005BF8(const void *object);
extern void func_08027DA0(NavigationState *state);
extern void func_080282D4(NavigationState *state);
extern u8 func_08028B20(NavigationState *state);
extern void func_0802800C(NavigationState *state);
extern u8 func_08017180(void *window);
extern void func_080253B0(u8 mode, void *task);
extern void func_080282A4(NavigationState *state);
extern u8 func_08028350(NavigationState *state);
extern u8 func_0802839C(NavigationState *state);
extern u8 func_08028D88(NavigationState *state);
extern u8 func_08028970(NavigationState *state);
extern void func_08028CA4(NavigationState *state);
extern void func_08016234(void *window);
extern void func_08017E28(void *control);
extern u16 func_08017B68(NavigationUnit *unit, u32 row);

u32 func_08028DE0(void *task, TaskEvent *event, NavigationState *state)
{
    switch (event->state) {
    case 0:
        state->task = task;
        state->parent = func_08005BF8(task);
        state->index = event->argument;
        break;
    case 1:
        break;
    case 0x100:
        func_08027DA0(state);
        func_080282D4(state);
        if (func_08028B20(state))
            event->state = 0x106;
        else
            event->state = 0x101;
        break;
    case 0x104:
        func_0802800C(state);
        event->state = 3;
        break;
    case 0x105:
        if (func_08017180(state->window)) {
            NavigationOptions *options = &state->cursor.options;

            func_080253B0(options->mode, state->task);
            event->state = 0x106;
        }
        break;
    case 0x107:
        data_0200F438->mode = state->index + 1;
        func_080282A4(state);
        event->state = 0x101;
        break;
    case 0x101:
        if (func_08028350(state))
            event->state = 0x102;
        break;
    case 0x103:
        if (func_0802839C(state))
            event->state = 0x104;
        break;
    case 0x108:
        if (func_08028D88(state))
            event->state = 0x102;
        func_08016234(state->window);
        break;
    case 0x102:
        if (func_08028970(state)) {
            switch (data_0200F438->status) {
            case 0:
                break;
            case -1:
                event->state = 0x103;
                break;
            case -2:
                func_08028CA4(state);
                event->state = 0x108;
                break;
            case -3:
                event->state = 0x109;
                break;
            default:
                if (state->cursor.options.selection == data_0200F438->status) {
                    NavigationPosition *position =
                        &data_0200F438->positions[state->index];

                    position->top = state->unit.top;
                    position->row = (u8)state->cursor.row;
                    event->state = 0x105;
                } else {
                    event->state = 0x103;
                }
                break;
            }
        }
        func_08016234(state->window);
        break;
    case 0x106:
        func_08016234(state->window);
        break;
    case 0x109:
        func_08017E28(state->cursor.second);
        func_08016234(state->window);
        if (data_0200F438->mode == 2)
            data_0200F438->selected =
                state->entries[func_08017B68(&state->unit, state->cursor.row)];
        event->state = 0x102;
        break;
    }
    return 0;
}
