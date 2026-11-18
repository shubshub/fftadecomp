#include "ffta.h"

typedef struct Context Context;

typedef struct {
    u8 unknown_00[0xD0];
    u16 field_D0;
    u16 unknown_D2;
    u16 field_D4;
    u8 unknown_D6[0x108 - 0xD6];
} Record0809F78C;

typedef struct {
    Record0809F78C *record;
} Entry0809F78C;

typedef struct Layout08027DA0 {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09;
    u8 unknown_0A[6];
    u16 cursor;
    u8 scroll;
    u8 unknown_13;
} Layout08027DA0;

typedef struct Menu08027DA0 {
    u8 unknown_00[0x80];
    Layout08027DA0 layout;
    u32 *items;
    u8 *enabled;
    void *text;
} Menu08027DA0;

extern void *func_08096D7C(void);
extern u32 func_0809F78C(Context *context, Entry0809F78C **entries, u16 count);

void func_08027528(Menu08027DA0 *menu)
{
    Entry0809F78C *entries[20];
    int i;

    func_0809F78C(func_08096D7C(), entries, 20);
    for (i = 0; i < 20; i++)
        menu->items[i] = (u32)entries[i]->record;
}
