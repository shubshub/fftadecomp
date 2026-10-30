#include "ffta.h"

typedef struct SelectionRecord080364BC {
    u8 type : 5;
    u8 unknown_05 : 3;
    u8 unknown_01[5];
} __attribute__((packed)) SelectionRecord080364BC;

typedef struct SelectionState080364BC {
    u8 unknown_0000[0x2E36];
    SelectionRecord080364BC records[5];
} SelectionState080364BC;

extern SelectionState080364BC g_state_02000000;

/* Complete target [0x080364BC, 0x080364FC): 64 bytes, 27 instructions. */
s32 func_080364BC(u8 type)
{
    s32 index;
    SelectionState080364BC *state;
    u32 search_type;

    if (type == 0)
        return -1;

    index = 0;
    state = &g_state_02000000;
    search_type = type;

    for (; index < 5; index++) {
        if (state->records[index].type == search_type)
            return index;
    }
    return -1;
}
