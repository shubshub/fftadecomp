#include "ffta.h"

/* 0x08067994..0x08067A3E: 170 bytes. */
typedef struct {
    u16 selection;
    u16 position;
} SavedTab;

typedef struct {
    u8 unknown_00[0xA24];
    SavedTab tabs[4];
} SavedMenu;

typedef struct {
    u8 unknown_00[0x1A];
    u16 selection;
    u8 unknown_1c[4];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x11];
    u8 position;
} MenuPanel;

typedef struct {
    SavedMenu *saved;
    u16 flags;
    u16 result;
    u8 mode;
    u8 unknown_09[2];
    s8 tab;
    u8 tab_count;
    u8 unknown_0d[0x43];
    MenuCursor cursor;
    MenuPanel panel;
} MenuContext;

extern void func_08141540(u32 sound);

u8 func_08067994(MenuContext *context, u16 pressed)
{
    MenuCursor *cursor = &context->cursor;
    MenuPanel *panel = &context->panel;

    if (pressed & 0x10) {
        SavedTab *tab = &context->saved->tabs[context->tab];

        tab->selection = cursor->selection;
        tab->position = panel->position;
        func_08141540(0x65);
        context->result = 0xFFFB;
        if (context->tab < context->tab_count - 1)
            ++context->tab;
        else
            context->tab = 0;
        return 1;
    } else if (pressed & 0x20) {
        SavedTab *tab = &context->saved->tabs[context->tab];

        tab->selection = cursor->selection;
        tab->position = panel->position;
        func_08141540(0x65);
        context->result = 0xFFFB;
        if (context->tab > 0)
            --context->tab;
        else
            context->tab = context->tab_count - 1;
        return 1;
    }
    return 0;
}
