/* Target: 92 bytes / 40 instructions, 0x08063B5C..0x08063BB8. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 mode;
    u8 unknown_50[4];
    u32 flags;
} CommandState;

typedef struct {
    u8 unknown_00[8];
    u32 field_08;
} CommandRecord;

extern CommandState *data_0200F450;
extern CommandRecord g_state_020020D0;

void func_08063B5C(void)
{
    CommandState *state;

    g_state_020020D0.field_08 = 5000;
    state = data_0200F450;
    state->flags = (state->flags | 3u) & ~4u;
    state->mode = 0xC2;
    state->current = 0x23;
    state->entries[state->count++] = state->current;
    state->current = 0x33;
    state->entries[state->count++] = state->current;
    state->current = 0x42;
}
