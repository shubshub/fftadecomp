#include "ffta.h"
#include "control_flags.h"

// 0x080E317C .. 0x080E3388: 524 bytes.
typedef struct E317CDescriptor {
    u16 state;
    u16 unknown_02;
    u32 unknown_04;
    void *object;
    u8 unknown_0C[8];
    u8 kind;
} E317CDescriptor;

typedef struct E317CState {
    u16 unknown_00;
    u8 index;
    u8 finished;
    s16 x;
    s16 y;
    void *object;
    void *startup;
    void *outputs[2];
    void *coordinate_task;
    void *display;
    void *script;
    void *auxiliary;
    void *overlay;
    u32 unknown_2C;
    void *effect;
} E317CState;

extern const u8 data_08149C84[];
extern const u8 data_08149C86[];
extern const u8 data_08395FF4[];
extern const u8 data_088EB650[];
extern const u8 data_088EA7F0[];
extern const u8 data_088F1870[];
extern const u8 data_0894D690[];
extern const void *const data_08396080[];
extern const void *const data_08396078[];
extern const u8 data_08396088[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080D38B4(void);
extern void *func_080D7A70(const void *data, u8 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void func_080D45D0(const void *record, u8 slot, u8 bank, u8 first, u8 count);
extern void func_080DE10C(void *object, u16 value);
extern void *func_080DE4B0(void *object, u8 *finished, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *parent);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u8 kind, u8 mode, u16 option, s16 x, s16 y);
extern void *func_080D4B64(u8 kind, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode, u16 count,
                           void **outputs, const void *entries, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags, u16 delay,
                           void *parent);
extern void *func_080D4D2C(void *display, u8 mode);
extern void *func_080D3F08(void *script);
extern void *func_080D4774(void *auxiliary);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080E317C(void *task, E317CDescriptor *descriptor, E317CState *state)
{
    u8 first[2];
    u8 second[2];

    switch (descriptor->state) {
    case 0:
        state->index = descriptor->kind - 0x62;
        state->object = descriptor->object;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        func_081443FC(first, data_08149C84, sizeof(first));
        func_081443FC(second, data_08149C86, sizeof(second));
        state->startup = func_080D7A70(data_08395FF4, 3, task);
        func_080D45D0(data_088EB650, 6, 0, first[state->index], 1);
        func_080D45D0(data_088EA7F0, 6, 1, second[state->index], 1);
        descriptor->state++;
        break;
    case 0x101:
        state->startup = func_080D7ABC(state->startup);
        if (state->startup)
            break;
        func_080DE10C(state->object, 0x3C);
        state->overlay = func_080DE4B0(state->object, &state->finished, 1, -1,
                                       0, 0x3A, 0, task);
        descriptor->state++;
        break;
    case 0x102:
        if (state->finished == 0)
            break;
        func_080DBDC8(state->object, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, state->y - 0x20);
        state->display = func_080D4B64(0, data_088F1870, 0x3CF, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        state->script = func_080D3E9C(data_0894D690, task);
        state->auxiliary = func_080D4704(data_08396080[state->index], task);
        state->coordinate_task = func_080D6098(state->x, state->y - 0x20, 0, 1,
                                               2, state->outputs,
                                               data_08396078[state->index],
                                               task);
        state->effect = func_080DFD8C(data_08396088, 1, 4, 0x1E, task);
        descriptor->state++;
        break;
    case 0x103:
        state->display = func_080D4D2C(state->display, 0);
        if (state->display)
            break;
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags &= ~mask;
            g_control_flags_03000940.display = flags;
        }
        state->auxiliary = func_080D4774(state->auxiliary);
        if (state->auxiliary)
            break;
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task)
            break;
        state->overlay = func_080DBA5C(state->overlay);
        if (state->overlay == 0)
            descriptor->state = 2;
        break;
    }
    return 0;
}
