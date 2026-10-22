#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *payload;
} ReleaseContext;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 unknown_4d;
    u16 field_4e;
    u8 unknown_50;
    u8 unknown_51;
    u8 unknown_52[2];
    u32 flags;
    u8 unknown_58[0x14];
    ReleaseContext context;
    u8 unknown_78[0x80C];
    void *object;
} ExtendedScriptState;

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 resource;
    u8 unknown_1f68[0x236];
    u16 field_219e;
    u8 unknown_21a0[0x1A84];
    u32 field_3c24;
    u16 field_3c28;
    u8 field_3c2a;
} StateView;

extern u8 g_state_02000000[];

void func_080C746C(void *context);
void func_080C95C0(u16 index, u32 value);
void func_08004C40(void);
void *func_08022840(u32 byte_count);
void func_0801174C(void *object, u8 kind, u16 selector,
                   void *primary, void *secondary, u16 field0e, u16 field0f,
                   u8 field1a, u8 field11, u16 offset);
void func_0801339C(u16 value);
void func_0802A2C0(u8 first, u8 second, u8 third, u8 fourth);

void func_08064CCC(void)
{
    u8 *control = (u8 *)0x03000ED0;
    StateView *globals;
    ExtendedScriptState **state_slot;
    ExtendedScriptState *state;
    void *object;

    control[5] = 1;
    globals = (StateView *)g_state_02000000;
    globals->field_3c24 = 0;
    globals->field_219e = 0;
    globals->field_3c28 = 0;
    globals->field_3c2a = 0;
    state_slot = (ExtendedScriptState **)0x0200F450;
    state = *state_slot;
    if (state->flags & 0x40) {
        globals->resource += 5000;
        state->flags &= ~0x40;
    }
    func_080C746C(&(*state_slot)->context);
    func_080C95C0(0x0D, 0);
    func_08004C40();
    object = func_08022840(0xA04);
    (*state_slot)->object = object;
    func_0801174C(object, 1, 0x0C, (void *)0x030008B0, (void *)0x03000990,
                   2, 2, 0x18, 4, 0x3A0);
    func_0801339C(2);
    func_0802A2C0(2, 2, 0x1A, 6);
    state = *state_slot;
    state->count = 1;
    state->entries[0] = 1;
    state->current = 0x34;
}
