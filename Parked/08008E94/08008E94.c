#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} Resource;

typedef struct {
    u8 unknown_00[4];
    u16 setting;
    u8 unknown_06[8];
    u16 tile;
} Descriptor;

typedef struct {
    u8 unknown_00[0x12];
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
} Widget;

typedef struct {
    u8 unknown_00[0x16];
    u8 value;
    u8 unknown_17;
    s16 limit;
    u16 position;
    u8 unknown_1C[4];
} List;

typedef struct {
    u16 unknown_00;
    u16 selector;
    u8 unknown_04[0x14];
    Resource *resource;
    u8 unknown_1C[5];
    u8 count;
    u8 unknown_22[0x292];
    Descriptor descriptor;
    Widget widget;
    List list;
    u8 scroll[0x150];
    u8 text[1];
} State;

typedef struct ScrollState ScrollState;
typedef void (*ScrollCallback)(ScrollState *state);

void func_08015C90(Widget *widget, void *text, u8 width, u8 height,
                   u16 tile, u16 setting);
u16 func_08017B50(List *list);
void func_08008F94(s8 index);
void func_08017AD8(List *list);
void func_08017AF4(List *list, u8 position, u8 mode);
void func_08015D58(Widget *widget, ScrollCallback first, ScrollCallback second);
void func_08017E80(ScrollState *state);
void func_08017F04(ScrollState *state);
void func_08017FB0(ScrollState *state, u8 value);
void func_08009414(u8 value);
void func_080157A8(u16 *tiles, u8 x, u8 y, u8 width, u8 height, u8 stride,
                   u16 tile, u8 palette);
void func_08016234(Widget *widget);

/* Target: 0x08008E94, 256 bytes including alignment and four literal words. */
void func_08008E94(void)
{
    State **active = (State **)0x02009188;
    Widget *widget = &(*active)->widget;
    Descriptor *descriptor = &(*active)->descriptor;
    List *list = &(*active)->list;
    ScrollState *scroll = (ScrollState *)(*active)->scroll;
    void *text = (*active)->text;
    u8 width = widget->width;
    u8 height = widget->height - 5;
    int index;

    func_08015C90(widget, text, width, height,
                   descriptor->tile + (*active)->selector, descriptor->setting);
    list->position = 0;
    (*active)->count = func_08017B50(list);
    for (index = 0; index < (*active)->count; index++)
        func_08008F94(index);
    func_08017AD8(list);
    func_08017AF4(list, 0, 11);
    func_08015D58(widget, func_08017E80, func_08017F04);
    func_08017FB0(scroll, 0);
    func_08009414(0);
    func_080157A8((*active)->resource->tiles, 4, 15, 22, 2, 32,
                   0x134 + (*active)->selector, 12);
    func_08016234(widget);
}
