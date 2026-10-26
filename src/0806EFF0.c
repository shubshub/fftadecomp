typedef unsigned char u8;

struct Context {
    u8 unknown_00[7];
    u8 mode;
    u8 unknown_08[4];
    void *object;
    u8 unknown_10[0x68];
    u8 x;
    u8 y;
};

extern void func_0802B2E8(void *object, u8 x, u8 y, u8 mode, int size);

void func_0806EFF0(struct Context *context)
{
    func_0802B2E8(context->object, context->x, context->y, context->mode * 2, 2);
}
