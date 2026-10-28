typedef unsigned char u8;

struct MenuState {
    u8 unknown_00[0x4C];
    u8 ready;
};

extern struct MenuState *data_0200F450;
extern void func_0802A2C0(int first, int second, int third, int fourth);
extern void func_08004C40(void);

void func_08062224(void)
{
    func_0802A2C0(0, 0, 0, 0);
    func_08004C40();
    data_0200F450->ready = 1;
}
