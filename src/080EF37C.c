typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Event { u16 phase; u16 unknown_2; void *object; u8 unknown_8[14]; u16 option; };
struct State { u8 count, index, timer, option; u32 tasks[2]; void *pending; void *object; };
extern const u8 data_08399A3C[];
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *, int);
extern int func_080E0570(u32 *, int);
extern u32 func_080DD4A4(void *, int);
extern void func_080EF234(void);
extern u32 func_08005B6C(void (*)(void), int, void *, void *);
/* Target: 0x080EF37C, complete 264-byte Thumb body.
 * f0b5474680b489b080460e1c151c338880204000834228d0834204dc002b0bd0012b1fd069e00348834231d0013083425ad062e001010000f08ae87074682c6102220006002800d000220549009340460190201c0123f1f711f8e8604de000003c9a3908e4f768fa47e0e868f1f7f8f8e860002841d128690021e9f72ffa28700006002837d00120a8703088013033e02f1d381c0221f1f7adf8a8780138a8700006002829d1686844420443e40f28696978eef739f803900a48282102aa434616f796fba4003c1920603220a8706878013068700006000e2d78a8420dd13088013009e035f20e08281d0221f1f782f80006002801d002203080002009b008bc9846f0bc02bc0847
 */
int func_080EF37C(void *owner, struct Event *event, struct State *state)
{
    u32 parameters[7];
    switch (event->phase) {
    case 0: {
        void *object;
        int mode;
        state->option = event->option;
        object = event->object;
        state->object = object;
        mode = 2;
        if (state->option) mode = 0;
        state->pending = func_080E03F8(object, data_08399A3C, mode, 1, 0, owner);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 256:
        state->pending = func_080E05DC(state->pending);
        if (!state->pending) {
            state->count = func_080D8858(state->object, 0);
            if (state->count) {
                state->timer = 1;
                event->phase++;
            } else event->phase = 2;
        }
        break;
    case 257:
        func_080E0570(state->tasks, 2);
        if (--state->timer == 0) {
            u8 slot = state->tasks[0] != 0;
            parameters[1] = func_080DD4A4(state->object, state->index);
            state->tasks[slot] = func_08005B6C(func_080EF234, 40, parameters, owner);
            state->timer = 50;
            state->index++;
            if (state->index == state->count) event->phase++;
        }
        break;
    case 258:
        if ((u8)func_080E0570(state->tasks, 2)) event->phase = 2;
        break;
    }
    return 0;
}
