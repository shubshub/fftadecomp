typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x0C];
    u8 flags;
};

void func_0809D8D0(struct Context *context, u8 enabled)
{
    if (enabled == 0)
        context->flags |= 2;
    else
        context->flags &= ~2;
}
