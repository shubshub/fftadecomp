typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Descriptor { u16 state; u16 unknown_02; void *object; u32 unknown_08[3]; u16 kind; u16 option; u32 unknown_18; };
struct State { u16 timer; u8 unknown_02; u8 flag; void *output; void *task; void *object; void *pending; void *input; void *effect; void *sound; };
extern const u8 data_0839C82C[], data_0839C85C[], data_0839C860[], data_0839C864[];
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void *func_080DDF68(void *, void **, int, int, void **, const void *, int, int, void *);
extern void func_080DE3BC(void *, int);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, int, void **, const void *, int, int, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern u8 func_080DE1F0(void *);
extern int func_080E6E10(void *, struct Descriptor *, void *);
extern void *func_08005B6C(int (*)(void *, struct Descriptor *, void *), int, struct Descriptor *, void *);
extern void *func_080E051C(void *);
/* Target: 080FA614..080FA76A, 342 bytes. */
int func_080FA614(void *owner, struct Descriptor *desc, struct State *state)
{
    struct Descriptor next;
    int mode;
    switch (desc->state) {
    case 0:
        state->flag = desc->option;
        state->input = desc->object;
        mode = 4;
        if (state->flag) mode = 0;
        state->pending = func_080E03F8(state->input, data_0839C82C, mode, 0, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->pending = func_080E05DC(state->pending);
        if (!state->pending) {
            if (func_080D8858(state->input, 0)) {
                state->effect = func_080DDF68(state->input, &state->object, 0x90, 1, &state->output, data_0839C85C, 0, 0, owner);
                state->timer = 30;
                desc->state++;
            } else desc->state = 2;
        }
        break;
    case 0x101:
        if (--state->timer == 0) {
            func_080DE3BC(state->object, 0);
            func_080DBA50(state->effect);
            state->effect = func_080DE4F4(state->object, 1, &state->output, data_0839C860, 0, 0, owner);
            state->sound = func_080DFD8C(data_0839C864, 1, 4, 0, owner);
            desc->state++;
        }
        break;
    case 0x102:
        if (func_080DE1F0(state->object)) {
            func_080DBA50(state->effect);
            state->effect = 0;
            next.kind = 0x7A;
            next.option = 1;
            next.object = state->input;
            state->task = func_08005B6C(func_080E6E10, sizeof(next), &next, owner);
            desc->state++;
        }
        break;
    case 0x103:
        state->task = func_080E051C(state->task);
        if (!state->task) desc->state = 2;
        break;
    }
    return 0;
}
