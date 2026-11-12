/* Target bytes: f0b5474680b489b080460e1c151c338880204000834228d0834204dc002b0bd0012b1fd06de00348834231d0013083425ed066e001010000f08ae87074682c6103220006002800d000220549009340460190201c0123eff705ffe86051e00000589d3908e3f75cf94be0e868eff7ecffe860002845d128690021e8f723f92870000600283bd00120a8703088013037e02f1d381c0221eff7a1ffa8780138a870000600282dd1686844420443e40f02a96878888228696978ecf72aff03900b482c2102aa434615f787faa4003c1920602820a8706878013068700006000e2d78a8420ed1308801300ae00000d1030f08281d0221eff772ff0006002801d002203080002009b008bc9846f0bc02bc0847 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 state; u16 unknown_2; void *object; u8 unknown_8[14]; u16 flag;} Request;
typedef struct {u8 count, index, timer, flag; void *children[2]; void *pending; void *object;} State;
typedef struct {u32 unknown_0; void *value; u8 unknown_8[12]; u16 index; u8 unknown_22[6];} Descriptor;
extern const u8 data_08399D58[];
extern int func_080F03D0(void);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *, int);
extern int func_080E0570(void **, int);
extern void *func_080DD4A4(void *, int);
extern void *func_08005B6C(int (*)(void), int, Descriptor *, void *);
int func_080F0594(void *owner, Request *request, State *state)
{
    Descriptor descriptor;
    switch (request->state) {
    case 0: {
        int mode;
        void *object;
        state->flag = request->flag;
        object = request->object;
        state->object = object;
        mode = 3;
        if (state->flag) mode = 0;
        state->pending = func_080E03F8(object, data_08399D58, mode, 1, 0, owner);
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
            descriptor.index = state->index;
            descriptor.value = func_080DD4A4(state->object, state->index);
            state->children[slot] = func_08005B6C(func_080F03D0, 0x2c, &descriptor, owner);
            state->timer = 40;
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
