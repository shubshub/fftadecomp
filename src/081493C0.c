#include "ffta.h"

typedef struct {
    u8 unknown_000[0x980];
    u8 category : 7;
    u8 active : 1;
    u8 unknown_981[9];
} __attribute__((packed)) CategoryState081493C0;

extern u8 data_03006168;
extern CategoryState081493C0 *data_0300616C;

static inline CategoryState081493C0 *find_inactive(CategoryState081493C0 *records, s32 count)
{
    CategoryState081493C0 *record;
    s32 i;

    for (i = 0, record = records; i < count; i++, record++) {
        u8 active = record->active;

        if (active == 0)
            return record;
    }
    return 0;
}

/* Complete [0x081493C0, 0x0814941C): 92 bytes, 39 instructions. */
CategoryState081493C0 *func_081493C0(void)
{
    CategoryState081493C0 *state = find_inactive(data_0300616C, data_03006168);

    state->active = 1;
    state->category = 4;
    return state;
}
