typedef unsigned char u8;
typedef unsigned short u16;

struct Context {
    u8 unknown_00[0x40];
    void *object;
};

extern void func_08021DF8(void *object, u16 first, u16 second);

void func_0809A5AC(struct Context *context, u16 first, u16 second)
{
    func_08021DF8(context->object, first, second);
}
