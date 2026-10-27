#include "ffta.h"

/* 0x08028708..0x080287C4: 188 bytes. */
typedef struct {
    u8 unknown_00[0x11];
    s8 selected;
} SelectionCursor;

typedef struct {
    u8 unknown_00[9];
    s8 count;
    u8 unknown_0A[0x2E];
    u8 highlights[0x20];
    SelectionCursor cursor;
} SelectionMenu;

extern u8 data_03000000[];
extern void func_08017AF4(u8 *highlights, s32 index, u32 value);
extern void func_08017FB0(SelectionCursor *cursor, u8 index);
extern void func_08141540(u32 sound);
extern void func_080023D0(void *state);

s32 func_08028708(SelectionMenu *menu, u16 keys)
{
    SelectionCursor *cursor = &menu->cursor;
    s8 selected = 0;
    s32 changed = 0;

    if (keys & 0x80) {
        selected = cursor->selected;
        func_08017AF4(menu->highlights, selected, 0xFF);
        if (menu->count > 1)
            func_08141540(0x6D);
        func_080023D0(data_03000000);
        selected++;
        if (selected >= menu->count)
            selected = 0;
        changed = 1;
    } else if (keys & 0x40) {
        selected = cursor->selected;
        func_08017AF4(menu->highlights, selected, 0xFF);
        if (menu->count > 1)
            func_08141540(0x6D);
        func_080023D0(data_03000000);
        selected--;
        if (selected < 0)
            selected = menu->count - 1;
        changed = 1;
    }

    if (changed) {
        func_08017FB0(cursor, selected);
        func_08017AF4(menu->highlights, selected, 0x0B);
    }
    return 0;
}
