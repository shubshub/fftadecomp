#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 state;
    u8 unknown_119A;
    u8 action;
    u8 unknown_119C[0x10];
    void *resources[169];
    void *current;
} MenuState;

typedef struct {
    void *resource;
    u8 unknown_04[12];
    u8 selection;
    u8 count;
    u8 mode;
} ResourceSelection;

extern MenuState *data_0200F448;
extern ResourceSelection g_state_020020D0;
extern u8 data_030008B0[];
extern u8 func_08060DD4(void);
extern u16 func_08060DC4(void);
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 width, s16 height, u8 enabled);

/* 0x0805DA10..0x0805DAA8 - 152 bytes, 59 reachable instructions. */
u32 func_0805DA10(u8 selection, u8 count, u8 mode)
{
    switch (func_08060DD4()) {
    case 1:
    case 2:
        return 1;
    case 3:
    case 4: {
        u16 index = func_08060DC4();

        data_0200F448->current = data_0200F448->resources[index];
        g_state_020020D0.resource = data_0200F448->current;
        g_state_020020D0.selection = selection;
        g_state_020020D0.count = count;
        g_state_020020D0.mode = mode;
        func_08029E48(data_030008B0, 0, 0, 20, 17, 0);
        data_0200F448->action = 5;
        data_0200F448->state = 0x13;
        break;
    }
    }
    return 0;
}
