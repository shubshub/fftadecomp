#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 field_4e;
    u8 unknown_50[4];
    u32 flags;
} State0806297C;

extern State0806297C *data_0200F450;
extern s16 func_08065050(void *);
extern void func_08066018(void *);

/* Complete [0x0806297C, 0x080629DC): 96 bytes, 44 instructions. */
void func_0806297C(void)
{
    s16 result = func_08065050(data_0200F450->context);

    if (result != 0) {
        func_08066018(data_0200F450->context);
        if (result == -1) {
            data_0200F450->current = 8;
        } else {
            State0806297C *state = data_0200F450;

            state->field_4e = 0xae;
            state->flags |= 2;
            state->current = 0x0b;
            state->entries[state->count++] = 0x0b;
            state->current = 0x33;
        }
    }
}
