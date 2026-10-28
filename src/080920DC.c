typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x144];
    u8 value;
    u8 unknown_145[3];
};

extern void *func_08022840(unsigned int size);

struct Context *func_080920DC(int value)
{
    struct Context *context = func_08022840(sizeof(*context));

    context->value = value;
    return context;
}
