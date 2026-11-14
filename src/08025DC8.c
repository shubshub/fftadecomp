#include "ffta.h"

// func_08025DC8 - complete [0x08025DC8, 0x08025F70), 424 bytes.

typedef struct {
    u16 selection;
    s8 row;
    u8 unknown_03;
} Config08025DC8;

typedef struct {
    u8 unknown_000[4];
    u8 mode;
    u8 scrollable;
    u8 unknown_006[0x12];
    u32 selected;
    u8 unknown_01c[0x428];
    Config08025DC8 configs[1];
} State08025DC8;

typedef struct {
    u8 unknown_00[4];
    u16 rows;
    u8 unknown_06[3];
    u8 flags;
} Rect08025DC8;

typedef struct {
    Struct08017AC4 core;
    u8 unknown_14[2];
    u8 visible;
    u8 unknown_17[3];
    u16 selection;
    u8 unknown_1c[4];
} List08025DC8;

typedef struct {
    u8 unknown_00[8];
    u8 index;
    s8 count;
    u8 unknown_0a[2];
    u8 renderer[0x2c];
    List08025DC8 list;
    u8 cursor[0x28];
    Rect08025DC8 rect;
    u8 unknown_8c[8];
    const u32 *entries;
    u8 unknown_98[4];
    const void *resource;
} Object08025DC8;

typedef void (*Callback08025DC8)(void *);

extern State08025DC8 *data_0200F438;
extern void func_08016210(void *, const void *, u32, u32);
extern u16 func_08017B50(List08025DC8 *);
extern void func_08025D14(Object08025DC8 *, Config08025DC8 *);
extern void func_080175E0(List08025DC8 *, u8, u16);
extern u16 func_08017B68(List08025DC8 *, s32);
extern u32 func_08025D84(const Object08025DC8 *, u32);
extern u32 func_08025DAC(const Object08025DC8 *, u32);
extern void func_08025B54(Object08025DC8 *, s16);
extern void func_08017AD8(List08025DC8 *);
extern void func_08017AF4(List08025DC8 *, s8, u32);
extern void func_08017F04(void *);
extern void func_08017E80(void *);
extern void func_08015D58(void *, Callback08025DC8, Callback08025DC8);
extern void func_08017FB0(void *, u8);
extern void func_08017D18(void *, u32);
extern void func_08016234(void *);

void func_08025DC8(Object08025DC8 *object, u8 adjust)
{
    List08025DC8 *list = &object->list;
    Rect08025DC8 *rect = &object->rect;
    Config08025DC8 *config = &data_0200F438->configs[object->index];
    Callback08025DC8 secondary;
    s32 i;

    func_08016210(object->renderer, object->resource, 0x200, rect->rows);
    object->count = func_08017B50(list);
    if (adjust)
        func_08025D14(object, config);
    list->selection = config->selection;
    switch (data_0200F438->mode) {
    case 12:
        func_080175E0(list, 0, 1);
        break;
    case 2:
        data_0200F438->selected = object->entries[func_08017B68(list, config->row)];
        break;
    case 3:
        func_08017AC4(&list->core, (u32)func_08025D84, (u32)object);
        break;
    case 13:
    case 14:
        func_08017AC4(&list->core, (u32)func_08025DAC, (u32)object);
        break;
    }
    for (i = 0; i < object->count; i++)
        func_08025B54(object, i);
    func_08017AD8(list);
    func_08017AF4(list, config->row, 11);
    if (list->visible < rect->rows) {
        secondary = func_08017F04;
        data_0200F438->scrollable = 0;
    } else {
        secondary = 0;
        data_0200F438->scrollable = 1;
    }
    func_08015D58(object->renderer, func_08017E80, secondary);
    func_08017FB0(object->cursor, config->row);
    if (rect->flags & 1)
        func_08017D18(object->cursor, 0);
    func_08016234(object->renderer);
}
