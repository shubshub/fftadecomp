#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 variant;
    u8 unknown_08[0x30a];
    u8 text[18];
    u8 position;
    u8 index;
    u8 length;
    u8 unknown_327;
    u8 alternate;
    u8 unknown_329[3];
    void *window;
    u8 stage;
} State0812A5BC;

typedef void (*ClearBuffer)(void *destination, u32 size);
extern ClearBuffer const g_callbacks_0836D4B8[];
extern void func_0814186C(const void *source, void *destination, u32 control);

/* 0x0812A878..0x0812A91C, 164 bytes including the literal pool. */
void func_0812A878(State0812A5BC *state, void *destination)
{
    u8 name[20];
    u8 i;

    g_callbacks_0836D4B8[0](name, sizeof(name));
    for (i = 0; i < 9; i++) {
        if (state->text[2 * i] != 0x40 || state->text[2 * i + 1] != 0x73) {
            func_0814186C(&state->text[2 * i], name, (9 - i) & 0x1FFFFF);
            break;
        }
    }
    for (i = 8; (s8)i >= 0; i--) {
        /* 0812A8E2 clears an empty cell. 0812A8FC clears an encoded space. */
        if (name[2 * i] == 0) {
            name[2 * i] = 0;
            name[2 * i + 1] = 0;
        } else if (name[2 * i] == 0x40 && name[2 * i + 1] == 0x73) {
            name[2 * i] = 0;
            name[2 * i + 1] = 0;
        } else {
            break;
        }
    }
    func_0814186C(name, destination, 10);
}
