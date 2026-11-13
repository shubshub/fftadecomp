#include "ffta.h"

// Complete target: [0x0806025C, 0x080603F4), 408 bytes, including the
// jump table and literal pools.

typedef struct {
    u16 value;
    u16 mode;
} MenuEntry0806025C;

typedef struct {
    u8 unknown_00;
    u8 flags;
} MenuRecord0806025C;

typedef struct {
    u8 unknown_000[0x1B];
    u8 count;
    u8 unknown_01C[4];
    MenuRecord0806025C *records[66];
    MenuEntry0806025C entries[1];
} MenuState0806025C;

typedef struct {
    u8 unknown_00[0x16];
    u8 visible;
    u8 unknown_17[3];
    u16 value;
} MenuList0806025C;

typedef struct {
    u8 unknown_00[4];
    u16 limit;
    u8 unknown_06[3];
    u8 flags;
    u8 unknown_0A[4];
    u16 base;
} MenuLayout0806025C;

typedef struct {
    u8 type;
    s8 count;
    u8 unknown_02[0x0E];
    u8 window[0x2C];
    MenuList0806025C list;
    u8 unknown_58[4];
    u8 other[0x28];
    MenuLayout0806025C layout;
    const void *content;
} Menu0806025C;

typedef void (*MenuCallback0806025C)(void *object);

extern MenuState0806025C *data_0200F44C;

extern void func_08016210(void *window, const void *content, u16 first, u16 second);
extern void func_080175E0(MenuList0806025C *list, u8 mode, u16 flags);
extern u16 func_08017B50(MenuList0806025C *list);
extern void func_080601D0(Menu0806025C *menu, s16 index);
extern void func_08017AD8(MenuList0806025C *list);
extern void func_08017AF4(MenuList0806025C *list, s8 index, u8 value);
extern void func_0806144C(u8 enabled);
extern void func_08015D58(void *window, MenuCallback0806025C draw, MenuCallback0806025C cursor);
extern void func_08017FB0(void *state, u8 value);
extern void func_08016234(void *window);

extern u32 func_08060100(const void *control, u32 index);
extern u32 func_080601B4(const void *control, u32 index);
extern u32 func_080601A4(const void *control, u32 index);
extern void func_08017E80(void *object);
extern void func_08017F04(void *object);

static inline MenuRecord0806025C *menu_record(int offset)
{
    MenuState0806025C *state = data_0200F44C;

    return state->records[offset + state->count];
}

void func_0806025C(Menu0806025C *menu)
{
    void *window = menu->window;
    MenuList0806025C *list = &menu->list;
    void *other = menu->other;
    MenuLayout0806025C *layout = &menu->layout;
    MenuCallback0806025C cursor = 0;
    MenuEntry0806025C *entry = &data_0200F44C->entries[menu->type];
    int i;

    func_08016210(window, menu->content, 0x1C0 + layout->base, layout->limit);

    switch (menu->type) {
    case 7:
        func_080175E0(list, 1, 4);
    case 3:
        func_08017AC4((Struct08017AC4 *)list, (u32)func_08060100, (u32)menu);
        break;
    case 5:
        func_08017AC4((Struct08017AC4 *)list, (u32)func_080601B4, (u32)menu);
        break;
    case 6:
        func_08017AC4((Struct08017AC4 *)list, (u32)func_080601A4, (u32)menu);
        break;
    case 2:
        func_080175E0(list, 1, 4);
        break;
    }

    list->value = entry->value;
    menu->count = func_08017B50(list);
    for (i = 0; i < menu->count; i++)
        func_080601D0(menu, i);
    func_08017AD8(list);

    if (menu->type == 5) {
        for (i = 0; i <= 1; i++) {
            MenuRecord0806025C *record = menu_record(i - 2);

            if (record && (record->flags & 1))
                func_08017AF4(list, i, 10);
        }
        if (entry->mode == 2)
            func_0806144C(0);
    }

    func_08017AF4(list, entry->mode, 11);

    if (list->visible < layout->limit)
        cursor = func_08017F04;
    else
        layout->flags |= 1;

    func_08015D58(window, func_08017E80, cursor);
    func_08017FB0(other, entry->mode);

    if (!(layout->flags & 0x10))
        func_08016234(window);
}
