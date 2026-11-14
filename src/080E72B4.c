#include "ffta.h"

// Target: 0x080E72B4..0x080E75B8, 772 bytes, 314 reachable instructions.
// f0b5474680b48bb0061c0f1c151c3b880648834200d1a9e083420edc012b2fd0012b05dc
// 002b17d063e100000101000080204000834226d05be10648834200d10ce1834200daebe0
// 0130834200d137e14fe1000003010000f88a28707c682c6406220006002800d000220449
// 00930196201c0123f9f766f8e8633ae118773908ecf7befa35e1e86bf9f74ef9e8630028
// 00d02ee1287800280ad00120e870286c0021f1f77ffa6870004821e1030100007820a880
// 6020e880281c08303e2156227723f9f747f904202b5e0821685e0090002002210022edf7
// 37fb1d491d4a00200623edf7e5fba862012124f701fd02201cf700f9184a118801431180
// 1748311cedf7a6f928631648311cecf76dfde8620c21ff22ecf7dcfd0422a85e0622a95e
// 022200922a1c1c3201920e4a0292039600220123eef756fe68620b480096022104220023
// f8f7c8fc686438880130cfe038d58e08e303000040090003749594089cd6940860773908
// cc7739082c1c0834201cf9f733f9000600280ad1201cf9f70bf90420295e08202a5e0020
// 24f7e2fbafe0e86aecf75efde862002800d0a8e0286bedf78df9041c2c63002c00d0a0e0
// a86a0021edf754fcac6202201cf79af8124a118881431180114804216b5ee9880a390904
// 09140091019401210322eff7c5fe0c48311cedf733f928630a48311cedf72ef968630948
// 311c1e22edf738f9a8633120a8703888013071e040090003a0548f089c959408fc959408
// 84869408a878002801d00138a870686aeef728fe686200285dd1a87800285ad10120e870
// 286c0021f1f7aef968700006002802d1822040004ce03888013049e01422521990464046
// 0221f9f729f8e8780138e870000600283dd1686944420443e40f286ca978f5f7b5ff0590
// 04a9a87888820b48242104aa331c1ef70ffba400444420603220e870a8780130a8700006
// 000e6d78a8421ed1388801301ae0000031710e08281c30300321edf7aff90006002810d0
// 03201cf70ff80a4a118881431180281c14300221f8f7eaff0006002801d0022038800020
// 0bb008bc9846f0bc02bc084740090003

typedef struct Descriptor {
    u16 state;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    s16 index;
    u16 option;
    u32 unknown_18;
} Descriptor;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct State {
    u8 option;
    u8 count;
    u8 counter;
    u8 timer;
    s16 x;
    s16 y;
    InterpolationState height;
    void *children[2];
    u8 unknown_1c[8];
    void *particle;
    void *effect;
    void *animation;
    void *overlays[3];
    void *transition;
    void *object;
    void *controller;
} State;

extern const u8 data_08397718[];
extern const u8 data_088ED538[];
extern const u8 data_08949574[];
extern const u8 data_0894D69C[];
extern const u8 data_08397760[];
extern const u8 data_083977CC[];
extern const u8 data_088F54A0[];
extern const u8 data_0894959C[];
extern const u8 data_089495FC[];
extern const u8 data_08948684[];
extern u16 g_control_flags_03000940;

extern void func_080E7130(void);
extern void *func_08005B6C(void (*)(void), int, Descriptor *, void *);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void func_080E0608(InterpolationState *, int, int, int);
extern void func_080D49FC(int, int, int, s16, s16);
extern void *func_080D4B64(int, const void *, int, int);
extern void func_0800BDA4(void *, int);
extern u32 func_080035A8(u32);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, int, int);
extern void *func_080D6098(s16, s16, int, int, int, void *, const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080E064C(InterpolationState *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void func_080D4D14(void *, int);
extern void func_080D7220(const void *, int, int, s16, s16, void *);
extern void *func_080D4724(const void *, void *, int);
extern void *func_080D6134(void *);
extern void *func_080DD4A4(void *, int);
extern u8 func_080D48DC(void **, int);
extern u8 func_080E0570(void **, int);

int func_080E72B4(void *context, Descriptor *desc, State *state)
{
    Descriptor child;
    int mode;
    u8 slot;
    u32 mask;
    u16 *control_flags;
    u32 flags;

    switch (desc->state) {
    case 0:
        state->option = desc->option;
        state->object = desc->object;
        mode = 6;
        if (state->option)
            mode = 0;
        state->transition = func_080E03F8(state->object, data_08397718, mode, 1, 0, context);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->transition = func_080E05DC(state->transition);
        if (state->transition)
            break;
        if (state->option) {
            state->timer = 1;
            state->count = func_080D8858(state->object, 0);
            desc->state = 0x103;
            break;
        }
        state->x = 0x78;
        state->y = 0x60;
        func_080E0608(&state->height, 0x3E, 0x56, 0x77);
        func_080D49FC(0, 2, 0, state->x, state->height.current);
        state->effect = func_080D4B64(0, data_088ED538, 0x3E3, 6);
        func_0800BDA4(state->effect, 1);
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        state->overlays[0] = func_080D4704(data_08949574, context);
        state->animation = func_080D3E9C(data_0894D69C, context);
        func_080D3F84(state->animation, 0xC, 0xFF);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 2, state->unknown_1c,
                                        data_08397760, context);
        state->controller = func_080DFD8C(data_083977CC, 2, 4, 0, context);
        desc->state++;
        break;
    case 0x101:
        if (!func_080E0690(&state->height)) {
            func_080E064C(&state->height);
            func_0800BC08(0, state->x, state->height.current);
            break;
        }
        state->animation = func_080D3F08(state->animation);
        if (state->animation)
            break;
        state->overlays[0] = func_080D4774(state->overlays[0]);
        if (state->overlays[0])
            break;
        func_080D4D14(state->effect, 0);
        state->effect = 0;
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        func_080D7220(data_088F54A0, 1, 3, state->x, state->y - 10, 0);
        state->overlays[0] = func_080D4704(data_0894959C, context);
        state->overlays[1] = func_080D4704(data_089495FC, context);
        state->overlays[2] = func_080D4724(data_08948684, context, 0x1E);
        state->counter = 0x31;
        desc->state++;
        break;
    case 0x102:
        if (state->counter)
            state->counter--;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        if (state->counter)
            break;
        state->timer = 1;
        state->count = func_080D8858(state->object, 0);
        if (!state->count) {
            desc->state = 0x104;
            break;
        }
        desc->state++;
        break;
    case 0x103:
        func_080E0570(state->children, 2);
        if (--state->timer)
            break;
        slot = state->children[0] != 0;
        child.object = func_080DD4A4(state->object, state->counter);
        child.index = state->counter;
        state->children[slot] = func_08005B6C(func_080E7130, 0x24, &child, context);
        state->timer = 0x32;
        state->counter++;
        if (state->counter == state->count)
            desc->state++;
        break;
    case 0x104:
        if (!func_080D48DC(state->overlays, 3))
            break;
        mask = func_080035A8(3);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        if (func_080E0570(state->children, 2))
            desc->state = 2;
        break;
    }
    return 0;
}
