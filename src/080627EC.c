typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct CommandState {
    u16 command;
    u16 depth;
    u16 history[36];
    u8 unknown_4C;
    u8 status;
    u8 unknown_4E[6];
    u32 flags;
};

extern struct CommandState *data_0200F450;
extern void func_0802A2C0(u32 first, u32 second, u32 third, u32 fourth);

void func_080627EC(void)
{
    data_0200F450->flags &= ~2u;
    data_0200F450->status = 3;
    func_0802A2C0(0, 0, 0, 0);
    data_0200F450->command = 9;
    data_0200F450->history[data_0200F450->depth++] = data_0200F450->command;
    data_0200F450->command = 49;
}
