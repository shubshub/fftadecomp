#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x103];
} CharacterState;

extern CharacterState g_state_02000080[24];

/* 0803600C..08036032: 38 bytes. */
CharacterState *func_0803600C(void)
{
    CharacterState *character = g_state_02000080;
    s32 index;

    for (index = 0; index < 24; index++, character++) {
        if (character->active == 0)
            return character;
    }
    return 0;
}
