#include "ffta.h"

typedef struct {
    u8 panel[0x2c];
    u8 list[0x20];
    u8 cursor[0x14];
    u8 settings[0x14];
} Menu08084C98;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[0x16];
    u16 *count;
    Menu08084C98 menu;
    const void *resource;
    u8 unknown_c4[8];
} Slot08084C98;

typedef struct {
    u8 unknown_0000[0x2c88];
    Slot08084C98 slots[1];
} State08084C98;

typedef struct {
    u8 unknown_00[0x0e];
    u16 height;
    u8 unknown_10[0x3c];
} RenderObject08084C98;

typedef void (*Callback08084C98)(void);

extern State08084C98 *data_03002818;
extern RenderObject08084C98 data_030009E0[];
extern void func_08016210(u8 *panel, const void *resource, u16 height, u16 count);
extern u16 func_08017B50(u8 *list);
extern void func_08084A98(u32 index, s16 row, u8 *list);
extern void func_08084BD0(u16 object_id, u8 *list);
extern void func_08017C28(u8 *cursor, u8 *list, Callback08084C98 callback, u32 mode);
extern void func_08017DB4(u8 *settings, u8 *list, Callback08084C98 callback, u32 mode);
extern void func_08081078(void);
extern void func_0808118C(void);

static inline void attach_menu(Menu08084C98 *menu, Callback08084C98 select,
                               Callback08084C98 change)
{
    u8 *list = menu->list;

    func_08017C28(menu->cursor, list, select, 0);
    func_08017DB4(menu->settings, list, change, 13);
}

/* Complete target: [0x08084C98, 0x08084DA0), 264 bytes. */
u16 func_08084C98(s32 index, u32 refresh)
{
    u16 object_id = data_03002818->slots[index].object_id;
    u16 count;
    s32 row;

    if (!refresh)
        func_08016210(data_03002818->slots[index].menu.panel,
                      data_03002818->slots[index].resource,
                      data_030009E0[object_id].height,
                      *data_03002818->slots[index].count);
    count = func_08017B50(data_03002818->slots[index].menu.list);
    for (row = 0; row < count; row++)
        func_08084A98(index, row, data_03002818->slots[index].menu.list);
    func_08084BD0(object_id, data_03002818->slots[index].menu.list);
    if (!refresh)
        attach_menu(&data_03002818->slots[index].menu, func_08081078,
                    func_0808118C);
    return count;
}
