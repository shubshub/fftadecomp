#include "ffta.h"

typedef struct {
    u32 key;
    u8 unknown_04[0x102];
    u8 table;
} KeyedObject08063904;

typedef struct {
    u16 current;
    u16 count;
    u16 history[32];
    void *task;
    u8 unknown_0048[8];
    u8 mode;
    u8 counter;
    u16 unknown_0052;
    u32 flags;
    s32 result_0058;
    s32 result_005C;
    void *selected;
    u16 value_0064;
    u16 value_0066;
} State08063904;

typedef struct {
    u32 unknown_00;
    KeyedObject08063904 *selected;
} Selection08063904;

extern State08063904 *data_0200F450;
extern Selection08063904 g_state_020020D0;
extern s16 func_08065050(const void *task);
extern KeyedObject08063904 *func_08065060(void *task);
extern u32 func_080CA0F8(const KeyedObject08063904 *object);
extern void *func_0806514C(void *task);
extern void func_08066028(void *task);

/* 08063904..08063ABC: 440 bytes, 202 reachable instructions. */
void func_08063904(void)
{
    s16 result;
    KeyedObject08063904 *entry;
    State08063904 *state;

    result = func_08065050(data_0200F450->task);
    if (result == 0)
        return;

    data_0200F450->result_0058 = data_0200F450->result_005C = result;
    data_0200F450->flags |= 2;
    data_0200F450->counter = 0x10;
    data_0200F450->mode = 3;
    if (result != -1) {
        entry = func_08065060(data_0200F450->task);
        g_state_020020D0.selected = entry;
        entry->key = func_080CA0F8(entry);
        data_0200F450->selected = func_0806514C(data_0200F450->task);
    }
    func_08066028(data_0200F450->task);
    state = data_0200F450;
    if (state->flags & 4) {
        if (result == -1) {
            state->value_0064 = 0x9001;
            state->value_0066 = 0x1234;
            state->current = 0x22;
            state->history[state->count++] = 0x22;
            state->current = 0x21;
            state->history[state->count++] = 0x21;
            state->current = 0x37;
            state->history[state->count++] = 0x37;
            state->current = 0x2B;
            state->history[state->count++] = 0x2B;
            state->current = 0x28;
            state->history[state->count++] = 0x28;
            state->current = 0x39;
            state->history[state->count++] = 0x39;
        } else {
            state->current = 0x22;
            state->history[state->count++] = 0x22;
        }
    } else {
        state->value_0064 = 0x9001;
        state->value_0066 = 0x1234;
        state->current = 0x22;
        state->history[state->count++] = 0x22;
        state->current = 0x21;
        state->history[state->count++] = 0x21;
        state->current = 0x37;
        state->history[state->count++] = 0x37;
        state->current = 0x2B;
        state->history[state->count++] = 0x2B;
        state->current = 0x28;
        state->history[state->count++] = 0x28;
        state->current = 0x39;
        state->history[state->count++] = 0x39;
        state->current = 0x3B;
        state->history[state->count++] = 0x3B;
    }
    state->current = 0x32;
    state->history[state->count++] = 0x32;
    state->current = 0x38;
}
