/* Target: 0x080E7C04, complete 284-byte Thumb body including literal pools. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 state; u16 unknown_2; void *object; u32 unknown_8; u32 flags; u8 unknown_16[6]; u16 flag;} Request;
typedef struct {u8 count, index, timer, flag; void *children[2]; void *pending; void *object;} State;
typedef struct {u32 unknown_0; void *value; u8 unknown_8[12]; u16 index; u8 unknown_22[6];} Descriptor;
extern const u8 data_08397A50[];
extern int func_080E7B04(void);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *, int);
extern int func_080E0570(void **, int);
extern void *func_080DD4A4(void *, int);
extern void *func_08005B6C(int (*)(void), int, Descriptor *, void *);
int func_080E7C04(void *owner, Request *request, State *state)
{
    Descriptor descriptor;
    switch (request->state) {
    case 0: {
        int mode;
        void *object;
        state->flag = request->flag;
        object = request->object;
        state->object = object;
        mode = 2;
        if (state->flag) mode = 0;
        if (request->flags & 1) mode = 0;
        state->pending = func_080E03F8(object, data_08397A50, mode, 1, 0, owner);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->pending = func_080E05DC(state->pending);
        if (!state->pending) {
            state->count = func_080D8858(state->object, 0);
            if (state->count) {
                state->timer = 1;
                request->state++;
            } else request->state = 2;
        }
        break;
    case 0x101:
        func_080E0570(state->children, 2);
        if (--state->timer == 0) {
            u8 slot = state->children[0] != 0;
            descriptor.value = func_080DD4A4(state->object, state->index);
            descriptor.index = state->index;
            state->children[slot] = func_08005B6C(func_080E7B04, 0x34, &descriptor, owner);
            state->timer = 50;
            state->index++;
            if (state->index == state->count) request->state++;
        }
        break;
    case 0x102:
        if ((u8)func_080E0570(state->children, 2)) request->state = 2;
        break;
    }
    return 0;
}
