#include "ffta.h"

typedef struct {
    u16 selection;
    s8 row;
    u8 unknown_03;
} Config08066ED8;

typedef struct {
    u8 unknown_000[0xa04];
    Config08066ED8 normal[8];
    Config08066ED8 special[1];
} Context08066ED8;

typedef struct {
    u8 unknown_00[4];
    u16 rows;
    u8 unknown_06[8];
    u16 count;
} Rect08066ED8;

typedef struct {
    Struct08017AC4 core;
    u8 unknown_14[2];
    u8 visible;
    u8 unknown_17[3];
    u16 selection;
    u8 unknown_1c[4];
} List08066ED8;

typedef struct {
    Context08066ED8 *context;
    union {
        u16 word;
        u8 bytes[4];
    } flags;
    u8 mode;
    u8 unknown_09;
    u8 count;
    s8 special_index;
    u8 unknown_0c;
    u8 active;
    u8 unknown_0e[6];
    Rect08066ED8 rect;
    u8 renderer[0x2c];
    List08066ED8 list;
    u8 cursor[0x2c];
    const void *resource;
    u8 unknown_a0[0x1c];
    u8 first_label[0x10];
    u8 second_label[0x10];
} Object08066ED8;

typedef void (*Callback08066ED8)(void *);

extern const u8 data_0851BA72[];
extern const u8 data_0851BA7A[];
extern void func_08017FA8(void *, const u8 *, u32, u32);
extern void func_08016210(void *, const void *, u32, u32);
extern void func_080674B0(void);
extern void func_08067504(void);
extern void func_08067528(void);
extern void func_08067574(void);
extern u8 func_08017B50(List08066ED8 *);
extern void func_080676F8(Object08066ED8 *, s16);
extern void func_08017AD8(List08066ED8 *);
extern void func_08017AF4(List08066ED8 *, s8, u32);
extern void func_08067E48(Object08066ED8 *, u8, u32);
extern void func_08017F04(void *);
extern void func_08017E80(void *);
extern void func_08015D58(void *, Callback08066ED8, Callback08066ED8);
extern void func_08017FB0(void *, u8);
extern void func_08016234(void *);
extern void func_08017D18(void *, u32);

/* 0x08066ED8..0x0806707C: 420 bytes, 174 instructions. */
void func_08066ED8(Object08066ED8 *object)
{
    u8 *renderer = object->renderer;
    Rect08066ED8 *rect = &object->rect;
    List08066ED8 *list = &object->list;
    u8 *cursor = object->cursor;
    Callback08066ED8 secondary = 0;
    Config08066ED8 *config = &object->context->normal[object->mode];
    s32 i;

    if (object->mode == 4) {
        config = &object->context->special[object->special_index];
        object->active = 1;
        func_08017FA8(object->first_label, data_0851BA72, 196, 8);
        func_08017FA8(object->second_label, data_0851BA7A, 12, 8);
    }
    {
        const void *resource = object->resource;
        u32 count = rect->count;

        func_08016210(renderer, resource,
                      (object->mode == 4 ? count + 1 : count) ? 0x100 : 0x1c0,
                      rect->rows);
    }
    switch (object->mode) {
    case 3:
        func_08017AC4(&list->core, (u32)func_080674B0, (u32)object);
        break;
    case 4:
        func_08017AC4(&list->core, (u32)func_08067504, (u32)object);
        break;
    case 5:
        func_08017AC4(&list->core, (u32)func_08067528, (u32)object);
        break;
    case 6:
        func_08017AC4(&list->core, (u32)func_08067574, (u32)object);
        break;
    }
    list->selection = config->selection;
    object->count = func_08017B50(list);
    for (i = 0; i < object->count; i++)
        func_080676F8(object, i);
    func_08017AD8(list);
    func_08017AF4(list, config->row, 11);
    if (object->mode == 5) {
        for (i = 0; i < object->count; i++)
            func_08067E48(object, i, 1);
    }
    if (list->visible < rect->rows)
        secondary = func_08017F04;
    else
        object->flags.word |= 0x10;
    func_08015D58(renderer, func_08017E80, secondary);
    func_08017FB0(cursor, (u8)config->row);
    func_08016234(renderer);
    if (object->flags.bytes[0] & 1)
        func_08017D18(object->cursor, 1);
}
