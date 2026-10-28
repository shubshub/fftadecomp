typedef unsigned char u8;

struct Widget {
    u8 unknown_00[0x10];
    u8 flags;
};

struct Source {
    u8 unknown_00[0x84];
    struct Widget widget;
};

struct MenuConfig {
    u8 unknown_00[8];
    u8 appearance;
    u8 unknown_09[7];
};

struct Context {
    void *global;
    struct Source *source;
    u8 handle;
    u8 flags;
    u8 unknown_0A[0xE];
    struct MenuConfig config;
    u8 menu[1];
};

extern void func_080686C0(struct Context *context);
extern void func_08016C90(void *menu, u8 appearance);
extern void func_08066EA0(struct Context *context);
extern u8 func_080098F4(void (*callback)(struct Context *), struct Context *context);

void func_0806890C(struct Context *context)
{
    struct MenuConfig *config = &context->config;
    struct Widget *widget = &context->source->widget;

    context->flags |= 1;
    if (widget)
        widget->flags &= 0xF3;
    func_080686C0(context);
    func_08016C90(context->menu, config->appearance);
    context->handle = func_080098F4(func_08066EA0, context);
}
