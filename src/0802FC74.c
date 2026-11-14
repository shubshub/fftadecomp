#include "ffta.h"

// Complete [0x0802FC74, 0x0802FF84): 784 bytes, including the jump table
// and literal pools.

typedef struct Root0802FC74 {
    u8 unknown_0000[0x3C34];
    u16 items[0];
} Root0802FC74;

typedef struct ItemEntry0802FC74 {
    u8 unknown_00;
    u8 text;
    u8 unknown_02[14];
} ItemEntry0802FC74;

typedef struct Input0802FC74 {
    u16 unknown_00;
    u16 pressed;
    u16 repeated;
} Input0802FC74;

typedef struct Map0802FC74 Map0802FC74;

typedef struct DrawState0802FC74 {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
} DrawState0802FC74;

typedef struct Panel0802FC74 {
    u16 x;
    u16 y;
    u8 state;
    u8 unknown_05[3];
    u8 height;
    u8 unknown_09[3];
    s16 selected;
    u8 unknown_0E;
    u8 page;
    u8 unknown_10[0x834];
    u8 text_state[0xA04];
    DrawState0802FC74 draw;
} Panel0802FC74;

typedef void (*Callback0802FC74)(void);

extern Panel0802FC74 *data_0200F444;
extern Root0802FC74 g_state_02000000;
extern const ItemEntry0802FC74 g_table_08528F34[];
extern Input0802FC74 data_03000000;
extern Map0802FC74 data_030008B0;
extern Map0802FC74 data_03000990;

extern void func_0802E160(void);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_0802F4F4(void);
extern u8 func_0802E3E0(void);
extern u8 func_0802E520(void);
extern void func_08141540(u16 sound);
extern void func_08141570(s32 player, u16 sound);
extern void func_0802E070(void);
extern void func_080A9478(u16 value);
extern void func_080023D0(void *input);
extern void func_0802F35C(u8 update);
extern void func_08019A8C(void *state, u16 text, Map0802FC74 *first,
                          Map0802FC74 *second);
extern void func_08013404(Callback0802FC74 first, Callback0802FC74 second);
extern void func_0802F254(void);
extern void func_0802F268(void);
extern void func_08017FE8(const DrawState0802FC74 *state);
extern u16 func_08011860(void);

u32 func_0802FC74(void)
{
    u32 pressed;
    u32 repeated;
    u16 item;
    const ItemEntry0802FC74 *entry;
    u16 text;

    if (data_0200F444 == 0)
        return 1;

    switch (data_0200F444->state) {
    case 0:
        func_0802E160();
        func_0802A2C0(data_0200F444->x, data_0200F444->y, 0x1A,
                      data_0200F444->height * 2 + 3);
        data_0200F444->state = 3;
        break;
    case 1:
        func_0802F4F4();
        data_0200F444 = 0;
        return 1;
    case 3:
        if (func_0802E3E0())
            data_0200F444->state = 10;
        break;
    case 4:
        if (func_0802E520()) {
            func_0802A2C0(0, 0, 0, 0);
            data_0200F444->state = 1;
        }
        break;
    case 10:
        pressed = data_03000000.pressed;
        repeated = data_03000000.repeated;
        if (pressed & 3) {
            if (pressed & 1)
                func_08141540(0x64);
            else
                func_08141570(1, 0x69);
            func_0802E070();
            data_0200F444->state = 4;
            break;
        }
        if (pressed & 4) {
            item = g_state_02000000.items[data_0200F444->selected];
            if (item == 0) {
                func_08141570(1, 0x6B);
            } else {
                entry = &g_table_08528F34[item];
                if (data_0200F444->page != 0 && entry->text == 0) {
                    func_08141570(1, 0x6B);
                } else {
                    func_080A9478(2);
                    data_0200F444->state = 0x11;
                    func_08017FE8(&data_0200F444->draw);
                    break;
                }
            }
        }
        if (repeated & 0x30) {
            data_0200F444->page ^= 1;
            if (data_0200F444->page == 0)
                data_0200F444->draw.x = (data_0200F444->x - 1) * 8 + 2;
            else
                data_0200F444->draw.x = (data_0200F444->x + 11) * 8 + 6;
            func_08141540(0x6D);
        }
        if (data_0200F444->height > 1) {
            if (repeated & 0x80) {
                func_080023D0(&data_03000000);
                func_08141540(0x6D);
                if (data_0200F444->selected < data_0200F444->height - 1)
                    data_0200F444->selected++;
                else
                    data_0200F444->selected = 0;
            } else if (repeated & 0x40) {
                func_080023D0(&data_03000000);
                func_08141540(0x6D);
                if (data_0200F444->selected > 0)
                    data_0200F444->selected--;
                else
                    data_0200F444->selected = data_0200F444->height - 1;
            }
        }
        func_0802F35C(1);
        break;
    case 0x11:
        text = g_state_02000000.items[data_0200F444->selected] + 0x4B8;
        if (data_0200F444->page != 0)
            text += 0x106;
        func_08019A8C(data_0200F444->text_state, text, &data_030008B0,
                      &data_03000990);
        func_08013404(func_0802F254, func_0802F268);
        data_0200F444->state = 0x12;
        func_08017FE8(&data_0200F444->draw);
        break;
    case 0x12:
        if (data_0200F444->draw.y + data_0200F444->draw.offset_y > 0x3F)
            func_08017FE8(&data_0200F444->draw);
        if (func_08011860()) {
            func_080A9478(0);
            data_0200F444->state = 10;
        }
        break;
    }
    return 0;
}
