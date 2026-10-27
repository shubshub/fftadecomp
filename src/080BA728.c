#include "ffta.h"

/* 080BA728 .. 080BA7D8: 176 bytes. */
typedef struct {
    void *object;
    u32 unknown_04;
    u32 unknown_08;
} ObjectEntry;

typedef struct {
    u32 unknown_00;
    ObjectEntry entries[13];
    u32 unknown_A0;
} State;

extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_08394040[])(void *, s32);
extern void (*data_08394038[])(void *, const void *);
extern void (*data_08394034[])(void *, s32, s32, s32, s32, s32);
extern void (*data_0836D4BC[])(void *, const void *, u32);
extern const u8 data_0839168C[];
extern u8 data_03003BA4[];
extern State *func_08022840(u32);
extern void *func_0808F79C(void);
extern const u8 *func_080CBABC(s32);

State *func_080BA728(void)
{
    State *state = func_08022840(sizeof(State));
    s32 index;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    for (index = 0; index < 13; index++) {
        state->entries[index].object = func_0808F79C();
        data_08394040[0](state->entries[index].object, -127);
        data_08394038[0](state->entries[index].object, data_0839168C);
        data_08394034[0](state->entries[index].object, 0, 0, 0, 0, 10);
    }
    data_0836D4BC[0](data_03003BA4, func_080CBABC(4) + 4, 14);
    return state;
}
