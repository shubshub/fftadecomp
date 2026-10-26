#include "ffta.h"

typedef struct {
    u8 unknown_00[0xd0];
    s16 readiness;
    u8 unknown_d2[2];
    s16 bonus;
    u8 unknown_d6[0x32];
} Entry0809DF7C;

typedef struct {
    s32 count;
    Entry0809DF7C entries[13];
} State0809DF7C;

extern u8 func_080CD92C(const void *entry);
extern s32 func_0812E368(const void *entry);
extern u8 func_080CDCEC(const void *entry);

/* Complete [0x0809DF7C, 0x0809E05A): 222 bytes, 103 instructions. */
void func_0809DF7C(State0809DF7C *state)
{
    s32 maximum = -8000;
    s32 i;

    for (i = 0; i < state->count; i++) {
        if (func_080CD92C(&state->entries[i]) || !func_0812E368(&state->entries[i]) ||
            func_080CDCEC(&state->entries[i])) {
            state->entries[i].readiness = 0;
            state->entries[i].bonus = 0;
        } else {
            s32 increment = func_0812E368(&state->entries[i]) + state->entries[i].bonus;
            s32 value = state->entries[i].readiness + increment;

            state->entries[i].bonus = 0;
            state->entries[i].readiness = value;
        }
        if (state->entries[i].readiness > maximum)
            maximum = state->entries[i].readiness;
    }

    if (maximum > 1000) {
        maximum -= 1000;
        if (maximum > 500)
            maximum = 500;
        for (i = 0; i < state->count; i++) {
            s32 value = state->entries[i].readiness - maximum;

            if (value < 0) {
                state->entries[i].bonus = value + maximum;
                value = 0;
            } else {
                state->entries[i].bonus = maximum;
            }
            state->entries[i].readiness = value;
        }
    }
}
