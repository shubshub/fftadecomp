typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Input { u16 phase; u16 unknown_2; u32 object; u8 unknown_8[14]; u16 mode; };
struct State { u8 count, index, delay, mode; u32 object; u32 tasks[2]; u32 task; };
struct Payload { u32 unknown_0; u32 object; u8 unknown_8[12]; u16 index; u8 unknown_22[6]; };
extern const u8 data_083999E0[];
extern u32 func_080EEF98(void);
extern u32 func_080E03F8(u32, const void *, int, int, int, u32);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32);
extern u32 func_080D8858(u32, int);
extern u32 func_080E0570(u32 *, int);
extern u32 func_080DD4A4(u32, int);
extern u32 func_08005B6C(void *, int, void *, u32);
/* Target: 0x080EF120, complete 0x112-byte Thumb body including literal pools. */
u32 func_080EF120(u32 owner, struct Input *input, struct State *state)
{
    struct Payload payload;
    switch (input->phase) {
    case 0: {
        u32 object;
        int mode;
        state->mode = input->mode;
        object = input->object;
        state->object = object;
        mode = 3;
        if (state->mode) mode = 0;
        state->task = func_080E03F8(object, data_083999E0, mode, 1, 0, owner);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 256:
        state->task = func_080E05DC(state->task);
        if (!state->task) {
            state->count = func_080D8858(state->object, 0);
            if (state->count) {
                state->delay = 1;
                input->phase++;
            } else input->phase = 2;
        }
        break;
    case 257: {
        u32 *tasks = state->tasks;
        func_080E0570(tasks, 2);
        if (!--state->delay) {
            u8 slot = tasks[0] != 0;
            payload.index = state->index;
            payload.object = func_080DD4A4(state->object, state->index);
            state->tasks[slot] = func_08005B6C(func_080EEF98, 44, &payload, owner);
            state->delay = 52;
            state->index++;
            if (state->index == state->count) input->phase++;
        }
        break;
    }
    case 258:
        if ((u8)func_080E0570(state->tasks, 2)) input->phase = 2;
        break;
    }
    return 0;
}
