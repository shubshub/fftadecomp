typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x3C];
    void *object;
};

extern void func_081492A8(void *object);

void func_08099F00(struct Context *context)
{
    func_081492A8(context->object);
}
