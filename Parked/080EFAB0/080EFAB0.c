#include "ffta.h"

// Target [0x080EFAB0, 0x080EFCBE), 526 bytes:
// f0b54f464646c0b48cb081460e1c151c31888020400081426bd0814204dc00290ed0012962d0eae00448814200d1c9e00130814200d1dae0e1e0000001010000f08ae87072686a62a97000270120804600241423f15e1348814229d14046a870377a06239846101c391cedf7cbfc6c460a3403ab02a9221cecf73af902a8008878380004000c084a0b99114001430b91208860380004054a114001430b910bac0ee00000170100000000ffffffff000094204000814203d10220a87007208046686a391cedf796fca8610322e878002800d00022686a044900944b4601934346f0f732fca8628ae0989a3908e3f78afe85e0a86af0f71afda862002800d07ee0686a0021e8f750fe0006002875d0a869a91d2a1c08320023edf7befde8610027a869edf7d5fc0006002819d1a87801281fd1e869edf748fc0621d8f75bf90004000c052151f03efe002812d0e869042100224b46edf706fb2862812040004de0a8690021edf72cfd00060227002800d0012704ace888a0822889e0820e482421221c4b4615f79affe860022f08d0a86960600a482c21221c4b4615f78fff2861a869606006482821221c4b4615f786ff68613088013021e085f40e0839f60e0871f90e08e868f0f751fce860002816d12869f0f74bfc2861002810d16869f0f745fc686100280ad13088013006e0286aebf7dcfe2862002801d10220308000200cb018bc9846a146f0bc02bc0847

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 index;
    u8 unknown_09[11];
    s16 selector;
    u16 flags;
    u16 unknown_18;
} Command080EFAB0;

typedef struct {
    s16 x;
    s16 y;
} Offset080EFAB0;

typedef struct {
    u8 unknown_00[2];
    u8 variant;
    u8 mode;
    u8 unknown_04[2];
    s16 x;
    s16 y;
    u8 unknown_0a[2];
    void *first_child;
    void *second_child;
    void *third_child;
    void *target;
    void *coordinate_result;
    void *effect_child;
    void *object;
    void *initial_child;
} State080EFAB0;

typedef u32 (*Callback080EFAB0)(void *, Command080EFAB0 *, void *);

extern const u8 data_08399A98[];
extern void *func_080DD4B4(void *, u8);
extern void func_080DBDA0(void *, s16 *, s16 *, s16 *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080E03F8(void *, const void *, u8, u8, Offset080EFAB0 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD580(void *);
extern u8 func_080DD670(void *, u8);
extern void *func_080DD478(void *);
extern u32 func_080C7EA4(void *, u32);
extern s32 func_08141874(s32, s32);
extern void *func_080DD214(void *, u8, u8, void *);
extern void *func_08005B6C(Callback080EFAB0, u16, Command080EFAB0 *, void *);
extern void *func_080E051C(void *);
extern void *func_080DBA5C(void *);
extern u32 func_080EF484(void *, Command080EFAB0 *, void *);
extern u32 func_080EF638(void *, Command080EFAB0 *, void *);
extern u32 func_080EF970(void *, Command080EFAB0 *, void *);

u32 func_080EFAB0(void *task, Command080EFAB0 *command, State080EFAB0 *state)
{
    s16 x;
    s16 y;
    s16 z;
    Offset080EFAB0 offset;
    Offset080EFAB0 *origin;
    u8 index;
    u8 kind;
    u8 mode;
    u8 effect_mode;

    switch (command->state) {
    case 0:
        state->mode = command->flags;
        state->object = command->object;
        state->variant = 0;
        index = 0;
        kind = 1;
        origin = 0;
        if (command->selector == 0x117) {
            state->variant = 1;
            index = command->index;
            kind = 6;
            func_080DBDA0(func_080DD4B4(state->object, index), &x, &y, &z);
            offset.x = x - 0x78;
            offset.y = y - 0x60;
            origin = &offset;
        } else if (command->selector == 0x128) {
            state->variant = 2;
            kind = 7;
        }
        state->target = func_080DD4A4(state->object, index);
        mode = 3;
        if (state->mode != 0)
            mode = 0;
        state->initial_child = func_080E03F8(state->object, data_08399A98,
                                             mode, kind, origin, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        Command080EFAB0 descriptor;

        state->initial_child = func_080E05DC(state->initial_child);
        if (state->initial_child != 0)
            break;
        if (func_080D8858(state->object, 0) == 0) {
            command->state = 2;
            break;
        }
        state->coordinate_result = func_080DD748(state->target,
                                                 &state->x, &state->y, 0);
        effect_mode = 0;
        if (func_080DD580(state->target) == 0) {
            if (state->variant == 1
                && func_08141874((u16)func_080C7EA4(
                       func_080DD478(state->coordinate_result), 6), 5)) {
                state->effect_child = func_080DD214(state->coordinate_result,
                                                    4, 0, task);
                command->state = 0x102;
                break;
            }
        } else {
            if (func_080DD670(state->target, 0))
                effect_mode = 1;
            else
                effect_mode = 2;
        }
        descriptor.selector = state->x;
        descriptor.flags = state->y;
        state->first_child = func_08005B6C(func_080EF484, 0x24, &descriptor, task);
        if (effect_mode != 2) {
            descriptor.object = state->target;
            state->second_child = func_08005B6C(func_080EF638, 0x2c,
                                                &descriptor, task);
        }
        descriptor.object = state->target;
        state->third_child = func_08005B6C(func_080EF970, 0x28, &descriptor, task);
        command->state++;
        break;
    }
    case 0x101:
        state->first_child = func_080E051C(state->first_child);
        if (state->first_child != 0)
            break;
        state->second_child = func_080E051C(state->second_child);
        if (state->second_child != 0)
            break;
        state->third_child = func_080E051C(state->third_child);
        if (state->third_child != 0)
            break;
        command->state++;
        break;
    case 0x102:
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child == 0)
            command->state = 2;
        break;
    }
    return 0;
}
