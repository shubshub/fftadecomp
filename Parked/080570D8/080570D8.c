#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *dest;
    u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 columns;
    u8 count;
    s16 limit;
    u16 position;
    u16 tile;
    u8 stride;
    u8 palette;
} List;

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 x;
    u16 y;
    u16 counter;
    u16 extent;
    u8 flags;
    u8 value;
    u8 field_12;
    u8 unknown_13;
} Controls;

typedef struct Cursor Cursor;
typedef void (*CursorCallback)(Cursor *);
typedef struct {
    u8 unknown_00[0x2C];
    List list;
    Controls controls;
    u8 cursor[0x14];
} Window;

typedef struct {
    u8 unknown_00[0x1490];
    Window window;
    u8 content[0x19C8 - 0x1504];
    u8 text[0x2D3A - 0x19C8];
    u8 entries[24];
    u8 count;
    u8 unknown_2D53[2];
    u8 selected;
} State;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;
extern State *data_0200F428;
extern Graphics data_030008B0;
extern u8 data_0600C000[];
extern void func_0814186C(const void *source, void *dest, u32 control);
extern u8 func_0805459C(void);
extern void func_08016210(void *window, const void *content, u16 first, u16 second);
extern void func_08057CDC(List *list, void *text, u8 entry, u8 row, u8 mode);
extern void func_08057E24(List *list, const u8 *entries, u8 mode);
extern void func_0802B108(List *list);
extern void func_08015D58(Window *window, u32 value, CursorCallback callback);
extern void func_08017E80(void *object);
extern void func_08017F04(Cursor *object);
extern void func_08017D18(Controls *controls, u8 mask);
extern void func_0805872C(Controls *controls, u8 value);
extern u8 func_0805871C(List *list, u8 value);
extern void func_080573E8(void);

void func_080570D8(u8 position, u8 direction)
{
    List *list;
    u16 fill;
    u16 row;
    u16 entry;

    data_0200F428->count = func_0805459C();
    list = &data_0200F428->window.list;
    fill = 0;
    func_0814186C(&fill, list->source,
                 0x01000000 | (list->width * list->columns * 2));
    func_08016210(&data_0200F428->window, data_0200F428->content,
                 (data_0600C000 - data_030008B0.tiles) / 32,
                 data_0200F428->count);
    list->position = position;
    for (row = 0, entry = list->position;
         row < (data_0200F428->count < 3 ? data_0200F428->count : 3);
         row++, entry++) {
        func_08057CDC(list, data_0200F428->text,
                     data_0200F428->entries[entry], row, 1);
    }
    func_08057E24(list, data_0200F428->entries, 1);
    func_0802B108(list);
    if (data_0200F428->count <= 3)
        func_08015D58(&data_0200F428->window, (u32)func_08017E80, 0);
    else
        func_08015D58(&data_0200F428->window, (u32)func_08017E80,
                     func_08017F04);
    func_08017D18(&data_0200F428->window.controls, 3);
    func_0805872C(&data_0200F428->window.controls, direction);
    {
        Controls *current = &data_0200F428->window.controls;
        List *currentList = &data_0200F428->window.list;
        data_0200F428->selected = func_0805871C(currentList, current->value);
    }
    func_080573E8();
}
