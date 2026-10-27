#include "ffta.h"

/* 0x08038564..0x080385A6: 66 bytes. */
typedef struct {
    u8 identifier;
    u8 unknown_01;
    u16 value;
} CachedRecord;

typedef struct {
    u8 unknown_00[0x2B08];
    CachedRecord entries[64];
} CacheState;

extern CacheState g_state_02000000;

int func_08038564(u16 identifier)
{
    int i;
    CacheState *state = &g_state_02000000;

    for (i = 0; i < 64; i++) {
        if (state->entries[i].identifier == identifier) {
            state->entries[i].identifier = 0;
            state->entries[i].value = 0;
            return 1;
        }
    }
    return 0;
}
