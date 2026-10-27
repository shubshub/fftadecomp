#include "ffta.h"

/* 080282D4..08028350: 124 bytes. */
struct Window {
    u8 unknown_00[0x1C];
    u8 flags;
    u8 unknown_1D[0x57];
};

struct WindowConfig {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 tile;
    u16 unknown_08;
    u8 color;
    u8 style;
};

struct Dialog {
    u32 unknown_00;
    void *owner;
    u32 unknown_08;
    struct Window window;
    struct WindowConfig config;
};

struct Options {
    u8 unknown_00[3];
    u8 enabled;
};

enum { WINDOW_CONTROL_MASK = 0xC00 };

extern u16 g_control_flags_03000940;
extern struct Options *data_0200F438;
extern void func_08017490(struct Window *window, u8 x, u8 y,
                         u8 width, u8 height, u16 tile,
                         u8 color, u8 style, u8 kind);
extern void func_080282A4(struct Dialog *dialog);

void func_080282D4(struct Dialog *dialog)
{
    struct Window *window = &dialog->window;
    const struct WindowConfig *config = &dialog->config;

    u16 *control = &g_control_flags_03000940;
    u16 mask = WINDOW_CONTROL_MASK;
    u32 control_flags = *control;

    *control = mask | control_flags;
    func_08017490(window, config->x, config->y, config->width,
                 config->height, config->tile, config->color,
                 config->style, config->color == 0x32 ? 0xB : 0xC);
    if (dialog->owner != 0 && data_0200F438->enabled != 0)
        window->flags |= 1;
    func_080282A4(dialog);
}
