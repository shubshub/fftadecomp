#include "ffta.h"

/* Complete [0x080E7D20, 0x080E7F4C): 556 bytes. */

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

extern const void *const data_08397CC0[];
extern const u16 data_08397CCC[];
extern const u8 data_08397CA0[];
extern const void *const data_08397C94[];
extern const void *const data_08397CD4[];
extern const void *const data_08397CA4[];
extern const void *const data_08397CB0[];
extern const u8 data_08397CF8[];
extern const u8 data_08397CBC[];
extern const void *const data_08397D1C[];
extern const u8 data_088E9C0C[];
extern const u8 data_08397CE4[];

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
extern void *func_080DFD8C(const void *record, u8 count, u32 flags,
                          u16 delay, void *parent);
extern void *func_080D4D2C(void *resource, u8 slot);
extern void *func_080D6134(void *child);
extern void *func_080D3F08(void *child);
extern u32 func_080D48DC(void **children, u16 count);
extern void *func_080DBA5C(void *child);

u32 func_080E7D20(void *task, EffectDescriptor *entry, EffectState *state)
{
    u32 flags;
    u32 record_flags;

    switch (entry->phase) {
    case 0:
        state->selector = entry->selector;
        state->flags = entry->flags;
        state->wrapper = entry->object;
        state->underlying = func_080DD748(state->wrapper, &state->x, &state->y, 0);
        func_080D45D0(data_088E9C0C, 6, 0, 0, 1);
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->resource = func_080D4B64(0,
            data_08397CC0[state->selector],
            data_08397CCC[state->selector], 6);
        *(u16 *)0x03000940 |= func_080035A8(2);
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
            data_08397CA0[state->selector], state->unknown_14,
            data_08397C94[state->selector], task);
        state->sequence_child = func_080D3E9C(
            data_08397CD4[state->selector], task);
        state->children[0] = func_080D4704(
            data_08397CA4[state->selector], task);
        state->children[1] = func_080D4724(
            data_08397CB0[state->selector], task,
            data_08397CBC[state->selector]);
        if (state->flags & 1)
            flags = 4;
        else
            flags = 2;
        state->effect_child = func_080DCFE4(state->wrapper,
            data_08397CE4, 12,
            data_08397CF8[state->selector],
            flags, task,
            data_08397CF8[state->selector]);
        if (state->flags & 1)
            record_flags = 16;
        else
            record_flags = 8;
        state->record_child = func_080DFD8C(
            data_08397D1C[state->selector], 1,
            record_flags | 4, 0, task);
        entry->phase++;
        break;
    case 0x101:
    {
        u8 had_resource = state->resource != 0;

        state->resource = func_080D4D2C(state->resource, 0);
        if (had_resource && state->resource == 0)
            *(u16 *)0x03000940 &= ~func_080035A8(2);
        if (state->resource != 0)
            break;
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child != 0)
            break;
        state->sequence_child = func_080D3F08(state->sequence_child);
        if (state->sequence_child != 0)
            break;
        if ((u8)func_080D48DC(state->children, 2) != 0)
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
