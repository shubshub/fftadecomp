#include "ffta.h"

typedef struct {
    u16 selection;
    u16 row;
} Config0806025C;

typedef struct {
    u8 unknown_00;
    u8 flags;
} Record0806025C;

typedef struct {
    u8 unknown_000[0x1B];
    u8 count;
    u8 unknown_01C[4];
    Record0806025C *records[66];
    Config0806025C configs[1];
} State0806025C;

typedef struct {
    Struct08017AC4 core;
    u8 unknown_14[2];
    u8 visible;
    u8 unknown_17[3];
    u16 selection;
    u8 unknown_1c[4];
} List0806025C;

typedef struct {
    u8 unknown_00[4];
    u16 rows;
    u8 unknown_06[3];
    u8 flags;
    u8 unknown_0a[4];
    u16 tile;
} Rect0806025C;

typedef struct {
    u8 mode;
    s8 count;
    u8 unknown_02[0x0e];
    u8 renderer[0x2c];
    List0806025C list;
    u8 cursor[0x28];
    Rect0806025C rect;
    const void *resource;
} Object0806025C;

typedef void (*Callback0806025C)(void *);

extern State0806025C *data_0200F44C;

extern void func_08016210(void *, const void *, u16, u16);
extern void func_080175E0(List0806025C *, u8, u16);
extern u16 func_08017B50(List0806025C *);
/* s16, as 0806094C declares it: this caller sign-extends the row from 16 bits
 * (lsls/asrs #0x10 at 0x0806032C); func_080601D0 narrows it to s8 itself. */
extern void func_080601D0(Object0806025C *, s16);
extern void func_08017AD8(List0806025C *);
/* s8 row, as 0805F824 and 0804F948 declare it: both calls sign-extend it from
 * 8 bits (asrs #0x18 at 0x08060370, ldrsb at 0x08060392). */
extern void func_08017AF4(List0806025C *, s8, u8);
extern void func_0806144C(u8);
extern void func_08015D58(void *, Callback0806025C, Callback0806025C);
extern void func_08017FB0(void *, u8);
extern void func_08016234(void *);
extern void func_08017E80(void *);
extern void func_08017F04(void *);
extern u8 func_08060100(void *, int);
extern u32 func_080601B4(const void *, u32);
extern u32 func_080601A4(const void *, u32);

/* Complete target: [0x0806025C, 0x080603F4), 408 bytes: 160 instructions,
 * the six-word jump table and the literal pools. */
void func_0806025C(Object0806025C *object)
{
    u8 *renderer = object->renderer;
    List0806025C *list = &object->list;
    u8 *cursor = object->cursor;
    Rect0806025C *rect = &object->rect;
    Callback0806025C secondary = 0;
    Config0806025C *config = &data_0200F44C->configs[object->mode];
    s32 i;

    func_08016210(renderer, object->resource, 0x1c0 + rect->tile, rect->rows);
    switch (object->mode) {
    case 7:
        /* Falls into case 3: the call at 0x080602EA runs on into 0x080602EE. */
        func_080175E0(list, 1, 4);
    case 3:
        func_08017AC4(&list->core, (u32)func_08060100, (u32)object);
        break;
    case 5:
        func_08017AC4(&list->core, (u32)func_080601B4, (u32)object);
        break;
    case 6:
        func_08017AC4(&list->core, (u32)func_080601A4, (u32)object);
        break;
    case 2:
        func_080175E0(list, 1, 4);
        break;
    }
    list->selection = config->selection;
    object->count = func_08017B50(list);
    for (i = 0; i < object->count; i++)
        func_080601D0(object, i);
    func_08017AD8(list);
    if (object->mode == 5) {
        for (i = 0; i < 2; i++) {
            Record0806025C *record = data_0200F44C->records[data_0200F44C->count - 2 + i];

            if (record && (record->flags & 1))
                func_08017AF4(list, i, 10);
        }
        if (config->row == 2)
            func_0806144C(0);
    }
    func_08017AF4(list, config->row, 11);
    if (list->visible < rect->rows)
        secondary = func_08017F04;
    else
        rect->flags |= 1;
    func_08015D58(renderer, func_08017E80, secondary);
    func_08017FB0(cursor, config->row);
    if (!(rect->flags & 0x10))
        func_08016234(renderer);
}
