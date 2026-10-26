typedef unsigned char u8;

struct Context {
    u8 unknown_00[2];
    u8 value;
};

void func_0806F0D4(struct Context *context, u8 value)
{
    context->value = value;
}
