#include "ffta.h"

/* 0809A0F4 .. 0809A204: 272 bytes. */
typedef struct {
    u8 unknown_00[8];
    const void *resource;
} ResourceSource;

typedef struct {
    void *unit;
    u8 unknown_04[0x3C];
    void *resource;
    u8 unknown_44[0x10];
    void *first;
    void *second;
    u8 unknown_5C[0x24];
    ResourceSource *source;
} ObjectState;

extern void *func_08021B1C(const void *);
extern void *func_0808F79C(void);
extern s32 func_080C92F0(void *, s32);
extern s32 func_080C7EA4(void *, s32);
extern void (*data_08394030[])(void *, void *);
extern void (*data_08394038[])(void *, const u8 *);
extern const u8 data_08391576[];
extern const u8 data_08391584[];

void func_0809A0F4(ObjectState *state)
{
    state->resource = func_08021B1C(state->source->resource);
    state->first = func_0808F79C();
    state->second = func_0808F79C();
    data_08394030[0](state->first, state->resource);
    data_08394030[0](state->first, state->resource);
    if (func_080C92F0(state->unit, 3) == 1 ||
        func_080C7EA4(state->unit, 1) == 6 ||
        func_080C7EA4(state->unit, 1) == 18 ||
        func_080C7EA4(state->unit, 1) == 30 ||
        func_080C7EA4(state->unit, 1) == 57 ||
        func_080C7EA4(state->unit, 1) == 58 ||
        func_080C7EA4(state->unit, 1) == 59 ||
        func_080C7EA4(state->unit, 1) == 60 ||
        func_080C7EA4(state->unit, 1) == 61 ||
        func_080C7EA4(state->unit, 1) == 62 ||
        func_080C7EA4(state->unit, 1) == 63 ||
        func_080C7EA4(state->unit, 1) == 23 ||
        func_080C7EA4(state->unit, 1) == 14 ||
        func_080C7EA4(state->unit, 1) == 75) {
        data_08394038[0](state->second, data_08391576);
    } else {
        data_08394038[0](state->second, data_08391584);
    }
}
