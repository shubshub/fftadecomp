#include "ffta.h"

/* Target: [0x08008818, 0x08008880), 104 bytes: 82 code bytes, two alignment
 * bytes and five literal words. */
typedef struct {
    u16 phase;
    u16 row;
    u8 unknown_04[0x14];
    void *first;
    void *second;
    u8 unknown_20[0x1BAC];
    u8 settings[4];
} State;

typedef struct {
    u8 unknown_00[0xB0];
    s16 depth;
    u8 unknown_B2[0xE3E];
    u8 settings[4];
} Control;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern State *data_02009188;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern Control g_state_020020D0;
extern void *func_081443FC(void *destination, const void *source, u32 bytes);

void func_08008818(State *state, void *first, void *second, u16 row,
                   s32 depth)
{
    data_02009188 = state;
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    data_02009188->first = first;
    data_02009188->second = second;
    data_02009188->row = row;
    g_state_020020D0.depth = depth;
    func_081443FC(data_02009188->settings, g_state_020020D0.settings, 4);
    data_02009188->phase = 0;
}
