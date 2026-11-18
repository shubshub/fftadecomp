#include "ffta.h"
#include "effect_task.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *resource;
    u8 unknown_08[12];
    u16 options;
} RequestE7B04;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 options;
    u8 unknown_07;
    void *resource;
    void *entity;
    u8 unknown_10[0x18];
    void *first;
    void *second;
    void *third;
} StateE7B04;

extern void *func_080DD748(void *resource, s16 *x, s16 *y, u32 alternate);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                          void *slots, const u8 *script, void *parent);
extern void func_080DBDA0(void *entity, s16 *x, s16 *y, s16 *z);
extern void func_080D620C(void *task, s16 value);

extern void *func_080DFD8C(const u8 *script, u8 count, u16 flags,
                          u16 value, void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);
extern const u8 data_08397A68[];
extern const u8 data_08397AF8[];
extern const u8 data_08397B0C[];

s32 func_080E7B04(void *parent, RequestE7B04 *request, StateE7B04 *state)
{
    s16 x;
    s16 y;
    s16 z;
    u16 flags;

    switch (request->phase) {
    case 0:
        state->resource = request->resource;
        state->options = request->options;
        state->entity = func_080DD748(state->resource, &state->x, &state->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        state->first = func_080D6098(state->x, state->y, 0, 1, 6,
                                    state->unknown_10, data_08397A68, parent);
        func_080DBDA0(state->entity, &x, &y, &z);
        func_080D620C(state->first, (s16)-z);
        flags = (state->options & 1) ? 4 : 2;
        state->second = func_080DCFE4(state->resource, data_08397AF8, 12,
                                     0x55, flags, parent, 0x55);
        flags = (state->options & 1) ? 0x10 : 8;
        state->third = func_080DFD8C(data_08397B0C, 1, flags | 4, 0, parent);
        request->phase++;
        break;
    case 0x101:
        state->first = func_080D6134(state->first);
        if (state->first != 0)
            break;
        state->second = func_080DBA5C(state->second);
        if (state->second != 0)
            break;
        request->phase = 2;
        break;
    }
    return 0;
}
