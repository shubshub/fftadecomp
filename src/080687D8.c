typedef unsigned char u8;

struct Context {
    u8 unknown_00[9];
    u8 handle;
    u8 unknown_0A[4];
    u8 counter;
    u8 unknown_0F[0xD];
    u8 appearance;
    u8 unknown_1D[7];
    u8 menu[0x4C];
    u8 panel[1];
};

extern void func_08017508(void *menu, u8 appearance);
extern void func_08017D18(void *panel, int mode);
extern void func_08066E08(struct Context *context);
extern u8 func_080098F4(void (*callback)(struct Context *), struct Context *context);

void func_080687D8(struct Context *context)
{
    func_08017508(context->menu, context->appearance);
    func_08017D18(context->panel, 0);
    context->counter = 0;
    context->handle = func_080098F4(func_08066E08, context);
}
