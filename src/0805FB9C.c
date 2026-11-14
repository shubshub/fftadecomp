#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09[7];
} Layout0805FB9C;

typedef struct Context0805FB9C {
    u8 mode;
    u8 unknown_01[6];
    u8 handle;
    u8 unknown_08[8];
    u8 window[0x74];
    Layout0805FB9C layout;
    void *tiles;
} Context0805FB9C;

typedef struct {
    u8 unknown_00[0x1B];
    u8 count;
    u8 unknown_1C[0x3BC];
    u8 blocks[0];
} State0805FB9C;

extern void (*const data_0836D4BC)(void *, const void *, u32);
extern const Layout0805FB9C data_08393890[];
extern const u8 data_08393910[];
extern State0805FB9C *data_0200F44C;
extern u16 func_08013B50(Layout0805FB9C *);
extern void *func_08005B28(u32);
extern void func_08017490(void *, u8, u8, u8, u8, u16, u16, u16, u8);
extern void func_08013B7C(const Layout0805FB9C *, void *, const void *);
extern void func_08016C90(void *, u8);
extern u8 func_080603F4(Context0805FB9C *);
extern u8 func_080098F4(u8 (*)(Context0805FB9C *), Context0805FB9C *);

// Complete [0x0805FB9C, 0x0805FD04): 360 bytes, 136 instructions.
void func_0805FB9C(Context0805FB9C *context)
{
    Layout0805FB9C *layout;
    void *window;

    data_0836D4BC(&context->layout, &data_08393890[context->mode], sizeof(context->layout));
    layout = &context->layout;

    switch (context->mode) {
    case 3:
    case 7:
        layout->count = data_0200F44C->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_08393910[layout->count];
        break;
    case 2:
        layout->count = data_0200F44C->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 8)
            layout->y = data_08393910[layout->count - 1];
        break;
    case 4:
        layout->count = data_0200F44C->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        break;
    case 6:
        layout->count = data_0200F44C->count - 2;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_08393910[layout->count + 1] * 2 + 4;
        break;
    }

    context->tiles = func_08005B28(func_08013B50(layout));
    window = context->window;
    func_08017490(window, layout->x, layout->y, layout->width, layout->height,
                 layout->flags, 5, 1, 12);
    func_08013B7C(layout, window, data_0200F44C->blocks);
    func_08016C90(window, layout->appearance);
    context->handle = func_080098F4(func_080603F4, context);
}
