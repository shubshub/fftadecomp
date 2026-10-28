typedef unsigned char u8;

struct Context {
    u8 unknown_00[9];
    u8 flags;
    u8 unknown_0A[0xB2];
    void *child;
};

extern void func_08005B40(void *child);

void func_08066D74(struct Context *context)
{
    if (context->child) {
        func_08005B40(context->child);
        context->child = 0;
    }
    context->flags |= 2;
}
