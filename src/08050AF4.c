#include "ffta.h"

/* 0x08050AF4..0x08050B9A: 166 bytes. */
typedef struct {
    s16 top;
    u16 selected;
} SavedSelection;

typedef struct {
    u8 unknown_000[0x53C];
    SavedSelection selections[1];
} MenuData;

typedef struct {
    u8 unknown_00[0x1A];
    s16 top;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 selected;
} MenuCursor;

typedef struct {
    MenuData *data;
    u8 unknown_04[4];
    u8 group;
    u8 unknown_09;
    u8 page_size;
    u8 unknown_0B[0x3D];
    MenuList list;
    u8 unknown_64[4];
    MenuCursor cursor;
} Menu;

extern s16 func_08017BE8(MenuList *list);
extern void func_08141540(u32 sound);
extern void func_0804F948(Menu *menu);

void func_08050AF4(Menu *menu, u8 direction)
{
    MenuList *list = &menu->list;
    MenuCursor *cursor = &menu->cursor;
    SavedSelection *saved = &menu->data->selections[menu->group];
    s32 old_top = list->top;
    s32 top = old_top;
    s32 total = func_08017BE8(list) + 1;
    s32 selected = cursor->selected;
    s32 remaining = menu->page_size;

    while (remaining != 0) {
        remaining--;
        if (direction == 0x80) {
            if (top + menu->page_size < total) {
                top++;
            } else {
                remaining = 0;
                if (old_top == total - menu->page_size)
                    selected = menu->page_size - 1;
            }
        } else {
            if (top > 0) {
                top--;
            } else {
                remaining = 0;
                if (old_top == 0)
                    selected = 0;
            }
        }
    }

    if (old_top != top || cursor->selected != selected) {
        saved->top = top;
        saved->selected = selected;
        func_08141540(0x6D);
        func_0804F948(menu);
    }
}
