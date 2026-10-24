#include "ffta.h"

/* Target 080E8590..080E87C0 (560 bytes):
f0b54f464646c0b484b080460f1c151c398880204000814228d0814202dc00290cd0fde00448814200d1bbe00130814200d1ede0f4e0000001010000b88a2870f88a68707868a860a91c2a1d0023f5f7b3f8e860044801210091062100220023ebf7eeffdce00000409c8e0802202b5e0421685e0090002002210022ecf7f6f93d492a789000401801683c4852001218128800200623ecf79dfa286102201af7bbff374a1188014311800222a85e0422a95e344b2a78d218127800922a1c14320192314b2a789200d218126802924246039200220123edf717fde8612b4928788000401800684146ebf710fc2862284928788000401800684146ecf73bf868622449287880004018006841462922ecf741f8a86269780120814608400226002800d00426a8681c491c4c2a78121913780096424601922a781219127802920c22f4f788fce8626978484608400822002800d010221249287880004018006804210a434146009101210023f7f747fb28633888013053e00000c4813908d081390840090003a88139089c813908d8813908ac813908b8813908e8813908fc813908208239080126286941420143cc0f0021ecf7f4fa2861002800d00026002c08d0002806d102201af727ff104a118881431180e869edf7e6fce861002800d00026286aebf7c9fb2862002800d00026281c24300221ecf7aaf80006002800d10026002e0dd03888013009e0000040090003e86af3f75bf9e862002801d102203880002004b018bc9846a146f0bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 flags;
} EffectDescriptor;

typedef struct {
    u8 selector;
    u8 flags;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    void *wrapper;
    void *underlying;
    void *resource;
    u8 unknown_14[8];
    void *coordinate_child;
    void *sequence_child;
    void *children[2];
    void *effect_child;
    void *record_child;
} EffectState;

extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern void func_080D45D0(const void *record, u8 slot, u8 bank, u8 first, u8 count);
extern void func_080D49FC(u8 slot, u8 mode, u16 value, s16 x, s16 y);
extern void *func_080D4B64(u8 slot, const void *record, u16 value, u8 mode);
extern u16 func_080035A8(u8 index);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                          void *storage, const void *record, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080D4704(const void *record, void *parent);
extern void *func_080D4724(const void *record, void *parent, u16 value);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                          u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_080D4D2C(void *resource, u8 slot);
extern void *func_080D6134(void *child);
extern void *func_080D3F08(void *child);
extern u32 func_080D48DC(void **children, u16 count);
extern void *func_080DBA5C(void *child);

u32 func_080E8590(void *task, void *descriptor, void *payload)
{
    EffectDescriptor *entry = descriptor;
    EffectState *state = payload;

    switch (entry->phase) {
    case 0:
        state->selector = entry->selector;
        state->flags = entry->flags;
        state->wrapper = entry->object;
        state->underlying = func_080DD748(state->wrapper, &state->x, &state->y, 0);
        func_080D45D0((const void *)0x088E9C40, 6, 0, 0, 1);
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->resource = func_080D4B64(0,
            ((const void *const *)0x083981C4)[state->selector],
            ((const u16 *)0x083981D0)[state->selector], 6);
        *(u16 *)0x03000940 |= func_080035A8(2);
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
            ((const u8 *)0x083981A8)[state->selector], state->unknown_14,
            ((const void *const *)0x0839819C)[state->selector], task);
        state->sequence_child = func_080D3E9C(
            ((const void *const *)0x083981D8)[state->selector], task);
        state->children[0] = func_080D4704(
            ((const void *const *)0x083981AC)[state->selector], task);
        state->children[1] = func_080D4724(
            ((const void *const *)0x083981B8)[state->selector], task, 41);
        state->effect_child = func_080DCFE4(state->wrapper,
            (const void *)0x083981E8, 12,
            ((const u8 *)0x083981FC)[state->selector],
            (state->flags & 1) ? 4 : 2, task,
            ((const u8 *)0x083981FC)[state->selector]);
        state->record_child = func_080DFD8C(
            ((const void *const *)0x08398220)[state->selector], 1,
            ((state->flags & 1) ? 16 : 8) | 4, 0, task);
        entry->phase++;
        break;
    case 0x101:
    {
        u8 complete = 1;
        u8 had_resource = state->resource != 0;

        state->resource = func_080D4D2C(state->resource, 0);
        if (state->resource != 0)
            complete = 0;
        if (had_resource && state->resource == 0)
            *(u16 *)0x03000940 &= ~func_080035A8(2);
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child != 0)
            complete = 0;
        state->sequence_child = func_080D3F08(state->sequence_child);
        if (state->sequence_child != 0)
            complete = 0;
        if ((u8)func_080D48DC(state->children, 2) == 0)
            complete = 0;
        if (complete)
            entry->phase++;
        break;
    }
    case 0x102:
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child == 0)
            entry->phase = 2;
        break;
    }
    return 0;
}
