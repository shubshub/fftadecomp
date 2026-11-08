#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17;
    s16 count;
    u16 position;
    u16 base;
    u8 stride;
    u8 unknown_1F;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[0x16];
} MenuCursor;

typedef struct {
    u8 unknown_0000[0xCF0];
    u8 window[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 unknown_D64[0x1A60 - 0xD64];
    u8 buffer[0x1D45 - 0x1A60];
    u8 count;
    u8 selected;
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    const u8 *tiles;
} GraphicsState;

typedef void (*MenuCallback)(void *);
extern MenuState *data_0200F428;
extern GraphicsState data_030008B0;
extern u8 data_0600B400[];
typedef struct {
    u8 unknown_0000[0x2E64];
    u8 values[256];
} ValueState;

extern ValueState g_state_02000000;
extern u32 func_080CCA54(void);
extern void func_0814186C(const void *, void *, u32);
extern void func_08016210(void *, const void *, u16, u16);
extern void func_08054314(MenuList *list, u8 *buffer, u8 row, u8 value, u32 mode);
extern void func_08053674(MenuList *list, u8 row, u8 selected, u8 value);
extern void func_08015D58(void *, MenuCallback, MenuCallback);
extern void func_08017E80(void *);
extern void func_08017FB0(MenuCursor *cursor, u8 row);
extern void func_08052800(void *);
extern void func_08052790(void);
extern u16 func_08017B68(MenuList *list, s8 row);
extern void func_0802B108(MenuList *list);

/* Complete owner: 0x0805262C..0x08052790, 356 bytes including literal pools. */
void func_0805262C(u16 position, u16 row)
{
    MenuList *list = &data_0200F428->list;
    MenuState *state;
    u8 *window;
    u8 *resource;
    u16 fill;
    u16 *source;
    u8 count;
    u8 i;
    u8 item;
    MenuCursor *cursor;

    source = &fill;
    *source = 0;
    func_0814186C(source, list->source,
                  0x01000000 | (list->rows * list->columns * 2));
    data_0200F428->count = func_080CCA54();
    state = data_0200F428;
    window = state->window;
    resource = (u8 *)state + 0xD64;
    func_08016210(window, resource,
                  (s32)((u32)data_0600B400 - (u32)data_030008B0.tiles) / 32,
                  state->count);
    list->position = position;
    count = (u8)func_080CCA54() <= 7 ? (u8)func_080CCA54() : 7;
    for (i = 0, item = (u8)list->position; i < count; i++, item++) {
        func_08054314(list, data_0200F428->buffer, i,
                      g_state_02000000.values[item], 0);
        func_08053674(list, i, item, g_state_02000000.values[item]);
    }
    func_08015D58(data_0200F428->window, func_08017E80, 0);
    func_08017FB0(&data_0200F428->cursor, row);
    func_08052800(data_0200F428->window);
    func_08052790();
    cursor = &data_0200F428->cursor;
    data_0200F428->selected = func_08017B68(&data_0200F428->list, cursor->row);
    func_0802B108(list);
}
