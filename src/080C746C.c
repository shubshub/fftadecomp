typedef unsigned char u8;

struct Context {
    u8 unknown_00[8];
    void *allocation;
};

extern void func_08022854(void *allocation);

/* Target: 080C746C..080C7484, 24 bytes. */
void func_080C746C(struct Context *context)
{
    if (context->allocation) {
        func_08022854(context->allocation);
        context->allocation = 0;
    }
}
