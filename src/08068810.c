typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x10];
    void *resources;
};

int func_08068810(struct Context *context)
{
    return context->resources != 0;
}
