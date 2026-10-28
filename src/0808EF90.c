typedef unsigned char u8;
typedef unsigned short u16;

struct State {
    u8 unknown_00[0x2D50];
    void *context;
};

extern struct State *data_03002818;
extern int func_0808CBDC(u16 index, void *context);

int func_0808EF90(int count)
{
    int index;

    for (index = 0; index < count; index++) {
        if (func_0808CBDC(index, data_03002818->context))
            return 1;
    }

    return 0;
}
