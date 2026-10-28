typedef unsigned char u8;
typedef unsigned short u16;

struct MenuState {
    u16 command;
    u16 depth;
    u16 history[36];
    u8 unknown_4C[4];
    u8 handle;
    u8 unknown_51[0x1B];
    u8 dialog[1];
};

extern struct MenuState *data_0200F450;
extern u8 func_080C73D8(void *dialog);
extern void func_080C71B4(u8 handle);

void func_080641D4(void)
{
    switch (func_080C73D8(data_0200F450->dialog)) {
    case 2:
        data_0200F450->command = 68;
        data_0200F450->history[data_0200F450->depth++] = data_0200F450->command;
        data_0200F450->command = 52;
        data_0200F450->history[data_0200F450->depth++] = data_0200F450->command;
        data_0200F450->command = 54;
        break;
    case 0:
        func_080C71B4(data_0200F450->handle);
        data_0200F450->command = data_0200F450->history[--data_0200F450->depth];
        break;
    }
}
