#include "ffta.h"

// Complete [0x080BAB90, 0x080BACF0): 352 bytes, 176 instructions.

typedef struct {
    u8 unknown_00[0x30];
} UnitSource;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    UnitSource *sources;
    u8 unknown_08[0x19];
    u8 source_index;
    u8 unknown_22[6];
} UnitGroup;

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xCC];
    u8 field_f6;
    u8 field_f7;
    u8 field_f8;
    u8 unknown_f9[0x0F];
} Unit;

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} SceneObject;

typedef struct {
    void *record;
} ListEntry;

typedef struct {
    void *context;
    UnitGroup *group;
    void *object;
    u16 id;
    u8 unknown_0E[0xE];
    u16 current;
    u16 count;
    u16 history[34];
} State;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern const BufferInitializer g_callbacks_0836D4B8[];
extern UnitGroup data_0854CD54[];
extern Unit data_02002FC4[];
extern UnitGroup data_0854D1DC;
extern s32 func_08099CDC(void *context, ListEntry **entries);
extern u8 func_080C8298(const void *record);
extern u8 func_080BC7AC(u16 index);
extern void func_080C9644(Unit *unit, UnitSource *source, u8 mode);
extern u8 func_080C84F4(void);
extern u8 func_080C8530(void);
extern SceneObject *func_08092440(void *context, Unit *unit);

void func_080BAB90(State *state, void *context, u16 id)
{
    ListEntry *entries[13];
    s32 found;
    s32 count;
    s32 i;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->context = context;
    state->id = id;
    state->group = &data_0854CD54[id];
    found = 0;
    count = func_08099CDC(context, entries);
    for (i = 0; i < count; i++) {
        if (func_080C8298(entries[i]->record)) {
            found = 1;
            state->object = entries[i];
            break;
        }
    }
    if (found) {
        state->current = 8;
        state->history[state->count++] = state->current;
        state->current = 4;
        state->history[state->count++] = state->current;
        state->current = 0;
    } else if (!func_080BC7AC(id)) {
        state->current = 8;
        state->history[state->count++] = state->current;
        state->current = 6;
    } else {
        UnitSource *source =
            &data_0854D1DC.sources[state->group->source_index - 1];
        Unit *unit = data_02002FC4;
        SceneObject *object;

        while (unit->active != 0)
            unit++;
        func_080C9644(unit, source, 0);
        unit->flags |= 0x1000;
        unit->field_f8 = 0;
        unit->field_f6 = func_080C84F4();
        unit->field_f7 = func_080C8530();
        object = func_08092440(state->context, unit);
        state->object = object;
        object->flags |= 5;
        state->current = 2;
        state->history[state->count++] = state->current;
        state->current = 0;
    }
}
