/* Target: 0x080E6E10, 400 bytes.
f0b590b0071c0e1c151c33888020400083422ed0834204dc002b0dd0012b25d0aee081204000834270d0834232db0130834200d190e0a3e01421705e7a2801d10120a870f08ae87074686c6104220006002800d00022044900930197201c0123f9f7c2fa28618be03c753908ecf71afd86e02869f9f7aafb2861002800d07fe068690021f1f7e0fc0006002876d03088013074e002a9a878888268690021f6f7f9fa039068690121f6f7f4fa04900398f6f75efb041c2406240e0f482c2102aa3b1c1ef74bfe6860002c1bd00b488c21490002aa3b1c1ef741fea86008480097022104220023f8f749ffa861782028803088013043e00000496a0e08116b0e086476390800483ae0030100002888002810d001382880000400280bd168690121f6f7b8fa09aa5060184824213b1c1ef715fee8606868f9f7e9fa686000281fd1a868f9f7e3faa860002819d1e868002816d03088013030806868f9f7d7fa686000280dd1a868f9f7d1faa860002807d1e868f9f7cbfae860002801d102203080002010b0f0bc02bc08470000556d0e08
*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Descriptor {
    u16 state;
    u16 unknown_02;
    void *first;
    void *second;
    u32 unknown_0c;
    u32 unknown_10;
    s16 kind;
    u16 option;
    u32 unknown_18;
} Descriptor;
typedef struct State {
    u16 timer;
    u8 kind;
    u8 option;
    void *first;
    void *second;
    void *third;
    void *pending;
    void *owner;
    void *effect;
} State;
extern const u8 data_0839753C[];
extern const u8 data_08397664[];
extern void func_080E6A48(void);
extern void func_080E6B10(void);
extern void func_080E6D54(void);
extern void *func_08005B6C(void (*)(void), int, Descriptor *, void *);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern u8 func_080DD580(void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080E051C(void *);

int func_080E6E10(void *context, Descriptor *desc, State *state)
{
    Descriptor first;
    Descriptor second;
    u8 active;
    int mode;
    switch (desc->state) {
    case 0:
        if (desc->kind == 0x7a)
            state->kind = 1;
        state->option = desc->option;
        state->owner = desc->first;
        mode = 4;
        if (state->option)
            mode = 0;
        state->pending = func_080E03F8(state->owner, data_0839753C,
                                     mode, 1, 0, context);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->pending = func_080E05DC(state->pending);
        if (!state->pending) {
            if (func_080D8858(state->owner, 0))
                desc->state++;
            else
                desc->state = 2;
        }
        break;
    case 0x101:
        first.kind = state->kind;
        first.first = func_080DD4A4(state->owner, 0);
        first.second = func_080DD4A4(state->owner, 1);
        active = func_080DD580(first.first);
        state->first = func_08005B6C(func_080E6A48, 0x2c, &first, context);
        if (active) {
            state->second = func_08005B6C(func_080E6B10, 0x118, &first, context);
            state->effect = func_080DFD8C(data_08397664, 2, 4, 0, context);
            state->timer = 120;
            desc->state++;
        } else
            desc->state = 0x103;
        break;
    case 0x102:
        if (state->timer && !--state->timer) {
            second.first = func_080DD4A4(state->owner, 1);
            state->third = func_08005B6C(func_080E6D54, 0x24, &second, context);
        }
        state->first = func_080E051C(state->first);
        if (state->first) break;
        state->second = func_080E051C(state->second);
        if (state->second) break;
        if (!state->third) break;
        desc->state++;
    case 0x103:
        state->first = func_080E051C(state->first);
        if (state->first) break;
        state->second = func_080E051C(state->second);
        if (state->second) break;
        state->third = func_080E051C(state->third);
        if (!state->third) desc->state = 2;
        break;
    }
    return 0;
}
