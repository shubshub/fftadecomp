#include "ffta.h"

// Complete target: [0x080EF970, 0x080EFAAE), 318 bytes.

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
} Event080EF970;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    void *entity;
    u8 result[12];
    void *task18;
    void *task1C;
    void *task20;
    void *task24;
} State080EF970;

typedef struct {
    u8 unknown_00[20];
} Record080EF970;

extern const u16 data_08149D0C[];
extern const u8 data_08399ABC[];
extern const u8 data_08399B34[];
extern const Record080EF970 data_08399B04[];
extern void *func_081443FC(void *, const void *, u32);
extern void *func_080DD4C4(void *);
extern u8 func_080DD580(void *);
extern u8 func_080DD670(void *, u8);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DF8E8(void *, u32, u32, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

s32 func_080EF970(void *context, Event080EF970 *event, State080EF970 *state)
{
    switch (event->state) {
    case 0:
        {
            u16 values[2];
            int mode;
            u32 index;
            func_081443FC(values, data_08149D0C, 4);
            state->object = event->object;
            state->entity = func_080DD4C4(state->object);
            state->entity = func_080DD4C4(state->object);
            mode = 2;
            if (func_080DD580(state->object)) {
                if (func_080DD670(state->object, 0))
                    mode = 0;
                else
                    mode = 1;
            }
            if (mode == 1) {
                s16 x, y;
                func_080DBDC8(state->entity, &x, &y);
                state->task18 = func_080D6098(x, y, 0, 1, 3, state->result,
                                              data_08399ABC, context);
                state->task24 = func_080DFD8C(data_08399B34, 1, 4, 180, context);
            }
            index = mode;
            if (mode == 2)
                index = 0;
            state->task20 = func_080DCFE4(state->object, &data_08399B04[index],
                                          12, values[index], 4, context, 216);
            if (mode == 0)
                state->task1C = func_080DF8E8(state->entity, 2, 224, context);
            state->state = 224;
        }
        break;
    case 1:
        break;
    case 0x100:
        state->task18 = func_080D6134(state->task18);
        if (state->task18 != 0)
            break;
        state->task1C = func_080DBA5C(state->task1C);
        if (state->task1C != 0)
            break;
        state->task20 = func_080DBA5C(state->task20);
        if (state->task20 == 0)
            event->state = 2;
        break;
    }
    return 0;
}
