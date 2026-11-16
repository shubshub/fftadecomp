#include "ffta.h"

/* Complete target [0x08082924,0x08082AEC), 456 bytes:
 * f0b557464e464546e0b481b082460091504f3d68cc205446444328194e4940180688009a002a19d1
 * 60194c4bc0184c4aa918091909684b4b4c227243d218d289494eab191b191b681b8893f74ffc3868
 * 2018b42189014018fef7f0ff38680219424bd21813880221194311802018b426b601801995f7daf8
 * 0004060c0025b5420edab8463a4827182904091443461a68d21978325046fef77bfd0135b542f3db
 * 2c480168cc2056464643301c0918314a881800884004b4239b01cc18050c201c95f7b4f84004667d
 * b046a768060c002e1bd0c146e17d4900281cbff0a7ff0004050c414669434900e0684018391c4a46
 * 214b1a40bef028ffa07f40003f18013e681c0004050c002ee4d1009e002e4dd110480168cc205446
 * 4443134a881800190068006800282ddd64180c4be418134a134e251c2c35201c4c30291c002395f7
 * e1f86034201c291c321c0d2395f7a0f92ce0000018280003b82c0000d42c0000482d0000e0090003
 * d02c0000102d0000882c00001a2d0000ffff1f00791008088d11080864180d4ea4190d4a0d4e251c
 * 2c35201c4c30291c002395f7b3f86034201c291c321c0d2395f772f901b038bc9846a146aa46f0bc
 * 01bc0047d42c0000795308088d110808
 */

typedef struct {
    u8 unknown_00[8];
    u16 *unknown_08;
    u16 *unknown_0C;
    u16 unknown_10;
    u8 unknown_12[3];
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
    u8 unknown_18[2];
    u16 unknown_1A;
    u8 unknown_1C[2];
    u8 unknown_1E;
    u8 unknown_1F;
} List08082924;

typedef struct {
    u8 panel[0x2C];
    List08082924 list;
    u8 cursor[0x14];
    u8 settings[0x14];
} Menu08082924;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[0x16];
    s32 *count;
    Menu08082924 menu;
    const void *resource;
    u8 unknown_C4[8];
} Slot08082924;

typedef struct {
    u8 unknown_0000[0x2C88];
    Slot08082924 slots[1];
} State08082924;

typedef struct {
    u8 unknown_00[0x0E];
    u16 height;
    u8 unknown_10[0x3C];
} RenderObject08082924;

typedef void (*Callback08082924)();

extern State08082924 *data_03002818;
extern RenderObject08082924 data_030009E0[];
extern void func_08016210(void *object, const void *content, u16 first, u16 second);
extern void func_08081960(List08082924 *list);
extern u16 func_08017B50(List08082924 *list);
extern void func_080814B4(u32 slot, s16 row, List08082924 *list);
extern s32 func_08142950(s32 first, s32 second);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_08017C28(u8 *cursor, List08082924 *list, Callback08082924 callback, u8 flags);
extern void func_08017DB4(u8 *settings, List08082924 *list, Callback08082924 callback, u8 flags);
extern void func_08081078(u32 index, void *geometry);
extern void func_0808118C(u32 index, void *context);
extern void func_08085378(void);

/* An inlined copy of func_08085558 (src/08085558.c). */
static inline void inlined_08085558(List08082924 *state, u16 index)
{
    u16 rows = func_08017B50(state) * 2;
    int width = state->unknown_15;
    u16 *destination = state->unknown_08;
    u32 remaining = rows;

    while (remaining != 0) {
        index = (u16)func_08142950(index, state->unknown_17 * 2);
        func_0814186C(state->unknown_0C + width * index,
                      destination, ((u32)(width * sizeof(u16)) >> 1) & 0x001FFFFF);
        destination += state->unknown_1E;
        remaining--;
        index++;
    }
}

static inline void attach_menu(Menu08082924 *menu, Callback08082924 select,
                               Callback08082924 change)
{
    List08082924 *list = &menu->list;

    func_08017C28(menu->cursor, list, select, 0);
    func_08017DB4(menu->settings, list, change, 13);
}

void func_08082924(s32 index, u32 refresh)
{
    u16 object_id = data_03002818->slots[index].object_id;
    u16 count;
    s32 row;

    if (!refresh) {
        func_08016210(data_03002818->slots[index].menu.panel,
                      data_03002818->slots[index].resource,
                      data_030009E0[object_id].height,
                      *data_03002818->slots[index].count);
        func_08081960((List08082924 *)(index * sizeof(Slot08082924) + (u32)data_03002818 + 0x2D00));
    }

    data_03002818->slots[index].menu.list.unknown_10 |= 2;
    count = func_08017B50(&data_03002818->slots[index].menu.list);
    for (row = 0; row < count; row++)
        func_080814B4(index, row, &data_03002818->slots[index].menu.list);

    inlined_08085558(&data_03002818->slots[index].menu.list,
                     data_03002818->slots[index].menu.list.unknown_1A * 2);

    if (!refresh) {
        if (*data_03002818->slots[index].count > 0)
            attach_menu(&data_03002818->slots[index].menu, func_08081078, func_0808118C);
        else
            attach_menu(&data_03002818->slots[index].menu, func_08085378, func_0808118C);
    }
}
