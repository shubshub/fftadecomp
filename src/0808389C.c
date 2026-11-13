#include "ffta.h"

// Complete target: [0x0808389C, 0x08083A00), 356 bytes.

typedef struct {
    u8 unknown_00[0x0c];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[2];
    u16 offset;
    u16 tile_base;
    u8 unknown_1e;
    u8 palette;
} List0808389C;

typedef struct {
    u8 panel[0x2c];
    List0808389C list;
    u8 cursor[0x14];
    u8 settings[0x14];
} Menu0808389C;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[0x16];
    u16 *count;
    Menu0808389C menu;
    const void *resource;
    u8 unknown_c4[8];
} Slot0808389C;

typedef struct {
    u8 unknown_0000[0x2c88];
    Slot0808389C slots[1];
} State0808389C;

typedef struct {
    u8 unknown_00[0x0e];
    u16 height;
    u8 unknown_10[0x3c];
} RenderObject0808389C;

typedef void (*Callback0808389C)(void);

extern State0808389C *data_03002818;
extern RenderObject0808389C data_030009E0[];
extern void func_08016210(u8 *panel, const void *resource, u16 height, u16 count);
extern u16 func_08017B50(List0808389C *list);
extern void func_08083A00(s32 index, s16 row, List0808389C *list);
extern void func_08085558(List0808389C *list, u16 offset);
extern void func_08017C28(u8 *cursor, List0808389C *list, Callback0808389C callback, u32 mode);
extern void func_08017DB4(u8 *settings, List0808389C *list, Callback0808389C callback, u32 mode);
extern void func_08081078(void);
extern void func_0808118C(void);

static inline void fill_tiles(List0808389C *list)
{
    u16 *line = list->tiles;
    u16 tile = (list->palette << 12) + list->tile_base;
    s32 width = 11;
    s32 rows = list->rows;

    for (; rows != 0; rows--) {
        s32 n;

        for (n = 0; n < width; n++) {
            u16 *p = &line[n];

            p[0] = tile++;
            p[list->stride] = tile++;
        }
        line += list->stride * 2;
    }
    func_08085558(list, list->offset * 2);
}

static inline void attach_menu(Menu0808389C *menu, Callback0808389C select,
                               Callback0808389C change)
{
    List0808389C *list = &menu->list;

    func_08017C28(menu->cursor, list, select, 0);
    func_08017DB4(menu->settings, list, change, 13);
}

u16 func_0808389C(s32 index, u32 refresh)
{
    u16 object_id = data_03002818->slots[index].object_id;
    u16 count;
    s32 row;

    if (!refresh)
        func_08016210(data_03002818->slots[index].menu.panel,
                      data_03002818->slots[index].resource,
                      data_030009E0[object_id].height,
                      *data_03002818->slots[index].count);
    count = func_08017B50(&data_03002818->slots[index].menu.list);
    for (row = 0; row < count; row++)
        func_08083A00(index, row, &data_03002818->slots[index].menu.list);
    fill_tiles(&data_03002818->slots[index].menu.list);
    if (!refresh)
        attach_menu(&data_03002818->slots[index].menu, func_08081078,
                    func_0808118C);
    return count;
}
